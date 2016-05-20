
SOURCES=boot/boot.o kern/kernel.o kern/process.o kern/common.o kern/monitor.o kern/descriptor_tables.o kern/gdt.o kern/interrupt.o kern/isr.o kern/timer.o kern/ordered_map.o kern/paging.o kern/kheap.o kern/task.o

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS=-Tlink.ld
ASFLAGS=-felf


all: $(SOURCES) link

clean:
	-rm $(wildcard **/*.o) kernel
	-rm *.o

link:
	ld -m elf_i386 $(LDFLAGS) -o kernel $(SOURCES)

.c.o:
	gcc -m32 -fno-stack-protector -c $< -o $@
 
.s.o:
	nasm $(ASFLAGS) $<
