print_string_bios:
    mov ah, 0x0e
    .loop:
        cmp [si], byte 0
        je .exit
        mov al, [si]
        int 0x10
        inc si
        jmp .loop
    .exit:
    ret