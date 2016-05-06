
/* interuptų deaktyvavimas */
#define cli asm("cli"::)

/* interuptų aktyvavimas */
#define sti asm("sti"::)

/* bito įrašymas į portą */
#define outb(port,value) \
	asm volatile ("outb %%al, %%dx" :: "d" (port), "a" (value));

/* bito įrašymas į portą su laiku */
#define outbp(port,value) \
	asm volatile ("outb %%al, %%dx; jmp 1f; 1:" :: "d" (port), "a" (value));

/* skaito bitą iš portą */
#define inb(port) ({    \
	unsigned char _v;       \
	asm volatile ("inb %%dx, %%al" : "=a" (_v) : "d" (port)); \
        _v;     \
})
