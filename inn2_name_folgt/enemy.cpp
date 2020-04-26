#include "enemy.h"

Enemy::Enemy(int x, int y, int w, int h, int t, Point b) : Sprite(x, y, w, h, t),
                                                          point_a(Point(x,y)),
                                                          point_b(b),
                                                          destination(b),
                                                          delta(Point(0,0))
{
  this->direction = DOWN;
  this->frame_counter = 0;
  this->number_animation = 0;
};

void Enemy::move()
{
  if (frame_counter < 2)
  {
    frame_counter ++;
    return;
  }
  frame_counter = 0;
  delta = destination - position;
  if (delta.x == 0 && delta.y == 0)
  {
    destination = position == point_a ?  point_b : point_a;
    delta = destination - position;
  }
  if (abs(delta.x) <= abs(delta.y) ? delta.x != 0 : delta.y == 0) 
  {
    if (delta.x > 0)
    {
      this->position.x ++;
      this->tex_id = 66;
    }
    else
    {
      this->position.x --;  
      this->tex_id = 76;
    }
  }
  else 
  {
    if (delta.y > 0)
    {
      this->position.y ++;
      this->tex_id = 71;
    }
    else
    {
      this->position.y --;
      this->tex_id = 61;
    }
  }
  this->tex_id = this->number_animation == 2 ? this->tex_id + 1 : this->number_animation == 1 || this->number_animation == 3 ? this->tex_id + 2 : this->tex_id;
  this->number_animation = (this->number_animation + 1) % 4;
}

