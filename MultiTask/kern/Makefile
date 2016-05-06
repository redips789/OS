OBJ=kernel
CC=gcc -Wall -m32 -fno-stack-protector

all: $(OBJ) 

kernel: kernel.o screen.o lib.o gdt.o idt.o interrupt.o int.o pic.o syscalls.o mm.o printk.o process.o schedule.o sched.o 
	ld -melf_i386 --oformat binary -Ttext 1000 $^ -o $@

int.o: int.asm 
	nasm -f elf -o $@ $^ 

sched.o: sched.asm
	nasm -f elf -o $@ $^ 

.o: .c 
	$(CC) -c $^

clean:
	rm -f $(OBJ) *.o
