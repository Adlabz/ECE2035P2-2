#ifndef MAP_H
#define MAP_H

#include "hash_table.h"

/**
 * A structure to represent the map. The implementation is private.
 */
struct Map;

// A function pointer type for drawing MapItems.
// All tiles are 11x11 blocks.
// u,v is the top left corner pixel of the block
typedef void (*DrawFunc)(int u, int v);

/**
 * The data for elements in the map. Each item in the map HashTable is a
 * MapItem.
 */
typedef struct {
    /**
     * Indicates the "type" of the MapItem: WALL, DOOR, PLANT, etc. This is
     * useful for determining how to interact with the object when updating the
     * game state.
     */
    int type;

    /**
     * A function pointer to the drawing function for this item. Used by draw_game.
     */
    DrawFunc draw;

    /**
     * If zero, this item should block character motion.
     */
    int walkable;
} MapItem;

typedef struct {
    int tm;
    int tx, ty;
} StairsData;

// MapItem types
// Define more of these!
#define WALL    0
#define PLANT   1
#define CAVE_ENTRY 2
#define CAVE_ENTRY_OPENING 3
#define CAVE_WALL 4
#define CAVE_FLOOR 5
#define NPC1 6
#define NPC2 7
#define NPC3 8
#define NPC4 9
#define NPC5 10
#define NPC6 11

/**
 * Initializes the internal structures for all maps. This does not populate
 * the map with items, but allocates space for them, initializes the hash tables,
 * and sets the width and height.
 */
void maps_init();
void caves_init();

/**
 * Returns a pointer to the active map.
 */
Map* get_active_map();
/**
 * returns index of current map
 */
int get_active_map_no();

/**
 * Sets the active map to map m, where m is the index of the map to activate.
 * Returns a pointer to the new active map.
 */
Map* set_active_map(int m);

/**
 * Returns the map m, regardless of whether it is the active map. This function
 * does not change the active map.
 */
Map* get_map(int m);

/**
 * Print the active map to the serial console.
 */
void print_map();

// Access
/**
 * Returns the width of the active map.
 */
int map_width();

/**
 * Returns the heigh of the active map.
 */
int map_height();

/**
 * Returns the total number of cells in the active map.
 */
int map_area();

/**
 * Returns the MapItem immediately above the given location.
 */
MapItem* get_north(int x, int y);

/**
 * Returns the MapItem immediately below the given location.
 */
MapItem* get_south(int x, int y);

/**
 * Returns the MapItem immediately to the right of the given location.
 */
MapItem* get_east(int x, int y);

/**
 * Returns the MapItem immediately to the left of  the given location.
 */
MapItem* get_west(int x, int y);

/**
 * Returns the MapItem at the given location.
 */
MapItem* get_here(int x, int y);

// Directions, for using the modification functions
#define HORIZONTAL  0
#define VERTICAL    1

/**
 * If there is a MapItem at (x,y), remove it from the map.
 */
void map_erase(int x, int y);

/**
 * Add WALL items in a line of length len beginning at (x,y).
 * If dir == HORIZONTAL, the line is in the direction of increasing x.
 * If dir == VERTICAL, the line is in the direction of increasing y.
 *
 * If there are already items in the map that collide with this line, they are
 * erased.
 */
void add_wall(int x, int y, int dir, int len);

/**
 * Add a PLANT item at (x,y). If there is already a MapItem at (x,y), erase it
 * before adding the plant.
 */
void add_plant(int x, int y);
/**
 * Add a CAVE_ENTRY item at (x,y). If there is already a MapItem at (x,y), erase it
 * before adding the entry.
 */
void add_cave_entry(int x, int y);
/**
 * Animate the opening of a CAVE_ENTRY item at (x,y). If there is already a MapItem at (x,y), erase it
 * before adding the opened cave.
 */
void set_cave_opening(int x, int y);
//Functions for cave elements which look and behave differently than their counterparts in the main map
void add_cave_wall(int x, int y);
void add_cave_floor(int x, int y);
//n is for which NPC draw function to use
void add_unmoving_NPC(int x, int y, int n);

#endif //MAP_H
