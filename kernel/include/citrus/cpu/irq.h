#ifndef IRQ_H
#define IRQ_H

#include <citrus/types.h>
#include <citrus/cpu/idt.h>

typedef InterruptRegisters* (*handler_t)(InterruptRegisters* regs);

void irq_install_handler(int irq, handler_t handler);
void irq_uninstall_handler(int irq);
InterruptRegisters* irq_handler(InterruptRegisters* regs);

#endif
