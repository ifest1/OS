#include "../include/stdint.h"
#include "../include/screen.h"
#include "../include/ports.h"

uint8_t x(uint16_t pos) {
    return pos % VGA_WIDTH;
}

uint8_t y(uint16_t pos) {
    return pos / VGA_WIDTH;
}

uint16_t position(uint8_t x, uint8_t y) {
    return (uint16_t) y * VGA_WIDTH + x;
}

void set_cursor(uint8_t x, uint8_t y) {
    uint16_t pos = position(x, y);
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
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

void write_char(unsigned char c, uint16_t clr) {
    uint16_t cursor_pos = get_cursor();
    uint8_t cursor_x = x(cursor_pos) + 1;
    uint8_t cursor_y = y(cursor_pos);
    write_char_at(cursor_pos, c, clr);
    set_cursor(cursor_x, cursor_y);
}

void write_char_at(uint16_t pos, unsigned char c, uint16_t clr) {
    uint16_t *vga_mm = (uint16_t *) VIDEO_MEMORY + pos;
    *vga_mm = c | clr << 8;
}

void fill_screen(uint16_t clr) {
    uint16_t *vga_mm = (uint16_t *) VIDEO_MEMORY;
    for(int i = 0; i < SCREEN_SIZE; i++)
        *vga_mm++ = ' ' | clr << 8;
}
