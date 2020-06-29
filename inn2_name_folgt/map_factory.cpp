#include "map_factory.h"

Map* map_factory::get_map_1() {
  Map* map = new Map();

  // to set other entities like a bottle or trap
  // use the responsible funtions of the Map-Class
  map->set_start_position(3, 7);
  map->set_key(1, 5);
  map->set_computer(1, 1, Direction::down);
  map->set_red_door(2,3, Direction::left);
  map->set_green_door(9, 5, Direction::left);
  map->set_enemy_path(3, 3, 8, 1);

  //Border right
  map->add_solid(Sprite::new_wall_r(9, 1));
  map->add_solid(Sprite::new_wall_r(9, 2));
  map->add_solid(Sprite::new_wall_r(9, 3));
  map->add_solid(Sprite::new_sprite(9, 4, 59));
  map->add_solid(Sprite::new_wall_r(9, 6));

  //Border bottom
  map->add_solid(Sprite::new_wall_b(1, 7));
  map->add_solid(Sprite::new_wall_b(2, 7));
  map->add_solid(Sprite::new_wall_b(4, 7));
  map->add_solid(Sprite::new_wall_b(5, 7));
  map->add_solid(Sprite::new_wall_b(6, 7));
  map->add_solid(Sprite::new_wall_b(7, 7));
  map->add_solid(Sprite::new_wall_b(8, 7));

  //Border left
  map->add_solid(Sprite::new_wall_l(0, 1));
  map->add_solid(Sprite::new_wall_l(0, 2));
  map->add_solid(Sprite::new_wall_l(0, 3));
  map->add_solid(Sprite::new_sprite(0, 4, 58));
  map->add_solid(Sprite::new_wall_l(0, 5));
  map->add_solid(Sprite::new_wall_l(0, 6));

  //Border Top
  map->add_solid(Sprite::new_wall_t(1, 0));
  map->add_solid(Sprite::new_sprite(2, 0, 57));
  map->add_solid(Sprite::new_wall_t(3, 0));
  map->add_solid(Sprite::new_wall_t(4, 0));
  map->add_solid(Sprite::new_wall_t(5, 0));
  map->add_solid(Sprite::new_wall_t(6, 0));
  map->add_solid(Sprite::new_sprite(7, 0, 57));
  map->add_solid(Sprite::new_wall_t(8, 0));

  // Border Corners
  map->add_solid(Sprite::new_corner_tl(0, 0));
  map->add_solid(Sprite::new_corner_tr(9, 0));
  map->add_solid(Sprite::new_corner_bl(0, 7));
  map->add_solid(Sprite::new_corner_br(9, 7));

  // Inner Walls
  map->add_solid(Sprite::new_sprite(2, 1, 17));

  map->add_solid(Sprite::new_sprite(2, 2, 8));
  map->add_solid(Sprite::new_sprite(3, 2, 19));
  map->add_solid(Sprite::new_sprite(4, 2, 18));
  map->add_solid(Sprite::new_sprite(6, 2, 7));
  map->add_solid(Sprite::new_sprite(7, 2, 3));

  map->add_solid(Sprite::new_sprite(1, 4, 19));
  map->add_solid(Sprite::new_sprite(2, 4, 23));
  map->add_solid(Sprite::new_sprite(3, 4, 19));
  map->add_solid(Sprite::new_sprite(4, 4, 19));
  map->add_solid(Sprite::new_sprite(5, 4, 16));
  map->add_solid(Sprite::new_sprite(6, 4, 18));
  map->add_solid(Sprite::new_sprite(8, 4, 7));

  map->add_solid(Sprite::new_sprite(2, 5, 5));
  map->add_solid(Sprite::new_sprite(5, 5, 5));

  map->add_solid(Sprite::new_sprite(7, 1, 17));
  // in the sprite_list, elsewise the collision won't work!

  
  map->finalize();
  return map;
}

Map* map_factory::get_map_2() {
  Map* map = new Map();

  // to set other entities like a bottle or trap
  // use the responsible funtions of the Map-Class
  map->set_start_position(4, 7);
  map->set_key(2, 6);
  map->set_computer(7,6, Direction::right);
  map->set_red_door(2,2, Direction::down);
  map->set_green_door(9, 1, Direction::left);
  map->set_enemy_path(1, 6, 8, 5);

  //Border right
 
  map->add_solid(Sprite::new_sprite(9, 2, 59));
  map->add_solid(Sprite::new_wall_r(9, 3));
  map->add_solid(Sprite::new_wall_r(9, 4));
  map->add_solid(Sprite::new_wall_r(9, 5));
  map->add_solid(Sprite::new_wall_r(9, 6));

  //Border bottom
  map->add_solid(Sprite::new_wall_b(1, 7));
  map->add_solid(Sprite::new_wall_b(2, 7));
  map->add_solid(Sprite::new_sprite(3, 7, 3));
  map->add_solid(Sprite::new_sprite(6, 7, 4));
  map->add_solid(Sprite::new_wall_b(7, 7));
  map->add_solid(Sprite::new_wall_b(8, 7));

  //Border left
  map->add_solid(Sprite::new_wall_l(0, 1));
  map->add_solid(Sprite::new_sprite(0, 2, 58));
  map->add_solid(Sprite::new_wall_l(0, 3));
  map->add_solid(Sprite::new_wall_l(0, 4));
  map->add_solid(Sprite::new_wall_l(0, 5));
  map->add_solid(Sprite::new_wall_l(0, 6));

  //Border Top
  map->add_solid(Sprite::new_wall_t(1, 0));
  map->add_solid(Sprite::new_wall_t(2, 0));
  map->add_solid(Sprite::new_wall_t(3, 0));
  map->add_solid(Sprite::new_wall_t(4, 0));
  map->add_solid(Sprite::new_wall_t(5, 0));
  map->add_solid(Sprite::new_wall_t(6, 0));
  map->add_solid(Sprite::new_wall_t(7, 0));
  map->add_solid(Sprite::new_wall_t(8, 0));

  // Border Corners
  map->add_solid(Sprite::new_corner_tl(0, 0));
  map->add_solid(Sprite::new_corner_tr(9, 0));
  map->add_solid(Sprite::new_corner_bl(0, 7));
  map->add_solid(Sprite::new_corner_br(9, 7));

  // Inner Walls
  //top wall
  map->add_solid(Sprite::new_sprite(1, 2, 19));
  map->add_solid(Sprite::new_sprite(3, 2, 19));
  map->add_solid(Sprite::new_sprite(4, 2, 19));
  map->add_solid(Sprite::new_sprite(5, 2, 19));
  map->add_solid(Sprite::new_sprite(6, 2, 19));
  map->add_solid(Sprite::new_sprite(7, 2, 19));
  map->add_solid(Sprite::new_sprite(8, 2, 19));
  
  
  //inner wall, bottom left
  map->add_solid(Sprite::new_sprite(3, 6, 17));
  map->add_solid(Sprite::new_sprite(3, 5, 13));
  map->add_solid(Sprite::new_sprite(2, 5, 7));

  //inner wall, bottom right
  map->add_solid(Sprite::new_sprite(6, 6, 17));
  map->add_solid(Sprite::new_sprite(6, 5, 17));
  map->add_solid(Sprite::new_sprite(6, 4, 14));
  map->add_solid(Sprite::new_sprite(7, 4, 18));

  // Needs to be called before returning the map, to wrap up every sprite
  // in the sprite_list, elsewise the collision won't work!

  
  map->finalize();
  return map;
}

// Map 3 aka map3_2
Map* map_factory::get_map_3() {
  Map* map = new Map();

  // to set other entities like a bottle or trap
  // use the responsible funtions of the Map-Class
  map->set_start_position(0, 6);
  //map->set_key(5, 6);
  map->set_key(2, 1);
  //map->set_computer(5, 1, Direction::left);
  map->set_computer(5, 6, Direction::right);
  //map->set_red_door(4,3, Direction::down);
  //map->set_red_door(8,3, Direction::down);
  map->set_red_door(8,5, Direction::up);
  map->set_green_door(9, 4, Direction::left);
  map->set_enemy_path(8, 4, 1, 4);
  //Border right
 
  map->add_solid(Sprite::new_wall_r(9, 1));
  map->add_solid(Sprite::new_wall_r(9, 2));
  map->add_solid(Sprite::new_wall_r(9, 3));
  map->add_solid(Sprite::new_sprite(9, 5, 59));
  map->add_solid(Sprite::new_wall_r(9, 6));

  //Border bottom
  map->add_solid(Sprite::new_wall_b(1, 7));
  map->add_solid(Sprite::new_wall_b(2, 7));
  map->add_solid(Sprite::new_wall_b(3, 7));
  map->add_solid(Sprite::new_sprite(4, 7, 56));
  map->add_solid(Sprite::new_wall_b(5, 7));
  map->add_solid(Sprite::new_wall_b(6, 7));
  map->add_solid(Sprite::new_wall_b(7, 7));
  map->add_solid(Sprite::new_wall_b(8, 7));

  //Border left
  map->add_solid(Sprite::new_wall_l(0, 1));
  map->add_solid(Sprite::new_wall_l(0, 2));
  map->add_solid(Sprite::new_wall_l(0, 3));
  map->add_solid(Sprite::new_wall_l(0, 4));
  map->add_solid(Sprite::new_sprite(0, 5, 58));

  //Border Top
  map->add_solid(Sprite::new_wall_t(1, 0));
  map->add_solid(Sprite::new_wall_t(2, 0));
  map->add_solid(Sprite::new_sprite(3, 0, 57));
  map->add_solid(Sprite::new_wall_t(4, 0));
  map->add_solid(Sprite::new_wall_t(5, 0));
  map->add_solid(Sprite::new_sprite(6, 0, 57));
  map->add_solid(Sprite::new_wall_t(7, 0));
  map->add_solid(Sprite::new_wall_t(8, 0));

  // Border Corners
  map->add_solid(Sprite::new_corner_tl(0, 0));
  map->add_solid(Sprite::new_corner_tr(9, 0));
  map->add_solid(Sprite::new_corner_bl(0, 7));
  map->add_solid(Sprite::new_corner_br(9, 7));

  // Inner Walls
  //entrance wall
  map->add_solid(Sprite::new_sprite(1, 5, 19));
  map->add_solid(Sprite::new_sprite(2, 5, 18));

  
  
  //inner wall, top left
  map->add_solid(Sprite::new_sprite(3, 1, 17));
  map->add_solid(Sprite::new_sprite(3, 2, 17));
  map->add_solid(Sprite::new_sprite(3, 3, 3));
  map->add_solid(Sprite::new_sprite(2, 3, 7));

  //inner wall, top right
  map->add_solid(Sprite::new_sprite(6, 1, 17));
  map->add_solid(Sprite::new_sprite(6, 2, 17));
  map->add_solid(Sprite::new_sprite(6, 3, 6));
  map->add_solid(Sprite::new_sprite(7, 3, 18));
  map->add_solid(Sprite::new_sprite(5, 3, 7));

  //inner wall, bottom right
  map->add_solid(Sprite::new_sprite(4, 6, 17));
  map->add_solid(Sprite::new_sprite(4, 5, 14));
  map->add_solid(Sprite::new_sprite(5, 5, 19));
  map->add_solid(Sprite::new_sprite(6, 5, 19));
  map->add_solid(Sprite::new_sprite(7, 5, 19));
 

  // Needs to be called before returning the map, to wrap up every sprite
  // in the sprite_list, elsewise the collision won't work!

  
  map->finalize();
  return map;
}
