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
}

#endif // INTERRUPT_HANDLER_GUARD