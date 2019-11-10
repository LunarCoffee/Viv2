section .text

gdt:
null_seg:
    dq 0

code_seg:
    dw 0FFFFh
    dw 0
    db 0
    db 10011010b
    db 11001111b
    db 0

data_seg:
    dw 0FFFFh
    dw 0
    db 0
    db 10010010b
    db 11001111b
    db 0

gdt_end:

gdtr:
    dw gdt_end - gdt
    dd gdt

global load_gdt
load_gdt:
    lgdt [gdtr]
    jmp 8h:reload
    ret

reload:
    mov ax, 10h
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret