#ifndef UART_H_
#define UART_H_

#define rULCON0  		(*(volatile unsigned long *)0xE2900000)
#define rUCON0   		(*(volatile unsigned long *)0xE2900004)
#define rUFCON0  		(*(volatile unsigned long *)0xE2900008)
#define rUMCON0  		(*(volatile unsigned long *)0xE290000c)
#define rUTXH0   		(*(volatile unsigned long *)0xE2900020)
#define rURXH0    	(*(volatile unsigned long *)0xE2900024)
#define rUTRSTAT0   (*(volatile unsigned long *)0xE2900010)
#define rUBRDIV0 		(*(volatile unsigned long *)0xE2900028)
#define rUDIVSLOT0  (*(volatile unsigned long *)0xE290002c)

#define rGPA0CON  	(*(volatile unsigned long *)0xE0200000)

void uart_init();
void putc(unsigned char c);
unsigned char getc();

#endif