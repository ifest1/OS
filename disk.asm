load_kernel:
    mov si, READING_FROM_DISK_MESSAGE
    call print_string

    mov bx, KERNEL_LOCATION
    mov ah, 0x02        ; BIOS read from disk operation
    mov al, 1           ; Number of sectors to read
    mov ch, 0           ; Read from the cylinder 0
    mov cl, 2           ; Starting from sector 2
    mov dh, 0           ; Head 0
    int 0x13
    jc disk_failure
    ret

disk_failure:
    mov si, DISK_FAILURE_MESSAGE
    call print_string
    ret

DISK_FAILURE_MESSAGE: db 'Failure on disk loading', 0
READING_FROM_DISK_MESSAGE: db 'Loading Kernel from disk', 0
KERNEL_LOCATION equ 0x1000