#include "./utils.h"

char *itoa(int n, int base, int size) {
    char str[size], *result, *ptr_bg, *ptr;
    result = ptr = str;
    if (n < 0)
        *ptr++ = '-';

    ptr_bg = ptr;

    while(n) {
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + n % base];
        n /= base;
    }

    *ptr-- = '\0';

    while(ptr_bg < ptr) {
        char tmp = *ptr_bg;
        *ptr_bg++ = *ptr;
        *ptr-- = tmp;
    }

    return result;
}