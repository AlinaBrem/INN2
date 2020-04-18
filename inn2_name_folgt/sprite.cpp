#include <stdint.h>
#include <Gamebuino-Meta.h>
#include "texture.cpp"
#ifndef SPRITE
#define SPRITE
class Point
{
public:
    Point(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

class Sprite
{
protected:
    int tex_id;
    Point position;
    Point i_position;
    Point i_dimension;
    Sprite(int x, int y, int w, int h, int t) : position(Point(x, y)),
                                                i_dimension(Point(w, h)),
                                                tex_id(t),
                                                i_position(Point((t % 10) * 8, (t / 10) * 8)){};

public:
    void draw()
    {
        gb.display.drawImage(position.x, position.y, my_img_buf, i_position.x, i_position.y, i_dimension.x, i_dimension.y);
    }

    static Sprite *new_sprite(int x, int y, int t)
    {
        return new Sprite(x, y, 8, 8, t);
    }

    static Sprite *new_corner_tl(int x, int y) // ul ... TopLeft usw.
    {
        return new_sprite(x, y, 0);
    }
    static Sprite *new_corner_tr(int x, int y)
    {
        return new_sprite(x, y, 2);
    }
    static Sprite *new_corner_bl(int x, int y)
    {
        return new_sprite(x, y, 20);
    }
    static Sprite *new_corner_br(int x, int y)
    {
        return new_sprite(x, y, 22);
    }
    static Sprite *new_wall_t(int x, int y)
    {
        return new_sprite(x, y, 1);
    }
    static Sprite *new_wall_b(int x, int y)
    {
        return new_sprite(x, y, 21);
    }
    static Sprite *new_wall_l(int x, int y)
    {
        return new_sprite(x, y, 10);
    }
    static Sprite *new_wall_r(int x, int y)
    {
        return new_sprite(x, y, 12);
    }
};
#endif
