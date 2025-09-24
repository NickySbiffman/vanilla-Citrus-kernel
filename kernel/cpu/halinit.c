#include <citrus/cpu/halinit.h>
#include <citrus/cpu/gdt.h>
#include <citrus/cpu/idt.h>

void hal_init() 
{
	gdt_init();
	idt_init();
}
