#ifndef INTERRUPT_HANDLER_GUARD
#define INTERRUPT_HANDLER_GUARD

#include "Console.h"

namespace Interrupt
{
	extern "C" void dummy()
	{
		Console console;
		
		console.Clear();
		console.PrintLine("-----------------------------------------------");
		console.PrintLine("---                  Hello                  ---");
		console.PrintLine("-----------------------------------------------");
		
		while (true)
		{
			;
		}
	}
	
	void itoa(uint64_t target, char* dest)
	{
		int length = 0;
		uint64_t temp = target;
		
		while (temp /= 10)
		{
			length++;
		}
		
		for (int i = length; i >= 0; i--)
		{
			dest[i] = target % 10  + '0';
			target /= 10;
		}
		
		dest[length + 1] = '\0';
	}
}

#endif // INTERRUPT_HANDLER_GUARD