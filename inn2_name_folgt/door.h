#include "sprite.cpp"
#include "enum.h"

#ifndef DOOR_H
#define DOOR_H

class Door : public Sprite
{
public:
  Door(int x, int y, int w, int h, int t, int direction, bool is_greend_door);

  ~Door() = default;

  void set_is_locked(bool value);

  bool get_is_locked();

private:
  bool is_locked;
  bool is_green_door;

  Direction direction;
};

#endif //DOOR_H
