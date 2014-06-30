/***************************************
*µ„¡¡LEDµ∆
*
******************************************/
#include "clock.h"
#include "uart.h"


int mymain()
{
	unsigned char c;
	clock_init();
	uart_init();
	while(1)
	{
		c = getc();
		putc(c);
	}
	return 0;	
	
}