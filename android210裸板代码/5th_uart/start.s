.globl _start
_start:
	/* 关闭看门狗 */
	ldr r0, =0xE2700000	/* 0xE2700000 */
	mov r1, #0
	str r1, [r0]	
	
	/* 设置栈 */
	ldr sp, =0xd0037d80
	bl mymain
halt:
	b halt