#include "sprite.cpp"
#include "enum.h"

class Enemy : public Sprite
{
  private:
    bool reached_target;
    uint8_t * path_grid;
    Point point_a;
    Point point_b;
    Point destination;
    Direction direction;
    int frame_counter;
    Point delta;
    Point neighbors[4];
    int number_animation;
  public:
    Point get_next_target();
    Enemy(int x, int y, int w, int h, int t, Point b);
    void move();
    void set_path_grid(uint8_t * new_grid);
    bool has_reached_target();
};
