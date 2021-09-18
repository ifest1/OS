[ORG 0x1000]

[bits 32]
mov al, 'A'
mov ah, 0x0f
mov [0xb8000], ax
jmp $