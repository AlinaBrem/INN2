#include "player.h"

Player::Player(int x, int y, int w, int h, int t) : Sprite(x, y, w, h, t)
{
    this->width = w;
    this->height = h;
    this->speed = 1;
    this->health = 1;
    this->is_dead = false;
    this->is_colliding_enemy = false;

    this->reset_colliding_points();
};

Point *Player::get_collision_points()
{
    // get collision points
    auto *points = new Point[NUM_COLLISION_POINTS]
    {
        // front_left
        Point(this->position.x + 1, this->position.y),
        // front_middle
        Point(this->position.x + this->width / 2, this->position.y),
        // front_right
        Point(this->position.x + this->width - 1, this->position.y),
        // back_left
        Point(this->position.x + 1, this->position.y + this->height),
        // back_middle
        Point(this->position.x + this->width / 2, this->position.y + this->height),
        // back_right
        Point(this->position.x + this->width - 1, this->position.y + this->height),
        // middle_left_front
        Point(this->position.x, this->position.y + 1),
        // middle_left_center
        Point(this->position.x, this->position.y + this->height / 2),
        // middle_left_back
        Point(this->position.x, this->position.y + this->height - 1),
        // middle_right_front
        Point(this->position.x + this->width, this->position.y + 1),
        // middle_right_center
        Point(this->position.x + this->width, this->position.y + this->height / 2),
        // middle_right_back
        Point(this->position.x + this->width, this->position.y + this->height - 1)
    };
    return points;
}

int Player::get_health()
{
    return this->health;
}

void Player::set_is_colliding(bool value, int i)
{
    switch (i)
    {
        case Collision_Points::front_left:
            // gb.display.println("c_front_left");
            this->is_colliding_front_left = true;
            break;
            
        case Collision_Points::front_right:
            // gb.display.println("c_front_right");
            this->is_colliding_front_right = true;
            break;

        case Collision_Points::front_middle:
            // gb.display.println("c_front_middle");
            this->is_colliding_front_middle = true;
            break;

        case Collision_Points::back_left:
            // gb.display.println("c_back_left");
            this->is_colliding_back_left = true;
            break;

        case Collision_Points::back_right:
            // gb.display.println("c_back_right");
            this->is_colliding_back_right = true;
            break;

        case Collision_Points::back_middle:
            // gb.display.println("c_back_middle");
            this->is_colliding_back_middle = true;
            break;

        case Collision_Points::middle_left_front:
            // gb.display.println("c_middle_left_front");
            this->is_colliding_middle_left_front = true;
            break;

        case Collision_Points::middle_left_center:
            // gb.display.println("c_middle_left_center");
            this->is_colliding_middle_left_center = true;
            break;

        case Collision_Points::middle_left_back:
            // gb.display.println("c_middle_left_back");
            this->is_colliding_middle_left_back = true;
            break;

        case Collision_Points::middle_right_front:
            // gb.display.println("c_middle_right_front");
            this->is_colliding_middle_right_front = true;
            break;

        case Collision_Points::middle_right_center:
            // gb.display.println("c_middle_right_center");
            this->is_colliding_middle_right_center = true;
            break;

        case Collision_Points::middle_right_back:
            // gb.display.println("c_middle_right_back");
            this->is_colliding_middle_right_back = true;
            break;

        default:
            gb.display.println("SOMETHING WENT WRONG LOL");
            break;
    }
}

void Player::reset_colliding_points()
{
    this->is_colliding_front_left = false;
    this->is_colliding_front_right = false;
    this->is_colliding_front_middle = false;

    this->is_colliding_back_left = false;
    this->is_colliding_back_right = false;
    this->is_colliding_back_middle = false;
    
    this->is_colliding_middle_right_front = false;
    this->is_colliding_middle_right_center = false;
    this->is_colliding_middle_right_back = false;

    this->is_colliding_middle_left_front = false;
    this->is_colliding_middle_left_center = false;
    this->is_colliding_middle_left_back = false;
}

void Player::move_up()
{
    if (!this->is_colliding_front_left && !this->is_colliding_front_middle && !this->is_colliding_front_right)
    {
        this->position.y--;
        this->reset_colliding_points();
    }
}

void Player::move_down()
{
    if (!this->is_colliding_back_left && !this->is_colliding_back_middle && !this->is_colliding_back_right)
    {
        this->position.y++;
        this->reset_colliding_points();
    }
}

void Player::move_right()
{
    if (!this->is_colliding_middle_right_front && !this->is_colliding_middle_right_center && !this->is_colliding_middle_right_back)
    {
        this->position.x++;
        this->reset_colliding_points();
    }
}

void Player::move_left()
{
    if (!this->is_colliding_middle_left_front && !this->is_colliding_middle_left_center && !this->is_colliding_middle_left_back)
    {
        this->position.x--;
        this->reset_colliding_points();
    }
}

void Player::print_collision_points()
{
    gb.display.setColor(GREEN);

    // front_left
    gb.display.drawLine(this->position.x + 1, this->position.y, 
                        this->position.x + 1, this->position.y);
    // front_middle
    gb.display.drawLine(this->position.x + this->width / 2, this->position.y, 
                        this->position.x + this->width / 2, this->position.y);
    // front_right
    gb.display.drawLine(this->position.x + this->width - 1, this->position.y, 
                        this->position.x + this->width - 1, this->position.y);
    // back_left
    gb.display.drawLine(this->position.x + 1, this->position.y + this->height, 
                        this->position.x + 1, this->position.y + this->height);
    // back_middle
    gb.display.drawLine(this->position.x + this->width / 2, this->position.y + this->height,
                        this->position.x + this->width / 2, this->position.y + this->height);
    // back_right
    gb.display.drawLine(this->position.x + this->width - 1, this->position.y + this->height, 
                        this->position.x + this->width - 1, this->position.y + this->height);
    // middle_left_front
    gb.display.drawLine(this->position.x, this->position.y + 1, 
                        this->position.x, this->position.y + 1);
    // middle_left_center
    gb.display.drawLine(this->position.x, this->position.y + this->height / 2, 
                        this->position.x, this->position.y + this->height / 2);
    // middle_left_back
    gb.display.drawLine(this->position.x, this->position.y + this->height - 1, 
                        this->position.x, this->position.y + this->height - 1);
    // middle_right_front
    gb.display.drawLine(this->position.x + this->width, this->position.y + 1, 
                        this->position.x + this->width, this->position.y + 1);
    // middle_right_center
    gb.display.drawLine(this->position.x + this->width, this->position.y + this->height / 2,
                        this->position.x + this->width, this->position.y + this->height / 2);
    // middle_right_back
    gb.display.drawLine(this->position.x + this->width, this->position.y + this->height - 1, 
                        this->position.x + this->width, this->position.y + this->height - 1);
}
