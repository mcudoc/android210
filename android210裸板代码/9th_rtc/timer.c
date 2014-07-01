
#include "timer.h"


/**************************************************
函数名:timer_init
函数功能:定时器初始化
入口参数:utimer：定时器号（0-4）
				 uprescaler：第一分频系数
				 udivider：第二分频系数
				 utcntb：计数值
				 utcmpb：比较数值
出口参数:
备注:
****************************************************/
void timer_init(unsigned long utimer,
								unsigned long uprescaler,
								unsigned long udivider,
								unsigned long utcntb,
								unsigned long utcmpb)
{
		/* 1、设置分频系数 */
		unsigned long temp0;
		temp0 = TCFG0;
		/* 设置一级分频系数 */
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
		/* 设置二级分频系数 */
		TCFG1 = (TCFG1 & (~(0xf<<4*utimer))& (~(1<<20)))  
        |(udivider<<4*utimer);
    /* 设置计数和比较寄存器 */
    switch(utimer)         
  	{ 
   		case 0:            //装载定时器0 
        				TCNTB0 = utcntb; 
        				TCMPB0 = utcmpb; 
        				break; 
    	case 1:            //装载定时器1 
        				TCNTB1 = utcntb; 
        				TCMPB1 = utcmpb; 
        				break; 
      case 2:            //装载定时器2 
        				TCNTB2 = utcntb; 
        				TCMPB2 = utcmpb; 
        				break; 
 
    	case 3:            //装载定时器3 
        				TCNTB3 = utcntb; 
        				TCMPB3 = utcmpb; 
        				break; 
 
    	case 4:            //装载定时器4 
        				TCNTB4 = utcntb; 
        				break;          //无TCMPB4 
    	default:             
        				break; 
  	} 
  	//第一次必须手动更新,手册规定 
  	TCON |= 1<<(1+(utimer*8));  
    
  		//紧接着要清除手动更新位,手册规定 
  	TCON &= ~(1<<(1+(utimer*8)));    
  
  		// 自动加载和启动timer0 
		TCON |= (1<<(0+(utimer*8)))|(1<<(3+(utimer*8)));   
 
  		// 使能timer0中断 
  	TINT_CSTAT = (TINT_CSTAT & (~(1<<utimer)))|(1<<(utimer));	
}
