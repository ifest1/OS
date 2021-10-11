#include "../include/stdint.h"
#include "../include/screen.h"

/* Main print string kernel function */
void printk(char *str) {
    uint16_t cursor_pos = get_cursor();
    uint8_t cursor_x = x(cursor_pos) + 1;
    uint8_t cursor_y = y(cursor_pos);

    while(*str != 0) {
        print_char(cursor_pos++, *str++, BLACK_ON_WHITE);
        cursor_x++;
    }
    newline_cursor();
}