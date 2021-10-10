[ORG 0x7C00]

start:
    call text_mode
    call load_kernel
    call e820_mmap
    call enable_a20
    call switch_to_pm
    jmp CODE_SEG:start_pm

text_mode:
    mov ah, 0x0
    mov al, 0x3
    int 0x10
    ret

enable_a20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

%include "boot/gdt.asm"
%include "boot/pm.asm"
%include "boot/disk.asm"
%include "boot/mmap.asm"

[bits 32]
%include "boot/registers.asm"

start_pm:
    call set_registers
    call KERNEL_LOCATION
    jmp $

times 510 - ($-$$) db 0
dw 0xAA55