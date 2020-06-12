#include "sprite.cpp"
#include "enum.h"

#ifndef BOTTLE_H
#define BOTTLE_H

#define SPEED 4

class Bottle : public Sprite
{
private:
  int frame_counter = 0;

  Point start;
  Point destination;

  bool is_colliding;

  Direction direction;

public:
  Bottle(int x, int y, int w, int h, int t, Direction direction);

  Bottle(int x, int y, int w, int h, int t);

  ~Bottle() = default;

  bool get_is_colliding();

  void set_is_colliding(bool value);

  // moves the bottle ohne "?pixel?" towards the destination
  void get_next_point();

  // returns the destination point
  Point get_destination();

  // prints the current direction of the bottle
  void print_direction();

  // draws a line between the start point and the destination point
  void print_flight_path();
};
#endif //BOTTLE_H
