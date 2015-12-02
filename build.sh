rm -rf bin
mkdir -p bin

echo "Finding Sources..."
CSOURCES="$(find kernel -type f -name "*.c")"
HSOURCES="$(find kernel -type f -name "*.h")"
ASOURCES="$(find kernel -type f -name "*.asm")"

echo "Compiling Assembly..."
nasm -f elf32 "${ASOURCES}" -o bin/kasm.o

echo "Compiling C..."
gcc -m32 -ffreestanding -std=gnu99 -c "${CSOURCES}" "${HSOURCES}"
mv *.o bin/

echo "Linking..."
ld -T link.ld -o kernel.bin bin/*.o
objcopy -I elf32-i386 kernel.bin kernel.out
rm kernel.bin

echo "Running..."
qemu-system-i386 -kernel kernel.out