#ifndef NAND_H_
#define NAND_H_

#define NFCONF 			( *((volatile unsigned long *)0xB0E00000) )
#define NFCONT 			( *((volatile unsigned long *)0xB0E00004) )
#define NFCMMD 			( *((volatile unsigned long *)0xB0E00008) )
#define NFADDR 			( *((volatile unsigned long *)0xB0E0000C) )
#define NFDATA 			( *((volatile unsigned long *)0xB0E00010) )
#define NFSTAT 			( *((volatile unsigned long *)0xB0E00028) )

#define MP0_1CON 		( *((volatile unsigned long *)0xE02002E0) )
#define MP0_2CON 		( *((volatile unsigned long *)0xE0200300) )
#define MP0_3CON 		( *((volatile unsigned long *)0xE0200320) )

#define MAX_NAND_BLOCK  			  8192 			/*定义nand最大块数：8192块 	*/
#define NAND_PAGE_SIZE  			  2048 			/*定义一页的容量:2048 byte 	*/
#define NAND_BLOCK_SIZE 			  64  			/*定义block大小：64页		*/

#define TACLS    					  1				/* 时序相关的设置 			*/
#define TWRPH0   					  4
#define TWRPH1   					  1

#define NAND_CMD_READ_1st             0x00			/* 命令						*/
#define NAND_CMD_READ_2st             0x30
#define NAND_CMD_RANDOM_WRITE         0x85
#define NAND_CMD_RANDOM_READ_1st      0x05
#define NAND_CMD_RANDOM_READ_2st      0xe0
#define NAND_CMD_READ_CB_1st          0x00
#define NAND_CMD_READ_CB_2st          0x35
#define NAND_CMD_READ_ID              0x90
#define NAND_CMD_RES                  0xff
#define NAND_CMD_WRITE_PAGE_1st       0x80
#define NAND_CMD_WRITE_PAGE_2st       0x10
#define NAND_CMD_BLOCK_ERASE_1st      0x60
#define NAND_CMD_BLOCK_ERASE_2st      0xd0
#define NAND_CMD_READ_STATUS          0x70

#define BUSY 				  		  1
#define ECC_EN						  (1<<4)
#define CHIP_SELECTED   			  (~(1<<1))
#define CHIP_DESELECTED 			  (1<<1)
#define CONTROL_EN					  (1<<0)

unsigned char read_nand_status(void);
int copy_sdram_to_nand(unsigned char *sdram_addr, unsigned long nand_addr, unsigned long length);
int copy_nand_to_sdram(unsigned char *sdram_addr, unsigned long nand_addr, unsigned long length);
unsigned char nand_erase(unsigned long block_num);
void nand_read_id(void);
void nand_init(void);

#endif