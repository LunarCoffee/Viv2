MAGIC    equ 1BADB002h
FLAGS    equ 11b
CHECKSUM equ -MAGIC - FLAGS

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bss

align 16
stack_b:
    resb 4000h ; 16 KiB stack.
stack_t:

section .text

global _start
_start:
    mov esp, stack_t

    extern k_main
    call k_main

    cli
l:  hlt
    jmp l