#include "../../include/drivers/vga/tvga.h"

void divide_by_zero_handler(void) {
    tvga_puts("divide by zero\n");
}

void double_fault_handler(void) {
    tvga_puts("double fault\n");
}
