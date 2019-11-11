#ifndef VIV2_TVGA_H
#define VIV2_TVGA_H

#include "../../lib/alias.h"

#define TVGA_COLOR(fg, bg) fg | bg << 4
#define TVGA_CELL(ch, color) (u16) (ch | color << 8)

typedef enum {
    TVGA_COLOR_BLACK,
	TVGA_COLOR_BLUE,
	TVGA_COLOR_GREEN,
	TVGA_COLOR_CYAN,
	TVGA_COLOR_RED,
	TVGA_COLOR_MAGENTA,
	TVGA_COLOR_BROWN,
	TVGA_COLOR_LIGHT_GREY,
	TVGA_COLOR_DARK_GREY,
	TVGA_COLOR_LIGHT_BLUE,
	TVGA_COLOR_LIGHT_GREEN,
	TVGA_COLOR_LIGHT_CYAN,
	TVGA_COLOR_LIGHT_RED,
	TVGA_COLOR_LIGHT_MAGENTA,
	TVGA_COLOR_LIGHT_BROWN,
	TVGA_COLOR_WHITE
} tvga_color;

void tvga_init(void);

void tvga_putc(u8 ch);
void tvga_putcc(u8 ch, u16 color);

void tvga_puts(const char* s);
void tvga_putsc(const char* s, u16 color);

void tvga_scroll(void);

#endif
