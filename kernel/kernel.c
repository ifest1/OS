#include <stdlib.h>
#include <cpu/x86/mm.h>
#include <cpu/x86/init.h>

void main() {
    x86_init();
    print_mmap();
}