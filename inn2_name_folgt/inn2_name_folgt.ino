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
#include "teleporter.h"

#define FRAME_PERIOD 2
#define TEXTURE_WIDTH 8
#define TEXTURE_HEIGHT 8
#define BOTTLE_WIDTH 4
#define BOTTLE_HEIGHT 4

LinkedList<Sprite *> current_sprite_list;
LinkedList<Sprite *> sprite_list1 = LinkedList<Sprite *>();
LinkedList<Sprite *> sprite_list2 = LinkedList<Sprite *>();

// start position of all objects
//Point *start_pos = new Point(35, 30);
Point *start_pos = new Point(64, 48);
Point *key_pos = new Point(32, 40);
Point *current_key_pos = key_pos;
Point *computer_pos = new Point(8, 8);
Point *door_pos = new Point(24, 24);

Trap *test_trap = nullptr;
Bottle *bottle = nullptr;
Key *test_key = new Key(key_pos->x, key_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, 44);
Computer *test_computer = new Computer(computer_pos->x, computer_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, 30, 1);
Door *test_door = new Door(door_pos->x, door_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, 48);

Player *test_player = new Player(start_pos->x, start_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, 60);

Map *current_map = nullptr;
Map *map1 = Map::load_map1(&sprite_list1);
Map *map2 = Map::load_map2(&sprite_list2);

Enemy *current_enemy = nullptr;
Enemy *enemy1 = new Enemy(32, 16, TEXTURE_WIDTH, TEXTURE_HEIGHT, 60, Point(32, 32));
//uint8_t *path_test = NULL;

LinkedList<Teleporter *> current_teleporter_list;
LinkedList<Teleporter *> teleporter_list1;
LinkedList<Teleporter *> teleporter_list2;
Teleporter *tele1 = new Teleporter(64, 8, TEXTURE_WIDTH, TEXTURE_HEIGHT, 34);

void tele1_function()
{
	current_sprite_list = sprite_list2;
	current_map = map2;
	current_teleporter_list = teleporter_list2;
	test_player->set_position(40, 40);
}

void setup()
{
	gb.begin();
	sprite_list1.append_value(test_key);
	sprite_list1.append_value(test_door);
	sprite_list1.append_value(enemy1);
	sprite_list1.append_value(test_player);
	sprite_list1.append_value(test_computer);
	sprite_list1.append_value(tele1);

	sprite_list2.append_value(test_player);
	current_sprite_list = sprite_list1;

	map1->insert_type_at(*computer_pos, TileType::computer);
	map1->insert_type_at(*door_pos, TileType::door_closed);
	current_map = map1;

	enemy1->set_path_grid(map1->get_path_grid(enemy1->get_next_target()));
	current_enemy = enemy1;

	tele1->setTeleportFunction(tele1_function);

	teleporter_list1.append_value(tele1);
	current_teleporter_list = teleporter_list1;
	//path_test = current_map->get_path_grid(Point(8, 40));
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

	// current_enemy movement
	if (current_map->line_of_sight(current_enemy->get_direction(), current_enemy->get_position(), test_player->get_position()))
	{
		current_enemy->set_path_grid(current_map->get_path_grid(test_player->get_position()));
	}
	else if (test_trap != nullptr && test_trap->get_is_active())
	{
		current_enemy->set_path_grid(current_map->get_path_grid(test_trap->get_position()));
	}
	else if (current_enemy->has_reached_target())
	{
		current_enemy->set_path_grid(current_map->get_path_grid(current_enemy->get_next_target()));
	}

	current_enemy->move();

	// current_enemy arrests player
	if ((abs(test_player->get_position().x - current_enemy->get_position().x) < 6 && abs(test_player->get_position().y - current_enemy->get_position().y) < 6))
	{
		//to the level builderlings : THIS IS WHERE THE LOAD FIRST MAP AGAIN LOGIC GOES!!
		gb.lights.fill(RED);
	}

	if (current_enemy->get_position() == test_trap->get_position() && test_trap->get_is_active())
	{
		current_sprite_list.delete_element(test_trap);
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
        gb.display.print(current_map->tile_type_grid[i][j]);
      }
    }*/
	}
	else
	{
		draw();
		// player collision detection with objects
		Point *collision_points = test_player->get_collision_points();

		current_map->insert_type_if_empty(test_player->get_position(), TileType::player);

		for (int i = 0; i < NUM_COLLISION_POINTS; i++)
		{
			// check if player is colliding with solid, computer or door
			if (current_map->is_type_at(collision_points[i], TileType::solid) || current_map->is_type_at(collision_points[i], TileType::computer) || current_map->is_type_at(collision_points[i], TileType::door_closed))
			{
				// set is_colliding
				test_player->set_is_colliding(true, i);
			}

			// check if player is colliding with the key
			if (current_map->get_tile_grid_index(collision_points[i]) == current_map->get_tile_grid_index(*current_key_pos))
			{
				test_player->add_item(KEY);

				// delete key from linked list
				current_sprite_list.delete_element(test_key);
				delete current_key_pos;
				current_key_pos = nullptr;
			}

			auto it = current_teleporter_list.get_Iterator();
			while (it.has_next())
			{
				Teleporter **temp = it.get_next();

				if (current_map->get_tile_grid_index(collision_points[i]) == current_map->get_tile_grid_index((*temp)->get_position()))
				{
					(*temp)->teleport();
					gb.lights.fill(RED);
				}
			}
		}

		// check if player is in range of the computer
		if (current_map->is_type_at(*test_computer->get_interaction_point(), TileType::player) && current_map->is_type_at(test_player->get_interaction_point(), TileType::computer))
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
			if (test_player->get_current_item() == KEY && (current_map->is_type_at(test_player->get_interaction_point(), TileType::door_closed) || current_map->is_type_at(test_player->get_interaction_point(), TileType::door_open)))
			{
				test_door->set_is_locked(!test_door->get_is_locked());
				test_player->reset_collision_points();
				current_map->insert_type_at(test_player->get_interaction_point(), current_map->is_type_at(test_player->get_interaction_point(), TileType::door_closed) ? TileType::door_open : TileType::door_closed);
			}

			// place trap on the current player position
			if (test_player->get_current_item() == TRAP && test_player->get_current_item_count() > 0 && (current_map->is_type_at(test_player->get_position(), TileType::not_solid) || current_map->is_type_at(test_player->get_position(), TileType::player)))
			{
				test_player->delete_item(TRAP);
				test_trap = new Trap(test_player->get_interaction_point().x / 8 * 8, test_player->get_interaction_point().y / 8 * 8, TEXTURE_WIDTH, TEXTURE_HEIGHT, 52, true);

				current_sprite_list.push_value(test_trap);
				current_map->insert_type_at(test_player->get_position(), TileType::trap);
			}

			// interaction with the computer
			if (current_map->is_type_at(*test_computer->get_interaction_point(), TileType::player) && current_map->is_type_at(test_player->get_interaction_point(), TileType::computer))
			{
				test_computer->set_is_on(true);
				test_player->set_is_interacting(true);
			}

			// throw bottle
			if (test_player->get_current_item() == BOTTLE && test_player->get_current_item_count() > 0 && bottle == nullptr)
			{
				test_player->delete_item(BOTTLE);

				bottle = new Bottle(test_player->get_interaction_point().x, test_player->get_interaction_point().y, BOTTLE_WIDTH, BOTTLE_HEIGHT, (int)BottleTextureId::not_broken, test_player->get_direction());

				current_sprite_list.push_value(bottle);
			}
		}

		// bottle movement
		if (bottle != nullptr)
		{
			// bottle colliding with current_enemy
			if (abs(bottle->get_position().x - current_enemy->get_position().x) < 6 && abs(bottle->get_position().y - current_enemy->get_position().y) < 6)
			{
				current_enemy->set_stunned();
				gb.lights.fill(PURPLE);
				bottle->set_is_colliding(true);
			}

			// bottle colliding with solid
			if (current_map->is_type_at(bottle->get_position(), TileType::solid))
			{
				bottle->set_is_colliding(true);
			}

			// bottle colliding with closed_door
			if (current_map->is_type_at(bottle->get_position(), TileType::door_closed))
			{
				bottle->set_is_colliding(true);
			}

			// if bottle is colliding with something, delete it
			if (bottle->get_is_colliding())
			{
				current_sprite_list.delete_element(bottle);
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

		current_map->delete_type_at(test_player->get_position(), TileType::player);
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
	auto it = current_sprite_list.get_Iterator();
	while (it.has_next())
	{
		Sprite **temp = it.get_next();
		(*temp)->draw();
	}
}
