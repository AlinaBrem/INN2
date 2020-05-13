#include "sprite.cpp"
#include "enum.h"

#ifndef PLAYER_H
#define PLAYER_H

#define NUM_COLLISION_POINTS 12

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

    bool is_interacting;

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

public:
    Player(int x, int y, int w, int h, int t);

    ~Player() = default;

    void set_has_key(bool value);

    bool get_has_key();

    void set_is_interacting(bool value);

    bool get_is_interacting();

    // returns a pointer with the current coordinates(x,y) of all 8 collision points
    Point *get_collision_points();

    // returns current health of the player
    int get_health();

    // sets a specific is_colliding variable based on an index
    void set_is_colliding(bool value, int i);

    // sets a specific is_colliding variable based on the player direction
    void set_is_colliding(bool value);

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

    // play the interaction animation
    void interact();

    // handles the walking animation in all directions
    void play_walk_animation(PlayerTextureId start_texture_id);

    // returns the position of the sprite as a Point
    Point get_position();

    // returns the currently active interaction point
    Point get_interaction_point();

    // set all is_colliding variables to false
    void reset_collision_points();

    // set interaction texture id for the player
    void interact(PlayerTextureId start_texture_id);

    // debug function
    void print_collision_points();

    // displays a message (Debug only)
    void print_message(String message);

    // prints the interaction collision point (1 pixel in front of the player)
    void print_interaction_collision_points();
};

#endif //PLAYER_H
