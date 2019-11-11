#ifndef VIV2_PORTS_H
#define VIV2_PORTS_H

#include "alias.h"

void outb(u16 port, u8 value);
u8 inb(u16 port);

#endif
