/************************************************
文件名:int.c
作者:张益新
创建日期:2014-07-01
版本:V0.1
修改:
备注:S5PV210中断处理
*************************************************/

#include "int.h"
#include "stdio.h"

void exceptionundef(void)
{
    printf("undefined instruction exception.\n");
    while(1);
}

void exceptionswi(void)
{
    printf("swi exception.\n");
    while(1);
}

void exceptionpabort(void)
{
    printf("pabort exception.\n");
    while(1);
}

void exceptiondabort(void)
{

    printf("dabort exception.\n");
    while(1);
}

/**************************************************
函数名:system_initexception
函数功能:设置中断向量表及初始化中断控制器
入口参数:
出口参数:
备注:中断向入口地址为0xD0037400
****************************************************/
void system_initexception( void)
{
    // 设置中断向量表
    pExceptionUNDEF	  =	(unsigned long)exceptionundef;
    pExceptionSWI  	  =	(unsigned long)exceptionswi;
    pExceptionPABORT  =	(unsigned long)exceptionpabort;
    pExceptionDABORT  =	(unsigned long)exceptiondabort;
    pExceptionIRQ	  =	(unsigned long)IRQ_handle;
    pExceptionFIQ	  =	(unsigned long)IRQ_handle;

    // 初始化中断控制器
    // 禁止所有中断
    VIC0INTENCLEAR = 0xffffffff;
    VIC1INTENCLEAR = 0xffffffff;
    VIC2INTENCLEAR = 0xffffffff;
    VIC3INTENCLEAR = 0xffffffff;

    // 选择中断类型为IRQ
    VIC0INTSELECT = 0x0;
    VIC1INTSELECT = 0x0;
    VIC2INTSELECT = 0x0;
    VIC3INTSELECT = 0x0;

    // 清VICxADDR
    intc_clearvectaddr();

}

/**************************************************
函数名:intc_setvectaddr
函数功能:保存需要处理的中断的中断处理函数的地址
入口参数:intnum：需要处理的中断号
					void (*handler)(void)：中断处理函数地址
出口参数:
备注:当中断产生时，中断控制器会自动转到
			VIC0VECTADDR[intnum]地址执行。
****************************************************/
void intc_setvectaddr(unsigned long intnum, void (*handler)(void))
{
    //VIC0
    if(intnum<32)
    {
        *( (volatile unsigned long *)(VIC0VECTADDR + 4*intnum) ) = (unsigned)handler;
    }
    //VIC1
    else if(intnum<64)
    {
        *( (volatile unsigned long *)(VIC1VECTADDR + 4*(intnum-32)) ) = (unsigned)handler;
    }
    //VIC2
    else if(intnum<96)
    {
        *( (volatile unsigned long *)(VIC2VECTADDR + 4*(intnum-64)) ) = (unsigned)handler;
    }
    //VIC3
    else
    {
        *( (volatile unsigned long *)(VIC3VECTADDR + 4*(intnum-96)) ) = (unsigned)handler;
    }
    return;
}

/**************************************************
函数名:intc_clearvectaddr
函数功能:清除需要处理的中断的中断处理函数的地址
入口参数:
出口参数:
备注:向VICxADDR写入数据表示清除中断服务函数地址
****************************************************/
void intc_clearvectaddr(void)
{
    // VICxADDR:当前正在处理的中断的中断处理函数的地址
    VIC0ADDR = 0;
    VIC1ADDR = 0;
    VIC2ADDR = 0;
    VIC3ADDR = 0;
}

/**************************************************
函数名:intc_enable
函数功能:使能相应中断
入口参数:intnum:使能的中断号
出口参数:
备注:
****************************************************/
void intc_enable(unsigned long intnum)
{
    unsigned long temp;
    if(intnum<32)
    {
        temp = VIC0INTENABLE;
        temp |= (1<<intnum);
        VIC0INTENABLE = temp;
    }
    else if(intnum<64)
    {
        temp = VIC1INTENABLE;
        temp |= (1<<(intnum-32));
        VIC1INTENABLE = temp;
    }
    else if(intnum<96)
    {
        temp = VIC2INTENABLE;
        temp |= (1<<(intnum-64));
        VIC2INTENABLE = temp;
    }
    else if(intnum<NUM_ALL)
    {
        temp = VIC3INTENABLE;
        temp |= (1<<(intnum-96));
        VIC3INTENABLE = temp;
    }
    // NUM_ALL : enable all interrupt
    else
    {
        VIC0INTENABLE = 0xFFFFFFFF;
        VIC1INTENABLE = 0xFFFFFFFF;
        VIC2INTENABLE = 0xFFFFFFFF;
        VIC3INTENABLE = 0xFFFFFFFF;
    }

}

/**************************************************
函数名:intc_enable
函数功能:禁止中断
入口参数:intnum:禁止的中断号
出口参数:
备注:
****************************************************/
void intc_disable(unsigned long intnum)
{
    unsigned long temp;

    if(intnum<32)
    {
        temp = VIC0INTENCLEAR;
        temp |= (1<<intnum);
        VIC0INTENCLEAR = temp;
    }
    else if(intnum<64)
    {
        temp = VIC1INTENCLEAR;
        temp |= (1<<(intnum-32));
        VIC1INTENCLEAR = temp;
    }
    else if(intnum<96)
    {
        temp = VIC2INTENCLEAR;
        temp |= (1<<(intnum-64));
        VIC2INTENCLEAR = temp;
    }
    else if(intnum<NUM_ALL)
    {
        temp = VIC3INTENCLEAR;
        temp |= (1<<(intnum-96));
        VIC3INTENCLEAR = temp;
    }
    // NUM_ALL : disable all interrupt
    else
    {
        VIC0INTENCLEAR = 0xFFFFFFFF;
        VIC1INTENCLEAR = 0xFFFFFFFF;
        VIC2INTENCLEAR = 0xFFFFFFFF;
        VIC3INTENCLEAR = 0xFFFFFFFF;
    }

    return;
}

/**************************************************
函数名:intc_getvicirqstatus
函数功能:读中断状态
入口参数:ucontroller:中断控制器号
出口参数:
备注:
****************************************************/
unsigned long intc_getvicirqstatus(unsigned long ucontroller)
{
    if(ucontroller == 0)
        return	VIC0IRQSTATUS;
    else if(ucontroller == 1)
        return 	VIC1IRQSTATUS;
    else if(ucontroller == 2)
        return 	VIC2IRQSTATUS;
    else if(ucontroller == 3)
        return 	VIC3IRQSTATUS;
    else
    {}
    return 0;
}

/**************************************************
函数名:irq_handler
函数功能:通用中断执行函数
入口参数:
出口参数:
备注:当中断产生时，会执行irq_handler这个函数。
该函数会出VIC0ADDR寄存器中取出，中断服务程序
的地址，并执行。
****************************************************/
void irq_handler(void)
{
    unsigned long vicaddr[4] = {VIC0ADDR,VIC1ADDR,VIC2ADDR,VIC3ADDR};
    int i=0;
    void (*isr)(void) = NULL;

    for(; i<4; i++)
    {
    		/* 有中断产生 */
        if(intc_getvicirqstatus(i) != 0)
        {
            /* 读出注册的函数地址 */
            isr = (void (*)(void)) vicaddr[i];
            break;
        }
    }
    (*isr)();/* 执行中断服务程序 */
}


