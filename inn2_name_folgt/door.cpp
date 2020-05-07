#include "door.h"

Door::Door(int x, int y, int w, int h, int t) : Sprite(x, y, w, h, t)
{
  this->is_open = false;
};