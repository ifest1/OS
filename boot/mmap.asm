MMAP_ENTRY_COUNT    equ 0x5000
MMAP_ENTRY          equ 0x5004
SMAP                equ 0x0534D4150
E820                equ 0xe820

e820_mmap:
    mov ax, 0
    mov es, ax
    mov di, MMAP_ENTRY
    xor ebx, ebx
    xor bp, bp

    .loop:
        mov edx, SMAP
        mov eax, E820
        mov ecx, 24
        int 0x15

        cmp ebx, 0
        je .finished

        add di, 24
        inc bp
        jmp .loop

.finished:
    mov [MMAP_ENTRY_COUNT], bp
    ret