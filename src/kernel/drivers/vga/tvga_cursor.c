#include "../../../include/drivers/vga/tvga_cursor.h"
#include "../../../include/lib/ports.h"

void enable_cursor(void) {
    // Make the cursor fill most of the scanline height.
    outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | 0);
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | 0xD);
}

void reposition_cursor(u16 pos) {
    // Move the cursor directly in front of the last typed character. 
	outb(0x3D4, 0xF);
	outb(0x3D5, pos & 0xFF);
	outb(0x3D4, 0xE);
	outb(0x3D5, (pos >> 8) & 0xFF);
}
