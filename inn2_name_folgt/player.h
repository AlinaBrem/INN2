#include "sprite.cpp"
#include "enum.h"
#include "trap.h"
#include "linked_list.cpp"

#ifndef PLAYER_H
#define PLAYER_H

#define NUM_COLLISION_POINTS 8
#define MAX_ITEMS 3
#define KEY 0
#define TRAP 1
#define BOTTLE 2

class Player : public Sprite
{
private:
    int width;
    int height;
    int speed;
    int health;
    int number_animation;
    int current_item;

    bool is_dead;
    bool is_interacting;
    bool is_colliding_front_left;
    bool is_colliding_front_right;
    bool is_colliding_back_left;
    bool is_colliding_back_right;
    bool is_colliding_middle_right_front;
    bool is_colliding_middle_right_back;
    bool is_colliding_middle_left_front;
    bool is_colliding_middle_left_back;

    int inventory[MAX_ITEMS];

    Direction direction;

public:
    Player(int x, int y, int w, int h, int t);

    ~Player() = default;

    void set_is_interacting(bool value);

    bool get_is_interacting();


    // returns the current direction of the player
    Direction get_direction();

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

    // returns the currently active interaction point
    Point get_interaction_point();

    // set all is_colliding variables to false
    void reset_collision_points();

    // adds an item to the inventory
    void add_item(int item);

    // deletes the currently selected item, based on its name
    void delete_item(int item);

    // returns the value of the current item as int
    int get_current_item();

    int get_current_item_count();

    void next_item();

    // displays the currently selected item of the player
    void print_current_item();

    // prints all collision points of the player
    void print_collision_points();

    // displays a message
    void print_message(String message);

    // prints the interaction collision point (1 pixel in front of the player)
    void print_interaction_points();

    // prints the current direction of the player
    void print_direction();
};

#endif //PLAYER_H
