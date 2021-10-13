#include <stdlib.h>
#include <cpu/x86/mm.h>
#include <cpu/x86/init.h>

void main() {
    x86_init();
    int a[10] = {15,8,7,10,3,2,4,12,13,9};
    print_mmap();
}