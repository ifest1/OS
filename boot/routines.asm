[bits 16]
; real mode routines
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

[bits 32]
; protected mode routines
start_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call KERNEL_LOCATION
    jmp $