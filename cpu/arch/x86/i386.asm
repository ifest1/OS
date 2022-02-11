[BITS 32]
[extern irq_handler]
[extern syscall_handler]

MULTIBOOT_PAGE_ALIGN	      equ 1<<0
MULTIBOOT_MEMORY_INFO	      equ 1<<1
MULTIBOOT_HEADER_MAGIC	    equ 0x1BADB002
MULTIBOOT_HEADER_FLAGS	    equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
CHECKSUM                    equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)


section .multiboot
    align 4
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd CHECKSUM


section .bss
	align 8
  stack_bottom:
	  resb 16384
  stack_top:


section .text:
  global start:function (start.end - start)
  start:
	  mov esp, stack_top
    push eax
    push ebx
	  extern main
	  call main
    sti

.hang:
	hlt
	jmp .hang

.end:

GLOBAL gdt_flush
EXTERN gdt_p
gdt_flush:
    lgdt[gdt_p]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret

GLOBAL call_sys
call_sys:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 28]
    push eax
    mov eax, [ebp + 24]
    push eax
    mov eax, [ebp + 20]
    push eax
    mov eax, [ebp + 16]
    push eax
    mov eax, [ebp + 12]
    push eax
    mov eax, [ebp + 8]
    call eax
    add esp, 20

    pop ebp
    ret

GLOBAL _syscall0, _syscall1, _syscall2, _syscall3, _syscall4, _syscall5
_syscall0:
	mov eax, [esp + 4]
	int 0x80
	ret

_syscall1:
	push ebx
	mov eax, [esp + 4 + 4]
	mov ebx, [esp + 4 + 8]
	int 0x80
	pop ebx
	ret

_syscall2:
	push ebx
	push ecx

	mov eax, [esp + 8 + 4]
	mov ebx, [esp + 8 + 8]
	mov ecx, [esp + 8 + 12]
	int 0x80

	pop ecx
	pop ebx
	ret

_syscall3:
	push ebx
	push ecx

	mov eax, [esp + 8 + 4]
	mov ebx, [esp + 8 + 8]
	mov ecx, [esp + 8 + 12]
  mov edx, [esp + 8 + 16]
	int 0x80

	pop ecx
	pop ebx
	ret
  iret

%macro ISR_NOERRCODE 1
  [GLOBAL isr%1]
  isr%1:
    push byte 0
    push byte %1
    jmp 0x08:isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
  [GLOBAL isr%1]
  isr%1:
    push byte %1
    jmp 0x08:isr_common_stub
%endmacro

%macro ISR_DEVICES 2
  [GLOBAL isr%2]
  isr%2:
    push byte %1
    push byte %2
    jmp 0x08:isr_common_stub
%endmacro

isr_common_stub:
  pusha

  mov ax, ds
  push eax

  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  call irq_handler

  pop eax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  popa
  add esp, 8
  sti
  iret

GLOBAL irq_128_handler
irq_128_handler:
  pusha

  mov ax, ds
  push eax

  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  call syscall_handler

  pop eax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  popa
  add esp, 8
  sti
  iret

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

ISR_DEVICES 0, 32
ISR_DEVICES 1, 33
ISR_DEVICES 2, 34
ISR_DEVICES 3, 35
ISR_DEVICES 4, 36
ISR_DEVICES 5, 37
ISR_DEVICES 6, 38
ISR_DEVICES 7, 39
ISR_DEVICES 8, 40
ISR_DEVICES 9, 41
ISR_DEVICES 10, 42
ISR_DEVICES 11, 43
ISR_DEVICES 12, 44
ISR_DEVICES 13, 45
ISR_DEVICES 14, 46
ISR_DEVICES 15, 47
