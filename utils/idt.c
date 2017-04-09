#include "idt.h"

void idtInit(void)
{
	unsigned long kbAddress;
	unsigned long idtAddress;
	unsigned long idtPtr[2];

	/* populate IDT entry of keyboard's interrupt */
	kbAddress = (unsigned long) kbHandler;
	idt[0x21].offset_low = LOW16(kbAddress);
	idt[0x21].offset_high = HIGH16(kbAddress);
	idt[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	idt[0x21].flags = INTERRUPT_GATE;
	idt[0x21].zero = 0;

	doWrites();

	/* fill the IDT descriptor */
	idtAddress = (unsigned long) idt;
	idtPtr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idtAddress & 0xFFFF) << 16);
	idtPtr[1] = idtAddress >> 16 ;

	loadIdt(idtPtr);
}

void doWrites(void)
{
	/* ICW1 - begin initialization */
	wPort(0x20, 0x11);
	wPort(0xA0, 0x11);

	/* ICW2 - remap offset address of IDT */
	wPort(0x21, 0x20);
	wPort(0xA1, 0x28);

	/* ICW3 - setup cascading */
	wPort(0x21, 0x00);
	wPort(0xA1, 0x00);

	/* ICW4 - environment info */
	wPort(0x21, 0x01);
	wPort(0xA1, 0x01);
	/* Initialization finished */

	/* mask interrupts */
	wPort(0x21, 0xFF);
	wPort(0xA1, 0xFF);
}
