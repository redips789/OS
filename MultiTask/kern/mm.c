#include "types.h"


#define __MM__
#include "mm.h"


/* 
 * Bitmap iesko laisvo puslapio ir grazina jo fizini adresa
 */
char* get_page_frame(void)
{
	int byte, bit;
	int page = -1;

	for (byte = 0; byte < RAM_MAXPAGE / 8; byte++)
		if (mem_bitmap[byte] != 0xFF)
			for (bit = 0; bit < 8; bit++)
				if (!(mem_bitmap[byte] & (1 << bit))) {
					page = 8 * byte + bit;
					set_page_frame_used(page);
					return (char *) (page * PAGESIZE);
				}
	return (char *) -1;
}

/* Created a mapping as vaddr = PADDR on 4MB */
void init_mm(void)
{
	u32 page_addr;
	int i, pg;

	/* bitmap inicijuoja puslapius */
	for (pg = 0; pg < RAM_MAXPAGE / 8; pg++)
		mem_bitmap[pg] = 0;

	/*  puslapiai rezervuoti kerneliui */
	for (pg = PAGE(0x0); pg < PAGE(0x20000); pg++) 
		set_page_frame_used(pg);

	/*  puslapiai rezervuoti hardware */
	for (pg = PAGE(0xA0000); pg < PAGE(0x100000); pg++) 
		set_page_frame_used(pg);
	

	/* pasiemam Page Directory[0] ir Page Table[0] */
	pd0 = (u32*) get_page_frame();
	pt0 = (u32*) get_page_frame();

	/* Inicializuoja Page Directory */
	pd0[0] = (u32) pt0;
	pd0[0] |= 3;
	for (i = 1; i < 1024; i++)
		pd0[i] = 0;

	/* Inicializuoja Page table[0] */
	page_addr = 0;
	for (pg = 0; pg < 1024; pg++) {
		pt0[pg] = page_addr;
		pt0[pg] |= 3;
		page_addr += 4096;
	}
    
	asm("	mov %0, %%eax \n \
		mov %%eax, %%cr3 \n \
		mov %%cr0, %%eax \n \
		or %1, %%eax \n \
		mov %%eax, %%cr0"::"m"(pd0), "i"(PAGING_FLAG));
}

/* 
 * code_phys_addr (in physical memory)
 * code_size 
 */
u32* pd_create(u32 * code_phys_addr, unsigned int code_size)
{
	u32 *pd, *pt;
	u32 i, j;
	u32 pages;

	/* inicializuojam page table[0] ir likusia page directory */
	pd = (u32*) get_page_frame();
	for (i = 1; i < 1024; i++)
		pd[i] = 0;

	/* kernel space */
	pd[0] = pd0[0];
	pd[0] |= 3;

	/* user space */
	if (code_size % PAGESIZE)
		pages = code_size / PAGESIZE + 1;
	else
		pages = code_size / PAGESIZE;

	for (i = 0; pages; i++) {
		pt = (u32*) get_page_frame();

		pd[(USER_OFFSET + i * PAGESIZE * 1024) >> 22] = (u32) pt;
		pd[(USER_OFFSET + i * PAGESIZE * 1024) >> 22] |= 7;

		for (j = 0; j < 1024 && pages; j++, pages--) {
			pt[j] = (u32) (code_phys_addr + i * PAGESIZE * 1024 + j * PAGESIZE);
			pt[j] |= 7;
		}
	}

	return pd;
}

