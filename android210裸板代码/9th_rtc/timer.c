
#include "timer.h"


/**************************************************
������:timer_init
��������:��ʱ����ʼ��
��ڲ���:utimer����ʱ���ţ�0-4��
				 uprescaler����һ��Ƶϵ��
				 udivider���ڶ���Ƶϵ��
				 utcntb������ֵ
				 utcmpb���Ƚ���ֵ
���ڲ���:
��ע:
****************************************************/
void timer_init(unsigned long utimer,
								unsigned long uprescaler,
								unsigned long udivider,
								unsigned long utcntb,
								unsigned long utcmpb)
{
		/* 1�����÷�Ƶϵ�� */
		unsigned long temp0;
		temp0 = TCFG0;
		/* ����һ����Ƶϵ�� */
		if(utimer < 2 && utimer >= 0)
		{
					temp0 = ((temp0 & ~(0xff)) | ((uprescaler-1) << 0));
					TCFG0 = temp0;
		}
		else 
		{
					temp0 = ((temp0 & ~(0xff << 8)) | ((uprescaler-1) << 8));
					TCFG0 = temp0;
		}
		/* ���ö�����Ƶϵ�� */
		TCFG1 = (TCFG1 & (~(0xf<<4*utimer))& (~(1<<20)))  
        |(udivider<<4*utimer);
    /* ���ü����ͱȽϼĴ��� */
    switch(utimer)         
  	{ 
   		case 0:            //װ�ض�ʱ��0 
        				TCNTB0 = utcntb; 
        				TCMPB0 = utcmpb; 
        				break; 
    	case 1:            //װ�ض�ʱ��1 
        				TCNTB1 = utcntb; 
        				TCMPB1 = utcmpb; 
        				break; 
      case 2:            //װ�ض�ʱ��2 
        				TCNTB2 = utcntb; 
        				TCMPB2 = utcmpb; 
        				break; 
 
    	case 3:            //װ�ض�ʱ��3 
        				TCNTB3 = utcntb; 
        				TCMPB3 = utcmpb; 
        				break; 
 
    	case 4:            //װ�ض�ʱ��4 
        				TCNTB4 = utcntb; 
        				break;          //��TCMPB4 
    	default:             
        				break; 
  	} 
  	//��һ�α����ֶ�����,�ֲ�涨 
  	TCON |= 1<<(1+(utimer*8));  
    
  		//������Ҫ����ֶ�����λ,�ֲ�涨 
  	TCON &= ~(1<<(1+(utimer*8)));    
  
  		// �Զ����غ�����timer0 
		TCON |= (1<<(0+(utimer*8)))|(1<<(3+(utimer*8)));   
 
  		// ʹ��timer0�ж� 
  	TINT_CSTAT = (TINT_CSTAT & (~(1<<utimer)))|(1<<(utimer));	
}
