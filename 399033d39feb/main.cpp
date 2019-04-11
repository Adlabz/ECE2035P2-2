// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"

// Functions in this file
int get_action (GameInputs inputs);
int update_game (int action);
void draw_game (int init);
void init_main_map ();
int main ();

/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;    // Current locations
    int px, py; // Previous locations
    int has_key;
    int omnipotent, pomnipotent;
} Player;

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define OMNI 7
int get_action(GameInputs inputs)
{
    if (inputs.b1 == 0) {
        return ACTION_BUTTON;
    }
    if (inputs.b2 == 0) {
        return MENU_BUTTON;
    }
    if (inputs.b3 == 0) {
        return OMNI;
    }
    double absX = inputs.ax;
    if (inputs.ax < 0) {
        absX = absX * (-1);
    }
    double absY = inputs.ay;
    if (inputs.ay < 0) {
        absY = absY * (-1);
    }
    double absZ = inputs.az;
    if (inputs.az < 0) {
        absZ = absZ * (-1);
    }
    double threshold = 2;
    MapItem* north = get_north(Player.x, Player.y);
    MapItem* south = get_south(Player.x, Player.y);
    MapItem* east = get_east(Player.x, Player.y);
    MapItem* west = get_west(Player.x, Player.y);
    if (absX * threshold > absZ || absY * threshold > absZ) {
        if (absX * 0.9 > absY) {
            if (inputs.ax < 0) {
                if (west->walkable != 0 || Player.omnipotent){
                    if (Player.x - 1 > 0) {
                        return GO_LEFT;
                    }
                }
            } else {
                if (east->walkable != 0 || Player.omnipotent){
                    if (Player.x + 1 < map_width()) {
                        return GO_RIGHT;
                    }
                }
            }
        } else if (absY * 0.9 > absX) {
            if (inputs.ay < 0) {
                if (north->walkable != 0 || Player.omnipotent){
                    if (Player.y + 1 < map_height()) {
                        return GO_UP;
                    }
                }
            } else {
                if (south->walkable != 0 || Player.omnipotent){
                    if (Player.y - 1 > 0) {
                        return GO_DOWN;
                    }
                }
            }
        }
    }
    return NO_ACTION;
}

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 *
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
int update_game(int action)
{
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    Player.pomnipotent = Player.omnipotent;

    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.
    switch(action)
    {
        case GO_UP:
            Player.y = Player.y + 1;
            return FULL_DRAW;
        case GO_LEFT:
            Player.x = Player.x - 1;
            return FULL_DRAW;
        case GO_DOWN:
            Player.y = Player.y - 1;
            return FULL_DRAW;
        case GO_RIGHT:
            Player.x = Player.x + 1;
            return FULL_DRAW;
        case ACTION_BUTTON: break;
        case MENU_BUTTON: break;
        case OMNI:
            if (Player.omnipotent) {
                Player.omnipotent = 0;
            } else {
                Player.omnipotent = 1;
            }
            break;
        default:        break;
    }
    return NO_RESULT;
}

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status
 * bars. Unless init is nonzero, this function will optimize drawing by only
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int init)
{
    // Draw game border first
    if(init) draw_border();

    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)

            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;

            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;

            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;

            // Figure out what to draw
            DrawFunc draw = NULL;
            if (i == 0 && j == 0) // Only draw the player on init
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) // Only draw if they're different or init
                {
                        draw = (curr_item)?curr_item->draw:draw_nothing;
                        draw(u, v);
                        draw_player(u, v, Player.has_key);
                }
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars
    draw_upper_status(Player.x, Player.y);
    if (Player.omnipotent && !Player.pomnipotent) {
        draw_lower_status();
    } else if (Player.pomnipotent && !Player.omnipotent) {
        un_lower_status();
    }
}


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    // "Random" plants

    Map* map = set_active_map(0);

    for(int i = map_width() + 3; i < map_area(); i += 39)
    {

        add_plant(i % map_width(), i / map_width());
    }

    pc.printf("plants\r\n");

    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());

    //top section of map
    add_wall(0, 8, HORIZONTAL, 16);
    add_wall(0, 18, HORIZONTAL, 16);
    add_wall(16, 8, VERTICAL, 11);
    add_wall(20, 0, VERTICAL, 18);
    add_wall(24, 0, VERTICAL, 22);
    add_wall(4, 22, HORIZONTAL, 21);
    add_wall(0, 26, HORIZONTAL, 45);

    //bumpy surface on major wall
    add_wall(20, 26, VERTICAL, 5);
    add_wall(20, 31, HORIZONTAL, 5);
    add_wall(25, 31, VERTICAL, 5);
    add_wall(25, 36, HORIZONTAL, 10);
    add_wall(34, 31, VERTICAL, 5);
    add_wall(34, 31, HORIZONTAL, 5);
    add_wall(39, 26, VERTICAL, 5);


    char[25][25] wallxy =
    {
        {'W','W','W','W','W','W','W','W','W',' ',' ',' ',' ',' ','W','W','W','W','W','W','W','W',' ',' ',' '},
        {'W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W',' ',' ',' '},
        {'W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W',' ',' ',' '},
        {'W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W',' ',' ',' '},
        {'W',' ',' ',' ',' ',' ',' ','W','W',' ',' ',' ',' ',' ','W','W',' ',' ',' ',' ',' ','W',' ',' ',' '},
        {'W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W',' ',' ',' '},
        {'W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' '},
        {'W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' '},
        {'W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W','W','W','W',' ',' ',' '},
        {'W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {'W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {'W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W','W','W','W','W','W','W'},
        {'W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' '},
        {'W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' '},
        {'W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' '},
        {'W',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {'W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {'W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {'W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {'W','W','W','W','W','W','W','W','W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
    for (int z = 0; z < 25; z++) {
        for (int a = 0; a < 25; a++) {
            if (wallxy[z][a] == 'W') {
                add_wall(34 + z, 34 + a, VERTICAL, 1);
            }
        }
    }
    //Moving NPC village
    /*
    add_wall(35, 35, VERTICAL, 19);
    add_wall(26, 35, HORIZONTAL, 8);
    add_wall(44, 35, VERTICAL, 4);
    add_wall(43, 29, HORIZONTAL, 2);
    add_wall(42, 40, HORIZONTAL, 1);
    add_wall(41, 41, HORIZONTAL, 1);
    add_wall(40, 41, VERTICAL, 1);
    add_wall(39, 43, VERTICAL, 3);
    add_wall(38, 46, VERTICAL, 3);
    add_wall(39, 48, VERTICAL, 3);
    add_wall(40, 52, VERTICAL, 1);
    add_wall(41, 53, VERTICAL, 1);
    add_wall(42, 54, HORIZONTAL, 1);
    add_wall(35, 54, HORIZONTAL, 7);
    pc.printf("Walls done!\r\n");
    */

    print_map();

}

/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    // First things first: initialize hardware


    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");

    // Initialize the maps
    maps_init();

    init_main_map();


    // Initialize game state
    set_active_map(0);

    Player.x = Player.y = 5;


    // Initial drawing
    draw_game(true);

    // Main game loop
    while(1)
    {
        //pc.printf("made it into loop\n");
        // Timer to measure game update speed
        Timer t; t.start();

        // Actuall do the game update:
        // 1. Read inputs
        GameInputs inputs = read_inputs();
        // 2. Determine action (get_action)
        int action = get_action(inputs);
        // 3. Update game (update_game)
        int init = update_game(action);
        // 3b. Check for game over
        if (init == 1){

        }
        // 4. Draw frame (draw_game)
        draw_game(init);
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 80) wait_ms(80 - dt);
    }
}
