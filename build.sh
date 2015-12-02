nasm -f elf32 kernel.asm -o kasm.o
gcc -m32 -ffreestanding -std=gnu99 -c kernel.c -o kc.o
ld -T link.ld -o kernel.bin kasm.o kc.o
objcopy -I elf32-i386 kernel.bin kernel.out
rm kernel.bin
qemu-system-i386 -kernel kernel.out