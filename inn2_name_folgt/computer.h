#include "sprite.cpp"

#ifndef COMPUTER_H
#define COMPUTER_H

enum class ComputerTextureId
{
  up_on = 43,
  up_off = 41,
  down_on = 32,
  down_off = 30,
  left_on = 33,
  left_off = 31,
  right_on = 42,
  right_off = 40
};

enum class Direction
{
  up,
  down,
  left,
  right
};

class Computer : Sprite
{
private:
  int width;
  int height;

  bool is_colliding;
  bool is_on;

  Point *collision_point;

  Direction direction;

public:
  Computer(int x, int y, int w, int h, int t, int direction);

  ~Computer() = default;

  Point *get_collision_point();

  void set_collision_point();

  void set_is_on(bool value);

  bool get_is_on();

  void print_collision_point();
};

#endif //COMPUTER_H