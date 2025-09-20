#ifndef IO_H
#define IO_H

void outb(ui16 port, ui8 val)
{
	__asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}
#endif
