/*folder - main.c (init file)
 *   @developer: Nicky Sbiffman
 * 	 @license: BSD 3-Clause
 *   @Programming language: "C"
*/

#include <citrus/tty.h>
#include <citrus/halinit.h>
#include <citrus/log.h>


void kernel_main(void) 
{
	hal_init();	
	putsk("\nhello from Citrus 64 bit unix-like operating system\nBSD 3-Clause license\nCopyright (c) Nicky Sbiffman\n\n");
	__asm__("sti");
	
	
	
	__asm__ volatile ("cli");
	for (;;) __asm__ volatile ("hlt");
}

