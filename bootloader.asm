[ORG 0x7C00]

start:
    call enter_text_mode
    call load_kernel
    call enable_a20
    call switch_to_protected_mode
    jmp CODE_SEG:start_protected_mode

enter_text_mode:
    mov ah, 0x0
    mov al, 0x3
    int 0x10
    ret

enable_a20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

%include "gdt.asm"
%include "print.asm"
%include "disk.asm"
%include "switch_to_pm.asm"

[bits 32]
%include "screen.asm"
%include "set_registers_pm.asm"

start_protected_mode:
    call set_registers
    call clear_screen
    call KERNEL_LOCATION
    jmp $

times 510 - ($-$$) db 0
dw 0xAA55