
#include "sprite.cpp"
#include "linked_list.cpp"
#ifndef MAP
#define MAP

enum TileType
{
    solid,
    not_solid
};

class Map
{
private:
    Point dimensions;
    TileType **tile_type_grid;
    Map(int w, int h) : dimensions(w, h)
    {
        int grid_width = dimensions.x / 8;
        int grid_height = dimensions.y / 8;

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
        int x = p.x / 8;
        int y = p.y / 8;
        if (tile_type_grid[x][y] == solid)
        {
            return true;
        }
        return false;
    }
    ~Map(){};
};
#endif
