#ifndef INT_H
#define INT_H

#include <citrus/types.h>
#include <stddef.h>
//#include <cpu/cpu.h>


#define IDT_ENTRY_COUNT 256

#define IDT_ATTR_INTERRUPT_GATE 0x0e00
#define IDT_ATTR_PRESENT 0x8000


typedef struct {
    ui16 limit;
    ui64 base;
} __attribute__((packed)) IDTR;

typedef struct {
    ui16 base_low;
    ui16 selector;
    ui16 flags;		// ist + attributes
    ui16 base_mid;
    ui32 base_high;
    ui32 reserved;
} __attribute((packed)) IDTEntry;


typedef struct {
    ui64 r15;
    ui64 r14;
    ui64 r13;
    ui64 r12;
    ui64 r11;
    ui64 r10;
    ui64 r9;
    ui64 r8;
    ui64 rbp;
    ui64 rdi;
    ui64 rsi;
    ui64 rdx;
    ui64 rcx;
    ui64 rbx;
    ui64 rax;
    ui64 interrupt;  // this is pushed in the macro (Hopefully it's 8 bytes)
    ui64 error_code; // This is pushed by the cpu if the interrupt is an
                    // error interrupt. If not, then we push a dummy value
                    // of 0(in the macro)
    ui64 iret_rip;   // iret prefix means that the cpu pushed this
                    // automatically and we didn't
    ui64 iret_cs;
    ui64 iret_flags;
    ui64 iret_rsp;
    ui64 iret_ss;
} __attribute__((packed)) InterruptRegisters;

void idt_init(void);
void idt_set_gate(int i, ui64 handler, ui16 flags);
void idt_initGates();
void idt_load(void);

#endif
