.globl _start
_start:

	/* 关闭看门狗 */
	ldr r0, =0xE2700000	/* 0xE2700000 */
	mov r1, #0
	str r1, [r0]	
	
	/* 点亮3个LED灯 */
	ldr r0, =0xE0200C00  /* gph1con配置寄存器 0000 输入 0001输出 */
	ldr r1, =0x00011100 /* gpjh2-5设置成输出 */
	str r1, [r0]
	
	ldr r0, =0xE0200C04 /* gpj2dat数据寄存器*/
	mov r1, #0x1C  /* 输出为高 点亮LED */
	str r1, [r0]
	
hlod:
	b hlod
