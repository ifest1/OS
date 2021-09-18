GDT_START:
    dd 0x0
    dd 0x0

GDT_CODE_SEGMENT:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0

GDT_DATA_SEGMENT:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

GDT_END:

GDT_DESCRIPTOR:
    dw GDT_END - GDT_START - 1
    dd GDT_START

CODE_SEG equ GDT_CODE_SEGMENT - GDT_START
DATA_SEG equ GDT_DATA_SEGMENT - GDT_START
