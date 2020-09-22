#ifndef CONSOLE_GUARD
#define CONSOLE_GUARD

#include "stdint.h"

class Console
{
public:
	Console();
	~Console() = default;
	
	static void Clear();
	
	static void Print(const char* str);
	static void PrintLine(const char* str);
	
private:
	static uint8_t mCharacterCount;
	static uint8_t mLineCount;
	static char* const	mVideoMemory;
};

#endif // CONSOLE_GUARD