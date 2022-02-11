#include <file.h>
#include <stdlib.h>
#include <stdint.h>
#include <cpu/x86/syscall.h>


void write(int fd, void *buf, uint32_t count) {
    print("write syscall called [software interrupt]\n");
    _syscall3(SYS_WRITE, fd, (uint32_t) buf, count);
}