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
	
	bl clock_init
	
	bl ddr_init
	
	ldr r0, =0xE0200C04 /* gpj2dat数据寄存器*/
	mov r1, #0x0C  /* 输出为高 点亮LED */
	str r1, [r0]
	
	/* 代码重定向 */
	ldr r0, =0xD0020010
	ldr r1, =0x23e00000	@ copy to SDRAM
	ldr r2, =0xc800		@ size = 50k
move_loop:
	ldr r3, [r0]
	str r3, [r1]
	add r0, r0, #4
	add r1, r1, #4
	sub r2, r2, #4
	cmp r2, #0
	bne move_loop
	
	/* 设置栈 */
	ldr sp, =0x30008000
	@bl mymain
	ldr pc, =mymain
halt:
	b halt