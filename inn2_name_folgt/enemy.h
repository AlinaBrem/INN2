#include "sprite.cpp"

enum dir
{
  LEFT, UP, RIGHT, DOWN  
};

class Enemy : Sprite
{
  private:
    Point point_a;
    Point point_b;
    Point destination;
    dir direction;
    int frame_counter;
    Point delta;
    int number_animation;
  public:
    Enemy(int x, int y, int w, int h, int t, Point b);
    void move();
};
