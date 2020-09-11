#include "./include/KeyboardManager.h"
#include "./include/types.h"
#include "./include/Utility.h"

extern "C" int main()
{
    Utility util;

    util.PrintLine("IA-32e mode kernel executed...");
    util.PrintLine("Activate Keyboard...");

    KeyboardManager keyboardManager;

    util.PrintLine("Sucessfully activated keyboard");

    char temp[2];

    temp[1] = 0;

    util.PrintLine("Hello");

    while (true)
    {
        temp[0] = keyboardManager.GetKeyboardInput();

        if (temp[0])
        {
            util.Print(temp);
        }
    }
}