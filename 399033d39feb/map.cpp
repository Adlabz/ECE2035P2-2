#include "map.h"

#include "globals.h"
#include "graphics.h"

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items;
    int w, h;
};

/**
 * Storage area for the maps.
 * This is a global variable, but can only be access from this file because it
 * is static.
 */
static Map map;
static int active_map;

/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y) {
    int x = X * 256;//any power of 2 greater than H
    unsigned ret = x + Y;
    return ret;
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    int Y = key%256;
    unsigned y = Y;
    return y;
}

void maps_init()
{
    map.w = 75;
    map.h = 75;
    HashTable* table = createHashTable(map_hash, 256);
    add_wall(0 , 0, HORIZONTAL, 99);
    add_wall(0 , 99, HORIZONTAL, 99);
    add_wall(0 , 0, VERTICAL, 99);
    add_wall(99 , 0, VERTICAL, 99);
}

Map* get_active_map()
{
    // There's only one map
    return &map;
}

Map* set_active_map(int m)
{
    active_map = m;
    return &map;
}

void print_map()
{
    // As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'P'};
    for(int y = 0; y < map_height(); y++)
    {
        for (int x = 0; x < map_width(); x++)
        {
            MapItem* item = get_here(x,y);
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}

int map_width()
{
    return map.w;
}

int map_height()
{
    return map.h;
}

int map_area()
{
    return map.w * map.h;
}

MapItem* get_north(int x, int y)
{
    return (MapItem*) getItem(map.items, XY_KEY(x, y+1));
}

MapItem* get_south(int x, int y)
{
    return (MapItem*) getItem(map.items, XY_KEY(x, y-1));
}

MapItem* get_east(int x, int y)
{
    return (MapItem*) getItem(map.items, XY_KEY(x-1, y));
}

MapItem* get_west(int x, int y)
{
    return (MapItem*) getItem(map.items, XY_KEY(x+1, y+1));
}

MapItem* get_here(int x, int y)
{
    return (MapItem*) getItem(map.items, XY_KEY(x, y));
}


void map_erase(int x, int y)
{
    removeItem(map.items, XY_KEY(x, y));
}

void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
