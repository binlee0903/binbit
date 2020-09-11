NASM = nasm -f elf64
GPP = g++ -c -std=c++11 -m64 -ffreestanding
LD = ld -melf_x86_64 -T $(SOURCE_DIRECTORY)/elf_x86_64.x -nostdlib -e main -Ttext 0x200000
OBJCOPY = objcopy -j .text -j .data -j .rodata -j .bss -S -O binary

OBJECT_DIRECTORY = ../../Output
SOURCE_DIRECTORY = ../kernel/ia32

all: prepare $(OBJECT_DIRECTORY)/kernel64.bin

prepare:
	mkdir -p $(OBJECT_DIRECTORY)

dep:
	@echo make dependancy file
	make -C $(OBJECT_DIRECTORY) -f $(SOURCE_DIRECTORY)/makefile InternalDependency

executeInternalBuild: dep
	@echo execute internal build
	make -C $(OBJECT_DIRECTORY) -f $(SOURCE_DIRECTORY)/makefile kernel64.elf

$(OBJECT_DIRECTORY)/kernel64.bin: executeInternalBuild
	@echo object file copy
	$(OBJCOPY) $(OBJECT_DIRECTORY)/kernel64.elf $@

ASM_ENTRY_POINT_SOURCE_FILE = $(SOURCE_DIRECTORY)/entry.s
ASM_ENTRY_POINT_OBJECT_FILE = entry.o
CPP_SOURCE_FILES = $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
ASSEMBLY_SOURCE_FILES = $(wildcard $(SOURCE_DIRECTORY)/*.asm)
CPP_OBJECT_FILES = $(notdir $(patsubst %.cpp,%.o,$(CPP_SOURCE_FILES)))
ASSEMBLY_OBJECT_FILES = $(notdir $(patsubst %.asm,%.o,$(ASSEMBLY_SOURCE_FILES)))

$(ASM_ENTRY_POINT_OBJECT_FILE): $(ASM_ENTRY_POINT_SOURCE_FILE)
	$(NASM) -o $@ $<

%.o: $(SOURCE_DIRECTORY)/%.cpp
	$(GPP) -c $<

%.o: $(SOURCE_DIRECTORY)/%.asm
	$(NASM) -o $@ $<

InternalDependency:
	$(GPP) -MM $(CPP_SOURCE_FILES) > Dependency.dep

kernel64.elf: $(ASM_ENTRY_POINT_OBJECT_FILE) $(CPP_OBJECT_FILES) $(ASSEMBLY_OBJECT_FILES)
	$(LD) -o $@ $^

ifeq (Dependency.dep, $(wildcard Dependency.dep))
include Dependency.dep
endif