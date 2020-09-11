all: boot

OBJECT_DIRECTORY = ../../Output

boot: boot.asm
	mkdir -p $(OBJECT_DIRECTORY)
	nasm -o $(OBJECT_DIRECTORY)/boot.bin boot.asm
