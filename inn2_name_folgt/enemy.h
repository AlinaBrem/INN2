#include "sprite.cpp"
#include "enum.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Sprite
{
private:
  bool reached_target;

  uint8_t *path_grid;

  int frame_counter;
  int number_animation;
  int stun_counter;

  Point delta;
  Point neighbors[4];
  Point point_a;
  Point point_b;
  Point destination;

  Direction direction;

public:
  Enemy(int x, int y, int w, int h, int t, Point b);

  ~Enemy() = default;

  Point get_next_target();

  void move();

  void set_stunned();

  void set_path_grid(uint8_t *new_grid);

  bool has_reached_target();

  Direction get_direction();
};

#endif //ENEMY_H
