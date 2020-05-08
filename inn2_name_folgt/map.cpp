#include "sprite.cpp"
#include "linked_list.cpp"
#ifndef MAP
#define MAP

#define FACTOR 8

enum TileType
{
    solid,
    not_solid,
    key,
    computer,
    door
};

struct Distance_pp
{
    Distance_pp() : point(0,0){};
    Distance_pp(Point p, int d) : point(p), distance(d){};
    Point point;
    uint8_t distance;
};

class Map
{
private:
    Point dimensions;
    TileType **tile_type_grid;
    Point neighbors[4];
    Map(int w, int h) : dimensions(w, h), neighbors {Point(-1, 0), Point(0, -1), Point(1, 0), Point(0, 1)}
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
    static Map load_map1(LinkedList<Sprite *> *ll)
    {
        Map map1 = Map(80, 64);

        ll->append_value(Sprite::new_corner_tl(0, 0));
        map1.tile_type_grid[0][0] = solid;
        ll->append_value(Sprite::new_corner_tr(72, 0));
        map1.tile_type_grid[9][0] = solid;
        ll->append_value(Sprite::new_corner_bl(0, 56));
        map1.tile_type_grid[0][7] = solid;
        ll->append_value(Sprite::new_corner_br(72, 56));
        map1.tile_type_grid[9][7] = solid;

        //wand rechts
        for (int i = 1; i < 7; i++)
        {
            ll->append_value(Sprite::new_wall_r(72, i * 8));
            map1.tile_type_grid[9][i] = solid;
        }
        //wand unten
        for (int i = 1; i < 9; i++)
        {
            ll->append_value(Sprite::new_wall_b(i * 8, 56));
            map1.tile_type_grid[i][7] = solid;
        }

        //wand links
        ll->append_value(Sprite::new_wall_l(0, 8));
        map1.tile_type_grid[0][1] = solid;
        ll->append_value(Sprite::new_wall_l(0, 16));
        map1.tile_type_grid[0][2] = solid;
        ll->append_value(Sprite::new_wall_l(0, 24));
        map1.tile_type_grid[0][3] = solid;
        ll->append_value(Sprite::new_sprite(0, 32, 58));
        map1.tile_type_grid[0][4] = solid;
        ll->append_value(Sprite::new_wall_l(0, 40));
        map1.tile_type_grid[0][5] = solid;
        ll->append_value(Sprite::new_wall_l(0, 48));
        map1.tile_type_grid[0][6] = solid;

        ll->append_value(Sprite::new_sprite(8, 32, 19));
        map1.tile_type_grid[1][4] = solid;
        ll->append_value(Sprite::new_sprite(16, 32, 19));
        map1.tile_type_grid[2][4] = solid;
        ll->append_value(Sprite::new_sprite(24, 32, 18));
        map1.tile_type_grid[3][4] = solid;

        //wand oben
        ll->append_value(Sprite::new_wall_t(8, 0));
        map1.tile_type_grid[1][0] = solid;
        ll->append_value(Sprite::new_wall_t(16, 0));
        map1.tile_type_grid[2][0] = solid;
        ll->append_value(Sprite::new_sprite(24, 0, 57));
        map1.tile_type_grid[3][0] = solid;
        ll->append_value(Sprite::new_wall_t(32, 0));
        map1.tile_type_grid[4][0] = solid;
        ll->append_value(Sprite::new_wall_t(40, 0));
        map1.tile_type_grid[5][0] = solid;
        ll->append_value(Sprite::new_wall_t(48, 0));
        map1.tile_type_grid[6][0] = solid;
        ll->append_value(Sprite::new_wall_t(56, 0));
        map1.tile_type_grid[7][0] = solid;
        ll->append_value(Sprite::new_wall_t(64, 0));
        map1.tile_type_grid[8][0] = solid;

        ll->append_value(Sprite::new_sprite(24, 8, 17));
        map1.tile_type_grid[3][1] = solid;
        ll->append_value(Sprite::new_sprite(24, 16, 5));
        map1.tile_type_grid[3][2] = solid;

        return map1;
    }
    bool solid_at_position(Point p)
    {
        int x = p.x / FACTOR;
        int y = p.y / FACTOR;
        if (tile_type_grid[x][y] == solid)
        {
            return true;
        }
        return false;
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

    // returns true if a concrete type is at a given position
    // returns false if theres any ohter type
    bool is_type_at(Point position, TileType type)
    {
        int x = position.x / FACTOR;
        int y = position.y / FACTOR;

        return this->tile_type_grid[x][y] == type;
    }

    // delete type at a given position
    // also deletes the sprite from the LinkedList
    void delete_type_at(Point position, LinkedList<Sprite *> *ll, int i)
    {
        if(ll->try_delete(i))
        {
            this->insert_type_at(position, TileType::not_solid);
        }
    }

   //returns pointer to array of distances to target point for all tiles in tilegrid
   uint8_t * get_path_grid(Point target_point)
   {
      int x = target_point.x / FACTOR;
      int y = target_point.y / FACTOR;
      uint8_t * path_grid = new uint8_t[80]; //10*8
      for (int i = 0; i < 80; i++)
        path_grid[i] = 80;
      LinkedList<Distance_pp> distance_pp;
      distance_pp.append_value({ Point(x,y), 0});
      auto iterator = distance_pp.get_Iterator();
      auto current = &distance_pp.start->value;
      while(42)
      {
        path_grid[(current->point.x)+(current->point.y*10)] = current->distance;
        for(Point neighbor: neighbors)
        {
          Point current_point = current->point+neighbor;
          if (current_point.x >= 0 && current_point.x < 10 && current_point.y >= 0 && current_point.y < 8 && path_grid[current_point.x+current_point.y*10] == 80)
          {
            path_grid[current_point.x+current_point.y*10] = 70;
            if (this->tile_type_grid[current_point.x][current_point.y] == not_solid)
            {
              distance_pp.append_value({ current_point, current->distance+1});
            }
          }
        }
        if (iterator.has_next())
          current = iterator.get_next();
        else break;
      }
      return path_grid;
   }
};
#endif
