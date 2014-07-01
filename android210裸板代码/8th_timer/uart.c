/*************************************
 *
 *uart��ʼ��
 *
 **************************************/
#include "uart.h"

void uart_init()
{
	/* 1��GPIO�ڹ������� */
	rGPA0CON = (0x2 << 0) | (0x2 << 4);
	/* 2��uartͨ�Ÿ�ʽ���� */	
	/* 
   * ����UART0�����ݸ�ʽΪ:8������λ�� 
   * һ��ֹͣλ������żУ�� 
   */ 
	rULCON0 =(0x3 << 0);
	/* 
   * ����UART0��ʱ��ԴΪPCLK_PSYS = 66.7MHz����ʱ�ӷ�Ƶ������ 
   * ���͡����վ����ò�ѯ��ʽ 
   */ 
   rUCON0 = (1 << 2) | (1 << 0);
   /*  ��ֹUART0  FIFO */
	 /* 
   * ������ = 115200bps 
   * ��Ƶϵ�� = ( PCLK_PSYS / (Baud * 16)) - 1�� 
   * ��Ƶϵ�� = UBRDIVn�Ĵ�����ֵ + (UDIVSLOTn�Ĵ�����1�ĸ���) / 16; 
   *  For example: 
   *    PCLKP =66MHz����������Ϊ115200 
   *    ��Ƶϵ�� = ( 66700000 / (115200 * 16)) - 1 = 35.2�� 
   *    ���ԣ�UBRDIVn�Ĵ�����ֵ = 35�� 
   *    ����UDIVSLOTn�Ĵ�����ֵ�� 1�ĸ���Ϊ2�� 
   *    ����S5PV210�ֲ�p880��֪ UDIVSLOTn= 0x808�� 
   */ 
   
  rUBRDIV0 = 0x23; 
  rUDIVSLOT0 = 0x808;
  
  /* 9600  
  
  rUBRDIV0 = 0x1b1; 
  rUDIVSLOT0 = 0x808;*/
}

void putc(unsigned char c)
{
	while(!(rUTRSTAT0 & (1 << 2)));
	rUTXH0 = c;
}

unsigned char getc()
{
	while(!(rUTRSTAT0 & 1));
	
	return rURXH0;
}