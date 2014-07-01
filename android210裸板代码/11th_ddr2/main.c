/***************************************
*NAND FLSH
*
******************************************/
#include "clock.h"
#include "uart.h"
#include "stdio.h"
#include "nand.h"
//#include "string.h"

int mymain()
{
	unsigned char c = 68;
	//clock_init();
	uart_init();
	// 初始化nandflash
	nand_init();
	
	while (1)
	{
		printf("\r\n********Nandflash R/W Test*******\r\n");
		printf("[i] Read ID\r\n");
		printf("[e] Erase Nandflash\r\n");
		printf("[w] Write Nandflash\r\n");
		printf("[r] Read  Nandflash\r\n");
		printf("[n] read sdram to nand\r\n");
		printf("Enter your choice: ");
		c = getc();
		printf("%c\r\n",c);
		
		switch(c)
		{
		case 'i':
			nand_read_id();
			break;
		case 'e':
			erase_test();
			break;
		case 'w':
			write_test();
			break;
		case 'r':
			read_test();
			break;
		case 'n':
			sdram_to_nand_test();
			break;
		}
	}
	return 0;
}

int erase_test()
{
	int blocknum = 0;
	
	printf("Block # to erase: ");
	scanf("%d",&blocknum);
	printf("\r\n");

	if(nand_erase(blocknum) == -1)
		return -1;


	printf("Block %d erase ok\r\n", blocknum);
	return 0;
}


void write_test()
{
	char c;
	int count = 0;
	unsigned char buffer[128];

	printf("Enter a string:\r\n");
	
	// 接收字符串，回车时表示结束 
	while(1)
	{
		c = getc();
		putc(c);
		if(c == '\r')
		{
			buffer[count] = '\0';
			break;
		}
		else
		{
			buffer[count++] = c;
		}
	}

	printf("\r\n");
	// 擦除第0个块 
	nand_erase(0);
	printf("Erase block 0 ok\r\n");

	// 写第0个块 
	copy_sdram_to_nand(buffer, (unsigned long)0, strlen((char *)buffer)+1);
	printf("Write %s ok\r\n",buffer);
}



// 测试读
void read_test()
{
	unsigned char buffer[128];
	copy_nand_to_sdram(buffer,(unsigned long)0, 128);
	printf("Read string ok:%s\r\n",buffer);
}

void sdram_to_nand_test()
{
	unsigned long sdram_addr,nand_addr,len;
	printf("sdram addr,nand addr,len:");
	scanf("%d %d %d",&sdram_addr,&nand_addr,&len);
	nand_erase(0);/* 1块 128k */
	printf("Erase block 0 ok\r\n");
	nand_erase(1);
	printf("Erase block 0 ok\r\n");
	nand_erase(2);
	printf("Erase block 0 ok\r\n");
	copy_sdram_to_nand((unsigned long *)sdram_addr,(unsigned long)nand_addr,len);
}