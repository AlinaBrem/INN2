#include "player.h"

Player::Player(int x, int y, int w, int h, int t) : Sprite(x, y, w, h, t)
{
    this->width = w;
    this->height = h;
    this->speed = 1;
    this->health = 1;
    this->is_dead = false;
    this->frame_counter = 0;
    this->number_animation = 0;
    this->direction = Direction::up;
    this->is_interacting = false;
    this->trap_count = 1;
    this->current_item_index = 0;

    this->add_item(BOTTLE);
    this->add_item(TRAP);
    this->reset_collision_points();
};

Point *Player::get_collision_points()
{
    // get collision points
    auto *points = new Point[NUM_COLLISION_POINTS]{
        // front_left
        Point(this->position.x + 1, this->position.y),
        // front_right
        Point(this->position.x + this->width - 1, this->position.y),
        // back_left
        Point(this->position.x + 1, this->position.y + this->height),
        // back_right
        Point(this->position.x + this->width - 1, this->position.y + this->height),
        // middle_left_front
        Point(this->position.x, this->position.y + 1),
        // middle_left_back
        Point(this->position.x, this->position.y + this->height - 1),
        // middle_right_front
        Point(this->position.x + this->width, this->position.y + 1),
        // middle_right_back
        Point(this->position.x + this->width, this->position.y + this->height - 1)};

    return points;
}

int Player::get_health()
{
    return this->health;
}

void Player::set_is_interacting(bool value)
{
    this->is_interacting = value;

    if (value)
    {
        this->interact();
    }
    else
    {
        this->idle();
    }
}

bool Player::get_is_interacting()
{
    return this->is_interacting;
}

void Player::set_is_colliding(bool value, int i)
{
    switch ((CollisionPoints)i)
    {
    case CollisionPoints::front_left:
        this->is_colliding_front_left = value;
        break;

    case CollisionPoints::front_right:
        this->is_colliding_front_right = value;
        break;

    case CollisionPoints::back_left:
        this->is_colliding_back_left = value;
        break;

    case CollisionPoints::back_right:
        this->is_colliding_back_right = value;
        break;

    case CollisionPoints::middle_left_front:
        this->is_colliding_middle_left_front = value;
        break;

    case CollisionPoints::middle_left_back:
        this->is_colliding_middle_left_back = value;
        break;

    case CollisionPoints::middle_right_front:
        this->is_colliding_middle_right_front = value;
        break;

    case CollisionPoints::middle_right_back:
        this->is_colliding_middle_right_back = value;
        break;

    default:
        break;
    }
}

void Player::set_is_colliding(bool value)
{
    switch (this->direction)
    {
    case Direction::up:
        this->is_colliding_front_left = value;
        this->is_colliding_front_right = value;
        break;

    case Direction::down:
        this->is_colliding_back_left = value;
        this->is_colliding_back_right = value;
        break;

    case Direction::left:
        this->is_colliding_middle_left_front = value;
        this->is_colliding_middle_left_back = value;
        break;

    case Direction::right:
        this->is_colliding_middle_right_front = value;
        this->is_colliding_middle_right_back = value;
        break;

    default:
        break;
    }
}

void Player::reset_collision_points()
{
    this->is_colliding_front_left = false;
    this->is_colliding_front_right = false;

    this->is_colliding_back_left = false;
    this->is_colliding_back_right = false;

    this->is_colliding_middle_right_front = false;
    this->is_colliding_middle_right_back = false;

    this->is_colliding_middle_left_front = false;
    this->is_colliding_middle_left_back = false;
}

void Player::move_up()
{
    this->direction = Direction::up;
    if (!this->is_colliding_front_left && !this->is_colliding_front_right)
    {
        this->position.y--;

        this->set_is_interacting(false);
        this->play_walk_animation(PlayerTextureId::move_up);
        this->reset_collision_points();
    }
}

void Player::move_down()
{
    this->direction = Direction::down;
    if (!this->is_colliding_back_left && !this->is_colliding_back_right)
    {
        this->position.y++;

        this->set_is_interacting(false);
        this->play_walk_animation(PlayerTextureId::move_down);
        this->reset_collision_points();
    }
}

void Player::move_right()
{
    this->direction = Direction::right;
    if (!this->is_colliding_middle_right_front && !this->is_colliding_middle_right_back)
    {
        this->position.x++;

        this->set_is_interacting(false);
        this->play_walk_animation(PlayerTextureId::move_right);
        this->reset_collision_points();
    }
}

void Player::move_left()
{
    this->direction = Direction::left;
    if (!this->is_colliding_middle_left_front && !this->is_colliding_middle_left_back)
    {
        this->position.x--;

        this->set_is_interacting(false);
        this->play_walk_animation(PlayerTextureId::move_left);
        this->reset_collision_points();
    }
}

void Player::idle()
{
    switch (this->direction)
    {
    case Direction::up:
        this->tex_id = (int)PlayerTextureId::idle_up;
        break;

    case Direction::down:
        this->tex_id = (int)PlayerTextureId::idle_down;
        break;

    case Direction::left:
        this->tex_id = (int)PlayerTextureId::idle_left;
        break;

    case Direction::right:
        this->tex_id = (int)PlayerTextureId::idle_right;
        break;

    default:
        break;
    }
}

void Player::interact()
{
    switch (this->direction)
    {
    case Direction::up:
        this->tex_id = (int)PlayerTextureId::interacting_up;
        break;

    case Direction::down:
        this->tex_id = (int)PlayerTextureId::interacting_down;
        break;

    case Direction::left:
        this->tex_id = (int)PlayerTextureId::interacting_left;
        break;

    case Direction::right:
        this->tex_id = (int)PlayerTextureId::interacting_right;
        break;

    default:
        break;
    }
}

void Player::play_walk_animation(PlayerTextureId start_texture_id)
{
    this->tex_id = (int)start_texture_id;

    if (this->number_animation == 2)
    {
        this->tex_id += 1;
    }
    else if (this->number_animation == 1 || this->number_animation == 3)
    {
        this->tex_id += 2;
    }
    this->number_animation = (this->number_animation + 1) % 4;
}

void Player::print_collision_points()
{
    // front_left
    gb.display.setColor(this->is_colliding_front_left ? YELLOW : WHITE);
    gb.display.drawLine(this->position.x + 1, this->position.y,
                        this->position.x + 1, this->position.y);
    // front_right
    gb.display.setColor(this->is_colliding_front_right ? YELLOW : WHITE);
    gb.display.drawLine(this->position.x + this->width - 1, this->position.y,
                        this->position.x + this->width - 1, this->position.y);
    // back_left
    gb.display.setColor(this->is_colliding_back_left ? YELLOW : WHITE);
    gb.display.drawLine(this->position.x + 1, this->position.y + this->height,
                        this->position.x + 1, this->position.y + this->height);
    // back_right
    gb.display.setColor(this->is_colliding_back_right ? YELLOW : WHITE);
    gb.display.drawLine(this->position.x + this->width - 1, this->position.y + this->height,
                        this->position.x + this->width - 1, this->position.y + this->height);
    // middle_left_front
    gb.display.setColor(this->is_colliding_middle_left_front ? YELLOW : WHITE);
    gb.display.drawLine(this->position.x, this->position.y + 1,
                        this->position.x, this->position.y + 1);
    // middle_left_back
    gb.display.setColor(this->is_colliding_middle_left_back ? YELLOW : WHITE);
    gb.display.drawLine(this->position.x, this->position.y + this->height - 1,
                        this->position.x, this->position.y + this->height - 1);
    // middle_right_front
    gb.display.setColor(this->is_colliding_middle_right_front ? YELLOW : WHITE);
    gb.display.drawLine(this->position.x + this->width, this->position.y + 1,
                        this->position.x + this->width, this->position.y + 1);
    // middle_right_back
    gb.display.setColor(this->is_colliding_middle_right_back ? YELLOW : WHITE);
    gb.display.drawLine(this->position.x + this->width, this->position.y + this->height - 1,
                        this->position.x + this->width, this->position.y + this->height - 1);
}

Point Player::get_position()
{
    return this->position;
}

void Player::print_message(String message)
{
    gb.display.println(message);
}

Point Player::get_interaction_point()
{
    switch (this->direction)
    {
    case Direction::up:
        return Point((this->position.x + this->width / 2), (this->position.y - 1));

    case Direction::down:
        return Point((this->position.x + this->width / 2), (this->position.y + this->height + 1));

    case Direction::left:
        return Point((this->position.x - 1), (this->position.y + this->height / 2));

    case Direction::right:
        return Point((this->position.x + this->width + 1), (this->position.y + this->height / 2));

    default:
        return Point((this->position.x + this->width / 2), (this->position.y - 1));
    }
}

void Player::print_interaction_points()
{
    gb.display.setColor(BLUE);

    // front_middle
    gb.display.drawLine(this->position.x + this->width / 2, this->position.y - 1,
                        this->position.x + this->width / 2, this->position.y - 1);

    // back_middle
    gb.display.drawLine(this->position.x + this->width / 2, this->position.y + this->height + 1,
                        this->position.x + this->width / 2, this->position.y + this->height + 1);

    // middle_right_center
    gb.display.drawLine(this->position.x + this->width + 1, this->position.y + this->height / 2,
                        this->position.x + this->width + 1, this->position.y + this->height / 2);

    // middle_left_center
    gb.display.drawLine(this->position.x - 1, this->position.y + this->height / 2,
                        this->position.x - 1, this->position.y + this->height / 2);
}

int Player::get_trap_count()
{
    return this->trap_count;
}

void Player::set_trap_count(int value)
{
    this->trap_count += value;

    if (this->trap_count < 0)
    {
        this->trap_count = 0;
    }

    if(this->trap_count == 0)
    {
        this->delete_item(TRAP);
    }
}

void Player::add_item(String item)
{
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        if (this->inventory[i] == "")
        {
            this->inventory[i] = item;
            return;
        }
    }
}

void Player::delete_item(String item)
{
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        if (this->inventory[i] == item)
        {
            this->inventory[i] = "";
            return;
        }
    }
}

void Player::print_current_item()
{
    while (this->inventory[this->current_item_index] == "")
    {
        this->next_item();
    }

    gb.display.println(this->inventory[this->current_item_index]);
}

String Player::get_current_item()
{
    return this->inventory[this->current_item_index];
}

void Player::next_item()
{
    this->current_item_index = (this->current_item_index + 1) % 3;
}