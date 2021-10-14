#ifndef UTILS_H__
#define UTILS_H__
#define MAX_STR_ITOA_SIZE 20
#include <stdint.h>

char *itoa(long int n, int base, char *str);
void ms(int *n, int b, int e, int (*c)(int v1, int v2));
void merge(int *a, int b, int m, int e, int (*c)(int v1, int v2));
void printk(char *str, bool nl);
int comp(int a, int b);
#endif
