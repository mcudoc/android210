/************************************************
�ļ���:int.c
����:������
��������:2014-07-01
�汾:V0.1
�޸�:
��ע:S5PV210�жϴ���
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
������:system_initexception
��������:�����ж���������ʼ���жϿ�����
��ڲ���:
���ڲ���:
��ע:�ж�����ڵ�ַΪ0xD0037400
****************************************************/
void system_initexception( void)
{
    // �����ж�������
    pExceptionUNDEF	  =	(unsigned long)exceptionundef;
    pExceptionSWI  	  =	(unsigned long)exceptionswi;
    pExceptionPABORT  =	(unsigned long)exceptionpabort;
    pExceptionDABORT  =	(unsigned long)exceptiondabort;
    pExceptionIRQ	  =	(unsigned long)IRQ_handle;
    pExceptionFIQ	  =	(unsigned long)IRQ_handle;

    // ��ʼ���жϿ�����
    // ��ֹ�����ж�
    VIC0INTENCLEAR = 0xffffffff;
    VIC1INTENCLEAR = 0xffffffff;
    VIC2INTENCLEAR = 0xffffffff;
    VIC3INTENCLEAR = 0xffffffff;

    // ѡ���ж�����ΪIRQ
    VIC0INTSELECT = 0x0;
    VIC1INTSELECT = 0x0;
    VIC2INTSELECT = 0x0;
    VIC3INTSELECT = 0x0;

    // ��VICxADDR
    intc_clearvectaddr();

}

/**************************************************
������:intc_setvectaddr
��������:������Ҫ������жϵ��жϴ������ĵ�ַ
��ڲ���:intnum����Ҫ������жϺ�
					void (*handler)(void)���жϴ�������ַ
���ڲ���:
��ע:���жϲ���ʱ���жϿ��������Զ�ת��
			VIC0VECTADDR[intnum]��ִַ�С�
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
������:intc_clearvectaddr
��������:�����Ҫ������жϵ��жϴ������ĵ�ַ
��ڲ���:
���ڲ���:
��ע:��VICxADDRд�����ݱ�ʾ����жϷ�������ַ
****************************************************/
void intc_clearvectaddr(void)
{
    // VICxADDR:��ǰ���ڴ�����жϵ��жϴ������ĵ�ַ
    VIC0ADDR = 0;
    VIC1ADDR = 0;
    VIC2ADDR = 0;
    VIC3ADDR = 0;
}

/**************************************************
������:intc_enable
��������:ʹ����Ӧ�ж�
��ڲ���:intnum:ʹ�ܵ��жϺ�
���ڲ���:
��ע:
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
������:intc_enable
��������:��ֹ�ж�
��ڲ���:intnum:��ֹ���жϺ�
���ڲ���:
��ע:
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
������:intc_getvicirqstatus
��������:���ж�״̬
��ڲ���:ucontroller:�жϿ�������
���ڲ���:
��ע:
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
������:irq_handler
��������:ͨ���ж�ִ�к���
��ڲ���:
���ڲ���:
��ע:���жϲ���ʱ����ִ��irq_handler���������
�ú������VIC0ADDR�Ĵ�����ȡ�����жϷ������
�ĵ�ַ����ִ�С�
****************************************************/
void irq_handler(void)
{
    unsigned long vicaddr[4] = {VIC0ADDR,VIC1ADDR,VIC2ADDR,VIC3ADDR};
    int i=0;
    void (*isr)(void) = NULL;

    for(; i<4; i++)
    {
    		/* ���жϲ��� */
        if(intc_getvicirqstatus(i) != 0)
        {
            /* ����ע��ĺ�����ַ */
            isr = (void (*)(void)) vicaddr[i];
            break;
        }
    }
    (*isr)();/* ִ���жϷ������ */
}


