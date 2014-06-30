/***************************************
*µ„¡¡LEDµ∆
*
******************************************/
#include "clock.h"
#include "uart.h"
#include "stdio.h"

int mymain()
{
	unsigned char c = 68;
	clock_init();
	uart_init();
	printf("uart printf text!\n");
	printf("c=%c\n",c);
	while(1)
	{
		c = getc();
		putc(c);
	}
	return 0;	
	
}