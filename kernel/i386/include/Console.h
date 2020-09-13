#ifndef CONSOLE_GUARD
#define CONSOLE_GUARD

class Console
{
public:
	Console();
	~Console() = default;
	
	static void Clear();
	
	static void Print(const char* str);
	static void PrintLine(const char* str);
	
private:
	static unsigned char mCharacterCount;
	static unsigned char mLineCount;
	static char* const	mVideoMemory;
};

#endif // CONSOLE_GUARD