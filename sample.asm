print_string:
    cld
    htl
    mov si, message
    mov ah, 0x0e
    mov bh, 0

    .loop:
        lodsb
        int 0x10
        cmp al, 0x00
        jne .loop

message: db 'Testando', 0