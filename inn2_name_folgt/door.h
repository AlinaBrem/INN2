#include "sprite.cpp"

#ifndef DOOR_H
#define DOOR_H

class Door : Sprite
{
public:
  Door(int x, int y, int w, int h, int t);
  
  ~Door() = default;

private:
  bool is_open;
};

#endif //DOOR_H
