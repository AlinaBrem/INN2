#include "sprite.cpp"

#ifndef TRAP_H
#define TRAP_H

class Trap : public Sprite
{
private:
  bool active;

public:
  Trap(int x, int y, int w, int h, int t, bool active);

  ~Trap() = default;

  bool is_active();
};

#endif //TRAP_H
