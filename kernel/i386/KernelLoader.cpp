#include "./include/KernelLoader.h"

KernelLoader::KernelLoader()
    : mVideoMemory(reinterpret_cast<char*>(0xB8000))
    , m64KernelStartAddress(reinterpret_cast<int*>(0x100000))
    , m64KernelEndAddress(reinterpret_cast<int*>(0x600000))
    , mMaxOSMemorySize(reinterpret_cast<int*>(0x4000000))
    , mCharacterCount(0)
    , mLineCount(1) // after print bootloader messages
    , mMemorySize(1)
{

}

void KernelLoader::Execute64bitMode()
{
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
	
	PrintLine(cpuVenderString);
}

void KernelLoader::Print(const char* str)
{
    for (int i = 0; str[i] != 0; i++, mCharacterCount +=2)
    {
        if (mCharacterCount >= 160)
        {
			if (mLineCount >= 25)
			{
				mLineCount = 0;
			} 
			else
			{
				mLineCount++;
			}
			
            mCharacterCount = 0;
        }
    
        mVideoMemory[mCharacterCount + (mLineCount * 160)] = str[i];
    }
}

void KernelLoader::PrintLine(const char* str)
{
    for (int i = 0; str[i] != 0; i++, mCharacterCount += 2)
    {
        if (mCharacterCount >= 160)
        {
            mLineCount++;
            mCharacterCount = 0;
        }
        
        mVideoMemory[mCharacterCount + (mLineCount * 160)] = str[i];
    }
    
	if (mLineCount >= 25)
	{
		mLineCount = 0;
	} else {
		mLineCount++;
	}
	
    mCharacterCount = 0;
}

void KernelLoader::InitializeKernelAreaMemory()
{
	int* startAddress = m64KernelStartAddress;
	const int* endAddress = m64KernelEndAddress;
	
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
    PrintLine("Start memory check");

    int* temp = m64KernelStartAddress;
    char memorySizeString[3];

    while (temp < mMaxOSMemorySize)
    {
        *temp = 0xbadf00d;
        mMemorySize += 1;

        if (*temp != 0xbadf00d)
        {
            IntegerToString(mMemorySize, memorySizeString);
            PrintLine("Memory size not enough, min memory : 64MB");
            Print("Your memory size : ");
            Print(memorySizeString);
            PrintLine("MB");
            return false;
        }

        temp += 0x100000 / 4;
    }
    
    IntegerToString(mMemorySize, memorySizeString);

    Print("Memory check complete... Your memory size : ");
    Print(memorySizeString);
    PrintLine("MB");

    return true;
}