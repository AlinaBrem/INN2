#include "texture.cpp"
#include "sprite.cpp"
#include "linked_list.cpp"
#include "player.h"
#include "enemy.h"
#include "computer.h"
#include "door.h"
#include "key.h"
#include "trap.h"
#include "enum.h"
#include "bottle.h"

#ifndef MAP
#define MAP

#define FACTOR 8
#define FRAME_PERIOD 2
#define TEXTURE_WIDTH 8
#define TEXTURE_HEIGHT 8
#define BOTTLE_WIDTH 4
#define BOTTLE_HEIGHT 4

struct Distance_pp
{
    Distance_pp() : point(0, 0){};
    Distance_pp(Point p, int d) : point(p), distance(d){};
    Point point;
    uint8_t distance;
};

class Map
{
private:
    // META DATA
    TileType tile_type_grid[80][64];
    Point dimensions = Point(80, 64);
    Point neighbors[4] = { Point(-1, 0), Point(0, -1), Point(1, 0), Point(0, 1) };

public:
  LinkedList<Sprite *> sprite_list = LinkedList<Sprite *>();

  // TODO: Move the Dynamic Entities Positions into their classes
  // DYNAMIC ENTITIES POSITIONS
  Point *start_pos = new Point(24, 56);
  Point *key_pos = new Point(8, 40);
  Point *computer_pos = new Point(8, 8);
  Point *door_pos = new Point(16, 24);
  Point *empty_bottle_pos = nullptr;
  Point *disarmed_trap_pos = nullptr;
  Point *green_door_pos = new Point(72, 40);

  // DYNAMIC ENTITIES
  Trap *test_trap = nullptr;
  Bottle *bottle = nullptr; // maybe rename to "flying_bottle"
  Key *test_key = new Key(key_pos->x, key_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, 45);
  Computer *test_computer = new Computer(computer_pos->x, computer_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, (int)ComputerTextureId::down_off, (int)Direction::down);
  Door *red_door = new Door(door_pos->x, door_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, (int)RedDoorTextureId::left_closed, (int)Direction::left, false);
  Player *test_player = new Player(start_pos->x, start_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, 60);
  Enemy *enemy = new Enemy(24, 24, TEXTURE_WIDTH, TEXTURE_HEIGHT, 80, Point(64, 8));
  Bottle *empty_bottle = nullptr;
  Trap *disarmed_trap = nullptr;
  Door *green_door = new Door(green_door_pos->x, green_door_pos->y, TEXTURE_WIDTH, TEXTURE_HEIGHT, (int)GreenDoorTextureId::left_closed, (int)Direction::left, true);


    Map()
    {
        for (int i = 0; i < 80; ++i) {   // for each row
          for (int j = 0; j < 64; ++j) { // for each column
            tile_type_grid[i][j] = not_solid;
          }
        }

        sprite_list.append_value(test_key);
      	sprite_list.append_value(red_door);
      	sprite_list.append_value(green_door);
      	sprite_list.append_value(enemy);
      	sprite_list.append_value(test_player);
      	sprite_list.append_value(test_computer);

        insert_type_at(*computer_pos, TileType::computer);
      	insert_type_at(*door_pos, TileType::red_door_closed);
        insert_type_at(*green_door_pos, TileType::green_door_closed);

        //Border right
        add_component(Sprite::new_wall_r(72, 8), solid);
        add_component(Sprite::new_wall_r(72, 16), solid);


        add_component(Sprite::new_wall_r(72, 24), solid);
        add_component(Sprite::new_sprite(72, 32, 59), solid);
        add_component(Sprite::new_wall_r(72, 48), solid);

        //Border bottom
        add_component(Sprite::new_wall_b(8, 56), solid);
        add_component(Sprite::new_wall_b(16, 56), solid);
        add_component(Sprite::new_wall_b(32, 56), solid);
        add_component(Sprite::new_wall_b(40, 56), solid);
        add_component(Sprite::new_wall_b(48, 56), solid);
        add_component(Sprite::new_wall_b(56, 56), solid);
        add_component(Sprite::new_wall_b(64, 56), solid);

        //Border left
        add_component(Sprite::new_wall_l(0, 8), solid);
        add_component(Sprite::new_wall_l(0, 16), solid);
        add_component(Sprite::new_wall_l(0, 24), solid);
        add_component(Sprite::new_sprite(0, 32, 58), solid);
        add_component(Sprite::new_wall_l(0, 40), solid);
        add_component(Sprite::new_wall_l(0, 48), solid);

        //Border Top
        add_component(Sprite::new_wall_t(8, 0), solid);
        add_component(Sprite::new_sprite(16, 0, 57), solid);
        add_component(Sprite::new_wall_t(24, 0), solid);
        add_component(Sprite::new_wall_t(32, 0), solid);
        add_component(Sprite::new_wall_t(40, 0), solid);
        add_component(Sprite::new_wall_t(48, 0), solid);
        add_component(Sprite::new_sprite(56, 0, 57), solid);
        add_component(Sprite::new_wall_t(64, 0), solid);

        // Border Corners
        add_component(Sprite::new_corner_tl(0, 0), solid);
        add_component(Sprite::new_corner_tr(72, 0), solid);
        add_component(Sprite::new_corner_bl(0, 56), solid);
        add_component(Sprite::new_corner_br(72, 56), solid);

        // Inner Walls
        add_component(Sprite::new_sprite(16, 8, 17), solid);

        add_component(Sprite::new_sprite(16, 16, 8), solid);
        add_component(Sprite::new_sprite(24, 16, 19), solid);
        add_component(Sprite::new_sprite(32, 16, 18), solid);
        add_component(Sprite::new_sprite(48, 16, 7), solid);
        add_component(Sprite::new_sprite(56, 16, 3), solid);

        add_component(Sprite::new_sprite(8, 32, 19), solid);
        add_component(Sprite::new_sprite(16, 32, 23), solid);
        add_component(Sprite::new_sprite(24, 32, 19), solid);
        add_component(Sprite::new_sprite(32, 32, 19), solid);
        add_component(Sprite::new_sprite(40, 32, 16), solid);
        add_component(Sprite::new_sprite(48, 32, 18), solid);
        add_component(Sprite::new_sprite(64, 32, 7), solid);

        add_component(Sprite::new_sprite(16, 40, 5), solid);
        add_component(Sprite::new_sprite(40, 40, 5), solid);

        add_component(Sprite::new_sprite(56, 8, 17), solid);
    };

    ~Map(){};

    void add_component(Sprite* sprite, TileType type) {
      sprite_list.append_value(sprite);
      Point pos = sprite->get_position() / FACTOR;
      tile_type_grid[pos.x][pos.y] = type;
    }

    // inserts a new object at the given position
    // and sets the type in the tile_type_grid
    void insert_type_at(Point position, TileType type)
    {
        int x = position.x / FACTOR;
        int y = position.y / FACTOR;

        this->tile_type_grid[x][y] = type;
    }

    // inserts a new object at the given position
    // and sets the type in the tile_type_grid if the tile is empty (not_solid)
    void insert_type_if_empty(Point position, TileType type)
    {
        int x = position.x / FACTOR;
        int y = position.y / FACTOR;

        if (this->is_type_at(position, TileType::not_solid))
        {
            this->tile_type_grid[x][y] = TileType::player;
        }
    }

    // return the tile_grid index of a position
    Point get_tile_grid_index(Point position)
    {
        int x = position.x / FACTOR;
        int y = position.y / FACTOR;

        return Point(x, y);
    }

    // returns true if a concrete type is at a given position
    // returns false if theres any ohter type
    bool is_type_at(Point position, TileType type)
    {
        int x = position.x / FACTOR;
        int y = position.y / FACTOR;

        return this->tile_type_grid[x][y] == type;
    }

    // delete type at a given position
    void delete_type_at(Point position, TileType type)
    {
        if (this->is_type_at(position, type))
        {
            this->insert_type_at(position, TileType::not_solid);
        }
    }

    // prints the index of a given point in the tile_grid
    void print_tile_grid_index_at(Point position)
    {
        int x = position.x / FACTOR;
        int y = position.y / FACTOR;

        gb.display.print("x: ");
        gb.display.println(x);
        gb.display.print("y: ");
        gb.display.println(y);
    }

    // prints the type of the tile at a given position
    void print_tile_type_at(Point position)
    {
        gb.display.println(this->get_tile_type_at(position));
    }

    // returns the type of the Point in the tile_grid as string
    String get_tile_type_at(Point position)
    {
        int x = position.x / FACTOR;
        int y = position.y / FACTOR;

        auto type = this->tile_type_grid[x][y];

        switch (type)
        {
        case TileType::solid:
            return "solid";

        case TileType::not_solid:
            return "not_solid";

        case TileType::key:
            return "key";

        case TileType::computer:
            return "computer";

        case TileType::red_door_closed:
            return "red_door_closed";

        case TileType::red_door_open:
            return "red_door_open";

        case TileType::player:
            return "player";

        case TileType::trap:
            return "trap";

        case TileType::green_door_closed:
            return "green_door_closed";

        case TileType::green_door_open:
            return "green_door_open";

        default:
            return "not_solid";
        }
    }

    //returns pointer to array of distances to target point for all tiles in tilegrid
    uint8_t *get_path_grid(Point target_point)
    {
        int x = target_point.x / FACTOR;
        int y = target_point.y / FACTOR;
        uint8_t *path_grid = new uint8_t[80]; //10*8

        for (int i = 0; i < 80; i++)
        {
            path_grid[i] = 80;
        }

        LinkedList<Distance_pp> distance_pp;
        distance_pp.append_value({Point(x, y), 0});
        LinkedList<Distance_pp>::Iterator iterator = distance_pp.get_Iterator();
        path_grid[x + y * 10] = tile_type_grid[x][y] == not_solid || tile_type_grid[x][y] == trap ? 0 : 80;
        Distance_pp *current;

        while (iterator.has_next())
        {
            current = iterator.get_next();

            for (Point neighbor : neighbors)
            {
                Point current_point = current->point + neighbor;
                if (current_point.x >= 0 && current_point.x < 10 && current_point.y >= 0 && current_point.y < 8 && path_grid[current_point.x + current_point.y * 10] == 80)
                {
                    if (this->tile_type_grid[current_point.x][current_point.y] == not_solid || this->tile_type_grid[current_point.x][current_point.y] == trap || this->tile_type_grid[current_point.x][current_point.y] == red_door_open)
                    {
                        path_grid[(current_point.x) + (current_point.y * 10)] = current->distance + 1;
                        distance_pp.append_value({current_point, current->distance + 1});
                    }
                    else if (this->tile_type_grid[current_point.x][current_point.y] == red_door_closed)
                    {
                        path_grid[current_point.x + current_point.y * 10] = 75;
                        distance_pp.append_value({current_point, current->distance + 1});
                    }
                    else
                    {
                        path_grid[current_point.x + current_point.y * 10] = 70;
                    }
                }
            }
        }

        return path_grid;
    }

    //checks if there is a line of sight between two given points on the map
    bool line_of_sight(Direction direction, Point a, Point b)
    {
        int delta_x = b.x - a.x;
        int delta_y = b.y - a.y;

        //check if basic direction is valid
        switch (direction)
        {
        case Direction::right:
            if (a.x > b.x || abs(delta_y) > 10)
            {
                return false;
            }

            break;

        case Direction::down:
            if (a.y > b.y || abs(delta_x) > 10)
            {
                return false;
            }

            break;

        case Direction::left:
            if (a.x < b.x || abs(delta_y) > 10)
            {
                return false;
            }

            break;

        case Direction::up:
            if (a.y < b.y || abs(delta_x) > 10)
            {
                return false;
            }

            break;
        }

        //if so, check cell by cell in the correct direction
        Point current_grid_cell = Point(a.x / 8, a.y / 8);
        Point current_pixel_point = Point(a.x, a.y);
        int number_of_steps = sqrt(pow(delta_x, 2) + pow(delta_y, 2));

        for (int i = 0; i < number_of_steps; i++)
        {
            current_pixel_point = Point(a.x + i * delta_x / number_of_steps, a.y + i * delta_y / number_of_steps);
            if (current_grid_cell != current_pixel_point / 8)
            {
                current_grid_cell = current_pixel_point / 8;
                if (tile_type_grid[current_grid_cell.x][current_grid_cell.y] == TileType::solid || tile_type_grid[current_grid_cell.x][current_grid_cell.y] == TileType::computer)
                {
                    return false;
                }
            }
        }

        return true;
    }
};
#endif
