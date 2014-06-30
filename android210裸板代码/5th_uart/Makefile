OBJ = start.o main.o clock.o uart.o
uart.bin:$(OBJ)
	arm-linux-ld -Ttext 0 -o uart.elf $(OBJ)
	arm-linux-objcopy -O binary uart.elf uart.bin
	arm-linux-objdump -D uart.elf > uart.dis
%.o:%.s
	arm-linux-gcc -o $@ $< -c -nostdlib
%.o:%.c
	arm-linux-gcc -o $@ $< -c -nostdlib
clean:
	rm -rf *.o *.elf *.bin *.dis