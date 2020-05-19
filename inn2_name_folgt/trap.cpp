#include "trap.h"

Trap::Trap(int x, int y, int w, int h, int t, bool is_active) : Sprite(x, y, w, h, t)
{
  this->is_active = is_active;
};

bool Trap::get_is_active()
{
  return this->is_active;
}
