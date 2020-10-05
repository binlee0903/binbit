#include "./include/IOManager.h"
#include "./include/KeyboardManager.h"

KeyboardManager::KeyboardManager(Console& console)
    : mConsole(console)
	, mIOManager()
	, mbShift(false)
	, mbCaps(false)
	, mbNum(false)
	, mbScroll(false)
    , mScancode(0)
    , mKeyStatus(KEY_ACTION_NONE)
    , mConvertTable
    ({
    /*  0   */  {   KEY_NONE        ,   KEY_NONE        },
    /*  1   */  {   KEY_ESC         ,   KEY_ESC         },
    /*  2   */  {   '1'             ,   '!'             },
    /*  3   */  {   '2'             ,   '@'             },
    /*  4   */  {   '3'             ,   '#'             },
    /*  5   */  {   '4'             ,   '$'             },
    /*  6   */  {   '5'             ,   '%'             },
    /*  7   */  {   '6'             ,   '^'             },
    /*  8   */  {   '7'             ,   '&'             },
    /*  9   */  {   '8'             ,   '*'             },
    /*  10  */  {   '9'             ,   '('             },
    /*  11  */  {   '0'             ,   ')'             },
    /*  12  */  {   '-'             ,   '_'             },
    /*  13  */  {   '='             ,   '+'             },
    /*  14  */  {   KEY_BACKSPACE   ,   KEY_BACKSPACE   },
    /*  15  */  {   KEY_TAB         ,   KEY_TAB         },
    /*  16  */  {   'q'             ,   'Q'             },
    /*  17  */  {   'w'             ,   'W'             },
    /*  18  */  {   'e'             ,   'E'             },
    /*  19  */  {   'r'             ,   'R'             },
    /*  20  */  {   't'             ,   'T'             },
    /*  21  */  {   'y'             ,   'Y'             },
    /*  22  */  {   'u'             ,   'U'             },
    /*  23  */  {   'i'             ,   'I'             },
    /*  24  */  {   'o'             ,   'O'             },
    /*  25  */  {   'p'             ,   'P'             },
    /*  26  */  {   '['             ,   '{'             },
    /*  27  */  {   ']'             ,   '}'             },
    /*  28  */  {   '\n'            ,   '\n'            },
    /*  29  */  {   KEY_CTRL        ,   KEY_CTRL        },
    /*  30  */  {   'a'             ,   'A'             },
    /*  31  */  {   's'             ,   'S'             },
    /*  32  */  {   'd'             ,   'D'             },
    /*  33  */  {   'f'             ,   'F'             },
    /*  34  */  {   'g'             ,   'G'             },
    /*  35  */  {   'h'             ,   'H'             },
    /*  36  */  {   'j'             ,   'J'             },
    /*  37  */  {   'k'             ,   'K'             },
    /*  38  */  {   'l'             ,   'L'             },
    /*  39  */  {   ';'             ,   ':'             },
    /*  40  */  {   '\''            ,   '\"'            },
    /*  41  */  {   '`'             ,   '~'             },
    /*  42  */  {   KEY_LSHIFT      ,   KEY_LSHIFT      },
    /*  43  */  {   '\\'            ,   '|'             },
    /*  44  */  {   'z'             ,   'Z'             },
    /*  45  */  {   'x'             ,   'X'             },
    /*  46  */  {   'c'             ,   'C'             },
    /*  47  */  {   'v'             ,   'V'             },
    /*  48  */  {   'b'             ,   'B'             },
    /*  49  */  {   'n'             ,   'N'             },
    /*  50  */  {   'm'             ,   'M'             },
    /*  51  */  {   ','             ,   '<'             },
    /*  52  */  {   '.'             ,   '>'             },
    /*  53  */  {   '/'             ,   '?'             },
    /*  54  */  {   KEY_RSHIFT      ,   KEY_RSHIFT      },
    /*  55  */  {   '*'             ,   '*'             },
    /*  56  */  {   KEY_LALT        ,   KEY_LALT        },
    /*  57  */  {   ' '             ,   ' '             },
    /*  58  */  {   KEY_CAPSLOCK    ,   KEY_CAPSLOCK    },
    /*  59  */  {   KEY_F1          ,   KEY_F1          },
    /*  60  */  {   KEY_F2          ,   KEY_F2          },
    /*  61  */  {   KEY_F3          ,   KEY_F3          },
    /*  62  */  {   KEY_F4          ,   KEY_F4          },
    /*  63  */  {   KEY_F5          ,   KEY_F5          },
    /*  64  */  {   KEY_F6          ,   KEY_F6          },
    /*  65  */  {   KEY_F7          ,   KEY_F7          },
    /*  66  */  {   KEY_F8          ,   KEY_F8          },
    /*  67  */  {   KEY_F9          ,   KEY_F9          },
    /*  68  */  {   KEY_F10         ,   KEY_F10         },
    /*  69  */  {   KEY_NUMLOCK     ,   KEY_NUMLOCK     },
    /*  70  */  {   KEY_SCROLLLOCK  ,   KEY_SCROLLLOCK  },

    /*  71  */  {   KEY_HOME        ,   '7'             },
    /*  72  */  {   KEY_UP          ,   '8'             },
    /*  73  */  {   KEY_PAGEUP      ,   '9'             },
    /*  74  */  {   '-'             ,   '-'             },
    /*  75  */  {   KEY_LEFT        ,   '4'             },
    /*  76  */  {   KEY_CENTER      ,   '5'             },
    /*  77  */  {   KEY_RIGHT       ,   '6'             },
    /*  78  */  {   '+'             ,   '+'             },
    /*  79  */  {   KEY_END         ,   '1'             },
    /*  80  */  {   KEY_DOWN        ,   '2'             },
    /*  81  */  {   KEY_PAGEDOWN    ,   '3'             },
    /*  82  */  {   KEY_INS         ,   '0'             },
    /*  83  */  {   KEY_DEL         ,   '.'             },
    /*  84  */  {   KEY_NONE        ,   KEY_NONE        },
    /*  85  */  {   KEY_NONE        ,   KEY_NONE        },
    /*  86  */  {   KEY_NONE        ,   KEY_NONE        },
    /*  87  */  {   KEY_F11         ,   KEY_F11         },
    /*  88  */  {   KEY_F12         ,   KEY_F12         }
    })
{
    if (!activateKeyboard())
    {
		mConsole.PrintLine("activation failed");
		
        while (true);
		{
			;
		}
    }
}

char KeyboardManager::GetKey()
{
    if (isOutputBufferFull())
    {
        char key = getKey();

        if (mKeyStatus == KEY_ACTION_DOWN && key != KEY_INVALID)
        {
            return key;
        }
    }
    
    return KEY_NOT_EXIST;
}

bool KeyboardManager::setKeyboardLED()
{
    waitForInputBufferAvailable();

    // send keyboard led change command
    mIOManager.WritePort(OUTPUT_BUFFER, 0xED);
    waitForInputBufferAvailable();
    waitForKeyboardResponse();

    // send led status values
    mIOManager.WritePort(INPUT_BUFFER, (mbCaps << 2) | (mbNum << 1) | mbScroll);
    waitForInputBufferAvailable();
    return waitForKeyboardResponse();
}

char KeyboardManager::getKey()
{
    while (!isOutputBufferFull())
    {
        ;
    }
	
    uint8_t scanCode = mIOManager.ReadPort(OUTPUT_BUFFER);

    if (scanCode & 0x80)
    {
        scanCode &= 0x7F;
        mKeyStatus = KEY_ACTION_UP;
    }
    else
    {
        mKeyStatus = KEY_ACTION_DOWN;
    }
    
    if (scanCode == 0xE1)
    {
        processPauseKey();
        return KEY_PAUSE;
    }

    if (scanCode == 0xE0)
    {
        scanCode = processExtendedKey();
    }

    if (updateCombinationKeyStatus(scanCode))
	{
		return KEY_INVALID;
	}

    // check alphabet key
    if ('a' <= mConvertTable[scanCode].NormalCode && mConvertTable[scanCode].NormalCode <='z')
    {
        if (mbShift || mbCaps)
        {
            return mConvertTable[scanCode].CombinationCode;
        }
        else
        {
            return mConvertTable[scanCode].NormalCode;
        }
    }

    // check number and special key
    if (2 <= scanCode && scanCode <= 53)
    {
        if (mbShift)
        {
            return mConvertTable[scanCode].CombinationCode;
        }
        else
        {
            return mConvertTable[scanCode].NormalCode;
        }
    }

    // check numpad
    if (71 <= scanCode && scanCode <= 83)
    {
        if (mbNum)
        {
            return mConvertTable[scanCode].CombinationCode;
        }
        else
        {
            return mConvertTable[scanCode].NormalCode;
        }
    }
	
	if (57 == scanCode)
	{
		return mConvertTable[scanCode].NormalCode;
	}
	
	return KEY_INVALID;
}

bool KeyboardManager::activateKeyboard()
{
    // activate keyboard device, but real keyboard not activated
    mIOManager.WritePort(0x64, 0xAE);
	
    waitForInputBufferAvailable();
	
    // send keyboard activate command
    mIOManager.WritePort(0x60, 0xF4);
    
    return waitForKeyboardResponse();
}


uint8_t KeyboardManager::processExtendedKey()
{
    while (!isOutputBufferFull())
    {
        ;
    }

    return mIOManager.ReadPort(OUTPUT_BUFFER);
}

void KeyboardManager::processPauseKey()
{
    uint8_t scanCode = 0;

    for (uint8_t i = 0; i < 2; i++)
    {
        while (!isOutputBufferFull())
        {
            ;
        }

        scanCode = mIOManager.ReadPort(OUTPUT_BUFFER);
    }
}

bool KeyboardManager::isInputBufferFull()
{
    if (mIOManager.ReadPort(KEYBOARD_STATUS_REG) & 0x02)
    {
        return true;
    }
	
    return false;
}

bool KeyboardManager::isOutputBufferFull()
{
    if (mIOManager.ReadPort(KEYBOARD_STATUS_REG) & 0x01)
    {
        return true;
    }

    return false;
}

bool KeyboardManager::updateCombinationKeyStatus(uint8_t scanCode)
{

    if (mKeyStatus == KEY_ACTION_DOWN)
    {
		switch (scanCode)
		{
			case 42:
			case 54:
				mbShift = true;
				return true;
				
			case 58:
				mbCaps ^= true;
				setKeyboardLED();
				return true;
				
			case 69:
				mbNum ^= true;
				setKeyboardLED();
				return true;
				
			case 70:
				mbScroll ^= true;
				setKeyboardLED();
				return true;
				
			default:
				return false;
		}
    }

    if (mKeyStatus == KEY_ACTION_UP)
    {
        if ((scanCode == 42 || scanCode == 54))
        {
            mbShift = false;
			return true;
        }
    }
	
	return false;
}

// temp function while no interrupt
bool KeyboardManager::waitForKeyboardResponse()
{
    for (uint32_t i = 0; i < 100; i++)
    {
        for (uint32_t j = 0; j < 0xFFFF; j++)
        {
            if (isOutputBufferFull())
            {
                break;
            }
        }

        if (mIOManager.ReadPort(OUTPUT_BUFFER) == KEYBOARD_RESPONSE)
        {
            return true;
        }
    }
	
    return false;
}

bool KeyboardManager::waitForInputBufferAvailable()
{
    for (uint32_t i = 0; i < 0xFFFF; i++)
    {
        if (!isInputBufferFull())
        {
            return true;
        }
    }

    return false;
}