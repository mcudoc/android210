.globl _start
_start:

	/* �رտ��Ź� */
	ldr r0, =0xE2700000	/* 0xE2700000 */
	mov r1, #0
	str r1, [r0]	
	
	/* ����3��LED�� */
	ldr r0, =0xE0200C00  /* gph1con���üĴ��� 0000 ���� 0001��� */
	ldr r1, =0x00011100 /* gpjh2-5���ó���� */
	str r1, [r0]
	
	ldr r0, =0xE0200C04 /* gpj2dat���ݼĴ���*/
	mov r1, #0x1C  /* ���Ϊ�� ����LED */
	str r1, [r0]
	
hlod:
	b hlod
