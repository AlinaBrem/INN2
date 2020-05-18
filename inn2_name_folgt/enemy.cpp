#include "enemy.h"

Enemy::Enemy(int x, int y, int w, int h, int t, Point b) : Sprite(x, y, w, h, t),
                                                           point_a(Point(x, y)),
                                                           point_b(b),
                                                           destination(Point(x, y)), // so that enemy has to check grid as soon as he spawns
                                                           delta(Point(0, 0)),
                                                           neighbors{Point(-1, 0), Point(0, -1), Point(1, 0), Point(0, 1)}
{
  this->direction = Direction::down;
  this->frame_counter = 0;
  this->number_animation = 0;
  this->path_grid = nullptr;
  this->reached_target = false;
};

//set pathgrid assumes that only this enemy is using this grid & its safe to delete it
void Enemy::set_path_grid(uint8_t *new_grid)
{
  if (this->path_grid != nullptr)
  {
    delete[] this->path_grid;
  }

  this->path_grid = new_grid;
  this->reached_target = false;
}

Point Enemy::get_next_target()
{
  return position == point_a ? point_b : point_a;
}

bool Enemy::has_reached_target()
{
  return this->reached_target;
}

Direction Enemy::get_direction()
{
  return this->direction;
}

void Enemy::move()
{
  //enemy only moves every three frames
  if (frame_counter < 2)
  {
    frame_counter++;
    return;
  }

  frame_counter = 0;
  //if enemy reached destination check for next dest in grid
  if (destination == position)
  {
    Point grid_position = position / 8;
    int min = path_grid[(grid_position.x) + (grid_position.y * 10)];
    if (min >= 70)
    {
      this->reached_target = true;
      return;
    }

    //find next smallest distance to target in grid
    for (Point neighbor : neighbors)
    {
      Point temp = grid_position + neighbor;

      if (temp.x >= 0 && temp.x < 10 && temp.y >= 0 && temp.y < 8 && path_grid[temp.x + temp.y * 10] < min)
      {
        min = path_grid[temp.x + temp.y * 10];
        destination = (grid_position + neighbor) * 8;
      }
    }

    if (destination == position)
    {
      this->reached_target = true;
    }
  }

  delta = destination - position;
  // delta x and y cant both be != 0
  if (delta.x != 0)
  {
    if (delta.x > 0)
    {
      this->position.x++;
      this->direction = Direction::right;
    }
    else
    {
      this->position.x--;
      this->direction = Direction::left;
    }
  }
  else if (delta.y != 0)
  {
    if (delta.y > 0)
    {
      this->position.y++;
      this->direction = Direction::down;
    }
    else
    {
      this->position.y--;
      this->direction = Direction::up;
    }
  }

  this->tex_id = direction == Direction::up ? 61 : direction == Direction::down ? 71 : direction == Direction::right ? 66 : 76;
  //animation
  if (delta.x != 0 || delta.y != 0)
  {
    this->tex_id = this->number_animation == 2 ? this->tex_id + 1 : this->number_animation == 1 || this->number_animation == 3 ? this->tex_id + 2 : this->tex_id;
    this->number_animation = (this->number_animation + 1) % 4;
  }
  else
  {
    this->tex_id += 2;
  }
}
