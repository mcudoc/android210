led.bin:start.o
	arm-linux-ld -Ttext 0 -o led.elf start.o
	arm-linux-objcopy -O binary led.elf led.bin
	arm-linux-objdump -D led.elf > led.dis
start.o:start.s
	arm-linux-gcc -o start.o start.s -c
clean:
	rm -rf *.o *.elf *.bin *.dis