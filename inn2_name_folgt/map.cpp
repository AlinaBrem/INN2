#include "sprite.cpp"
#include "linked_list.cpp"
#include "enum.h"

#ifndef MAP
#define MAP

#define FACTOR 8

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
    TileType **tile_type_grid;
    Point dimensions;
    Point neighbors[4];

    Map(int w, int h) : dimensions(w, h), neighbors{Point(-1, 0), Point(0, -1), Point(1, 0), Point(0, 1)}
    {
        int grid_width = dimensions.x / FACTOR;
        int grid_height = dimensions.y / FACTOR;

        tile_type_grid = (TileType **)malloc(sizeof(TileType *) * grid_width);
        for (int i = 0; i < grid_width; i++)
        {
            tile_type_grid[i] = (TileType *)malloc(sizeof(TileType) * grid_height);
            for (int y = 0; y < grid_height; y++)
            {
                tile_type_grid[i][y] = not_solid;
            }
        }
    };

public:
    static Map *load_map1(LinkedList<Sprite *> *ll)
    {
        Map *map1 = new Map(80, 64);

        ll->append_value(Sprite::new_corner_tl(0, 0));
        map1->tile_type_grid[0][0] = solid;
        ll->append_value(Sprite::new_corner_tr(72, 0));
        map1->tile_type_grid[9][0] = solid;
        ll->append_value(Sprite::new_corner_bl(0, 56));
        map1->tile_type_grid[0][7] = solid;
        ll->append_value(Sprite::new_corner_br(72, 56));
        map1->tile_type_grid[9][7] = solid;

        //wand rechts
        for (int i = 1; i < 7; i++)
        {
            ll->append_value(Sprite::new_wall_r(72, i * 8));
            map1->tile_type_grid[9][i] = solid;
        }

        //wand unten
        for (int i = 1; i < 9; i++)
        {
            ll->append_value(Sprite::new_wall_b(i * 8, 56));
            map1->tile_type_grid[i][7] = solid;
        }

        //wand links
        ll->append_value(Sprite::new_wall_l(0, 8));
        map1->tile_type_grid[0][1] = solid;
        ll->append_value(Sprite::new_wall_l(0, 16));
        map1->tile_type_grid[0][2] = solid;
        ll->append_value(Sprite::new_wall_l(0, 24));
        map1->tile_type_grid[0][3] = solid;
        ll->append_value(Sprite::new_sprite(0, 32, 58));
        map1->tile_type_grid[0][4] = solid;
        ll->append_value(Sprite::new_wall_l(0, 40));
        map1->tile_type_grid[0][5] = solid;
        ll->append_value(Sprite::new_wall_l(0, 48));
        map1->tile_type_grid[0][6] = solid;

        ll->append_value(Sprite::new_sprite(8, 32, 19));
        map1->tile_type_grid[1][4] = solid;
        ll->append_value(Sprite::new_sprite(16, 32, 19));
        map1->tile_type_grid[2][4] = solid;
        ll->append_value(Sprite::new_sprite(24, 32, 18));
        map1->tile_type_grid[3][4] = solid;

        //wand oben
        ll->append_value(Sprite::new_wall_t(8, 0));
        map1->tile_type_grid[1][0] = solid;
        ll->append_value(Sprite::new_wall_t(16, 0));
        map1->tile_type_grid[2][0] = solid;
        ll->append_value(Sprite::new_sprite(24, 0, 57));
        map1->tile_type_grid[3][0] = solid;
        ll->append_value(Sprite::new_wall_t(32, 0));
        map1->tile_type_grid[4][0] = solid;
        ll->append_value(Sprite::new_wall_t(40, 0));
        map1->tile_type_grid[5][0] = solid;
        ll->append_value(Sprite::new_wall_t(48, 0));
        map1->tile_type_grid[6][0] = solid;
        ll->append_value(Sprite::new_wall_t(56, 0));
        map1->tile_type_grid[7][0] = solid;
        ll->append_value(Sprite::new_wall_t(64, 0));
        map1->tile_type_grid[8][0] = solid;

        ll->append_value(Sprite::new_sprite(24, 8, 17));
        map1->tile_type_grid[3][1] = solid;
        ll->append_value(Sprite::new_sprite(24, 16, 5));
        map1->tile_type_grid[3][2] = solid;

        return map1;
    }
    static Map *load_map2(LinkedList<Sprite *> *ll)
    {
        Map *map1 = new Map(80, 64);

        ll->append_value(Sprite::new_corner_tl(0, 0));
        map1->tile_type_grid[0][0] = solid;
        ll->append_value(Sprite::new_corner_tr(72, 0));
        map1->tile_type_grid[9][0] = solid;
        ll->append_value(Sprite::new_corner_bl(0, 56));
        map1->tile_type_grid[0][7] = solid;
        ll->append_value(Sprite::new_corner_br(72, 56));
        map1->tile_type_grid[9][7] = solid;

        //wand rechts
        for (int i = 1; i < 7; i++)
        {
            ll->append_value(Sprite::new_wall_r(72, i * 8));
            map1->tile_type_grid[9][i] = solid;
        }

        //wand links
        for (int i = 1; i < 7; i++)
        {
            ll->append_value(Sprite::new_wall_l(0, i * 8));
            map1->tile_type_grid[0][i] = solid;
        }

        //wand unten
        for (int i = 1; i < 9; i++)
        {
            ll->append_value(Sprite::new_wall_b(i * 8, 56));
            map1->tile_type_grid[i][7] = solid;
        }

        //wand oben
        for (int i = 1; i < 9; i++)
        {
            ll->append_value(Sprite::new_wall_t(i * 8, 0));
            map1->tile_type_grid[i][0] = solid;
        }
        return map1;
    }

    ~Map(){};

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

        case TileType::door_closed:
            return "door_closed";

        case TileType::door_open:
            return "door_open";

        case TileType::player:
            return "player";

        case TileType::trap:
            return "trap";

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
                    if (this->tile_type_grid[current_point.x][current_point.y] == not_solid || this->tile_type_grid[current_point.x][current_point.y] == trap || this->tile_type_grid[current_point.x][current_point.y] == door_open)
                    {
                        path_grid[(current_point.x) + (current_point.y * 10)] = current->distance + 1;
                        distance_pp.append_value({current_point, current->distance + 1});
                    }
                    else if (this->tile_type_grid[current_point.x][current_point.y] == door_closed)
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
