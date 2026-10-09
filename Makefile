CC = clang
OBJCOPY = llvm-objcopy
CFLAGS = -std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf -fuse-ld=lld -fno-stack-protector -ffreestanding -nostdlib

all: kernel.elf

shell.elf: shell.c user.c common.c user.ld
	$(CC) $(CFLAGS) -Wl,-Tuser.ld -Wl,-Map=shell.map -o shell.elf shell.c user.c common.c

shell.bin: shell.elf
	$(OBJCOPY) --set-section-flags .bss=alloc,contents -O binary shell.elf shell.bin

shell.bin.o: shell.bin
	$(OBJCOPY) -I binary -O elf32-littleriscv shell.bin shell.bin.o

kernel.elf: kernel.c common.c shell.bin.o kernel.ld
	$(CC) $(CFLAGS) -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf kernel.c common.c shell.bin.o

clean:
	rm -f *.elf *.bin *.o *.map