#include "trap.h"

Trap::Trap(int x, int y, int w, int h, int t, bool active) : Sprite(x, y, w, h, t)
{
  this->active = active;
};

bool Trap::is_active()
{
  return this->active;
}
