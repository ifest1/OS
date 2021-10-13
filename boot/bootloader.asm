[ORG 0x7C00]

start:
    call text_mode
    call load_kernel
    call e820_mmap
    call enable_a20
    call switch_to_pm
    jmp CODE_SEG:start_pm

%include "boot/gdt.asm"
%include "boot/pm.asm"
%include "boot/disk.asm"
%include "boot/mmap.asm"
%include "boot/routines.asm"

times 510 - ($-$$) db 0
dw 0xAA55