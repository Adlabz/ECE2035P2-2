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
static Map cave;
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
    return key%256;
}

void maps_init()
{
    map.w = 60;
    map.h = 60;
    HashTable* table = createHashTable(map_hash, 256);
    map.items = table;
}

void caves_init()
{
    cave.w = 20;
    cave.h = 20;
    HashTable* table = createHashTable(map_hash, 256);
    cave.items = table;
}

Map* get_active_map()
{
    // There's only one map
    switch(active_map) {
        case 0:
            return &map;
        case 1:
            return &cave;
        default:
            return &map;
    }
}

int get_active_map_no() {
    return active_map;
}
Map* set_active_map(int m)
{
    active_map = m;
    switch(m) {
        case 0:
            return &map;
        case 1:
            return &cave;
        default:
            return &map;
    }
}

void print_map()
{
    // As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'P', 'C', 'O'};
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
    return get_active_map()->w;
}

int map_height()
{
    return get_active_map()->h;
}

int map_area()
{
    return get_active_map()->w * get_active_map()->h;
}

MapItem* get_north(int x, int y)
{
    return (MapItem*) getItem(get_active_map()->items, XY_KEY(x, y+1));
}

MapItem* get_south(int x, int y)
{
    return (MapItem*) getItem(get_active_map()->items, XY_KEY(x, y-1));
}

MapItem* get_east(int x, int y)
{
    return (MapItem*) getItem(get_active_map()->items, XY_KEY(x+1, y));
}

MapItem* get_west(int x, int y)
{
    return (MapItem*) getItem(get_active_map()->items, XY_KEY(x-1, y));
}

MapItem* get_here(int x, int y)
{
    return (MapItem*) getItem(get_active_map()->items, XY_KEY(x, y));
}


void map_erase(int x, int y)
{
    removeItem(get_active_map()->items, XY_KEY(x, y));
}

void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
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


    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);

    if (val) free(val); // If something is already there, free it

}

void add_cave_entry(int x, int y)
{

    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));

    w1->type = CAVE_ENTRY;

    w1->draw = draw_cave_entry;

    w1->walkable = false;


    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);

    if (val) free(val); // If something is already there, free it

}



void set_cave_opening(int x, int y)
{

    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));

    w1->type = CAVE_ENTRY_OPENING;

    w1->draw = draw_cave_opening;

    w1->walkable = false;


    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);

    if (val) free(val); // If something is already there, free it

}

void add_cave_wall(int x, int y)
{

    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));

    w1->type = CAVE_WALL;

    w1->draw = draw_cave_wall;

    w1->walkable = false;


    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);

    if (val) free(val); // If something is already there, free it

}

void add_cave_floor(int x, int y)
{

    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));

    w1->type = CAVE_FLOOR;

    w1->draw = draw_cave_floor;

    w1->walkable = true;


    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);

    if (val) free(val); // If something is already there, free it

}
void add_unmoving_NPC(int x, int y, int n) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    int z = n + 5;
    w1->type = z;
    switch(n) {
        case 1:
            w1->draw = draw_Wizard;
            break;
        case 2:
            w1->draw = draw_NPC_green;
            break;
        case 3:
            w1->draw = draw_NPC_orange;
            break;
        case 4:
            w1->draw = draw_NPC_yellow;
            break;
        case 5:
            w1->draw = draw_NPC_white;
            break;
        case 6:
            w1->draw = draw_NPC_brown;
            break;
    }

    w1->walkable = false;


    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);

    if (val) free(val); // If something is already there, free it
}
void add_treasure(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));

    w1->type = TREASURE;

    w1->draw = draw_treasure;

    w1->walkable = false;


    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);

    if (val) free(val); // If something is already there, free it
}
void add_door(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));

    w1->type = DOOR;

    w1->draw = draw_door;

    w1->walkable = false;


    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);

    if (val) free(val); // If something is already there, free it
}
void add_bridge_path(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));

    w1->type = BRIDGE;

    w1->draw = draw_wall;

    w1->walkable = true;


    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);

    if (val) free(val); // If something is already there, free it
}
void add_bridge_edge(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));

    w1->type = EDGE;

    w1->draw = draw_edge_bridge;

    w1->walkable = true;


    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);

    if (val) free(val); // If something is already there, free it
}
