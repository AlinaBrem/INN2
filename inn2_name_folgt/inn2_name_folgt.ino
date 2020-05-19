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
#include "bottle.h"

#define FRAME_PERIOD 2
#define TEXTURE_WIDTH 8
#define TEXTURE_HEIGHT 8
#define BOTTLE_WIDTH 4
#define BOTTLE_HEIGHT 4

LinkedList<Sprite *> sprite_list = LinkedList<Sprite *>();

// start position of all objects
//Point *start_pos = new Point(35, 30);
Point *start_pos = new Point(64, 48);
Point *key_pos = new Point(32, 40);
Point *computer_pos = new Point(8, 8);
Point *door_pos = new Point(24, 24);

Trap *test_trap = nullptr;
Bottle *bottle = nullptr;
Key *test_key = new Key(key_pos->x, key_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, 44);
Computer *test_computer = new Computer(computer_pos->x, computer_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, 30, 1);
Door *test_door = new Door(door_pos->x, door_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, 48);

Player *test_player = new Player(start_pos->x, start_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, 60);

Map mymap = Map::load_map1(&sprite_list);

Enemy *enemy = new Enemy(32, 16, TEXTURE_WIDTH, TEXTURE_HEIGHT, 60, Point(32, 32));

//uint8_t *path_test = NULL;

void setup()
{
	gb.begin();
	sprite_list.append_value(test_key);
	sprite_list.append_value(test_door);
	sprite_list.append_value(enemy);
	sprite_list.append_value(test_player);
	sprite_list.append_value(test_computer);

	mymap.insert_type_at(*computer_pos, TileType::computer);
	mymap.insert_type_at(*door_pos, TileType::door);

	enemy->set_path_grid(mymap.get_path_grid(enemy->get_next_target()));
	//path_test = mymap.get_path_grid(Point(8, 40));
}

void loop()
{
	gb.waitForUpdate();
	gb.display.clear();
  gb.lights.clear();

	// Player movement
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

	// enemy movement
	if (mymap.line_of_sight(enemy->get_direction(), enemy->get_position(), test_player->get_position()))
	{
		enemy->set_path_grid(mymap.get_path_grid(test_player->get_position()));
	}
	else if (test_trap != nullptr && test_trap->get_is_active())
	{
		enemy->set_path_grid(mymap.get_path_grid(test_trap->get_position()));
	}
	else if (enemy->has_reached_target())
	{
		enemy->set_path_grid(mymap.get_path_grid(enemy->get_next_target()));
	}

	enemy->move();

  // enemy arrests player
  if ((abs(test_player->get_position().x - enemy->get_position().x) < 6 &&  abs(test_player->get_position().y - enemy->get_position().y) < 6))
  {
    gb.lights.fill(RED);
  }

	if (enemy->get_position() == test_trap->get_position() && test_trap->get_is_active())
	{
		sprite_list.delete_element(test_trap);
		test_trap = nullptr;
	}

	// debug
	if (gb.buttons.repeat(BUTTON_MENU, 0))
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
			if (mymap.get_tile_grid_index(collision_points[i]) == mymap.get_tile_grid_index(*key_pos))
			{
				test_player->add_item(KEY);

				// delete key from linked list
				sprite_list.delete_element(test_key);
				delete key_pos;
				key_pos = nullptr;
			}
		}

		// check if player is in range of the computer
		if (mymap.is_type_at(*test_computer->get_interaction_point(), TileType::player) && mymap.is_type_at(test_player->get_interaction_point(), TileType::computer))
		{
			test_player->set_is_colliding(true);
		}
		else
		{
			test_computer->set_is_on(test_player->get_is_interacting());
		}

		if (gb.buttons.pressed(BUTTON_A))
		{
			// check if the player can interact with a door (open, close)
			if (test_player->get_current_item() == KEY && mymap.is_type_at(test_player->get_interaction_point(), TileType::door))
			{
				test_door->set_is_locked(!test_door->get_is_locked());
				test_player->reset_collision_points();
			}

			// place trap on the current player position
			if (test_player->get_current_item() == TRAP && test_player->get_current_item_count() > 0 && (mymap.is_type_at(test_player->get_position(), TileType::not_solid) || mymap.is_type_at(test_player->get_position(), TileType::player)))
			{
				test_player->delete_item(TRAP);
				test_trap = new Trap(test_player->get_interaction_point().x / 8 * 8, test_player->get_interaction_point().y / 8 * 8, TEXTURE_WIDTH, TEXTURE_HEIGHT, 35, true);

				sprite_list.push_value(test_trap);
				mymap.insert_type_at(test_player->get_position(), TileType::trap);
			}

			// interaction with the computer
			if (mymap.is_type_at(*test_computer->get_interaction_point(), TileType::player) && mymap.is_type_at(test_player->get_interaction_point(), TileType::computer))
			{
				test_computer->set_is_on(true);
				test_player->set_is_interacting(true);
			}

			// throw bottle
			if (test_player->get_current_item() == BOTTLE && test_player->get_current_item_count() > 0 && bottle == nullptr)
			{
				test_player->delete_item(BOTTLE);

				bottle = new Bottle(test_player->get_interaction_point().x, test_player->get_interaction_point().y, BOTTLE_WIDTH, BOTTLE_HEIGHT, (int)BottleTextureId::not_broken, test_player->get_direction());

				sprite_list.push_value(bottle);
			}
		}

		// bottle movement
		if (bottle != nullptr)
		{
			// bottle colliding with enemy
			if (abs(bottle->get_position().x - enemy->get_position().x) < 6 &&  abs(bottle->get_position().y - enemy->get_position().y) < 6)
			{
        enemy->set_stunned();
        gb.lights.fill(PURPLE);
				bottle->set_is_colliding(true);
			}

			// bottle colliding with solid
			if (mymap.is_type_at(bottle->get_position(), TileType::solid))
			{
				bottle->set_is_colliding(true);
			}

			// bottle colliding with closed_door
			if (mymap.is_type_at(bottle->get_position(), TileType::door) && test_door->get_is_locked())
			{
				bottle->set_is_colliding(true);
			}

			// if bottle is colliding with something, delete it
			if (bottle->get_is_colliding())
			{
				sprite_list.delete_element(bottle);
				delete bottle;
				bottle = nullptr;
			}
			else
			{
				bottle->get_next_point();
			}
		}

		// get next item
		if (gb.buttons.pressed(BUTTON_B))
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
