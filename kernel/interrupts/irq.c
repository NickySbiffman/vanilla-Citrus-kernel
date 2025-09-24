#include <citrus/cpu/irq.h>
#include <citrus/cpu/pic.h>
#include <citrus/io.h>
#include <citrus/tty/tty.h>

void* irq_handlers[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void irq_install_handler(int irq, handler_t handler) {
	irq_handlers[irq] = handler;
}

void irq_uninstall_handler(int irq) {
	irq_handlers[irq] = 0;
}

InterruptRegisters* irq_handler(InterruptRegisters* regs) {
	// void (*handler)(InterruptRegisters* regs); 
	handler_t handler;
	handler = irq_handlers[regs->interrupt - 32];

	if (handler)
		handler(regs);
	iowait();
	pic_eoi(regs->interrupt - 32);

	return regs;
}
