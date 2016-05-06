#include "io.h"

void init_pic(void)
{
	/* Inicializuojam ICW1 */
	outb(0x20, 0x11);
	outb(0xA0, 0x11);

	/* Inicializuojam ICW2 */
	outb(0x21, 0x20);	/* starting vector = 32 */
	outb(0xA1, 0x70);	/* starting vector = 96 */

	/* Inicializuojam ICW3 */
	outb(0x21, 0x04);
	outb(0xA1, 0x02);

	/* Inicializuojam ICW4 */
	outb(0x21, 0x01);
	outb(0xA1, 0x01);

	/* interrupt masking */
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
}
