.globl _start
_start:
	/* �رտ��Ź� */
	ldr r0, =0xE2700000	/* 0xE2700000 */
	mov r1, #0
	str r1, [r0]	
	
	/* ����ջ */
	ldr sp, =0xd0037d80
	bl mymain
halt:
	b halt