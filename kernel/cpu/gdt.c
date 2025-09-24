#include <citrus/cpu/gdt.h>
#include <citrus/tty/tty.h>
#include <citrus/log.h>

ui64 gdt_addr;
GDT gdt;
GDTR gdt_ptr;
tss_t the_tss;

void gdt_ent(ui8 num, ui32 base, ui16 limit, ui8 access, ui8 flags)
{
	gdt.gdt_ent[num].limit 		 = (limit & 0xFFFF);
	
	gdt.gdt_ent[num].base_low 	 = (base & 0xFFFF);
	gdt.gdt_ent[num].base_mid 	 = (base << 16) & 0xFF;
	gdt.gdt_ent[num].base_high 	 = (base << 24) & 0xFF;
	
	gdt.gdt_ent[num].access_byte = access;
	gdt.gdt_ent[num].flags 		 = (((limit >> 16) & 0xF) | (flags & 0xF0));
}

void gdt_load(GDTR le_gdt_pointer)
{
	__asm__ volatile("lgdt %0\n\t"
                 "push $0x48\n\t"
                 "lea 1f(%%rip), %%rax\n\t"
                 "push %%rax\n\t"
                 "lretq\n\t"
                 "1:\n\t"
                 "mov $0x50, %%eax\n\t"
                 "mov %%eax, %%ds\n\t"
                 "mov %%eax, %%es\n\t"
                 "mov %%eax, %%fs\n\t"
                 "mov %%eax, %%gs\n\t"
                 "mov %%eax, %%ss\n\t"
                 :
                 : "m"(le_gdt_pointer)
                 : "rax", "memory");
                 
}

void gdt_init()
{
	putsk("[GDT] initializing GDT...\n");
	
	gdt_ptr.limit = sizeof(gdt) - 1;
	gdt_ptr.base = (ui64) &gdt;
	
	gdt_addr = gdt_ptr.base;
	
	
	gdt_ent(0, 0, 0, 0, 0);                            // Null-Segment                 0x00

    gdt_ent(1,  0,  (ui16) 0xFFFF,      0x9A, 0xA0);    // Kernel 16bit Code Segment    0x08
    gdt_ent(2,  0,  (ui16) 0xFFFF,      0x92, 0xC0);    // Kernel 16bit Code Segment    0x10
    gdt_ent(3,  0,  (ui16) 0xFFFF,      0x9A, 0xA0);    // User 16bit Code Segment    0x18
    gdt_ent(4,  0,  (ui16) 0xFFFF,      0x92, 0xC0);    // User 16bit Code Segment    0x20

    gdt_ent(5,  0,  (ui16) 0xFFFFFFFF,  0x9A, 0xA0);    // Kernel 32bit Code Segment    0x28
    gdt_ent(6,  0,  (ui16) 0xFFFFFFFF,  0x92, 0xC0);    // Kernel 32bit Code Segment    0x30
    gdt_ent(7,  0,  (ui16) 0xFFFFFFFF,  0x9A, 0xA0);    // User 32bit Code Segment    0x38
    gdt_ent(8,  0,  (ui16) 0xFFFFFFFF,  0x92, 0xC0);    // User 32bit Code Segment    0x40

    gdt_ent(9,  0,  (ui16) 0xFFFFF,     0x9A, 0xA0);    // Kernel 64bit Code Segment    0x48
    gdt_ent(10, 0, (ui16) 0xFFFFF,      0x92, 0xC0);    // Kernel 64bit Data Segment    0x50
    gdt_ent(11, 0, (ui16) 0xFFFFF,      0xFA, 0xA0);    // User   64bit Data Segment    0x58
    gdt_ent(12, 0, (ui16) 0xFFFFF,      0xF2, 0xC0);    // User   64bit Data Segment    0x60

	 // TSS 0x28
    gdt.tss.length 		= 104;
    gdt.tss.base_low 	= (ui16) (((ui64) &the_tss) & 0xffff);
    gdt.tss.base_mid 	= (ui8) (((ui64) &the_tss >> 16) & 0xff);
    gdt.tss.flags1 		= 0b10001001;
    gdt.tss.flags2 		= 0;
    gdt.tss.base_high 	= (ui8) (((ui64) &the_tss >> 24) & 0xff);
    gdt.tss.base_upper 	= (ui32) (((ui64) &the_tss >> 32) & 0xffffffff);
    gdt.tss.reserved 	= 0;
    
    gdt_load(gdt_ptr);
    //putsk("Loaded GDT at %X\n\n", gdt_addr);
    tss_init();
	
}

void tss_load(void) {
    //putsk("Loading TSS at %X...\n", &the_gdt.tss);
    // this must be the offset of tss
    __asm__ volatile("mov $0x68, %%ax\n\t"
                 "ltr %%ax\n\t"
                 :
                 :
                 : "rax", "memory");
}

void tss_set_rsp0(ui64 rsp0) { the_tss.rsp0 = rsp0; }

void tss_init(void) {
    the_tss.resereved0 = 0;
    the_tss.rsp0 = 0;
    the_tss.rsp1 = 0;
    the_tss.rsp2 = 0;
    the_tss.resereved1 = 0;
    the_tss.resereved2 = 0;
    the_tss.ist1 = 0;
    the_tss.ist2 = 0;
    the_tss.ist3 = 0;
    the_tss.ist4 = 0;
    the_tss.ist5 = 0;
    the_tss.ist6 = 0;
    the_tss.ist7 = 0;
    the_tss.resereved3 = 0;
    the_tss.resereved4 = 0;
    the_tss.iomap_offset = 0;

    tss_load();
}
