#include "../../../include/drivers/vga/tvga.h"
#include "../../../include/drivers/vga/tvga_cursor.h"
#include "../../../include/lib/ports.h"

static const isz TW = 80;
static const isz TH = 25;

static u16* vram;
static i8 row;
static i8 col;
static u8 default_color;

void tvga_init(void) {
    vram = (u16*) 0xB8000;
    default_color = TVGA_COLOR(TVGA_COLOR_WHITE, TVGA_COLOR_BLACK);

    for (isz i = 0; i < TW * TH; i++)
        tvga_putc(' ');

    row = 0;
    col = 0;
    enable_cursor();
}

inline void tvga_putc(u8 ch) {
    tvga_putcc(ch, default_color);
}

void tvga_putcc(u8 ch, u16 color) {
    switch (ch) {
    case '\n':
        // Mark rest of row for deletion.
        for (isz i = TW - col; i > 1; i--)
            tvga_putcc(0xFF, color);

        if (++row == TH)
            tvga_scroll();
    case '\r':
        col = 0;
        break;
    case '\b':
        vram[row * TW + col - 1] = TVGA_CELL(' ', color);
        if (--col < 0) {
            col = TW - 1;
            if (--row < 0) {
                row = 0;
                col = 0;
            }
        }

        // Delete characters which are marked for deletion.
        if (row + col > 0 && (vram[row * TW + col - 1] & 0xFF) == 0xFF)
            tvga_putcc('\b', color);
        break;
    default:
        vram[row * TW + col] = TVGA_CELL(ch, color);
        if (++col == TW) {
            col = 0;
            if (++row == TH)
                tvga_scroll();
        }
    }
	reposition_cursor(row * TW + col);
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

    for (isz i = 0; i < TW * (TH - 1); i++)
        vram[i] = vram[i + TW];
    for (isz i = TW * (TH - 1); i < TW * TH; i++)
        vram[i] = TVGA_CELL(' ', default_color);
}
