#include "./stdint.h"
#ifndef SCREEN_H__
#define SCREEN_H__
#define VIDEO_MEMORY            0xB8000
#define VGA_HEIGHT              25
#define VGA_WIDTH               80
#define SCREEN_SIZE             2000

#define BLACK                   0x0
#define BLUE                    0x1
#define GREEN                   0x2
#define CYAN                    0x3
#define RED                     0x4
#define MAGENTA                 0x5
#define BROWN                   0x6
#define LIGHT                   0x7
#define BRIGHT                  0x8

#define WHITE_ON_BLACK          ((uint8_t) (BLACK << 4) | (uint8_t) (LIGHT + BRIGHT))
#define WHITE_ON_BLUE           ((uint8_t) (BLUE << 4)  | (uint8_t) (LIGHT + BRIGHT))
#define BLACK_ON_WHITE           ((uint8_t) (LIGHT << 4)  | (uint8_t) (BLACK))

void print_char(uint16_t pos, uint8_t c, uint16_t clr);

uint8_t x(uint16_t pos);
uint8_t y(uint16_t pos);

uint16_t position(uint8_t x, uint8_t y);

uint16_t get_cursor(void);
void newline_cursor();
void set_cursor(uint16_t pos);
void set_cursor_coordinates(uint8_t x, uint8_t y);
void fill_screen(uint16_t clr);
#endif
