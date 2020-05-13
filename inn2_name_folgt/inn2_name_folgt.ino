#include <Gamebuino-Meta.h>

#include "texture.cpp"
#include "sprite.cpp"
//#include "wonder_wall.cpp"
#include "linked_list.cpp"
#include "map.cpp"
#include "player.h"
#include "enemy.h"
#include "computer.h"
#include "door.h"
#include "key.h"
#include "trap.h"

#define FRAME_PERIOD 2

LinkedList<Sprite *> sprite_list = LinkedList<Sprite *>();

// start position of all objects
Point *start_pos = new Point(35, 30);
Point *key_pos = new Point(35, 40);
Point *computer_pos = new Point(8, 8);
Point *door_pos = new Point(24, 24);

Enemy *enemy = new Enemy(40, 8, 8, 8, 60, Point(64, 48));

Key *test_key = new Key(key_pos->x, key_pos->y, 8, 8, 44);
Computer *test_computer = new Computer(computer_pos->x, computer_pos->y, 8, 8, 30, 1);
Door *test_door = new Door(door_pos->x, door_pos->y, 8, 8, 48);

Player *test_player = new Player(start_pos->x, start_pos->y, 8, 8, 60);

Map mymap = Map::load_map1(&sprite_list);
uint8_t *path_test = NULL;

void setup()
{
	gb.begin();
	sprite_list.append_value((Sprite *)enemy);				 // linked list index = 37
	sprite_list.append_value((Sprite *)test_key);			 // linked list index = 38
	sprite_list.append_value((Sprite *)test_door);		 // linked list index = 39
	sprite_list.append_value((Sprite *)test_player);	 // linked list index = 40
	sprite_list.append_value((Sprite *)test_computer); // linked list index = 41

	mymap.insert_type_at(*key_pos, TileType::key);
	mymap.insert_type_at(*computer_pos, TileType::computer);
	mymap.insert_type_at(*door_pos, TileType::door);
	path_test = mymap.get_path_grid(Point(20, 10));
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

	enemy->move();
	if (gb.buttons.repeat(BUTTON_B, 0))
	{
		gb.display.drawImage(0, 0, my_img_buf);
		uint16_t ram = gb.getFreeRam();
		gb.display.print("RAM:");
		gb.display.println(ram);
		/* // path test
    for (int i = 0; i < 80; i++)
    {
      gb.display.setCursor(8*(i%10), 8*(i/10));
      gb.display.print(path_test[i]);
    }*/
	}
	else
	{
		draw();
		// player collision detection with 'solid' objects
		Point *collision_points = test_player->get_collision_points();

		mymap.insert_type_if_empty(test_player->get_position(), TileType::player);

		for (int i = 0; i < NUM_COLLISION_POINTS; i++)
		{
			// check if player is colliding with something
			if (mymap.is_type_at(collision_points[i], TileType::solid))
			{
				// set is_colliding
				test_player->set_is_colliding(true, i);
			}

			if (mymap.is_type_at(collision_points[i], TileType::key))
			{
				test_player->set_has_key(true);

				// delete key from the linked list
				mymap.delete_type_at(*key_pos, &sprite_list, 38);
			}

			if (mymap.is_type_at(collision_points[i], TileType::computer))
			{
				test_player->set_is_colliding(true, i);
			}

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

			// check if the player can interact with a door
			if (mymap.is_type_at(collision_points[i], TileType::door))
			{
				if (test_door->get_is_locked())
				{
					test_player->set_is_colliding(true, i);

					if (gb.buttons.pressed(BUTTON_A) && test_player->get_has_key())
					{
						test_door->set_is_locked(false);
						test_player->reset_collision_points();
					}
				}
				else
				{
					if (gb.buttons.pressed(BUTTON_A) && test_player->get_has_key())
					{
						test_door->set_is_locked(true);
					}
				}
			}
		}

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
