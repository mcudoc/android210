#include "clock.h"

#define rGPH1CON (*(volatile unsigned long *)0xE0200C00)
#define rGPH1DAT (*(volatile unsigned long *)0xE0200C04)

void delay()
{
	volatile int i = 0x80000;
	while (i--);
}

void mymain()
{
		clock_init();
		rGPH1CON = 0x00011100;
		while(1)
		{
			rGPH1DAT = 0x1C;
			delay();
			rGPH1DAT = 0x0;
			delay();
		}
}