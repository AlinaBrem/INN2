#include <Gamebuino-Meta.h>

#include "texture.cpp"
#include "sprite.cpp"
//#include "wonder_wall.cpp"
#include "linked_list.cpp"
#include "map.cpp"
#include "player.h"

#define FRAME_PERIOD 2

LinkedList<Sprite *> sprite_list = LinkedList<Sprite *>();

//WonderWall *ww = new WonderWall(35, 30, 8, 8, 23);

// start position of the player
Point *start_pos = new Point(35, 30);

Player *player = new Player(start_pos->x, start_pos->y, 8, 7, 60);

Map mymap = Map::load_map1(&sprite_list);

void setup()
{
	gb.begin();
	sprite_list.append_value((Sprite *)player);
}

void loop()
{
	while (!gb.update())
		gb.display.clear(/*RED*/);

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

		// player collision detection
		Point *collision_points = player->get_collision_points();
		for (int i = 0; i < NUM_COLLISION_POINTS; i++)
		{
			// check if player is colliding with something
			if (mymap.solid_at_position(collision_points[i]))
			{
        // set is_colliding
				player->set_is_colliding(true, i);
			}
		}

  	delete collision_points;
  	collision_points = nullptr;
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
