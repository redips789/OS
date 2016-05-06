#include "types.h"
#include "lib.h"
#include "io.h"
#include "idt.h"

void _asm_default_int(void);
void _asm_exc_GP(void);
void _asm_exc_PF(void);
void _asm_irq_0(void);
void _asm_irq_1(void);
void _asm_syscalls(void);

/*
 * 'init_idt_desc' inicializuoja segmento descriptorių
 */
void init_idt_desc(u16 select, u32 offset, u16 type, struct idtdesc *desc)
{
	desc->offset0_15 = (offset & 0xffff);
	desc->select = select;
	desc->type = type;
	desc->offset16_31 = (offset & 0xffff0000) >> 16;
	return;
}

/*
 * Ši funkcija inicializuoja IDT po kernelio pakrovimo į atmintį
 */
void init_idt(void)
{
	int i;

	/* Priskiria default reikšmes */
	for (i = 0; i < IDTSIZE; i++) 
		init_idt_desc(0x08, (u32) _asm_default_int, INTGATE, &kidt[i]);

	/* vectoriai 0 -> 31 priskirti exceptions */
	init_idt_desc(0x08, (u32) _asm_exc_GP, INTGATE, &kidt[13]);	/* #GP */
	init_idt_desc(0x08, (u32) _asm_exc_PF, INTGATE, &kidt[14]);     /* #PF */

	/* interuptų vektoriai */
	init_idt_desc(0x08, (u32) _asm_irq_0, INTGATE, &kidt[32]);	/* laikrodis */
	init_idt_desc(0x08, (u32) _asm_irq_1, INTGATE, &kidt[33]);	/* klaviatūra */

	/* interuptas - int 0x30 */
	init_idt_desc(0x08, (u32) _asm_syscalls, INTGATE | 0x6000, &kidt[48]); 

	/* IDTR struktūros inicializacija */
	kidtr.limite = IDTSIZE * 8;
	kidtr.base = IDTBASE;

	/* IDT adresų kopijavimas */
	memcpy((char *) kidtr.base, (char *) kidt, kidtr.limite);

	/* IDTR registro pakrovimas */
	asm("lidtl (kidtr)");
}
