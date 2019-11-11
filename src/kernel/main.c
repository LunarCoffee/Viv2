#include "../include/lib/alias.h"
#include "../include/drivers/vga/tvga.h"
#include "../include/drivers/vga/tvga_cursor.h"
#include "../include/drivers/keyboard/keyboard.h"

int k_main() {
    tvga_init();
    tvga_puts("Viv2 0.1.0. GDT, IDT loaded.\n");
    enable_keyboard();

    // asm volatile (
    //     "mov edx, 0\n"
    //     "mov eax, 0\n"
    //     "mov ecx, 0\n"
    //     "div ecx"
    // );

    while (true)
        asm("hlt");
}
