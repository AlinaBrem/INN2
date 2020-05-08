#include "sprite.cpp"

#ifndef DOOR_H
#define DOOR_H

enum DoorTexturesIds : int
{
  is_open = 49,
  is_closed = 48 
};

class Door : Sprite
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
