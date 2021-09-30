#include "./print.h"

void printk(char *str, int addr) {
    char *mm_loc = (char*) addr;
    while(*str != 0) {
        *mm_loc++ = *str++;
        *mm_loc++;
    }
}