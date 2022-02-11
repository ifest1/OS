#include <cpu/x86/isr.h>
#include <stdlib.h>


void sys_write(int fd, char *buf, uint32_t count) {
    print("%d %d %d\n", fd, buf, count);
    print("called write syscall!\n");
}


static void *syscalls[] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    &sys_write,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};


uint32_t syscall_handler(registers_t regs) {
    void *syscall = syscalls[regs.eax];
    regs.eax = call_sys(syscall, regs.ebx, regs.ecx, regs.edx, regs.esi, regs.edi); // eax will store the function pointer
    return regs.eax;
}


void syscall_init() {
    load_irq_handler(0x80, syscall_handler);
    print("Syscall handler initialized\n");
}

