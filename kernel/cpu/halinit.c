#include <citrus/halinit.h>
#include <citrus/gdt.h>

void hal_init() 
{
	gdt_init();
}
