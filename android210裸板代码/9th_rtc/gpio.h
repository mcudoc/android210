#ifndef GPIO_H_
#define GPIO_H_

/* led */
#define GPH1CON (*(volatile unsigned long *)0xE0200C00)
#define GPH1DAT (*(volatile unsigned long *)0xE0200C04)


#define 	GPH2CON 	(*(volatile unsigned long *) 0xE0200C40)
#define 	GPH2DAT		(*(volatile unsigned long *) 0xE0200C44)
#define 	GPH3CON 	(*(volatile unsigned long *) 0xE0200C60)



#define 	GPH2_0_EINT16 	(0xf<<(0*4))
#define 	GPH2_1_EINT17 	(0xf<<(1*4))
#define 	GPH2_2_EINT18 	(0xf<<(2*4))
#define 	GPH2_3_EINT19 	(0xf<<(3*4))

#define		EXT_INT_0_CON  			( *((volatile unsigned long *)0xE0200E00) )
#define		EXT_INT_1_CON  			( *((volatile unsigned long *)0xE0200E04) )
#define		EXT_INT_2_CON  			( *((volatile unsigned long *)0xE0200E08) )
#define		EXT_INT_3_CON  			( *((volatile unsigned long *)0xE0200E0C) )

#define		EXT_INT_0_MASK   		( *((volatile unsigned long *)0xE0200F00) )
#define		EXT_INT_1_MASK   		( *((volatile unsigned long *)0xE0200F04) )
#define		EXT_INT_2_MASK   		( *((volatile unsigned long *)0xE0200F08) )
#define		EXT_INT_3_MASK   		( *((volatile unsigned long *)0xE0200F0C) )

#define		EXT_INT_0_PEND   		( *((volatile unsigned long *)0xE0200F40) )
#define		EXT_INT_1_PEND   		( *((volatile unsigned long *)0xE0200F44) )
#define		EXT_INT_2_PEND   		( *((volatile unsigned long *)0xE0200F48) )
#define		EXT_INT_3_PEND   		( *((volatile unsigned long *)0xE0200F4C) )

#endif