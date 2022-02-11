#include <drivers/screen.h>
#include <drivers/keyboard.h>
#include <drivers/timer.h>
#include <cpu/x86/idt.h>
#include <cpu/x86/gdt.h>
#include <cpu/x86/pic.h>
#include <cpu/x86/isr.h>
#include <cpu/x86/syscall.h>


void x86_init() {
    reset_cursor();
    fill_screen(BLACK_ON_WHITE);
    gdt_init();
    idt_init();
    syscall_init();
    keyboard_install();
    timer_install();
}