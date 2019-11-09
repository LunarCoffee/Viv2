#include "../../../include/drivers/vga/tvga.h"

static const isz TW = 80;
static const isz TH = 25;

static u16* buffer;
static isz row;
static isz col;
static u8 default_color;

void tvga_init(void) {
    buffer = (u16*) 0xB8000;
    default_color = TVGA_COLOR(TVGA_COLOR_LIGHT_BROWN, TVGA_COLOR_BLUE);

    // Ensure the screen is cleared.
    for (isz i = 0; i < TW * TH; i++)
        tvga_putc(' ');

    row = 0;
    col = 0;
}

inline void tvga_putc(u8 ch) {
    tvga_putcc(ch, default_color);
}

void tvga_putcc(u8 ch, u16 color) {
    if (ch == '\n') {
        col = 0;
        if (++row == TH)
            tvga_scroll();
    } else if (ch == '\r') {
        col = 0;
    } else {
        buffer[row * TW + col] = TVGA_CELL(ch, color);
        if (++col == TW) {
            col = 0;
            if (++row == TH)
                tvga_scroll();
        }
    }
}

inline void tvga_puts(const char* s) {
    tvga_putsc(s, default_color);
}

void tvga_putsc(const char* s, u16 color) {
    for (isz i = 0; s[i]; i++)
        tvga_putcc(s[i], color);
}

void tvga_scroll(void) {
    row--;
    col = 0;

    // Shift everything up.
    for (isz i = 0; i < TW * (TH - 1); i++)
        buffer[i] = buffer[i + TW];

    // Clear bottom row.
    for (isz i = TW * (TH - 1); i < TW * TH; i++)
        buffer[i] = TVGA_CELL(' ', default_color);
}
