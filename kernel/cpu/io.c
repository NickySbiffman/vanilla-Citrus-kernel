#include <citrus/io.h>
#include <citrus/types.h>

#define UNUSED_PORT     0x80

void outb(ui16 port, ui8 val)
{
	__asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void iowait() {
    outb(UNUSED_PORT, 0);
}


unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ volatile("in %%dx , %% al" : "=a" (result) : "d" (port));
    return result;
}

