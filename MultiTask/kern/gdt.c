#include "types.h"
#include "lib.h"

#define __GDT__
#include "gdt.h"


/ * * Init desc 'inicijuoja segmento deskriptorių GDT ar LDT. * "desc" yra linijinis adresas deskriptoriui inicializuoti. * /
void init_gdt_desc(u32 base, u32 limit, u8 acces, u8 other,
		   struct gdtdesc *desc)
{
	desc->lim0_15 = (limit & 0xffff);
	desc->base0_15 = (base & 0xffff);
	desc->base16_23 = (base & 0xff0000) >> 16;
	desc->acces = acces;
	desc->lim16_19 = (limit & 0xf0000) >> 16;
	desc->other = (other & 0xf);
	desc->base24_31 = (base & 0xff000000) >> 24;
	return;
}

/ *
  * Ši funkcija inicijuoja GDT.
  * /
void init_gdt(void)
{

	default_tss.debug_flag = 0x00;
	default_tss.io_map = 0x00;
	default_tss.esp0 = 0x20000;
	default_tss.ss0 = 0x18;

	/* segmento deskriptorių inicializacija */
	init_gdt_desc(0x0, 0x0, 0x0, 0x0, &kgdt[0]);
	init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &kgdt[1]);	/* code */
	init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &kgdt[2]);	/* data */
	init_gdt_desc(0x0, 0x0, 0x97, 0x0D, &kgdt[3]);		/* stack */

	init_gdt_desc(0x0, 0xFFFFF, 0xFF, 0x0D, &kgdt[4]);	/* ucode */
	init_gdt_desc(0x0, 0xFFFFF, 0xF3, 0x0D, &kgdt[5]);	/* udata */
	init_gdt_desc(0x0, 0x0, 0xF7, 0x0D, &kgdt[6]);		/* ustack */

	init_gdt_desc((u32) & default_tss, 0x67, 0xE9, 0x00, &kgdt[7]);	/* TSS deskriptorius */

	/* struktūros inicializacija GDTRui */
	kgdtr.limit = GDTSIZE * 8;
	kgdtr.base = GDTBASE;

	/* kopijuoja GDT adresą */
	memcpy((char *) kgdtr.base, (char *) kgdt, kgdtr.limit);

	/* pakrauna gdtr registą */
	asm("lgdtl (kgdtr)");

	/* segmentų inicializacija */
	asm("   movw $0x10, %ax	\n \
            movw %ax, %ds	\n \
            movw %ax, %es	\n \
            movw %ax, %fs	\n \
            movw %ax, %gs	\n \
            ljmp $0x08, $next	\n \
            next:		\n");
}
