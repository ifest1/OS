[bits 32]
NULL_CHAR equ ' '
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0F
WHITE_ON_BLUE equ 0x1F

clear_screen:
    mov cx, 2000
    mov edx, VIDEO_MEMORY

    .loop:
        mov al, NULL_CHAR
        mov ah, WHITE_ON_BLUE
        mov [edx], ax
        add edx, 2

        dec cx
        cmp cx, 0
        jne .loop
    ret