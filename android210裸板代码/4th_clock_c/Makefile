OBJ = start.o led.o clock.o
led.bin:$(OBJ)
	arm-linux-ld -Ttext 0 -o led.elf $(OBJ)
	arm-linux-objcopy -O binary led.elf led.bin
	arm-linux-objdump -D led.elf > led.dis
%.o:%.s
	arm-linux-gcc -o $@ $< -c -nostdlib
%.o:%.c
	arm-linux-gcc -o $@ $< -c -nostdlib
clean:
	rm -rf *.o *.elf *.bin *.dis