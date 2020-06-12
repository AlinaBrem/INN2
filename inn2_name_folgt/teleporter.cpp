#include "teleporter.h"

Teleporter::Teleporter(int x, int y, int w, int h, int t) : Sprite(x, y, w, h, t){

                                                            };

void Teleporter::setTeleportFunction(void (*f)())
{
  fcnPtr = f;
}

void Teleporter::teleport()
{
  fcnPtr();
}