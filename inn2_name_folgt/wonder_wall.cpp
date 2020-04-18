#include "sprite.cpp"

#ifndef WONDERWALL
#define WONDERWALL
class WonderWall : Sprite
{
public:
    WonderWall(int x, int y, int w, int h, int t) : Sprite(x, y, w, h, t){};
    ~WonderWall(){};
    Point get_position()
    {
        return position;
    }
    void go_up()
    {
        position.y--;
    }
    void go_down()
    {
        position.y++;
    }
    void go_right()
    {
        position.x++;
    }
    void go_left()
    {
        position.x--;
    }
};
#endif