#include <citrus/cpu/halinit.h>
#include <citrus/cpu/gdt.h>

void hal_init() 
{
	gdt_init();
}
