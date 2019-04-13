#include "graphics.h"

#include "globals.h"
#include "map.h"

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
    };
    uLCD.BLIT(u, v, 11, 11, playerOnDirtBlock);*/
    uLCD.pixel(u + 4, v, RED);
    uLCD.pixel(u + 4, v + 1, RED);
    uLCD.pixel(u + 5, v + 1, RED);
    uLCD.pixel(u + 3, v + 2, S);
    uLCD.pixel(u + 4, v + 2, RED);
    uLCD.pixel(u + 5, v + 2, RED);
    uLCD.pixel(u + 6, v + 2, RED);
    uLCD.pixel(u + 4, v + 3, M);
    uLCD.pixel(u + 5, v + 3, M);
    uLCD.pixel(u + 4, v + 4, M);
    uLCD.pixel(u + 5, v + 4, M);
    uLCD.pixel(u + 2, v + 5, RED);
    uLCD.pixel(u + 3, v + 5, RED);
    uLCD.pixel(u + 4, v + 5, RED);
    uLCD.pixel(u + 5, v + 5, S);
    uLCD.pixel(u + 6, v + 5, RED);
    uLCD.pixel(u + 7, v + 5, RED);
    uLCD.pixel(u + 1, v + 6, RED);
    uLCD.pixel(u + 2, v + 6, RED);
    uLCD.pixel(u + 4, v + 6, RED);
    uLCD.pixel(u + 5, v + 6, S);
    uLCD.pixel(u + 7, v + 6, RED);
    uLCD.pixel(u + 8, v + 6, RED);
    uLCD.pixel(u + 9, v + 6, RED);
    uLCD.pixel(u + 0, v + 7, RED);
    uLCD.pixel(u + 1, v + 7, RED);
    uLCD.pixel(u + 4, v + 7, RED);
    uLCD.pixel(u + 5, v + 7, S);
    uLCD.pixel(u + 7, v + 7, S);
    uLCD.pixel(u + 4, v + 8, RED);
    uLCD.pixel(u + 6, v + 8, RED);
    uLCD.pixel(u + 4, v + 9, RED);
    uLCD.pixel(u + 6, v + 9, RED);
    uLCD.pixel(u + 3, v + 10, RED);
    uLCD.pixel(u + 4, v + 10, S);
    uLCD.pixel(u + 6, v + 10, S);
    uLCD.pixel(u + 7, v + 10, RED);
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
    if (get_active_map_no() == 0){
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
    else {
        int caveLavaBlock[11*11] =
        {
            0x364a58, 0x24333c, 0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x364a58, 0x364a58, 0x692500, 0x24333c, 0x364a58,
            0x24333c, 0x364a58, 0x692500, 0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x24333c, 0x692500, 0x364a58, 0x24333c,
            0x24333c, 0x364a58, 0x834c01, 0x692500, 0x24333c, 0x364a58, 0x24333c, 0x364a58, 0x834c01, 0x692500, 0x24333c,
            0x364a58, 0x24333c, 0x692500, 0x364a58, 0x364a58, 0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x692500, 0x364a58,
            0x364a58, 0x364a58, 0x692500, 0x364a58, 0x834c01, 0x692500, 0x24333c, 0x364a58, 0x24333c, 0x834c01, 0x692500,
            0x834c01, 0x834c01, 0x364a58, 0x692500, 0x692500, 0x24333c, 0x834c01, 0x24333c, 0x364a58, 0x692500, 0x364a58,
            0x364a58, 0x364a58, 0x834c01, 0x692500, 0x834c01, 0x364a58, 0x24333c, 0x834c01, 0x24333c, 0x692500, 0x364a58,
            0x364a58, 0x24333c, 0x364a58, 0x692500, 0x834c01, 0x24333c, 0x364a58, 0x364a58, 0x692500, 0x834c01, 0x364a58,
            0x24333c, 0x364a58, 0x692500, 0x364a58, 0x24333c, 0x364a58, 0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x24333c,
            0x24333c, 0x834c01, 0x692500, 0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x24333c, 0x364a58, 0x834c01, 0x24333c,
            0x364a58, 0x692500, 0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x364a58, 0x364a58, 0x24333c, 0x834c01, 0x834c01
        };
        uLCD.BLIT(u, v, 11, 11, caveLavaBlock);
    }
}
#define R 0x8c8d8b
#define U 0x5c5c5c
void draw_cave_entry(int u, int v)
{
    // Fill a tile with grass
    int Rock[11 * 11] =
    {
        G, G, G, G, G, G, G, G, G, G, G,
        G, Y, G, G, G, G, G, G, G, G, G,
        G, G, Y, G, G, G, G, Y, G, G, G,
        G, G, G, U, U, G, G, G, G, G, G,
        G, G, U, R, R, U, U, G, G, Y, G,
        G, U, R, R, R, R, R, U, G, Y, G,
        U, R, R, R, R, R, R, R, U, G, G,
        U, R, U, R, R, R, U, R, R, U, G,
        U, R, R, R, R, U, R, R, R, U, G,
        G, U, R, R, R, R, R, R, U, G, G,
        G, G, U, U, U, U, U, U, G, G, G
    };
    uLCD.BLIT(u, v, 11, 11, Rock);
}
#define V BLACK
void draw_cave_opening(int u, int v)
{
    // Fill a tile with grass
    int f1[11 * 11] =
    {
        G, G, G, G, G, G, G, G, G, G, G,
        G, Y, G, G, G, G, G, G, G, G, G,
        G, G, Y, G, G, G, G, Y, G, G, G,
        G, G, G, U, U, G, G, G, G, G, G,
        G, G, U, R, R, U, U, G, G, Y, G,
        G, U, R, R, R, R, R, U, G, Y, G,
        U, R, R, R, R, R, R, R, U, G, G,
        U, R, U, R, R, R, U, R, R, U, G,
        U, R, R, R, R, U, R, R, R, U, G,
        G, U, R, R, R, R, R, R, U, G, G,
        G, G, U, U, U, U, U, U, G, G, G
    };
    int f2[11 * 11] =
    {
        G, G, G, G, G, G, G, G, G, G, G,
        G, Y, G, G, G, G, G, G, G, G, G,
        G, G, Y, G, G, G, G, Y, G, G, G,
        G, G, G, U, U, G, G, G, G, G, G,
        G, G, U, U, R, U, U, G, G, Y, G,
        G, U, R, R, U, R, R, U, G, Y, G,
        U, R, R, R, U, R, R, R, U, G, G,
        U, R, U, R, R, R, U, R, R, U, G,
        U, R, R, R, R, U, R, R, R, U, G,
        G, U, R, R, R, R, R, R, U, G, G,
        G, G, U, U, U, U, U, U, G, G, G
    };
    int f3[11 * 11] =
    {
        G, G, G, G, G, G, G, G, G, G, G,
        G, Y, G, G, G, G, G, G, G, G, G,
        G, G, Y, G, G, G, G, Y, G, G, G,
        G, G, G, U, U, G, G, G, G, G, G,
        G, G, U, U, R, U, U, G, G, Y, G,
        G, U, R, R, U, R, R, U, G, Y, G,
        U, R, R, R, U, R, R, R, U, G, G,
        U, R, U, U, R, R, U, R, R, U, G,
        U, R, R, R, U, U, R, R, R, U, G,
        G, U, R, U, R, R, U, R, U, G, G,
        G, G, U, U, U, U, U, U, G, G, G
    };
    int f4[11 * 11] =
    {
        G, G, G, G, G, G, G, G, G, G, G,
        G, Y, G, G, G, G, G, G, G, G, G,
        G, G, Y, G, G, G, G, Y, G, G, G,
        G, G, G, U, U, G, G, G, G, G, G,
        G, G, U, U, R, U, U, G, G, Y, G,
        G, U, R, R, U, R, R, U, G, Y, G,
        U, R, R, R, V, V, R, R, U, G, G,
        U, R, U, U, V, V, U, R, R, U, G,
        U, R, R, R, U, U, R, R, R, U, G,
        G, U, R, U, R, R, U, R, U, G, G,
        G, G, U, U, U, U, U, U, G, G, G
    };
    int f5[11 * 11] =
    {
        G, G, G, G, G, G, G, G, G, G, G,
        G, Y, G, G, G, G, G, G, G, G, G,
        G, G, Y, G, G, G, G, Y, G, G, G,
        G, G, G, U, U, G, G, G, G, G, G,
        G, G, U, U, R, U, U, G, G, Y, G,
        G, U, R, R, U, R, R, U, G, Y, G,
        U, R, R, V, V, V, R, R, U, G, G,
        U, R, V, V, V, V, U, R, R, U, G,
        U, R, R, V, V, V, R, R, R, U, G,
        G, U, R, U, V, R, U, R, U, G, G,
        G, G, U, U, U, U, U, U, G, G, G
    };
    int f6[11 * 11] =
    {
        G, G, G, G, G, G, G, G, G, G, G,
        G, Y, G, G, G, G, G, G, G, G, G,
        G, G, Y, G, G, G, G, Y, G, G, G,
        G, G, G, U, U, G, G, G, G, G, G,
        G, G, U, V, V, U, U, G, G, Y, G,
        G, U, V, V, V, V, V, U, G, Y, G,
        U, V, V, V, V, V, V, V, U, G, G,
        U, V, V, V, V, V, V, V, V, U, G,
        U, V, V, V, V, V, V, V, V, U, G,
        G, U, V, V, V, V, V, V, U, G, G,
        G, G, U, U, U, U, U, U, G, G, G
    };
    uLCD.BLIT(u, v, 11, 11, f1);
    wait_ms(200);
    uLCD.BLIT(u, v, 11, 11, f1);
    wait_ms(200);
    uLCD.BLIT(u, v, 11, 11, f2);
    wait_ms(200);
    uLCD.BLIT(u, v, 11, 11, f2);
    wait_ms(200);
    uLCD.BLIT(u, v, 11, 11, f3);
    wait_ms(200);
    uLCD.BLIT(u, v, 11, 11, f3);
    wait_ms(200);
    uLCD.BLIT(u, v, 11, 11, f4);
    wait_ms(200);
    uLCD.BLIT(u, v, 11, 11, f5);
    wait_ms(200);
    uLCD.BLIT(u, v, 11, 11, f6);
}

void draw_cave_opened(int u, int v)
{
    int f6[11 * 11] =
    {
        G, G, G, G, G, G, G, G, G, G, G,
        G, Y, G, G, G, G, G, G, G, G, G,
        G, G, Y, G, G, G, G, Y, G, G, G,
        G, G, G, U, U, G, G, G, G, G, G,
        G, G, U, V, V, U, U, G, G, Y, G,
        G, U, V, V, V, V, V, U, G, Y, G,
        U, V, V, V, V, V, V, V, U, G, G,
        U, V, V, V, V, V, V, V, V, U, G,
        U, V, V, V, V, V, V, V, V, U, G,
        G, U, V, V, V, V, V, V, U, G, G,
        G, G, U, U, U, U, U, U, G, G, G
    };
    uLCD.BLIT(u, v, 11, 11, f6);
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
#define B 0x0050bb
#define Z 0x3a8eff
void draw_NPC(int u, int v)
{
    /*int NPCBlock[11 * 11] =
    {
        B, B, B, B, B, B, B, B, B, B, B,
        B, Z, Z, Z, Z, Z, Z, Z, Z, Z, B,
        B, Z, Z, Z, B, B, B, Z, Z, Z, B,
        B, Z, Z, Z, B, B, B, Z, Z, Z, B,
        B, Z, Z, Z, B, B, B, Z, Z, Z, B,
        B, Z, B, Z, Z, B, Z, Z, B, Z, B,
        B, Z, Z, B, B, B, B, B, Z, Z, B,
        B, Z, Z, Z, Z, B, Z, Z, Z, Z, B,
        B, Z, Z, Z, Z, B, Z, Z, Z, Z, B,
        B, Z, Z, Z, B, Z, B, Z, Z, Z, B,
        B, B, B, B, B, B, B, B, B, B, B
    };
    uLCD.BLIT(u, v, 11, 11, NPCBlock);*/
    uLCD.pixel(u + 2, v + 5, B);
    uLCD.pixel(u + 3, v + 6, B);
    uLCD.pixel(u + 4, v + 2, B);
    uLCD.pixel(u + 4, v + 3, B);
    uLCD.pixel(u + 4, v + 4, B);
    uLCD.pixel(u + 4, v + 6, B);
    uLCD.pixel(u + 4, v + 9, B);
    uLCD.pixel(u + 4, v + 10, B);
    uLCD.pixel(u + 5, v + 3, B);
    uLCD.pixel(u + 5, v + 4, B);
    uLCD.pixel(u + 5, v + 5, B);
    uLCD.pixel(u + 5, v + 6, B);
    uLCD.pixel(u + 5, v + 7, B);
    uLCD.pixel(u + 5, v + 8, B);
    uLCD.pixel(u + 6, v + 2, B);
    uLCD.pixel(u + 6, v + 3, B);
    uLCD.pixel(u + 6, v + 4, B);
    uLCD.pixel(u + 6, v + 6, B);
    uLCD.pixel(u + 6, v + 9, B);
    uLCD.pixel(u + 6, v + 10, B);
    uLCD.pixel(u + 7, v + 6, B);
    uLCD.pixel(u + 8, v + 5, B);
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

void draw_cave_wall(int u, int v) {
    int caveWallBlock[11*11] =
    {
        0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x151f25, 0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x24333c,
        0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x151f25, 0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x24333c,
        0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x151f25, 0x364a58, 0x151f25, 0x151f25, 0x24333c, 0x24333c, 0x24333c,
        0x24333c, 0x24333c, 0x24333c, 0x151f25, 0x364a58, 0x24333c, 0x24333c, 0x24333c, 0x151f25, 0x24333c, 0x24333c,
        0x151f25, 0x24333c, 0x24333c, 0x151f25, 0x364a58, 0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x151f25, 0x151f25,
        0x24333c, 0x151f25, 0x151f25, 0x364a58, 0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x151f25, 0x364a58, 0x24333c,
        0x24333c, 0x24333c, 0x24333c, 0x151f25, 0x24333c, 0x24333c, 0x151f25, 0x151f25, 0x364a58, 0x24333c, 0x24333c,
        0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x151f25, 0x151f25, 0x364a58, 0x364a58, 0x24333c, 0x24333c, 0x24333c,
        0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x151f25, 0x364a58, 0x24333c, 0x24333c, 0x24333c,
        0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x151f25, 0x364a58, 0x24333c, 0x24333c, 0x24333c,
        0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x24333c, 0x151f25, 0x364a58, 0x24333c, 0x24333c, 0x24333c, 0x24333c
    };
    uLCD.BLIT(u, v, 11, 11, caveWallBlock);
}
void draw_cave_floor(int u, int v) {
    int caveFloorBlock[11*11] =
    {
        0x364a58, 0x24333c, 0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x364a58, 0x364a58, 0x24333c, 0x24333c, 0x364a58,
        0x24333c, 0x364a58, 0x364a58, 0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x24333c, 0x364a58, 0x364a58, 0x24333c,
        0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x24333c, 0x364a58, 0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x24333c,
        0x364a58, 0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x24333c, 0x364a58,
        0x364a58, 0x364a58, 0x24333c, 0x364a58, 0x24333c, 0x364a58, 0x24333c, 0x364a58, 0x24333c, 0x364a58, 0x364a58,
        0x364a58, 0x364a58, 0x364a58, 0x24333c, 0x364a58, 0x24333c, 0x364a58, 0x24333c, 0x364a58, 0x364a58, 0x364a58,
        0x364a58, 0x364a58, 0x24333c, 0x364a58, 0x24333c, 0x364a58, 0x24333c, 0x364a58, 0x24333c, 0x364a58, 0x364a58,
        0x364a58, 0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x24333c, 0x364a58,
        0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x24333c, 0x364a58, 0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x24333c,
        0x24333c, 0x364a58, 0x364a58, 0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x24333c, 0x364a58, 0x364a58, 0x24333c,
        0x364a58, 0x24333c, 0x24333c, 0x364a58, 0x364a58, 0x364a58, 0x364a58, 0x364a58, 0x24333c, 0x24333c, 0x364a58
    };
    uLCD.BLIT(u, v, 11, 11, caveFloorBlock);
}
void draw_upper_status(int xx, int yy, int hh)
{
    // Draw bottom border of status bar
    uLCD.line(0, 9, 127, 9, GREEN);

    // Add other status info drawing code here
    char x = xx % 10 + '0';
    char x2 = (xx/10) % 10 + '0';
    char y = yy % 10 + '0';
    char y2 = (yy/10) % 10 + '0';
    char h = hh % 10 + '0';
    char h2 = (hh/10) % 10 + '0';
    char s[] = {'x', ':', ' ', x2, x, ' ', 'y', ':', ' ', y2, y, ' ', 'H', 'P',':',' ',h2,h,'\0' };
    uLCD.text_string(s, 0, 0, FONT_7X8, GREEN);
}

void draw_lower_status()
{
    // Draw top border of status bar
    uLCD.line(0, 118, 127, 118, GREEN);

    // Add other status info drawing code here
    char s[] = {'O','M','N','I','P','O','T','E','N','T','\0' };
    char o[] = {'O','M','N','I','P','O','T','E','N','T', ' ', 'O', 'F', 'F','\0' };
    uLCD.text_string(o, 2, 15, FONT_7X8, BLACK);
    uLCD.text_string(s, 4, 15, FONT_7X8, GREEN);
}
void un_lower_status()
{
    // Draw top border of status bar
    uLCD.line(0, 118, 127, 118, GREEN);

    // Add other status info drawing code here
    char s[] = {'O','M','N','I','P','O','T','E','N','T', ' ', 'O', 'F', 'F','\0' };
    uLCD.text_string(s, 2, 15, FONT_7X8, GREEN);
}

void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}
