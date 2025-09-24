#ifndef ISR_H
#define ISR_H
#pragma once

#include <citrus/types.h>
#include <citrus/cpu/idt.h>

InterruptRegisters* isr_handler(InterruptRegisters* regs);

#endif
