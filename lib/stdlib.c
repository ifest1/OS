#include <stdint.h>
#include <stdlib.h>
#include <drivers/screen.h>

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

void merge(int *a, int b, int m, int e, int (*c)(int v1, int v2)) {
    int l, r, i;
    int l1 = m - b + 1;
    int l2 = e - m;
    int t1[l1], t2[l2];

    for(l = 0; l < l1; l++) {
        t1[l] = a[b+l];
    }

    for(r = 0; r < l2; r++) {
        t2[r] = a[m+1+r];
    }

    l = r = 0;

    while(l < l1 && r < l2) {
        if (c(t1[l], t2[r])) {
            a[b] = t1[l];
            l++;
        }
        else {
            a[b] = t2[r];
            r++;
        }
        b++;
    }

    while (l < l1) {
        a[b] = t1[l];
        l++;
        b++;
    }

    while (r < l2) {
        a[b] = t2[r];
        r++;
        b++;
    }
}

void ms(int *n, int b, int e, int (*c)(int v1, int v2)) {
    if (b < e) {
        int m = (b + e) / 2;
        ms(n, b, m, c);
        ms(n, m+1, e, c);
        merge(n, b, m, e, c);
    }
}