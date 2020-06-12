#include "sprite.cpp"
#include "enum.h"

#ifndef TELEPORTER_H
#define TELEPORTER_H

class Teleporter : public Sprite
{
public:
  Teleporter(int x, int y, int w, int h, int t);
  void setTeleportFunction(void (*f)());
  void teleport();
  ~Teleporter() = default;

private:
  void (*fcnPtr)();
};

#endif //teleporter_H
