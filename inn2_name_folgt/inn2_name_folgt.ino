#include <Gamebuino-Meta.h>
#include "map_factory.h"

// globals that monitor the overall game progress
Map* m;
bool gameOver = false;
bool nextLevel = false;
void draw();
void setup()
{
	gb.begin();
	m = map_factory::get_map_1();
}

void loop()
{

	// EFFECTS if player gets caught
	if (gameOver) {
		delete m;
		m = map_factory::get_map_1(); // currently loads same level again...
		gameOver = false;
	}

	// EFFECTS if the player can can escape
	if (nextLevel) {
		delete m;
		m = map_factory::get_map_1(); // currently loads same level again...
		nextLevel = false;
	}

	gb.waitForUpdate();
	gb.display.clear();
	gb.lights.clear();

	// Player movement
	if (gb.buttons.repeat(BUTTON_UP, FRAME_PERIOD))
	{
		m->test_player->move_up();
	}
	else if (gb.buttons.repeat(BUTTON_DOWN, FRAME_PERIOD))
	{
		m->test_player->move_down();
	}
	else if (gb.buttons.repeat(BUTTON_LEFT, FRAME_PERIOD))
	{
		m->test_player->move_left();
	}
	else if (gb.buttons.repeat(BUTTON_RIGHT, FRAME_PERIOD))
	{
		m->test_player->move_right();
	}

	// m->enemy movement
	if (m->line_of_sight(m->enemy->get_direction(), m->enemy->get_position(), m->test_player->get_position()))
	{
		m->enemy->set_path_grid(m->get_path_grid(m->test_player->get_position()));
	}
	else if (m->test_trap != nullptr && m->test_trap->get_is_active())
	{
		m->enemy->set_path_grid(m->get_path_grid(m->test_trap->get_position()));
	}
	else if (m->enemy->has_reached_target())
	{
		m->enemy->set_path_grid(m->get_path_grid(m->enemy->get_next_target()));
	}

	m->enemy->move();

	// m->enemy arrests player
	if ((abs(m->test_player->get_position().x - m->enemy->get_position().x) < 6 && abs(m->test_player->get_position().y - m->enemy->get_position().y) < 6))
	{
		//to the level builderlings : THIS IS WHERE THE LOAD FIRST MAP AGAIN LOGIC GOES!!
		gameOver = true;
	}

	if (m->enemy->get_position() == m->test_trap->get_position() && m->test_trap->get_is_active())
	{
		m->sprite_list.delete_element(m->test_trap);
    delete m->test_trap;
		m->test_trap = nullptr;
	}

	// debug
	if (gb.buttons.repeat(BUTTON_MENU, 0))
	{
  // tile_type_grid;
    for (int i = 0; i < 10; i++)
    {
      for (int j = 0; j < 8; j++)
      {
        gb.display.setCursor(8*i, 8*j);
        gb.display.print(m->tile_type_grid[i][j]);
      }
    }
		/*gb.display.drawImage(0, 0, my_img_buf);

		uint16_t ram = gb.getFreeRam();
		gb.display.print("RAM:");
		gb.display.println(ram);*/
	}
	else
	{
		draw();
		// player collision detection with objects
		Point *collision_points = m->test_player->get_collision_points();

		m->insert_type_if_empty(m->test_player->get_position(), TileType::player);

		for (int i = 0; i < NUM_COLLISION_POINTS; i++)
		{
			// check if player is colliding with solid, computer, door or m->green_door
			if (m->is_type_at(collision_points[i], TileType::solid) || m->is_type_at(collision_points[i], TileType::computer) || m->is_type_at(collision_points[i], TileType::red_door_closed) || m->is_type_at(collision_points[i], TileType::green_door_closed))
			{
				// set is_colliding
				m->test_player->set_is_colliding(true, i);
			}

			if (m->is_type_at(collision_points[i], TileType::green_door_open))
			{
				nextLevel = true;
			}

			// check if player is colliding with a key
			if (m->get_tile_grid_index(collision_points[i]) == m->get_tile_grid_index(*m->key_pos))
			{
				m->test_player->add_item(KEY);

				// delete key from linked list
				m->sprite_list.delete_element(m->test_key);
        delete m->test_key;
				delete m->key_pos;
				m->key_pos = nullptr;
			}

			// check if player is colliding with a m->bottle
			if (m->get_tile_grid_index(collision_points[i]) == m->get_tile_grid_index(*m->empty_bottle_pos))
			{
				m->test_player->add_item(BOTTLE);

				// delete key from linked list
				m->sprite_list.delete_element(m->empty_bottle);
        delete m->empty_bottle;
				delete m->empty_bottle_pos;
				m->empty_bottle_pos = nullptr;
			}

			// check if player is colliding with a disarmed trap
			if (m->get_tile_grid_index(collision_points[i]) == m->get_tile_grid_index(*m->disarmed_trap_pos))
			{
				m->test_player->add_item(TRAP);

				// delete key from linked list
				m->sprite_list.delete_element(m->disarmed_trap);
				delete m->disarmed_trap_pos;
        delete m->disarmed_trap;
				m->disarmed_trap_pos = nullptr;
			}
		}

		// check if player is in range of the computer
		if (m->is_type_at(*m->test_computer->get_interaction_point(), TileType::player) && m->is_type_at(m->test_player->get_interaction_point(), TileType::computer))
		{
			m->test_player->set_is_colliding(true);
		}
		else
		{
			m->test_computer->set_is_on(m->test_player->get_is_interacting());
		}

		if (gb.buttons.pressed(BUTTON_A))
		{
			// check if the player can interact with a door (open, close)
			if (m->test_player->get_current_item() == KEY && m->test_player->get_current_item_count() > 0 && (m->is_type_at(m->test_player->get_interaction_point(), TileType::red_door_closed) || m->is_type_at(m->test_player->get_interaction_point(), TileType::red_door_open)))
			{
				m->red_door->set_is_locked(!m->red_door->get_is_locked());
				m->test_player->delete_item(KEY);
				m->test_player->reset_collision_points();
				m->insert_type_at(m->test_player->get_interaction_point(), m->is_type_at(m->test_player->get_interaction_point(), TileType::red_door_closed) ? TileType::red_door_open : TileType::red_door_closed);
			}

			// place trap on the current player position
			if (m->test_player->get_current_item() == TRAP && m->test_player->get_current_item_count() > 0 && (m->is_type_at(m->test_player->get_position(), TileType::not_solid) || m->is_type_at(m->test_player->get_position(), TileType::player)))
			{
				m->test_player->delete_item(TRAP);
				m->test_trap = new Trap(m->test_player->get_interaction_point().x / 8 * 8, m->test_player->get_interaction_point().y / 8 * 8, TEXTURE_WIDTH, TEXTURE_HEIGHT, (int)TrapTextureId::armed, true);

				m->sprite_list.push_value(m->test_trap);
				m->insert_type_at(m->test_player->get_position(), TileType::trap);
			}

			// interaction with the computer
			if (m->is_type_at(*m->test_computer->get_interaction_point(), TileType::player) && m->is_type_at(m->test_player->get_interaction_point(), TileType::computer))
			{
				m->test_computer->set_is_on(true);
				m->test_player->set_is_interacting(true);

				// open green door
				m->insert_type_at(*m->green_door_pos, TileType::green_door_open);
				m->green_door->set_is_locked(false);
			}

			// throw m->bottle
			if (m->test_player->get_current_item() == BOTTLE && m->test_player->get_current_item_count() > 0 && m->bottle == nullptr)
			{
				m->test_player->delete_item(BOTTLE);

				m->bottle = new Bottle(m->test_player->get_interaction_point().x, m->test_player->get_interaction_point().y, BOTTLE_WIDTH, BOTTLE_HEIGHT, (int)BottleTextureId::not_broken, m->test_player->get_direction());

				m->sprite_list.push_value(m->bottle);
			}
		}

		// m->bottle movement
		if (m->bottle != nullptr)
		{
			// m->bottle colliding with m->enemy
			if (abs(m->bottle->get_position().x - m->enemy->get_position().x) < 6 && abs(m->bottle->get_position().y - m->enemy->get_position().y) < 6)
			{
				m->enemy->set_stunned();
				gb.lights.fill(PURPLE);
				m->bottle->set_is_colliding(true);
			}

			// m->bottle colliding with solid
			if (m->is_type_at(m->bottle->get_position(), TileType::solid))
			{
				m->bottle->set_is_colliding(true);
			}

			// m->bottle colliding with closed_door
			if (m->is_type_at(m->bottle->get_position(), TileType::red_door_closed))
			{
				m->bottle->set_is_colliding(true);
			}

			// if m->bottle is colliding with something, delete it
			if (m->bottle->get_is_colliding())
			{
				m->sprite_list.delete_element(m->bottle);
				delete m->bottle;
				m->bottle = nullptr;
			}
			else
			{
				m->bottle->get_next_point();
			}
		}

		// get next item
		if (gb.buttons.pressed(BUTTON_B))
		{
			m->test_player->next_item();
		}

		m->test_player->print_current_item();

		m->delete_type_at(m->test_player->get_position(), TileType::player);
		delete [] collision_points;
		collision_points = nullptr;

		if (!gb.buttons.repeat(BUTTON_UP, FRAME_PERIOD) && !gb.buttons.repeat(BUTTON_RIGHT, FRAME_PERIOD) && !gb.buttons.repeat(BUTTON_LEFT, FRAME_PERIOD) && !gb.buttons.repeat(BUTTON_DOWN, FRAME_PERIOD) && !m->test_player->get_is_interacting())
		{
			m->test_player->idle();
		}
	}
}

void draw()
{
  auto it = m->sprite_list.get_Iterator();
  while (it.has_next())
  {
    Sprite **temp = it.get_next();
    (*temp)->draw();
  }
}
