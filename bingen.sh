#!/usr/bin/bash

shopt -s globstar
nasm -felf32 src/kernel/boot/boot.asm -o a_boot.o
nasm -felf32 src/kernel/boot/gdt.asm -o a_gdt.o
nasm -felf32 src/kernel/boot/idt.asm -o a_idt.o
nasm -felf32 src/kernel/drivers/keyboard/keyboard.asm -o a_keyboard.o

i686-elf-gcc -c src/include/**/*.h src/kernel/**/*.c src/kernel/main.c -std=gnu99 -ffreestanding -masm=intel -O2 -Wall -Wextra
i686-elf-gcc -T linker.ld -o viv2.bin -ffreestanding -O2 -nostdlib ./*.o -lgcc

rm ./*.o src/include/**/*.gch
