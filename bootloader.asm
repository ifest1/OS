[ORG 0x7C00]

DISK: db 0
KERNEL_LOCATION equ 0x1000

GDT:
    dw GDT_END - GDT - 1
    dw GDT
    db 0
    db 0, 0
    db 0
    dw 0xFFFF
    db 0, 0, 0
    db 0x91
    db 11001110b
    db 0

GDT_END:


mov [DISK], dl
xor ax, ax
mov es, ax
mov ds, ax

start:
    xor bx, bx

    mov ah, 0x02        ; BIOS read from disk operation
    mov al, 1           ; Number of sectors to read
    mov ch, 0           ; Read from the cylinder 0
    mov cl, 2           ; Starting from sector 2
    mov dh, 0           ; Head 0
    mov dl, [DISK]

    push 0
    pop es
    mov bx, KERNEL_LOCATION
    int 0x13

    jmp start_protected_mode

start_protected_mode:
    mov ax, 3
    int 0x10

    xor edx, edx
    mov dx, es
    shl edx, 4
    add [GDT + 2], edx

    cli
    lgdt [GDT]
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    mov bx, 0x08
    mov fs, bx

    mov ebp, 0x90000		; 32 bit stack base pointer
    mov esp, ebp

    jmp KERNEL_LOCATION

times 510 - ($-$$) db 0
dw 0xAA55