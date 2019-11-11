section .bss

idt:
    resd 100h

section .text

idtr:
    dw 400h
    dd idt

%macro IDT_ENTRY 3
    mov eax, %1
    mov [idt + %2 * 8], ax
    mov word [idt + %2 * 8 + 2], 8h
    mov byte [idt + %2 * 8 + 4], 0
    mov byte [idt + %2 * 8 + 5], %3
    shr eax, 16
    mov [idt + %2 * 8 + 6], ax
%endmacro

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

    IDT_ENTRY ex_0, 0h, 8Fh
    IDT_ENTRY ex_8, 8h, 8Fh

    IDT_ENTRY irq_1, 21h, 8Eh

    mov al, 1
    out 21h, al
    out 0A1h, al

    mov al, 0FDh  ; Enable specific hardware interrupts.
    out 21h, al
    mov al, 0FFh
    out 0A1h, al

    sti
    ret

%macro EXCEPTION_HANDLER 2
ex_%1:
    cli
    pusha

    ; Push padding byte if the exception doesn't push an error code.
    %if %1 != 8 && %1 != 17 && %1 != 30 && (%1 < 10 || %1 > 14)
        push byte 0
    %endif

    push byte %1

    extern %2
    call   %2

    popa
    sti
    iret
%endmacro

EXCEPTION_HANDLER 0, divide_by_zero_handler
EXCEPTION_HANDLER 8, double_fault_handler

%macro IRQ_HANDLER 2
irq_%1:
    pusha

    extern %2
    call   %2

    %if %1 > 7
        out 0xA0, al
    %endif

    mov al, 0x20
    out 0x20, al

    popa
    iret
%endmacro

IRQ_HANDLER 1, keyboard_strike
