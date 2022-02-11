#ifndef SYSCALL_H__
#define SYSCALL_H__

#include <cpu/x86/isr.h>

extern uint32_t _syscall0(uint32_t sys_num);
extern uint32_t _syscall1(uint32_t sys_num, uint32_t arg1);
extern uint32_t _syscall2(uint32_t sys_num, uint32_t arg1, uint32_t arg2);
extern uint32_t _syscall3(uint32_t sys_num, uint32_t arg1, uint32_t arg2, uint32_t arg3);
extern uint32_t _syscall4(uint32_t sys_num, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);
extern uint32_t _syscall5(uint32_t sys_num, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5);
extern uint32_t call_sys();

enum {
    SYS_LSTREE,	// 0
    // process
    SYS_FORK,	// 1
    SYS_WAIT,	// 2
    SYS_EXIT,	// 3
    SYS_GETPID,	// 4
    SYS_EXEC,	// 5
    SYS_PS,		// 6
    // mem //
    SYS_SBRK,	// 7
    // files //
    SYS_OPEN,	// 8
    SYS_CLOSE,	// 9
    SYS_STAT,	// 10
    SYS_FSTAT,	// 11
    SYS_READ,	// 12
    SYS_WRITE,	// 13
    SYS_CHDIR,	// 14
    SYS_CHROOT,	// 15
    SYS_CHMOD,	// 16
    SYS_CHOWN,	// 17
    SYS_MKDIR,	// 19
    SYS_COFS_DUMP_CACHE, // 20
    SYS_ISATTY, // 21
    SYS_LSEEK,	// 22
    SYS_OPENDIR,	// 23
    SYS_CLOSEDIR,	// 24
    SYS_READDIR,	// 25
    SYS_LSTAT,		// 26
    SYS_READLINK,	// 27
    SYS_GETCWD,		// 28
    SYS_UNLINK,		// 29
    SYS_DUP,		// 30
    SYS_PIPE,		// 31
    SYS_CLRSCR,		// 32
    SYS_LINK,		// 33
    SYS_RENAME,		// 34
    SYS_KILL,       // 35
    SYS_SIGNAL,     // 36
    SYS_IOCTL,      // 37
    SYS_SETSID,     // 38
    SYS_TIME,       // 39
    SYS_FTRUNCATE,  // 40
};


uint32_t syscall_handler(registers_t regs);
void syscall_init();

#endif