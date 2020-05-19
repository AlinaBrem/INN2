#include "sprite.cpp"

#ifndef TRAP_H
#define TRAP_H

class Trap : public Sprite
{
private:
  bool is_active;

public:
  Trap(int x, int y, int w, int h, int t, bool is_active);

  ~Trap() = default;

  bool get_is_active();
};

#endif //TRAP_H
