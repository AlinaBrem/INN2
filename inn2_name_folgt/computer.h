#include "sprite.cpp"

#ifndef COMPUTER_H
#define COMPUTER_H

enum ComputerTexturesIds : int
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

class Computer : Sprite
{
public:
  Computer(int x, int y, int w, int h, int t);
  
  ~Computer() = default;

  void set_is_colliding();

  bool get_is_colliding();

private:
  bool is_colliding;
};

#endif //COMPUTER_H