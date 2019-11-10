#include "../../../include/drivers/vga/tvga.h"
#include "../../../include/drivers/keyboard/keyboard.h"

extern u8 read_scan_code(void);

static bool shift_down;

void keyboard_strike(void) {
    u8 scan_code = read_scan_code();

    if (scan_code == 0x2A || scan_code == 0x36)
        shift_down = true;
    else if (scan_code == 0xAA || scan_code == 0xB6)
        shift_down = false;

    // Key is released.
    if (scan_code & 0x80)
        return;

    u8 ch = shift_down ? shift_char_table[scan_code] : char_table[scan_code];
    if (ch)
        tvga_putc(ch);
}
