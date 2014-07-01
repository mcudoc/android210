#include "stdio.h"
#include "int.h"
#include "clock.h"
#include "uart.h"
#include "gpio.h"
#include "timer.h"


// 延时函数
void delay(unsigned long count)
{
	volatile unsigned long i = count;
	while (i--);
}

void isr_key(void)
{
	printf("we get company:EINT16_31\r\n");
	// clear VIC0ADDR
	intc_clearvectaddr();					
	// clear pending bit	
	EXT_INT_3_PEND |= 1<<0;					
}

void exint_init()
{
		// 外部中断相关的设置
	// 1111 = EXT_INT[24] 
	GPH3CON |= 0xF;							
	// 010 = Falling edge triggered
	EXT_INT_3_CON |= 1<<1;			
	// unmasked
	EXT_INT_3_MASK &= ~(1<<0);
	
	// 设置中断EINT16_31的处理函数
	intc_setvectaddr(NUM_EINT16_31, isr_key);	
	// 使能中断EINT16_31
	intc_enable(NUM_EINT16_31);
}

void irs_timer()
{
	 
	//清timer0的中断状态寄存器
	TINT_CSTAT = TINT_CSTAT;
	
	printf("timer0 irq OK!\n");	
	GPH1DAT = ~GPH1DAT;

	// vic相关的中断清除
	intc_clearvectaddr();
	
}

void timer_intc()
{
	//TCON = 0;
	
	// 设置timer0中断的中断处理函数
	intc_setvectaddr(NUM_TIMER0,irs_timer);	
	
	// 使能timer0中断
	intc_enable(NUM_TIMER0);
}

int main(void)
{
	int c = 0;
	//时钟初始化
	clock_init();
	// 初始化串口
	uart_init();
	GPH1CON = 0x00011100;
	GPH1DAT = 0x0;
	// 中断相关初始化
	system_initexception();	
					
	/* 外部中断初始化 */
	exint_init();
	/* 定时器中断向量设置 */
	timer_intc();
	/* 定时器初始化 */	
	timer_init(0,65,4,62500,0);
	printf("**************Int test *************** \r\n");
	while (1)
	{   
	}
}
