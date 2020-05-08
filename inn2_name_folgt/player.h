#include "sprite.cpp"

#ifndef PLAYER_H
#define PLAYER_H

#define NUM_COLLISION_POINTS 12

// position of the collision points
//    *  *  *
//  *         *
//  *    P    *
//  *         *
//    *  *  *
enum class CollisionPoints
{
    front_left,
    front_right,
    front_middle,
    back_left,
    back_right,
    back_middle,
    middle_left_front,
    middle_left_center,
    middle_left_back,
    middle_right_front,
    middle_right_center,
    middle_right_back,
};

enum class Direction
{
    up,
    down,
    left,
    right
};

enum class PlayerTextureId
{
    move_up_start = 61,
    move_down_start = 71,
    move_left_start = 76,
    move_right_start = 66,
    idle_up_start = 60,
    idle_down_start = 70,
    idle_left_start = 75,
    idle_right_start = 65
};

class Player : Sprite
{
private:
    int width;
    int height;

    int speed;

    int health;
    bool is_dead;

    int frame_counter;
    int number_animation;

    int has_key;

    bool is_colliding_enemy;

    bool is_colliding_front_left;
    bool is_colliding_front_right;
    bool is_colliding_front_middle;

    bool is_colliding_back_left;
    bool is_colliding_back_right;
    bool is_colliding_back_middle;

    bool is_colliding_middle_right_front;
    bool is_colliding_middle_right_center;
    bool is_colliding_middle_right_back;

    bool is_colliding_middle_left_front;
    bool is_colliding_middle_left_center;
    bool is_colliding_middle_left_back;

    Direction direction;

    // set all is_colliding variables to false
    void reset_collision_points();

public:
    Player(int x, int y, int w, int h, int t);

    ~Player() = default;

    void set_has_key(bool value);

    bool get_has_key();

    // returns a pointer with the current coordinates(x,y) of all 8 collision points
    Point *get_collision_points();

    // returns current health of the player
    int get_health();

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

    // play the idle animation
    void idle();

    // handles the walking animation in all directions
    void play_walk_animation(PlayerTextureId start_texture_id);

    // debug function
    void print_collision_points();

    // displays a text (Debug only)
    void print(String message);
};

#endif //PLAYER_H
