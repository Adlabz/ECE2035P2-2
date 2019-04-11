#include "graphics.h"

#include "globals.h"

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

void draw_player(int u, int v, int key)
{
    // Draw just the player
    /* int playerOnDirtBlock[11 * 11] =
    {
        G, G, G, G, C, G, G, G, G, G, G,
        G, Y, G, G, C, C, G, G, G, G, G,
        G, G, Y, S, C, C, C, Y, G, G, G,
        G, G, G, G, M, M, G, G, G, G, G,
        G, G, G, G, M, M, G, G, G, Y, G,
        G, G, C, C, C, S, C, C, G, Y, G,
        G, C, C, G, C, S, G, C, C, C, G,
        C, C, G, G, C, S, G, G, S, G, G,
        G, G, G, Y, C, G, C, G, G, G, G,
        G, G, Y, G, C, G, C, G, G, G, G,
        G, G, G, C, S, G, S, C, G, G, G
    }; */
    uLCD.BLIT(u, v, 11, 11, playerOnDirtBlock);
    uLCD.pixel(u + 4, v, C);
    uLCD.pixel(u + 4, v + 1, C);
    uLCD.pixel(u + 5, v + 1, C);
    uLCD.pixel(u + 3, v + 2, S);
    uLCD.pixel(u + 4, v + 2, C);
    uLCD.pixel(u + 5, v + 2, C);
    uLCD.pixel(u + 6, v + 2, C);
    uLCD.pixel(u + 4, v + 3, M);
    uLCD.pixel(u + 5, v + 3, M);
    uLCD.pixel(u + 4, v + 4, M);
    uLCD.pixel(u + 5, v + 4, M);
    uLCD.pixel(u + 2, v + 5, C);
    uLCD.pixel(u + 3, v + 5, C);
    uLCD.pixel(u + 4, v + 5, C);
    uLCD.pixel(u + 5, v + 5, S);
    uLCD.pixel(u + 6, v + 5, C);
    uLCD.pixel(u + 7, v + 5, C);
    uLCD.pixel(u + 1, v + 6, C);
    uLCD.pixel(u + 2, v + 6, C);
    uLCD.pixel(u + 4, v + 6, C);
    uLCD.pixel(u + 5, v + 6, S);
    uLCD.pixel(u + 7, v + 6, C);
    uLCD.pixel(u + 8, v + 6, C);
    uLCD.pixel(u + 9, v + 6, C);
    uLCD.pixel(u, v + 7, C);
    uLCD.pixel(u, v + 7, C);
    uLCD.pixel(u, v + 7, C);
    uLCD.pixel(u, v + 7, S);
    uLCD.pixel(u, v + 7, S);
    uLCD.pixel(u, v + 8, C);
    uLCD.pixel(u, v + 8, C);
    uLCD.pixel(u, v + 9, C);
    uLCD.pixel(u, v + 9, C);
    uLCD.pixel(u + 3, v + 10, C);
    uLCD.pixel(u + 4, v + 10, S);
    uLCD.pixel(u + 6, v + 10, S);
    uLCD.pixel(u + 7, v + 10, C);
}

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
