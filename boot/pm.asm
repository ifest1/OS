switch_to_pm:
    cli
    lgdt [GDT_DESCRIPTOR]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    ret
