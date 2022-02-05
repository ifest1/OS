#include <stdint.h>

#ifndef STDLIB_H__
#define STDLIB_H__
#define MAX_STR_ITOA_SIZE 20
#define NULL ( (void *) 0)

char *itoa(int n, int base);
void memcpy(void *dest, void *src, int size);
void memset(void *str, char c, int n);
void ms(int *n, int b, int e, int (*c)(int v1, int v2));
void merge(int *a, int b, int m, int e, int (*c)(int v1, int v2));
void print(char *str, ...);
int comp(int a, int b);
#endif
