#ifndef GDT_H
#define GDT_H

#pragma once

#include <citrus/types.h>

#define GDT_CODE_SEGMENT 0x48
#define GDT_DATA_SEGMENT 0x50
#define GDT_ENTRY_COUNT 13

typedef struct {
    ui16 limit;
    ui16 base_low;
    ui8  base_mid;
    ui8  access_byte;
    ui8  flags;
    ui8  base_high;
} __attribute__((packed)) GDTEntry;

typedef struct {
    ui16 length;
    ui16 base_low;
    ui8  base_mid;
    ui8  flags1;
    ui8  flags2;
    ui8  base_high;
    ui32 base_upper;
    ui32 reserved;
} __attribute__((packed)) TSSEntry;

typedef struct {
    ui32 resereved0;
    ui64 rsp0;
    ui64 rsp1;
    ui64 rsp2;
    ui64 resereved1;
    ui64 resereved2;
    ui64 ist1;
    ui64 ist2;
    ui64 ist3;
    ui64 ist4;
    ui64 ist5;
    ui64 ist6;
    ui64 ist7;
    ui64 resereved3;
    ui16 resereved4;
    ui16 iomap_offset;
} __attribute__((packed)) tss_t;

typedef struct {
    GDTEntry gdt_ent[GDT_ENTRY_COUNT];
    TSSEntry tss;
} __attribute__((packed)) GDT;

typedef struct {
    ui16 limit;
    ui64 base;
} __attribute__((packed)) GDTR;


void gdt_init();
void gdt_load(GDTR le_gdt_pointer);
void gdt_ent(ui8 num, ui32 base, ui16 limit, ui8 access, ui8 flags);

void tss_init(void);
void tss_load();
void tss_set_rsp0(ui64 rsp0);

#endif
