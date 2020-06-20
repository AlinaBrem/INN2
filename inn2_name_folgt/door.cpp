#include "door.h"

Door::Door(int x, int y, int w, int h, int t, Direction ndirection, bool is_greend_door) : Sprite(x, y, w, h, t)
{
  this->is_locked = true;
  this->direction = ndirection;
  this->is_green_door = is_green_door;
};

void Door::set_is_locked(bool value)
{
  // change is_locked value and texture id of the door
  this->is_locked = value;

  if (value)
  {
    if (this->direction == Direction::up || this->direction == Direction::down)
    {
      this->tex_id = this->is_green_door
                         ? (int)GreenDoorTextureId::up_closed
                         : (int)RedDoorTextureId::up_closed;
    }
    else
    {
      this->tex_id = this->is_green_door
                         ? (int)GreenDoorTextureId::left_closed
                         : (int)RedDoorTextureId::left_closed;
    }
  }
  else
  {
    if (this->direction == Direction::up || this->direction == Direction::down)
    {
      this->tex_id = this->is_green_door
                         ? (int)GreenDoorTextureId::up_open
                         : (int)RedDoorTextureId::up_open;
    }
    else
    {
      this->tex_id = this->is_green_door
                         ? (int)GreenDoorTextureId::left_open
                         : (int)RedDoorTextureId::left_open;
    }
  }
}

bool Door::get_is_locked()
{
  return this->is_locked;
}
