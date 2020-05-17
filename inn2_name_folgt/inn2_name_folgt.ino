#include <Gamebuino-Meta.h>

#include "texture.cpp"
#include "sprite.cpp"
#include "linked_list.cpp"
#include "map.cpp"
#include "player.h"
#include "enemy.h"
#include "computer.h"
#include "door.h"
#include "key.h"
#include "trap.h"
#include "enum.h"

#define FRAME_PERIOD 2

LinkedList<Sprite *> sprite_list = LinkedList<Sprite *>();

// start position of all objects
//Point *start_pos = new Point(35, 30);
Point *start_pos = new Point(64, 48);
Point *key_pos = new Point(32, 40);
Point *computer_pos = new Point(8, 8);
Point *door_pos = new Point(24, 24);

Key *test_key = new Key(key_pos->x, key_pos->y, 8, 8, 44);
Computer *test_computer = new Computer(computer_pos->x, computer_pos->y, 8, 8, 30, 1);
Door *test_door = new Door(door_pos->x, door_pos->y, 8, 8, 48);

Player *test_player = new Player(start_pos->x, start_pos->y, 8, 8, 60);

Map mymap = Map::load_map1(&sprite_list);

Enemy *enemy = new Enemy(32, 8, 8, 8, 60, Point(8, 40));

uint8_t *path_test = NULL;

void setup()
{
	gb.begin();
	sprite_list.append_value(enemy);				 
	sprite_list.append_value(test_key);			 
	sprite_list.append_value(test_door);		 
	sprite_list.append_value(test_player);	 
	sprite_list.append_value(test_computer);

	mymap.insert_type_at(*key_pos, TileType::key);
	mymap.insert_type_at(*computer_pos, TileType::computer);
	mymap.insert_type_at(*door_pos, TileType::door);

	enemy->set_path_grid(mymap.get_path_grid(enemy->get_next_target()));
	path_test = mymap.get_path_grid(Point(8, 40));
}

void loop()
{
	gb.waitForUpdate();
	gb.display.clear();

	if (gb.buttons.repeat(BUTTON_UP, FRAME_PERIOD))
	{
		test_player->move_up();
	}
	else if (gb.buttons.repeat(BUTTON_DOWN, FRAME_PERIOD))
	{
		test_player->move_down();
	}
	else if (gb.buttons.repeat(BUTTON_LEFT, FRAME_PERIOD))
	{
		test_player->move_left();
	}
	else if (gb.buttons.repeat(BUTTON_RIGHT, FRAME_PERIOD))
	{
		test_player->move_right();
	}

  if (mymap.line_of_sight(enemy->get_direction(), enemy->get_position(), test_player->get_position()))
  {
    path_test = mymap.get_path_grid(test_player->get_position());
    enemy->set_path_grid(path_test);
  }
	enemy->move();
	if (enemy->has_reached_target())
	{
    path_test = mymap.get_path_grid(enemy->get_next_target());
		enemy->set_path_grid(path_test);
	}
	if (gb.buttons.repeat(BUTTON_HOME, 0))
	{
		gb.display.drawImage(0, 0, my_img_buf);
		uint16_t ram = gb.getFreeRam();
		gb.display.print("RAM:");
		gb.display.println(ram);
		/*// path test
    for (int i = 0; i < 80; i++)
    {
      gb.display.setCursor(8*(i%10), 8*(i/10));
      gb.display.print(path_test[i]);
    }*/
		/*// tile_type_grid;
    for (int i = 0; i < 10; i++)
    {
      for (int j = 0; j < 8; j++)
      {
        gb.display.setCursor(8*i, 8*j);
        gb.display.print(mymap.tile_type_grid[i][j]);
      }
    }*/
	}
	else
	{
		draw();
		// player collision detection with objects
		Point *collision_points = test_player->get_collision_points();

		mymap.insert_type_if_empty(test_player->get_position(), TileType::player);

		for (int i = 0; i < NUM_COLLISION_POINTS; i++)
		{
			// check if player is colliding with solid, computer or door
			if (mymap.is_type_at(collision_points[i], TileType::solid) || mymap.is_type_at(collision_points[i], TileType::computer) || mymap.is_type_at(collision_points[i], TileType::door) && test_door->get_is_locked())
			{
				// set is_colliding
				test_player->set_is_colliding(true, i);
			}

			// check if player is colliding with the key
			if (mymap.is_type_at(collision_points[i], TileType::key))
			{
				 test_player->add_item(KEY);

				// delete key from tiletypegrid 
				mymap.delete_type_at(*key_pos, TileType::key);
        //delete key from linked list
        sprite_list.delete_element(test_key);
			}
		}

		// check if player is in range of the computer
		if (mymap.is_type_at(*test_computer->get_interaction_point(), TileType::player) && mymap.is_type_at(test_player->get_interaction_point(), TileType::computer))
		{
			test_player->set_is_colliding(true);

			if (gb.buttons.pressed(BUTTON_A))
			{
				test_computer->set_is_on(true);
				test_player->set_is_interacting(true);
			}
		}
		else
		{
			test_computer->set_is_on(test_player->get_is_interacting());
		}

		// check if the player can interact with a door (open, close)
		if (mymap.is_type_at(test_player->get_interaction_point(), TileType::door))
		{
			if (test_player->get_current_item() == KEY)
			{
				if (gb.buttons.pressed(BUTTON_A))
				{
					test_door->set_is_locked(!test_door->get_is_locked());
					test_player->reset_collision_points();
				}
			}
		}

		// place trap on the current player position
		if (gb.buttons.pressed(BUTTON_B) && test_player->get_current_item() == TRAP && (mymap.is_type_at(test_player->get_position(), TileType::not_solid) || mymap.is_type_at(test_player->get_position(), TileType::player)))
		{
			test_player->set_trap_count(-1);
			Trap *test_trap = new Trap(test_player->get_position().x, test_player->get_position().y, 8, 8, 35);

			sprite_list.push_value(test_trap);
			mymap.insert_type_at(test_player->get_position(), TileType::trap);
		}

		if (gb.buttons.pressed(BUTTON_MENU))
		{
			test_player->next_item();
		}

		test_player->print_current_item();

		mymap.delete_type_at(test_player->get_position(), TileType::player);
		delete collision_points;
		collision_points = nullptr;

		if (!gb.buttons.repeat(BUTTON_UP, FRAME_PERIOD) && !gb.buttons.repeat(BUTTON_RIGHT, FRAME_PERIOD) && !gb.buttons.repeat(BUTTON_LEFT, FRAME_PERIOD) && !gb.buttons.repeat(BUTTON_DOWN, FRAME_PERIOD) && !test_player->get_is_interacting())
		{
			test_player->idle();
		}
	}
}

void draw()
{
	auto it = sprite_list.get_Iterator();
	while (it.has_next())
	{
		Sprite **temp = it.get_next();
		(*temp)->draw();
	}
}
