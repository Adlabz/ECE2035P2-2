#ifndef GRAPHICS_H
#define GRAPHICS_H


/**
 * Draws the player. This depends on the player state, so it is not a DrawFunc.
 */
void draw_player(int u, int v, int key);

/**
 * Takes a string image and draws it to the screen. The string is 121 characters
 * long, and represents an 11x11 tile in row-major ordering (across, then down,
 * like a regular multi-dimensional array). The available colors are:
 *      R = Red
 *      Y = Yellow
 *      G = Green
 *      D = Brown ("dirt")
 *      5 = Light grey (50%)
 *      3 = Dark grey (30%)
 *      Any other character is black
 * More colors can be easily added by following the pattern already given.
 */
void draw_img(int u, int v, const char* img);

/**
 * DrawFunc functions.
 * These can be used as the MapItem draw functions.
 */
void draw_nothing(int u, int v);
void draw_wall(int u, int v);
void draw_plant(int u, int v);
void draw_NPC(int u, int v);
void draw_cave_entry(int u, int v);
void draw_cave_opening(int u, int v);
void draw_cave_opened(int u, int v);
void draw_cave_wall(int u, int v);
void draw_cave_floor(int u, int v);
void draw_Wizard(int u, int v);
void draw_NPC_green(int u, int v);
void draw_NPC_orange(int u, int v);
void draw_NPC_yellow(int u, int v);
void draw_NPC_white(int u, int v);
void draw_NPC_brown(int u, int v);
void draw_treasure(int u, int v);
void draw_open_treasure(int u, int v);
void draw_door(int u, int v);
void draw_opening_door(int u, int v);
void draw_opened_door(int u, int v);
void draw_edge_bridge(int u, int v);
void draw_edge_player(int u, int v);

/**
 * Draw the upper status bar.
 */
void draw_upper_status(int xx, int yy, int hh);

/**
 * Draw the lower status bar.
 */
void draw_lower_status();
/**
 * indicate that omnipotent has been turned off
 */
void un_lower_status();

/**
 * Draw the border for the map.
 */
void draw_border();

#endif // GRAPHICS_H
