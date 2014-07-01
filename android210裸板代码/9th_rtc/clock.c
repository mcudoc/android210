/**************************************
 *系统时钟初始化
 * 设置时钟情况如下: 
 * ARMCLK=1000MHz, HCLKM=200MHz, HCLKD=166.75MHz 
 * HCLKP =133.44MHz, PCLKM=100MHz, PCLKD=83.375MHz,  
 * PCLKP =66.7MHz 
 ***************************************/
 
#include "clock.h"

void clock_init()
{
		/* 1.设置PLL锁存时钟 */
			rAPLL_LOCK = 0xffff;
			rAPLL_LOCK = 0xffff;
		/* 2.配置PLL */
		/* 
   *   使能APLL控制器，使能锁标志位，MDIV = 0x7d,PDIV  = 0x3,SDIV = 0x1 
   *   FOUTapll = MDIV * FIN / (PDIV*2^(SDIV-1)) 
   *       = 0x7d*24/(0x3*2^(0x1-1)) 
   *       = 125*24/(3*2) = 1000MHz 
   */ 
  rAPLL_CON = (1 << 31)|(1 << 29)|(0x7d << 16)|(0x3 << 8)|(0x1 << 0);
  /* 
   * 使能MPLL控制器，使能锁标志位，MDIV = 0x29b,PDIV = 0xc,SDIV = 0x1 
   *  FOUTmpll = MDIV * FIN / (PDIV*2^SDIV) 
   *       = 0x29b*24/(0xc*2^1) 
   *       = 667*24/(12*2) = 667MHz 
   */ 
  rMPLL_CON = (1 << 31)|(1 << 29)|(0x29b << 16)|(0xc << 8)|(0x1 << 0);
  /* 
   *  时钟源的设置 
   *   ONENAND_SEL  = HCLK_DSYS  高位 
   *   MUX_PSYS_SEL = SCLKMPLL    
   *   MUX_DSYS_SEL = SCLKMPLL   /|\  
   *   MUX_MSYS_SEL = SCLKAPLL    | 
   *   VPLL_SEL     = FOUTVPLL    | 
   *   EPLL_SEL     = FOUTEPLL    | 
   *   MPLL_SEL     = FOUTMPLL 
   *   APLL_SEL     = FOUTAPLL   低位 
   */ 
  rCLK_SRC0 = (1 << 28)|(1 << 12)|(1 << 8)|(1 << 4)|(1 << 0);
   /* 
   *   设置系统时钟分频系数    
   *    PCLK_PSYS_RATIO = 0x1     高位 
     *   HCLK_PSYS_RATIO = 0x4     
     *   PCLK_DSYS_RATIO = 0x1     /|\ 
     *   HCLK_DSYS_RATIO = 0x3      | 
     *   PCLK_MSYS_RATIO = 0x1      | 
     *   HCLK_MSYS_RATIO = 0x4      | 
     *   A2M_RATIO  = 0x4 
     *   APLL_RATIO = 0x0      低位 
   */ 
  rCLK_DIV0 = (0x1 << 28)|(0x4 << 24)|(0x1 << 20)|(0x3 << 16)|(0x1 <<12)|(0x4 << 8)|(0x4 << 4)|(0 << 0);
}