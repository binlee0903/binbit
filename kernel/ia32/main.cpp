#include "include/KeyboardManager.h"
#include "include/Console.h"

extern "C" int main()
{
    Console console;

    console.PrintLine("IA-32e mode kernel executed...");
    console.PrintLine("Activate Keyboard...");

    KeyboardManager keyboardManager;

    console.PrintLine("Sucessfully activated keyboard");

    char temp[2];

    temp[1] = 0;

    while (true)
    {
        temp[0] = keyboardManager.GetKeyboardInput();

        if (temp[0])
        {
            console.Print(temp);
        }
    }
}