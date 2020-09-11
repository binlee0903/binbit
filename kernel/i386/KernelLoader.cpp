#include "./include/KernelLoader.h"

KernelLoader::KernelLoader()
    : mVideoMemory(reinterpret_cast<char*>(0xB8000))
    , m64KernelStartAddress(reinterpret_cast<int*>(0x100000))
    , m64KernelEndAddress(reinterpret_cast<int*>(0x600000))
    , mMaxOSMemorySize(reinterpret_cast<int*>(0x4000000))
    , mCharacterCount(0)
    , mLineCount(3) // after print bootloader messages
    , mMemorySize(1)
{

}

void KernelLoader::Execute64bitMode()
{
	return;
}

void KernelLoader::PrintCPUVender()
{
	return;
}

void KernelLoader::Print(const char* str)
{
    for (int i = 0; str[i] != 0; i++, mCharacterCount +=2)
    {
        if (mCharacterCount >= 160)
        {
            mLineCount++;
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
    
    mLineCount++;
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

void KernelLoader::GetCPUID(unsigned int flag, unsigned int* result)
{
	return;
}