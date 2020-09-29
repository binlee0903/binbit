#include "include/KeyboardManager.h"
#include "include/Console.h"

extern "C" int main()
{
    Console console;

    console.PrintLine("IA-32e mode kernel executed...");
    console.PrintLine("Activate Keyboard...");

    KeyboardManager keyboardManager(console);

    console.PrintLine("Sucessfully activated keyboard");
	
    char temp[2];

    temp[1] = 0;
	
    while (true)
    {
        temp[0] = keyboardManager.GetKey();

        if (temp[0] != keyboardManager.KEY_NOT_EXIST)
        {
            console.Print(temp);
        }
    }
}