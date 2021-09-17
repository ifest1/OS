[ORG 0x1000]
mov si, KERNEL_MESSAGE
call print_string

%include "print.asm"
KERNEL_MESSAGE: db 'This is a message from kernel', 0