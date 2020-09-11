#include "./include/Utility.h"

Utility::Utility()
    : mVideoMemory(reinterpret_cast<char*>(0xB8000))
    , m64KernelStartAddress(reinterpret_cast<int*>(0x100000))
    , m64KernelEndAddress(reinterpret_cast<int*>(0x600000))
    , mMaxOSMemorySize(reinterpret_cast<int*>(0x4000000))
    , mCharacterCount(0)
    , mLineCount(0) // after print bootloader messages
{
    for (int i = 0; i < 80 * 25; i += 2)
    {
        mVideoMemory[i] = 0;
    }
}

void Utility::Print(const char* str)
{
    if (mCharacterCount >= 80)
    {
        mCharacterCount = 0;
        mLineCount++;
    }

    for (int i = 0; str[i] != 0; i++, mCharacterCount +=2)
    {
        mVideoMemory[mCharacterCount + (mLineCount * 160)] = str[i];
    }
}

void Utility::PrintLine(const char* str)
{
    mCharacterCount = 0;

    for (int i = 0; str[i] != 0; i++, mCharacterCount += 2)
    {
        mVideoMemory[mCharacterCount + (mLineCount * 160)] = str[i];
    }
    mLineCount++;
    mCharacterCount = 0;
}

char* Utility::IntegerToString(int target, char* string)
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

bool Utility::CheckMemorySize()
{
    PrintLine("Start memory check");

    int* temp = m64KernelStartAddress;

    while (temp < mMaxOSMemorySize)
    {
        *temp = 0xbadf00d;
        mMemorySize += 1;

        if (*temp != 0xbadf00d)
        {
            Print("Memory size not enough, min memory : 64MB");
            return false;
        }

        temp += 0x100000 / 4;
    }
    
    char memorySizeString[3];
    IntegerToString(mMemorySize, memorySizeString);

    Print("Memory check complete... Your memory size : ");
    Print(memorySizeString);
    PrintLine("MB");

    return true;
}