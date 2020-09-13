#include "./include/Console.h"
#include "./include/KernelLoader.h"
#include "./include/PageManager.h"

unsigned int* KernelLoader::m64KernelStartAddress = reinterpret_cast<unsigned int*>(0x100000);
const unsigned int* KernelLoader::m64KernelEndAddress = reinterpret_cast<const unsigned int*>(0x600000);
const unsigned int* KernelLoader::mMaxOSMemorySize = reinterpret_cast<const unsigned int*>(0x4000000);
unsigned int KernelLoader::mCalculatedMemorySize = 1;

void KernelLoader::Execute64bitMode()
{
	if (!CheckMemorySize())
    {
        while (true)
        {
            ;
        }
    }
    
    InitializeKernelAreaMemory();
    PageManager::InitiallizePageTables();
    PrintCPUVender();
    Copy64bitKernelTo2MB();
	
	__asm__ __volatile__
	(
		"mov eax, cr4;"
		"or eax, 0x20;"
		"mov cr4, eax;"
		"mov eax, 0x100000;"
		"mov cr3, eax;"
		"mov ecx, 0xC0000080;"
		"rdmsr;"
		"or eax, 0x0100;"
		"wrmsr;"
		"mov eax, cr0;"
		"or eax, 0xE0000000;"
		"xor eax, 0x60000000;"
		"mov cr0, eax;"
		"jmp 0x08:0x200000;"
		:
		:
		: "eax", "ecx"
	);
}

void KernelLoader::PrintCPUVender()
{
	char cpuVenderString[15] = { 0, };
	
	__asm__ __volatile__
	(
		"xor eax, eax;"
		"cpuid;"
		"mov %0, ebx;"
		"mov %0 + 4, edx;"
		"mov %0 + 8, ecx;"
		: "=m" (cpuVenderString)
		: "m" (cpuVenderString)
		: "eax", "ebx", "ecx", "edx"
	);
	
	Console::PrintLine(cpuVenderString);
}

void KernelLoader::InitializeKernelAreaMemory()
{
	unsigned int* startAddress = m64KernelStartAddress;
	const unsigned int* endAddress = m64KernelEndAddress;
	
    while (startAddress < endAddress)
    {
        *startAddress = 0;

        if (*startAddress != 0)
        {
            while (true)
            {
                ;
            }
        }

        startAddress++;
    }
}

char* KernelLoader::IntegerToString(int target, char* string)
{
    int temp = target;
    int index = 0;

    while (temp > 0)
    {
        temp /= 10;
        index++;
    }

    for (int i = index - 1; i >= 0; i--)
    {
        string[i] = target % 10 + '0';
        target /= 10;
    }

    string[index] = '\0';

    return nullptr;
}

void KernelLoader::Copy64bitKernelTo2MB()
{
    unsigned int totalSectorCount = *(reinterpret_cast<unsigned int*>(0x7D50));
    unsigned int kernel32SectorCount = *(reinterpret_cast<unsigned int*>(0x7D52));

    unsigned int* sourceAddress = reinterpret_cast<unsigned int*>(0x10000 + kernel32SectorCount * SECTOR_SIZE);
    unsigned int* destAddress = reinterpret_cast<unsigned int*>(0x200000);

    for (int i = 0; i < (totalSectorCount - kernel32SectorCount) * SECTOR_SIZE / 4; i++)
    {
        *destAddress = *sourceAddress;
        destAddress++;
        sourceAddress++;
    }
}

bool KernelLoader::CheckMemorySize()
{
    Console::PrintLine("Start memory check");

    unsigned int* temp = m64KernelStartAddress;
    char memorySizeString[3];

    while (temp < mMaxOSMemorySize)
    {
        *temp = 0xbadf00d;
        mCalculatedMemorySize += 1;

        if (*temp != 0xbadf00d)
        {
            IntegerToString(mCalculatedMemorySize, memorySizeString);
            Console::PrintLine("Memory size not enough, min memory : 64MB");
            Console::Print("Your memory size : ");
            Console::Print(memorySizeString);
            Console::PrintLine("MB");
            return false;
        }

        temp += 0x100000 / 4;
    }
    
    IntegerToString(mCalculatedMemorySize, memorySizeString);

    Console::Print("Memory check complete... Your memory size : ");
    Console::Print(memorySizeString);
    Console::PrintLine("MB");

    return true;
}