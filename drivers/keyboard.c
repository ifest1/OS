#include "../include/keyboard.h"
#include "../include/ports.h"
#include "../include/screen.h"
#include "../lib/print.h"
#include "../lib/utils.h"

const char KEYBOARD_SCANCODES[50] = {
    ' ', ' ', '1', '2', '3', '4',
    '5', '6', '7', '8', '9', '0',
    '-', '=', ' ', ' ', 'Q', 'W',
    'E', 'R', 'T', 'Y', 'U', 'I',
    'O', 'P', '[', ']', ' ', ' ',
    'A', 'S', 'D', 'F', 'G', 'H',
    'J', 'K', 'L', 'Ç', '~', '\'',
    ' ','\\', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', ',', '.', '/',
    ' '
};

void keyboard_handler(registers_t regs) {
    uint8_t scancode = inb(0x60);
    uint16_t pos = get_cursor();
    print_char(pos, KEYBOARD_SCANCODES[scancode], WHITE_ON_BLUE);
    set_cursor(pos + 1);
}