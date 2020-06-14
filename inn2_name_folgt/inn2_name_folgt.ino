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
Map mymap = Map::load_map2(&sprite_list);

// start position of objects
Point *start_pos = new Point(24, 56);
Point *key_pos = new Point(8, 40);
Point *computer_pos = new Point(8, 8);
Point *door_pos = new Point(16, 24);
Point *empty_bottle_pos = nullptr;
Point *disarmed_trap_pos = nullptr;
Point *green_door_pos = new Point(72, 40);

// Initialize Objects for Map
Trap *test_trap = nullptr;
Bottle *bottle = nullptr; // maybe rename to "flying_bottle"
Key *test_key = new Key(key_pos->x, key_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, 45);
Computer *test_computer = new Computer(computer_pos->x, computer_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, (int)ComputerTextureId::down_off, (int)Direction::down);
Door *red_door = new Door(door_pos->x, door_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, (int)RedDoorTextureId::left_closed, (int)Direction::left, false);
Player *test_player = new Player(start_pos->x, start_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, 60);
Enemy *enemy = new Enemy(24, 24, TEXTURE_WIDTH, TEXTURE_HEIGHT, 60, Point(64, 8));
Bottle *empty_bottle = nullptr;
Trap *disarmed_trap = nullptr;
Door *green_door = new Door(green_door_pos->x, green_door_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, (int)GreenDoorTextureId::left_closed, (int)Direction::left, true);

void setup()
{
	gb.begin();

	// append Objects to sprite_list that was given to map
	sprite_list.append_value(test_key);
	sprite_list.append_value(red_door);
	sprite_list.append_value(green_door);
	sprite_list.append_value(enemy);
	sprite_list.append_value(test_player);
	sprite_list.append_value(test_computer);

	mymap.insert_type_at(*computer_pos, TileType::computer);
	mymap.insert_type_at(*door_pos, TileType::red_door_closed);
	mymap.insert_type_at(*green_door_pos, TileType::green_door_closed);

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
	if ((abs(test_player->get_position().x - enemy->get_position().x) < 6 && abs(test_player->get_position().y - enemy->get_position().y) < 6))
	{
		//to the level builderlings : THIS IS WHERE THE LOAD FIRST MAP AGAIN LOGIC GOES!!
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
	}
	else
	{
		draw();
		// player collision detection with objects
		Point *collision_points = test_player->get_collision_points();

		mymap.insert_type_if_empty(test_player->get_position(), TileType::player);

		for (int i = 0; i < NUM_COLLISION_POINTS; i++)
		{
			// check if player is colliding with solid, computer, door or green_door
			if (mymap.is_type_at(collision_points[i], TileType::solid) || mymap.is_type_at(collision_points[i], TileType::computer) || mymap.is_type_at(collision_points[i], TileType::red_door_closed) || mymap.is_type_at(collision_points[i], TileType::green_door_closed))
			{
				// set is_colliding
				test_player->set_is_colliding(true, i);
			}

			if (mymap.is_type_at(collision_points[i], TileType::green_door_open))
			{
				gb.lights.fill(GREEN);
			}

			// check if player is colliding with a key
			if (mymap.get_tile_grid_index(collision_points[i]) == mymap.get_tile_grid_index(*key_pos))
			{
				test_player->add_item(KEY);

				// delete key from linked list
				sprite_list.delete_element(test_key);
				delete key_pos;
				key_pos = nullptr;
			}

			// check if player is colliding with a bottle
			if (mymap.get_tile_grid_index(collision_points[i]) == mymap.get_tile_grid_index(*empty_bottle_pos))
			{
				test_player->add_item(BOTTLE);

				// delete key from linked list
				sprite_list.delete_element(empty_bottle);
				delete empty_bottle_pos;
				empty_bottle_pos = nullptr;
			}

			// check if player is colliding with a disarmed trap
			if (mymap.get_tile_grid_index(collision_points[i]) == mymap.get_tile_grid_index(*disarmed_trap_pos))
			{
				test_player->add_item(TRAP);

				// delete key from linked list
				sprite_list.delete_element(disarmed_trap);
				delete disarmed_trap_pos;
				disarmed_trap_pos = nullptr;
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
			if (test_player->get_current_item() == KEY && test_player->get_current_item_count() > 0 && (mymap.is_type_at(test_player->get_interaction_point(), TileType::red_door_closed) || mymap.is_type_at(test_player->get_interaction_point(), TileType::red_door_open)))
			{
				red_door->set_is_locked(!red_door->get_is_locked());
				test_player->delete_item(KEY);
				test_player->reset_collision_points();
				mymap.insert_type_at(test_player->get_interaction_point(), mymap.is_type_at(test_player->get_interaction_point(), TileType::red_door_closed) ? TileType::red_door_open : TileType::red_door_closed);
			}

			// place trap on the current player position
			if (test_player->get_current_item() == TRAP && test_player->get_current_item_count() > 0 && (mymap.is_type_at(test_player->get_position(), TileType::not_solid) || mymap.is_type_at(test_player->get_position(), TileType::player)))
			{
				test_player->delete_item(TRAP);
				test_trap = new Trap(test_player->get_interaction_point().x / 8 * 8, test_player->get_interaction_point().y / 8 * 8, TEXTURE_WIDTH, TEXTURE_HEIGHT, (int)TrapTextureId::armed, true);

				sprite_list.push_value(test_trap);
				mymap.insert_type_at(test_player->get_position(), TileType::trap);
			}

			// interaction with the computer
			if (mymap.is_type_at(*test_computer->get_interaction_point(), TileType::player) && mymap.is_type_at(test_player->get_interaction_point(), TileType::computer))
			{
				test_computer->set_is_on(true);
				test_player->set_is_interacting(true);

				// open green door
				mymap.insert_type_at(*green_door_pos, TileType::green_door_open);
				green_door->set_is_locked(false);
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
			if (abs(bottle->get_position().x - enemy->get_position().x) < 6 && abs(bottle->get_position().y - enemy->get_position().y) < 6)
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
			if (mymap.is_type_at(bottle->get_position(), TileType::red_door_closed))
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
