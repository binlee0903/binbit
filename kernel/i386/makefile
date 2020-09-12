NASM = nasm
GPP = g++ -c -masm=intel -std=c++11 -m32 -ffreestanding
LD = ld -melf_i386 -T $(SOURCE_DIRECTORY)/elf_i386.x -nostdlib -e main -Ttext 0x10200
OBJCOPY = objcopy -j .text -j .data -j .rodata -j .bss -S -O binary

OBJECT_DIRECTORY = ../../Output
SOURCE_DIRECTORY = ../kernel/i386

all: prepare $(OBJECT_DIRECTORY)/kernel32.bin

prepare:
	mkdir -p $(OBJECT_DIRECTORY)

$(OBJECT_DIRECTORY)/entry.bin: ./entry.s
	$(NASM) -o $@ $<

dep:
	@echo make dependency file
	make -C $(OBJECT_DIRECTORY) -f $(SOURCE_DIRECTORY)/makefile InternalDependency

executeInternalBuild: dep
	@echo execute internal build
	make -C $(OBJECT_DIRECTORY) -f $(SOURCE_DIRECTORY)/makefile kernel32.elf

$(OBJECT_DIRECTORY)/kernel32.elf.bin: executeInternalBuild
	@echo object copy
	$(OBJCOPY) $(OBJECT_DIRECTORY)/kernel32.elf $@

$(OBJECT_DIRECTORY)/kernel32.bin: $(OBJECT_DIRECTORY)/entry.bin $(OBJECT_DIRECTORY)/kernel32.elf.bin
	cat $^ > $@
		
clean:
	rm -f $(OBJECT_DIRECTORY)/*.*

CPP_ENTRY_POINT_OBJECT_FILE = main.o
CPP_SOURCE_FILES = $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
ASSEMBLY_SOURCE_FILES = $(wildcard $(SOURCE_DIRECTORY)/*.asm)
CPP_OBJECT_FILES = $(subst main.o, , $(notdir $(patsubst %.cpp,%.o,$(CPP_SOURCE_FILES))))
ASSEMBLY_OBJECT_FILES = $(notdir $(patsubst %.asm,%.o,$(ASSEMBLY_SOURCE_FILES)))

%.o: $(SOURCE_DIRECTORY)/%.cpp
	$(GPP) -c $<

%.o: $(SOURCE_DIRECTORY)/%.asm
	$(NASM) -f elf32 -o $@ $<

InternalDependency:
	$(GPP) -MM $(CPP_SOURCE_FILES) > Dependency.dep

kernel32.elf: $(CPP_ENTRY_POINT_OBJECT_FILE) $(CPP_OBJECT_FILES) $(ASSEMBLY_OBJECT_FILES)
	$(LD) -o $@ $^

ifeq (Dependency.dep, $(wildcard Dependency.dep))
include Dependency.dep
endif