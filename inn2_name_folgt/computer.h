#include "sprite.cpp"
#include "enum.h"

#ifndef COMPUTER_H
#define COMPUTER_H

class Computer : public Sprite
{
private:
  int width;
  int height;

  bool is_colliding;
  bool is_on;

  Point *interaction_point = nullptr;

  Direction direction;

public:
  Computer(int x, int y, int w, int h, int t, Direction ndirection);

  ~Computer();

  Point *get_interaction_point();

  // sets the interaction point
  // player ahs to collide with the interaction point to interact with the computer
  void set_interaction_point();

  void set_is_on(bool value);

  bool get_is_on();

  // returns the position of the sprite as a Point
  Point get_position();

  // prints the interaction point of the computer
  // always in front of the computer
  void print_interaction_point();
};

#endif //COMPUTER_H
