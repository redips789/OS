#include "types.h"

#ifdef __SCREEN__

#define RAMSCREEN 0xB8000	/* video atminties pradzia */
#define SIZESCREEN 0xFA0	/* 4000, bitu skaicius teksto puslapyje */
#define SCREENLIM 0xB8FA0

char kX = 0;			/* kursoriaus ekrane pozicija */
char kY = 8;
char kattr = 0x07;		/* spausdinamo char atributai */

#else

extern char kX;
extern char kY;
extern char kattr;

#endif				/* __SCREEN__ */

void scrollup(unsigned int);
void putcar(uchar);
void dump(uchar*, int);
void move_cursor(u8, u8);
void show_cursor(void);
void hide_cursor(void);

