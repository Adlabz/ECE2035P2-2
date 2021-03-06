#include "speech.h"

#include "globals.h"
#include "hardware.h"

/**
 * Draw the speech bubble background.
 */
static void draw_speech_bubble();

/**
 * Erase the speech bubble.
 */
static void erase_speech_bubble();

/**
 * Draw a single line of the speech bubble.
 * @param line The text to display
 * @param which If TOP, the first line; if BOTTOM, the second line.
 */
#define TOP    0
#define BOTTOM 1
static void draw_speech_line(const char* line, int which);

/**
 * Delay until it is time to scroll.
 */
static void speech_bubble_wait();

void draw_speech_bubble()
{
    uLCD.filled_rectangle(0, 50, 127, 117, GREEN);
    uLCD.filled_rectangle(3, 53, 124, 114, BLACK);
}

void erase_speech_bubble()
{
    //draw_game(1);
}

void draw_speech_line(const char* line, int which)
{
    uLCD.text_string((char*)line, 2, (which)?11:9, FONT_7X8, GREEN);
}

void speech_bubble_wait()
{
    GameInputs inputs = read_inputs();
    while (inputs.b1 == 0) { //if button is held down wait until player unpresses it
        inputs = read_inputs();
        //wait lmao
    }
    while (inputs.b1 != 0) {
        inputs = read_inputs();
        //wait lmao
    }
}

void speech(const char* line1, const char* line2)
{
    draw_speech_bubble();
    draw_speech_line(line1, TOP);
    draw_speech_line(line2, BOTTOM);
    speech_bubble_wait();
    //erase_speech_bubble();
}

void long_speech(const char* lines[], int n)
{
    for (int i = 0; i < n; i+=2) {
        draw_speech_bubble();
        draw_speech_line(lines[i], TOP);
        if ((i + 1) < n) {
            draw_speech_line(lines[i + 1], BOTTOM);
        }
        speech_bubble_wait();
    }
}
