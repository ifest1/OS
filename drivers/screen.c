#include "../include/stdint.h"
#include "../include/screen.h"
#include "../include/ports.h"

/* From position get the character/cursor coordinates */
uint8_t x(uint16_t pos) {
    return pos % VGA_WIDTH;
}

uint8_t y(uint16_t pos) {
    return pos / VGA_WIDTH;
}

/* From x and y get position on VGA memory */
uint16_t position(uint8_t x, uint8_t y) {
    return (uint16_t) y * VGA_WIDTH + x;
}

/* Cursor functions */
void set_cursor(uint16_t pos) {
    outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void set_cursor_coordinates(uint8_t x, uint8_t y) {
    uint16_t pos = position(x, y);
    set_cursor(pos);
}

uint16_t get_cursor(void)
{
    uint16_t pos = 0;
    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;
    return pos;
}

void newline_cursor() {
    set_cursor_coordinates(0, y(get_cursor()) + 1);
}

/* Writes char at given position with bg and fg specified */
void print_char(uint16_t pos, uint8_t c, uint16_t clr) {
    uint16_t *vga_mm = (uint16_t *) VIDEO_MEMORY + pos;
    *vga_mm = c | clr << 8;
}

/* Fill screen with specified color */
void fill_screen(uint16_t clr) {
    uint16_t *vga_mm = (uint16_t *) VIDEO_MEMORY;
    for(int i = 0; i < SCREEN_SIZE; i++)
        *vga_mm++ = ' ' | clr << 8;
}
