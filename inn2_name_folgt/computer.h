#include "sprite.cpp"

#ifndef COMPUTER_H
#define COMPUTER_H

class Computer : Sprite
{
public:
  Computer(int x, int y, int w, int h, int t);
  
  ~Computer() = default;
};

#endif //COMPUTER_H