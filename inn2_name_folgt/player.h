#include "sprite.cpp"

#ifndef PLAYER_H
#define PLAYER_H

#define NUM_COLLISION_POINTS 8

// position of the collision points
//    *  *  *
//    *  P  *
//    *  *  *
enum Collision_Points : int
{
    front_left,
    front_right,
    front_middle,
    back_left,
    back_right,
    back_middle,
    middle_left,
    middle_right
};

class Player : Sprite
{
private:
    int width;
    int height;
    int speed;
    bool is_dead;

    bool is_colliding_front_left;
    bool is_colliding_front_right;
    bool is_colliding_front_middle;
    bool is_colliding_back_left;
    bool is_colliding_back_right;
    bool is_colliding_back_middle;
    bool is_colliding_middle_left;
    bool is_colliding_middle_right;

    // set all is_colliding variables to false
    void reset_colliding_points();

    // debug function :D
    void print_collision_points();

public:
    Player(int x, int y, int w, int h, int t);

    ~Player() = default;

    // returns a pointer with the current coordinates(x,y) of all 8 collision points
    Point *get_collision_points();

    // sets a specific is_colliding variable based on an index
    void set_is_colliding(bool value, int i);

    // move up -> y--
    void move_up();

    // move up -> y++
    void move_down();

    // move up -> x++
    void move_right();

    // move up -> x--
    void move_left();
};

#endif //PLAYER_H
