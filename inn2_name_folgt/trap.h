#include "sprite.cpp"

#ifndef TRAP_H
#define TRAP_H

class Trap : Sprite
{
public:
  Trap(int x, int y, int w, int h, int t);
  
  ~Trap() = default;

private:
  bool is_active;
};

#endif //TRAP_H