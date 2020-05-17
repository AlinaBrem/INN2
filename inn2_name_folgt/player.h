#include "sprite.cpp"
#include "enum.h"
#include "trap.h"
#include "linked_list.cpp"

#ifndef PLAYER_H
#define PLAYER_H

#define NUM_COLLISION_POINTS 8
#define MAX_ITEMS 3
#define KEY "Key"
#define TRAP "Trap"
#define BOTTLE "Bottle"

class Player : public Sprite
{
private:
    int width;
    int height;

    int speed;

    int health;
    bool is_dead;

    int frame_counter;
    int number_animation;

    int trap_count;

    bool is_interacting;

    bool is_colliding_front_left;
    bool is_colliding_front_right;

    bool is_colliding_back_left;
    bool is_colliding_back_right;

    bool is_colliding_middle_right_front;
    bool is_colliding_middle_right_back;

    bool is_colliding_middle_left_front;
    bool is_colliding_middle_left_back;

    int current_item_index;
    String inventory[MAX_ITEMS];

    Direction direction;

public:
    Player(int x, int y, int w, int h, int t);

    ~Player() = default;

    void set_is_interacting(bool value);

    bool get_is_interacting();

    // adds a given value to the players trap_count (subtracts if value < 0)
    void set_trap_count(int value);

    int get_trap_count();

    // returns a pointer with the current coordinates(x,y) of all 12 collision points
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

    // adds an item to the inventory
    void add_item(String item);

    // deletes the currently selected item, based on its name
    void delete_item(String item);

    // returns the value(name) of the current item as a string
    String get_current_item();

    void next_item();

    // displays the currently selected item of the player
    void print_current_item();

    // prints all collision points of the player
    void print_collision_points();

    // displays a message
    void print_message(String message);

    // prints the interaction collision point (1 pixel in front of the player)
    void print_interaction_points();
};

#endif //PLAYER_H
