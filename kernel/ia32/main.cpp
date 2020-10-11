#include "include/KeyboardManager.h"
#include "include/Console.h"
#include "include/GDTBlockManager.h"

extern "C" int main()
{
    Console console;
	GDTBlockManager mamager(console);

    console.PrintLine("IA-32e mode kernel executed...");
    console.PrintLine("Activate Keyboard...");
	
    KeyboardManager keyboardManager(console);

    console.PrintLine("Sucessfully activated keyboard");
	
    char temp[2];

    temp[1] = 0;
	
    while (true)
    {
        temp[0] = keyboardManager.GetKey();

        if (temp[0] != keyboardManager.KEY_INVALID)
        {
			if (temp[0] == '0')
			{
				int a = 3 / 0;
			}
			
            console.Print(temp);
        }
    }
}