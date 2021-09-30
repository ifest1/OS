#include "./utils.h"

char *itoa(int n) {
    char str[MAX_STR_ITOA_SIZE];
    char *result;
    char *ptr_bg;
    char *ptr;

    result = ptr = str;

    if (n < 0) *ptr++ = '-';

    ptr_bg = ptr;

    while(n)
    {
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + n % 10];
        n /= 10;
    }

    *ptr-- = '\0';

    while(ptr_bg < ptr) {
        char tmp = *ptr_bg;
        *ptr_bg++ = *ptr;
        *ptr-- = tmp;
    }

    return result;
}