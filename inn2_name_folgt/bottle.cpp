#include "bottle.h"

Bottle::Bottle(int x, int y, int w, int h, int t, Direction direction) : Sprite(x, y, w, h, t),
                                                                         start(x, y),
                                                                         destination(x, y)
{
  this->direction = direction;
  this->is_colliding = false;
}

bool Bottle::get_is_colliding()
{
  return this->is_colliding;
}

void Bottle::set_is_colliding(bool value)
{
  this->is_colliding = value;
  if (value)
  {
    this->tex_id = (int)BottleTextureId::broken;
  }
}

Point Bottle::get_destination()
{
  switch (this->direction)
  {
  case Direction::up:
    return Point(this->start.x, this->start.y - gb.display.height());
    break;

  case Direction::down:
    return Point(this->start.x, this->start.y + gb.display.height());
    break;

  case Direction::left:
    return Point(this->start.x - gb.display.width(), this->start.y);
    break;

  case Direction::right:
    return Point(this->start.x + gb.display.width(), this->start.y);
    break;
  }
}

void Bottle::get_next_point()
{
  switch (this->direction)
  {
  case Direction::up:
    this->position.y -= SPEED;
    break;

  case Direction::down:
    this->position.y += SPEED;
    break;

  case Direction::left:
    this->position.x -= SPEED;
    break;

  case Direction::right:
    this->position.x += SPEED;
    break;

  default:
    break;
  }
}

void Bottle::print_direction()
{
  switch (this->direction)
  {
  case Direction::up:
    gb.display.println("Up");
    break;

  case Direction::down:
    gb.display.println("Down");
    break;

  case Direction::left:
    gb.display.println("Left");
    break;

  case Direction::right:
    gb.display.println("Right");
    break;

  default:
    break;
  }
}

void Bottle::print_flight_path()
{
  switch (this->direction)
  {
  case Direction::up:
    gb.display.drawLine(this->start.x, this->start.y,
                        this->start.x, this->start.y - gb.display.height());
    break;

  case Direction::down:
    gb.display.drawLine(this->start.x, this->start.y,
                        this->start.x, this->start.y + gb.display.height());
    break;

  case Direction::left:
    gb.display.drawLine(this->start.x, this->start.y,
                        this->start.x - gb.display.width(), this->start.y);
    break;

  case Direction::right:
    gb.display.drawLine(this->start.x, this->start.y,
                        this->start.x + gb.display.width(), this->start.y);
    break;

  default:
    break;
  }
}

Point Bottle::get_position()
{
  return this->position;
}