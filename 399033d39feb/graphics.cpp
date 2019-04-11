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
#define Y 0x7c8b00
#define D 0x3c6500
#define P 0x264000
#define C 0xce5505
#define M 0xdb8a54
#define S 0xb64901

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
    // Fill a tile with grass
    int dirtBlock[11 * 11] =
    {
        G, G, G, G, G, G, G, G, G, G, G,
        G, Y, G, G, G, G, G, G, G, G, G,
        G, G, Y, G, G, G, G, Y, G, G, G,
        G, G, G, G, G, G, G, G, G, G, G,
        G, G, G, G, G, G, G, G, G, Y, G,
        G, G, G, G, G, G, G, G, G, Y, G,
        G, G, G, G, G, G, G, G, G, G, G,
        G, G, G, G, G, G, G, G, G, G, G,
        G, G, G, Y, G, G, G, G, G, G, G,
        G, G, Y, G, Y, G, G, G, G, G, G,
        G, G, G, G, G, G, G, G, G, G, G
    };
    uLCD.BLIT(u, v, 11, 11, dirtBlock);
}

void draw_wall(int u, int v)
{
    int brickBlock[11 * 11] =
    {
        M, M, M, M, M, M, M, M, M, M, M,
        C, C, C, S, M, C, C, C, C, C, C,
        C, C, C, S, M, C, C, C, C, C, C,
        C, S, S, S, M, C, C, C, C, C, C,
        M, M, M, M, M, M, M, M, M, M, M,
        C, C, C, C, C, C, S, M, C, C, C,
        C, C, C, C, C, C, S, M, C, C, C,
        C, C, C, C, S, S, S, M, C, C, C,
        M, M, M, M, M, M, M, M, M, M, M,
        C, C, M, C, C, C, C, C, C, C, S,
        C, C, M, C, C, C, C, C, C, S, S
    };
    uLCD.BLIT(u, v, 11, 11, brickBlock);
}

void draw_plant(int u, int v)
{
    int plantBlock[11 * 11] =
    {
        P, P, D, P, P, P, D, P, P, P, P,
        P, D, P, P, P, P, P, D, P, P, P,
        P, D, P, P, P, P, D, P, P, P, P,
        D, P, P, P, P, P, P, D, P, P, D,
        P, P, P, D, P, D, D, P, P, D, P,
        P, P, P, P, D, P, P, D, D, P, D,
        P, P, P, D, P, P, P, P, P, P, P,
        P, P, P, P, D, P, P, P, D, P, P,
        P, P, P, D, D, P, D, P, P, P, P,
        P, D, P, P, P, D, P, P, P, D, P,
        D, P, P, P, D, P, P, P, D, P, D
    };
    uLCD.BLIT(u, v, 11, 11, plantBlock);
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
