#####################
# Build simple kernel
#
# Copyright (C) 2014  Arjun Sreedharan
# License: GPL version 2 or higher http://www.gnu.org/licenses/gpl.html
#
#####################

ASSEMBLER = nasm
C         = gcc
EMULATOR  = qemu-system-i386
LINKER    = ld

ASM_FLAGS  = -f elf32
C_FLAGS    = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs
C_WARNINGS = -Wall -Wextra -Werror
EMU_FLAGS  = -kernel
LD_FLAGS   = -m elf_i386


# Run assembler to create an object file
kasm.o: kernel.asm
	$(ASSEMBLER) $(ASM_FLAGS) kernel.asm -o kasm.o

# Compile the kernel code
keyboard.o: drivers/keyboard.c drivers/keyboard.h utils/macros.h
	$(C) $(C_FLAGS) $(C_WARNINGS) -c drivers/keyboard.c -o keyboard.o

screen.o: drivers/screen.c drivers/screen.h utils/macros.h
	$(C) $(C_FLAGS) $(C_WARNINGS) -c drivers/screen.c -o screen.o

idt.o: utils/idt.c utils/idt.h
	$(C) $(C_FLAGS) $(C_WARNINGS) -c utils/idt.c -o idt.o

math.o: utils/math.c utils/math.h utils/macros.h
	$(C) $(C_FLAGS) $(C_WARNINGS) -c utils/math.c -o math.o

kc.o: kernel.c keyboard.o screen.o idt.o math.o
	$(C) $(C_FLAGS) $(C_WARNINGS) -c kernel.c -o kc.o

# Make the kernel executable
kernel: kasm.o kc.o link.ld
	$(LINKER) $(LD_FLAGS) -T link.ld -o kernel kasm.o kc.o keyboard.o screen.o idt.o math.o

# Run the QEMU elumator
emulate: kernel
	$(EMULATOR) $(EMU_FLAGS) kernel

clean:
	rm -rf *.o kernel
