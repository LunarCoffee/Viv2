#include "../include/lib/alias.h"
#include "../include/drivers/vga/tvga.h"

int k_main() {
    tvga_init();
    tvga_puts("Hello, Viv2!\n");
    tvga_puts("Hello, Viv2!");
    tvga_puts("Hello, V\niv2!\n");
    tvga_puts("asidjaoisdjoiasjdioasjdiojiofjeiopgjiojzsdiojgfiobjawiopefniosdjfqwiopjernbiojwpdijfibw");
    
    while (true)
        asm("hlt");
}
