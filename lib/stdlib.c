#include <stdint.h>
#include <stdlib.h>
#include <drivers/screen.h>

/* Main print string kernel function */
void printk(char *str, bool nl) {
    uint16_t cursor_pos = get_cursor();
    uint8_t cursor_x = x(cursor_pos) + 1;
    uint8_t cursor_y = y(cursor_pos);

    while(*str != 0) {
        print_char(cursor_pos++, *str++, BLACK_ON_WHITE);
        cursor_x++;
    }
    if (nl) {
        newline_cursor();
    }
    else {
        set_cursor(cursor_pos);
    }
}

char *itoa(int n, int base, char *str) {
    int i = 0;
    int j = 0;
    int k = 0;
    char temp[32];
    char digits[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

    if (n == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if (n < 0 && base == 10)
        str[i] = '-';

    while (n != 0) {
        temp[i++] = digits[n % base];
        n /= base;
    }

    str[i] = '\0';
    k = i--;
    for (j = 0; j < k; i--, j++)
        str[j] = temp[i];

    return str;

}

void memcpy(void *dest, void *src, int size) {
    char *d = (char *) dest;
    char *s = (char *) src;
    for(int i = 0; i < size; i++)
        *d++ = *s++;
}

void memset(void *str, char c, int n) {
    char *s = (char *) str;
    for(int i = 0; i < n; i++)
        *s++ = c;
}

/* comparator must receive variable with different type */
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

int comp(int a, int b) {
    return a < b;
}


