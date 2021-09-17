
[ORG 0x7C00]

; Saving the disk number an cleaning registers
; mov [DISK], dl
; xor ax, ax
; xor bx, bx
; mov es, ax
; mov ds, ax

; Creating stack function
;mov bp, 0x7c00
;mov sp, bp

; GDT:
;     dw GDT_END - GDT - 1
;     dw GDT
;     db 0
;     db 0, 0
;     db 0
;     dw 0xFFFF
;     db 0, 0, 0
;     db 0x91
;     db 11001110b
;     db 0

; GDT_END:

start:
    mov si, TEST_STRING
    call print_string
    call load_kernel
    jmp KERNEL_LOCATION

    ;jmp start_protected_mode

; start_protected_mode:
;     mov ax, 3
;     int 0x10

;     xor edx, edx
;     mov dx, es
;     shl edx, 4
;     add [GDT + 2], edx

;     cli
;     lgdt [GDT]
;     mov eax, cr0
;     or eax, 1
;     mov cr0, eax

;     mov bx, 0x08
;     mov fs, bx

;     mov ebp, 0x90000		; 32 bit stack base pointer
;     mov esp, ebp

;     jmp KERNEL_LOCATION

%include "print.asm"
%include "disk.asm"

DISK: db 0
TEST_STRING: db 'teste string', 0

times 510 - ($-$$) db 0
dw 0xAA55