#include <citrus/cpu/idt.h>
#include <citrus/cpu/isr.h>
#include <citrus/cpu/irq.h>
//#include <cpu/cpu.h>
#include <citrus/cpu/pic.h>
#include <citrus/tty/tty.h>

IDTR idtr;
IDTEntry idt[IDT_ENTRY_COUNT];
extern ui64 isr_stub_table[IDT_ENTRY_COUNT];

void idt_load(void) {
    __asm__ volatile("lidt %0" : : "m"(idtr) : "memory");
}

void interrupts_init() {
    putsk("[IDT] Stubbing every IDT Gate...\n");
	for(size_t vector = 0; vector < sizeof(idt) / sizeof(IDTEntry); vector++) {
        // log("[IDT] Stubbing IDT Gate N%i\n", vector);
        idt_set_gate(vector, isr_stub_table[vector], IDT_ATTR_PRESENT | IDT_ATTR_INTERRUPT_GATE);
    }
}

void idt_init(void) {
    putsk("[IDT] Initializing IDT...\n");
	interrupts_init();

    idtr.base = (ui64) idt;
    idtr.limit = IDT_ENTRY_COUNT * sizeof(IDTEntry) - 1;

    pic_init();
    idt_load();
	enableInterrupts(); // 'sti' instruction
    putsk("[IDT] IDT Initialized!\n");
}

void idt_set_gate(int i, ui64 handler, ui16 flags) {
    idt[i].base_low = (ui16) (handler & 0xffff);
    idt[i].base_mid = (ui16) (handler >> 16) & 0xffff;
    idt[i].base_high = (ui32) (handler >> 32) & 0xffffffff;
    idt[i].flags = flags;
    idt[i].reserved = 0;
    idt[i].selector = 0x08;
    // log("[IDT] Set IDT Gate %i handler to %x with flags %i\n", i, handler, flags);
}
