#ifndef IDT_H
#define IDT_H 1

#include "macros.h"

/* --- Externals definition --- */
extern void kbHandler(void);
extern void wPort(unsigned short port, unsigned char data); //<<< write port
extern void loadIdt(unsigned long* idt_ptr);

/* --- Struct definition --- */
struct IDT_entry {
	unsigned short int offset_low;
	unsigned short int selector;
	unsigned char zero;
	unsigned char flags;
	unsigned short int offset_high;
};
struct IDT_entry idt[IDT_SIZE];

/* --- Function definition --- */
/**
 * Initializes the Interrupt Directory Table
 */
void idtInit(void);

/**
 * Writes the codes into the IDT
 */
void doWrites(void);

#endif /* IDT_H */
