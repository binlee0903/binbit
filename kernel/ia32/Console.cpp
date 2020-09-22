#include "include/Console.h"

Console::Console()
{
	Clear();
}

uint8_t Console::mCharacterCount = 0;
uint8_t Console::mLineCount = 0;
char* const	Console::mVideoMemory = reinterpret_cast<char*>(0xB8000);

void Console::Clear()
{
	constexpr int SCREEN_BYTE_COUNT = 4000;
		
	for (int i = 0; i < SCREEN_BYTE_COUNT; i += 2)
	{
		mVideoMemory[i] = 0;
	}
}

void Console::Print(const char* str)
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

void Console::PrintLine(const char* str)
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