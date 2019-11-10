section .bss

idt:
    resd 100h

section .text

idtr:
    dw 400h
    dd idt

global load_idt
load_idt:
    lidt [idtr]

    mov al, 11h  ; Init mode.
    out 20h, al
    out 0A0h, al

    mov al, 20h  ; Offsets.
    out 21h, al
    mov al, 28h
    out 0A1h, al

    mov al, 4
    out 21h, al
    mov al, 2
    out 0A1h, al

    mov eax, irq_1
    mov [idt + 21h * 8], ax
    mov word [idt + 21h * 8 + 2], 8h
    mov byte [idt + 21h * 8 + 4], 0
    mov byte [idt + 21h * 8 + 5], 10001110b
    shr eax, 16
    mov [idt + 21h * 8 + 6], ax

    mov al, 1
    out 21h, al
    out 0A1h, al

    mov al, 0FDh  ; Enable specific interrupts.
    out 21h, al
    mov al, 0FFh
    out 0A1h, al

    sti
    ret

irq_1:
    pusha

    extern keyboard_strike
    call   keyboard_strike


    mov al, 0x20
    out 0x20, al

    popa
    iret