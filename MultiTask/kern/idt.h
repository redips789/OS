/* idt.h */

#define IDTBASE  0x800		/* adresas kuriam yra IDT */
#define IDTSIZE  0xFF		/* max deskriptorių lentelėje */

#define INTGATE  0x8E00		/* naudojamas interuptų valdymui */
#define TRAPGATE 0xEF00		/* naudojamas syscall */

/* segmento deskriptorius */
struct idtdesc {
	u16 offset0_15;
	u16 select;
	u16 type;
	u16 offset16_31;
} __attribute__ ((packed));

/*  IDTR registras*/
struct idtr {
	u16 limit;
	u32 base;
} __attribute__ ((packed));

struct idtr kidtr; /* IDTR registras*/
struct idtdesc kidt[IDTSIZE]; /* IDT lenta*/

void init_idt_desc(u16, u32, u16, struct idtdesc *);
void init_idt(void);

