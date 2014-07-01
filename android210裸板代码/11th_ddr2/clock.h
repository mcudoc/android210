#ifndef CLOCK_H_
#define CLOCK_H_

#define rAPLL_LOCK (*(volatile unsigned long *)0xE0100000)
#define rMPLL_LOCK (*(volatile unsigned long *)0xE0100008)
#define rEPLL_LOCK (*(volatile unsigned long *)0xE0100010)
#define rVPLL_LOCK (*(volatile unsigned long *)0xE0100020)

#define rAPLL_CON (*(volatile unsigned long *)0xE0100100)
#define rMPLL_CON (*(volatile unsigned long *)0xE0100108)
#define rVPLL_CON (*(volatile unsigned long *)0xE0100110)
#define rCLK_SRC0 (*(volatile unsigned long *)0xE0100200)
#define rCLK_SRC1 (*(volatile unsigned long *)0xE0100204)

#define rCLK_DIV0 (*(volatile unsigned long *)0xE0100300)

void clock_init();

#endif