#include "sprite.cpp"
#include "enum.h"

#ifndef DOOR_H
#define DOOR_H

class Door : public Sprite
{
public:
  Door(int x, int y, int w, int h, int t);

  ~Door() = default;

  void set_is_locked(bool value);

  bool get_is_locked();

private:
  bool is_locked;
};

#endif //DOOR_H
