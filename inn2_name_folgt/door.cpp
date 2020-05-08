#include "door.h"

Door::Door(int x, int y, int w, int h, int t) : Sprite(x, y, w, h, t)
{
  this->is_locked = true;
};

void Door::set_is_locked(bool value)
{
  // change is_locked value and texutre id of the door
  if(value == true)
  {
    this->is_locked = value;
    this->tex_id = DoorTexturesIds::is_closed;
  }
  else
  {
    this->is_locked = value;
    this->tex_id = DoorTexturesIds::is_open;
  }
  
}

bool Door::get_is_locked()
{
  return this->is_locked;
}