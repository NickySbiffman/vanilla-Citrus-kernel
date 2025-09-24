#ifndef IO_H
#define IO_H

#include <citrus/types.h>

void iowait();

unsigned char inb(unsigned short port);

void outb(ui16 port, ui8 val);
#endif
