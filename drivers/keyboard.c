#include <stdlib.h>
#include <stdint.h>
#include <cpu/x86/isr.h>
#include <cpu/x86/ports.h>
#include <cpu/x86/idt.h>
#include <drivers/keyboard.h>
#include <drivers/screen.h>

const char KEYBOARD_SCANCODES[0x57] = {
    ' ', ' ', '1', '2', '3', '4',
    '5', '6', '7', '8', '9', '0',
    '-', '=', ' ', ' ', 'Q', 'W',
    'E', 'R', 'T', 'Y', 'U', 'I',
    'O', 'P', '[', ']', ' ', ' ',
    'A', 'S', 'D', 'F', 'G', 'H',
    'J', 'K', 'L', ' ', '~', '\'',
    ' ','\\', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', ',', '.', '/',
    ' '
};

void keyboard_handler(registers_t regs) {
    char c;
    uint8_t scancode = inb(0x60);
    uint16_t pos = get_cursor();

    if (scancode <= 0x57) {
        if (scancode == BACKSPACE) {
            set_cursor(pos - 1);
            print_char(pos - 1, ' ', BLACK_ON_WHITE);
        }

        if (scancode == ENTER) {
            newline_cursor();
        }

        c = KEYBOARD_SCANCODES[scancode];

        if (c != ' ') {
            print_char(pos, c, BLACK_ON_WHITE);
            set_cursor(pos + 1);
        }
    }
}

void keyboard_install() {
    load_irq_handler(IRQ1, keyboard_handler);
}
