#include "types.h"
#include "lib.h"

void do_syscalls(int sys_num)
{
	char *u_str;
	int i;

	if (sys_num == 1) {
		asm("mov %%ebx, %0": "=m"(u_str) :);
		for (i = 0; i < 100000; i++);	/* temporisation */
		printk(u_str);
	} else {
		printk("unknown syscall %d\n", sys_num);
	}

	return;
}
