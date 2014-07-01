#include "stdio.h"
#include "int.h"
#include "clock.h"
#include "uart.h"
#include "gpio.h"
#include "timer.h"


// ��ʱ����
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
		// �ⲿ�ж���ص�����
	// 1111 = EXT_INT[24] 
	GPH3CON |= 0xF;							
	// 010 = Falling edge triggered
	EXT_INT_3_CON |= 1<<1;			
	// unmasked
	EXT_INT_3_MASK &= ~(1<<0);
	
	// �����ж�EINT16_31�Ĵ�����
	intc_setvectaddr(NUM_EINT16_31, isr_key);	
	// ʹ���ж�EINT16_31
	intc_enable(NUM_EINT16_31);
}

void irs_timer()
{
	 
	//��timer0���ж�״̬�Ĵ���
	TINT_CSTAT = TINT_CSTAT;
	
	printf("timer0 irq OK!\n");	
	GPH1DAT = ~GPH1DAT;

	// vic��ص��ж����
	intc_clearvectaddr();
	
}

void timer_intc()
{
	//TCON = 0;
	
	// ����timer0�жϵ��жϴ�����
	intc_setvectaddr(NUM_TIMER0,irs_timer);	
	
	// ʹ��timer0�ж�
	intc_enable(NUM_TIMER0);
}

int main(void)
{
	int c = 0;
	//ʱ�ӳ�ʼ��
	clock_init();
	// ��ʼ������
	uart_init();
	GPH1CON = 0x00011100;
	GPH1DAT = 0x0;
	// �ж���س�ʼ��
	system_initexception();	
					
	/* �ⲿ�жϳ�ʼ�� */
	exint_init();
	/* ��ʱ���ж��������� */
	timer_intc();
	/* ��ʱ����ʼ�� */	
	timer_init(0,65,4,62500,0);
	printf("**************Int test *************** \r\n");
	while (1)
	{   
	}
}
