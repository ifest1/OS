#include "../include/screen.h"
#include "./print.h"

void printk(char *str) {
    while(*str != 0)
        write_char(*str++, WHITE_ON_BLUE);
    set_cursor(0, y(get_cursor()) + 1);
}

void print(char *str) {
    uint16_t pos = 60;
    while(*str != 0)
        write_char_at(pos++, *str++, WHITE_ON_BLUE);
}