#include "map_factory.h"

Map* map_factory::get_map_1() {
  Map* map = new Map();

  map->start_pos = new Point(24, 56);
  map->key_pos = new Point(8, 40);
  map->computer_pos = new Point(8, 8);
  map->door_pos = new Point(16, 24);
  map->empty_bottle_pos = nullptr;
  map->disarmed_trap_pos = nullptr;
  map->green_door_pos = new Point(72, 40);

  map->test_trap = nullptr;
  map->bottle = nullptr; // maybe rename to "flying_bottle"
  map->test_key = new Key(map->key_pos->x, map->key_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, 45);
  map->test_computer = new Computer(map->computer_pos->x, map->computer_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, (int)ComputerTextureId::down_off, (int)Direction::down);
  map->red_door = new Door(map->door_pos->x, map->door_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, (int)RedDoorTextureId::left_closed, (int)Direction::left, false);
  map->test_player = new Player(map->start_pos->x, map->start_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, 60);
  map->enemy = new Enemy(24, 24, TEXTURE_WIDTH, TEXTURE_HEIGHT, 80, Point(64, 8));
  map->empty_bottle = nullptr;
  map->disarmed_trap = nullptr;
  map->green_door = new Door(map->green_door_pos->x, map->green_door_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, (int)GreenDoorTextureId::left_closed, (int)Direction::left, true);

  map->sprite_list.append_value(map->test_key);
	map->sprite_list.append_value(map->red_door);
	map->sprite_list.append_value(map->green_door);
	map->sprite_list.append_value(map->enemy);
	map->sprite_list.append_value(map->test_player);
	map->sprite_list.append_value(map->test_computer);

  map->insert_type_at(*map->computer_pos, TileType::computer);
	map->insert_type_at(*map->door_pos, TileType::red_door_closed);
  map->insert_type_at(*map->green_door_pos, TileType::green_door_closed);

  //Border right
  map->add_component(Sprite::new_wall_r(72, 8), solid);
  map->add_component(Sprite::new_wall_r(72, 16), solid);


  map->add_component(Sprite::new_wall_r(72, 24), solid);
  map->add_component(Sprite::new_sprite(72, 32, 59), solid);
  map->add_component(Sprite::new_wall_r(72, 48), solid);

  //Border bottom
  map->add_component(Sprite::new_wall_b(8, 56), solid);
  map->add_component(Sprite::new_wall_b(16, 56), solid);
  map->add_component(Sprite::new_wall_b(32, 56), solid);
  map->add_component(Sprite::new_wall_b(40, 56), solid);
  map->add_component(Sprite::new_wall_b(48, 56), solid);
  map->add_component(Sprite::new_wall_b(56, 56), solid);
  map->add_component(Sprite::new_wall_b(64, 56), solid);

  //Border left
  map->add_component(Sprite::new_wall_l(0, 8), solid);
  map->add_component(Sprite::new_wall_l(0, 16), solid);
  map->add_component(Sprite::new_wall_l(0, 24), solid);
  map->add_component(Sprite::new_sprite(0, 32, 58), solid);
  map->add_component(Sprite::new_wall_l(0, 40), solid);
  map->add_component(Sprite::new_wall_l(0, 48), solid);

  //Border Top
  map->add_component(Sprite::new_wall_t(8, 0), solid);
  map->add_component(Sprite::new_sprite(16, 0, 57), solid);
  map->add_component(Sprite::new_wall_t(24, 0), solid);
  map->add_component(Sprite::new_wall_t(32, 0), solid);
  map->add_component(Sprite::new_wall_t(40, 0), solid);
  map->add_component(Sprite::new_wall_t(48, 0), solid);
  map->add_component(Sprite::new_sprite(56, 0, 57), solid);
  map->add_component(Sprite::new_wall_t(64, 0), solid);

  // Border Corners
  map->add_component(Sprite::new_corner_tl(0, 0), solid);
  map->add_component(Sprite::new_corner_tr(72, 0), solid);
  map->add_component(Sprite::new_corner_bl(0, 56), solid);
  map->add_component(Sprite::new_corner_br(72, 56), solid);

  // Inner Walls
  map->add_component(Sprite::new_sprite(16, 8, 17), solid);

  map->add_component(Sprite::new_sprite(16, 16, 8), solid);
  map->add_component(Sprite::new_sprite(24, 16, 19), solid);
  map->add_component(Sprite::new_sprite(32, 16, 18), solid);
  map->add_component(Sprite::new_sprite(48, 16, 7), solid);
  map->add_component(Sprite::new_sprite(56, 16, 3), solid);

  map->add_component(Sprite::new_sprite(8, 32, 19), solid);
  map->add_component(Sprite::new_sprite(16, 32, 23), solid);
  map->add_component(Sprite::new_sprite(24, 32, 19), solid);
  map->add_component(Sprite::new_sprite(32, 32, 19), solid);
  map->add_component(Sprite::new_sprite(40, 32, 16), solid);
  map->add_component(Sprite::new_sprite(48, 32, 18), solid);
  map->add_component(Sprite::new_sprite(64, 32, 7), solid);

  map->add_component(Sprite::new_sprite(16, 40, 5), solid);
  map->add_component(Sprite::new_sprite(40, 40, 5), solid);

  map->add_component(Sprite::new_sprite(56, 8, 17), solid);
  return map;
}
