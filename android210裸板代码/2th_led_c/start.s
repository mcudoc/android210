.globl _start
_start:

	/* πÿ±’ø¥√≈π∑ */
	ldr r0, =0xE2700000	/* 0xE2700000 */
	mov r1, #0
	str r1, [r0]	
	
	bl mymain
	
hlod:
	b hlod