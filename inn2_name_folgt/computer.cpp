#include "Computer.h"

Computer::Computer(int x, int y, int w, int h, int t, int direction) : Sprite(x, y, w, h, t)
{
  this->width = w;
  this->height = h;

  this->direction = (Direction)direction;
  this->is_on = false;

  this->set_interaction_point();
};

void Computer::set_interaction_point()
{
  switch (this->direction)
  {
  case Direction::up:
    this->interaction_point = new Point(this->position.x + this->width / 2, this->position.y);
    break;

  case Direction::down:
    this->interaction_point = new Point(this->position.x + this->width / 2, this->position.y + this->height);
    break;

  case Direction::left:
    this->interaction_point = new Point(this->position.x, this->position.y + this->height / 2);
    break;

  case Direction::right:
    this->interaction_point = new Point(this->position.x + this->width, this->position.y + this->height / 2);
    break;

  default:
    break;
  }
}

Point *Computer::get_interaction_point()
{
  return this->interaction_point;
}

void Computer::print_interaction_point()
{
  gb.display.drawLine(this->interaction_point->x, this->interaction_point->y,
                      this->interaction_point->x, this->interaction_point->y);
}

void Computer::set_is_on(bool value)
{
  switch (this->direction)
  {
  case Direction::up:
    this->is_on = value;
    this->tex_id = value
                       ? (int)ComputerTextureId::up_on
                       : (int)ComputerTextureId::up_off;
    break;

  case Direction::down:
    this->is_on = value;
    this->tex_id = value
                       ? (int)ComputerTextureId::down_on
                       : (int)ComputerTextureId::down_off;
    break;

  case Direction::left:
    this->is_on = value;
    this->tex_id = value
                       ? (int)ComputerTextureId::left_on
                       : (int)ComputerTextureId::left_off;
    break;

  case Direction::right:
    this->is_on = value;
    this->tex_id = value
                       ? (int)ComputerTextureId::right_on
                       : (int)ComputerTextureId::right_off;
    break;

  default:
    break;
  }
}

bool Computer::get_is_on()
{
  return this->is_on;
}

Point Computer::get_position()
{
  return this->position;
}