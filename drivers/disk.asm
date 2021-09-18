disk_failure:
    jmp $

load_kernel:
    mov [DISK], dl
    mov bx, KERNEL_LOCATION
    mov ah, 0x02        ; BIOS read from disk operation
    mov al, 15          ; Number of sectors to read
    mov ch, 0           ; Read from the cylinder 0
    mov cl, 2           ; Starting from sector 2
    mov dh, 0           ; Head 0
    int 0x13
    jc disk_failure
    ret

DISK: db 0
KERNEL_LOCATION equ 0x1000