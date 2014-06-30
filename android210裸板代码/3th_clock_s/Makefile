led.bin:start.o clock.o led.o
	arm-linux-ld -Ttext 0 -o led.elf $^
	arm-linux-objcopy -O binary led.elf led.bin
	arm-linux-objdump -D led.elf > led.dis
	
%.o:%.s
	arm-linux-gcc -o $@ $< -c
%.o:%.c
	arm-linux-gcc -o $@ $< -c
clean:
	rm -rf *.o *.elf *.bin *.dis