/*************************************
 *
 *uart初始化
 *
 **************************************/
#include "uart.h"

void uart_init()
{
	/* 1、GPIO口功能设置 */
	rGPA0CON = (0x2 << 0) | (0x2 << 4);
	/* 2、uart通信格式配置 */	
	/* 
   * 设置UART0的数据格式为:8个数据位， 
   * 一个停止位，无奇偶校验 
   */ 
	rULCON0 =(0x3 << 0);
	/* 
   * 设置UART0的时钟源为PCLK_PSYS = 66.7MHz，由时钟分频器产生 
   * 发送、接收均采用查询方式 
   */ 
   rUCON0 = (1 << 2) | (1 << 0);
   /*  禁止UART0  FIFO */
	 /* 
   * 波特率 = 115200bps 
   * 分频系数 = ( PCLK_PSYS / (Baud * 16)) - 1； 
   * 分频系数 = UBRDIVn寄存器的值 + (UDIVSLOTn寄存器中1的个数) / 16; 
   *  For example: 
   *    PCLKP =66MHz，波特率设为115200 
   *    分频系数 = ( 66700000 / (115200 * 16)) - 1 = 35.2； 
   *    所以：UBRDIVn寄存器的值 = 35； 
   *    所以UDIVSLOTn寄存器的值的 1的个数为2， 
   *    根据S5PV210手册p880可知 UDIVSLOTn= 0x808； 
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