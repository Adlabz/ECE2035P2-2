#include "graphics.h"

#include "globals.h"



void draw_player(int u, int v, int key)
{
    uLCD.filled_rectangle(u, v, u+11, v+11, RED);
}

#define YELLOW 0xEEDD33
#define BROWN  0xD2691E
#define DIRT   BROWN
#define G 0x307400
#define B 0x744300
#define D 0x707070
#define Y 0x7c8b00

void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_nothing(int u, int v)
{
    // Fill a tile with blackness
    int dirtBlock[11][11] =
    {
        {G, B, D, Y, G, Y, B, Y, G, Y, G},
        {G, Y, G, Y, G, B, Y, B, G, Y, Y},
        {Y, B, Y, Y, B, Y, Y, G, Y, G, G},
        {G, G, Y, G, Y, G, G, Y, B, Y, G},
        {Y, Y, G, Y, G, Y, G, Y, D, B, D},
        {D, Y, B, Y, B, G, Y, G, Y, Y, B},
        {Y, G, Y, Y, D, B, G, Y, G, B, B},
        {B, Y, B, Y, Y, G, Y, G, Y, Y, B},
        {Y, G, G, G, D, Y, B, Y, G, B, Y},
        {B, Y, G, Y, B, B, Y, G, B, G, B},
        {G, G, Y, G, D, G, B, Y, G, B, G}
    };
    for (int i = 0; i <= 10; i++){
        for (int j = 0; j <= 10; j++) {
            uLCD.pixel(u + i, v + j, dirtBlock[i][j]);
        }
    }
}

void draw_wall(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BROWN);
}

void draw_plant(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
}

void draw_upper_status()
{
    // Draw bottom border of status bar
    uLCD.line(0, 9, 127, 9, GREEN);

    // Add other status info drawing code here
}

void draw_lower_status()
{
    // Draw top border of status bar
    uLCD.line(0, 118, 127, 118, GREEN);

    // Add other status info drawing code here
}

void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}
