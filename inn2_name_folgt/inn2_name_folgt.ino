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

//WonderWall *ww = new WonderWall(35, 30, 8, 8, 23);

// start position of the player
Point *start_pos = new Point(35, 30);
Point *key_pos = new Point(35, 40);
Point *computer_pos = new Point(50, 25);
Point *door_pos = new Point(50, 20);

Enemy *enemy = new Enemy(40, 8, 8, 8, 60, Point(64,48));
Player *player = new Player(start_pos->x, start_pos->y, 8, 8, 60);
Key *test_key = new Key(key_pos->x, key_pos->y, 8, 8, 44);
Computer *test_computer = new Computer(computer_pos->x, computer_pos->y, 8, 8, 30);
Door *test_door = new Door(door_pos->x, door_pos->y, 8, 8, 48);

Map mymap = Map::load_map1(&sprite_list);

void setup()
{
	gb.begin();
	sprite_list.append_value((Sprite *)player);
	sprite_list.append_value((Sprite *)enemy);
  sprite_list.append_value((Sprite *)test_key);
	sprite_list.append_value((Sprite *)test_computer);
	sprite_list.append_value((Sprite *)test_door);

	mymap.insert_type_at(*key_pos, TileType::key);
	mymap.insert_type_at(*computer_pos, TileType::computer);
	mymap.insert_type_at(*door_pos, TileType::door);
}

void loop()
{
  gb.waitForUpdate();
  gb.display.clear();
  
	if (gb.buttons.repeat(BUTTON_UP, FRAME_PERIOD))
	{
		player->move_up();
	}
	else if (gb.buttons.repeat(BUTTON_DOWN, FRAME_PERIOD))
	{
		player->move_down();
	}
	else if (gb.buttons.repeat(BUTTON_LEFT, FRAME_PERIOD))
	{
		player->move_left();
	}
	else if (gb.buttons.repeat(BUTTON_RIGHT, FRAME_PERIOD))
	{
		player->move_right();
	}

  enemy->move();
	if (gb.buttons.repeat(BUTTON_B, 0))
	{
		gb.display.drawImage(0, 0, my_img_buf);
		uint16_t ram = gb.getFreeRam();
		gb.display.print("RAM:");
		gb.display.println(ram);
	}
	else
	{	
    draw();

		// player collision detection with 'solid' objects
		Point *collision_points = player->get_collision_points();
		for (int i = 0; i < NUM_COLLISION_POINTS; i++)
		{
			// check if player is colliding with something
			if (mymap.is_type_at(collision_points[i], TileType::solid))
			{
        // set is_colliding
				player->set_is_colliding(true, i);
			}

			if (mymap.is_type_at(collision_points[i], TileType::key))
			{
				mymap.delete_type_at(*key_pos, &sprite_list, 39);
			}

			if (mymap.is_type_at(collision_points[i], TileType::computer))
			{
				mymap.delete_type_at(*computer_pos, &sprite_list, 40);
			}

			if (mymap.is_type_at(collision_points[i], TileType::door))
			{
				mymap.delete_type_at(*door_pos, &sprite_list, 41);
			}
		}

  	delete collision_points;
  	collision_points = nullptr;
	
	  if(!gb.buttons.repeat(BUTTON_UP, FRAME_PERIOD)
        && !gb.buttons.repeat(BUTTON_RIGHT, FRAME_PERIOD)
        && !gb.buttons.repeat(BUTTON_LEFT, FRAME_PERIOD)
        && !gb.buttons.repeat(BUTTON_DOWN, FRAME_PERIOD))
    {
      player->idle();
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
