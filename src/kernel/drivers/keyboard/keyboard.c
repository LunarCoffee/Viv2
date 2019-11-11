#include "../../../include/drivers/vga/tvga.h"
#include "../../../include/drivers/keyboard/keyboard.h"
#include "../../../include/lib/ports.h"

extern u8 read_scan_code(void);

static u8 char_table[256] = {
    0,  0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    '-', '=', '\b', '\t',     
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 
    '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 
    0, 
    '*',
    0,
    ' ',
    0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
    '7', '8', '9', '-',
    '4', '5', '6', '+',
    '1', '2', '3', '0', '.',
    0
};

static u8 shift_char_table[256] = {
    0,  0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
    '_', '+', '\b', '\t',     
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 
    '\n', 0,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
    '"', '~', 0, '|',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 
    0, 
    '*',
    0,
    ' ',
    0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
    '7', '8', '9', '-',
    '4', '5', '6', '+',
    '1', '2', '3', '0', '.',
    0
};

static u8 caps_lock_char_table[256] = {
    0,  0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    '-', '=', '\b', '\t',      
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', 
    '\n', 0,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',
    '"', '~', 0, '|',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', 
    0, 
    '*',
    0,
    ' ',
    0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
    '7', '8', '9', '-',
    '4', '5', '6', '+',
    '1', '2', '3', '0', '.',
    0
};

static bool keyboard_enabled = true;
static bool shift_down;
static bool caps_lock_on;

void keyboard_strike(void) {
    u8 scan_code = inb(0x60);

    if (!keyboard_enabled)
        return;

    switch (scan_code) {
    case K_LSHIFT:
    case K_RSHIFT:
        shift_down = true;
        break;
    case 0xAA:
    case 0xB6:
        shift_down = false;
        break;
    case K_CAPSLOCK:
        caps_lock_on = !caps_lock_on;    
    }

    // Key is released.
    if (scan_code & 0x80)
        return;

    u8 ch = get_char(scan_code);
    if (ch)
        tvga_putc(ch);
}

u8 get_char(key_code kc) {
    if (shift_down)
        return shift_char_table[kc];
    if (caps_lock_on)
        return caps_lock_char_table[kc];
    return char_table[kc];
}
