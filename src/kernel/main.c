#include "../include/lib/alias.h"
#include "../include/drivers/vga/tvga.h"

int k_main() {
    tvga_init();
    tvga_puts("Viv2 0.1.0. GDT, IDT loaded.\n");
    
    while (true)
        asm("hlt");
}
