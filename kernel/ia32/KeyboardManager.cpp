#include "./include/tools.h"
#include "./include/KeyboardManager.h"

KeyboardManager::KeyboardManager()
    : mAsciiCode(0)
    , mFlags(0)
    , mbShift(false)
    , mbCapsLock(false)
    , mbNumLock(false)
    , mbScrollLock(false)
    , mbExtendedCode(false)
    , mPauseProcessing(0)
    , mKeyMappingTable(
    {
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
        while (true);
    }
    else
    {
        changeKeyboardLED();
    }
}

char KeyboardManager::GetKeyboardInput()
{
    if (isOutputBufferFull())
    {
        getScanCode();
        
        if (convertScanCodeToAscii())
        {
            if (mFlags == KEY_FLAGS_DOWN)
            {
                return mAsciiCode;
            }
        }
    }
    
    return 0;
}

bool KeyboardManager::isAlphabetScanCode()
{
    BYTE downKey = mScanCode & 0x7F;

    if ('a' <= mKeyMappingTable[downKey].NormalCode &&
        mKeyMappingTable[downKey].NormalCode <= 'z')
    {
        return true;
    }
    
    return false;
}

bool KeyboardManager::isNumpadScanCode()
{
    BYTE downKey = mScanCode & 0x7F;

    if ((71 <= downKey) && (downKey <= 83))
    {
        return true;
    }
    
    return false;
}

bool KeyboardManager::isNumberOrSymbolScanCode()
{
    BYTE downKey = mScanCode & 0x7F;

    if ((2 <= downKey && downKey <= 53) && isAlphabetScanCode() == false)
    {
        return true;
    }

    return false;
}

bool KeyboardManager::isCombinedCode()
{
    bool result = false;
    
    if (isAlphabetScanCode() == true)
    {
        if (mbShift ^ mbCapsLock)
        {
            result = true;
        }
        else
        {
            result = false;
        }
    }
    else if (isNumberOrSymbolScanCode() == true)
    {
        if (mbShift)
        {
            result = true;
        }
        else
        {
            result = false;
        }
    }
    else if (isNumpadScanCode() == true && mbExtendedCode == false)
    {
        if (mbNumLock)
        {
            result = true;
        }
        else
        {
            result = false;
        }
    }
    
    return result;
}

    
bool KeyboardManager::isInputBufferFull()
{
    if ((ASM_Utility::InputPort(STATUS_REG) & 0x02) == 1)
    {
        return true;
    }
    
    return false;
}

bool KeyboardManager::isOutputBufferFull()
{
    if (ASM_Utility::InputPort(STATUS_REG) & 0x01)
    {
        return true;
    }    
    
    return false;
}
    
bool KeyboardManager::activateKeyboard()
{
    constexpr int ACTIVATE_KEYBOARD_DEVICE = 0xAE;
    ASM_Utility::OutputPort(CTRL_REG, ACTIVATE_KEYBOARD_DEVICE);
    
    for (int i = 0; i < 0xFFFF; i++)
    {
        if (isInputBufferFull() == false)
        {
            break;
        }
    }
    
    constexpr int ACTIVATE_KEYBOARD = 0xF4;
    ASM_Utility::OutputPort(INPUT_BUFFER, ACTIVATE_KEYBOARD);
    
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 0xFFFF; j++)
        {
            if (isOutputBufferFull() == true)
            {
                break;
            }
        }

        if (ASM_Utility::InputPort(OUTPUT_BUFFER) == ACK)
        {
            return true;
        }
    }
    
    return false;
}

bool KeyboardManager::changeKeyboardLED()
{
    for (int i = 0; i < 0xFFFF; i++)
    {
        if (isInputBufferFull() == false)
        {
            break;
        }
    }
    
    constexpr int CHANGE_LED = 0xED;
    ASM_Utility::OutputPort(OUTPUT_BUFFER, CHANGE_LED);
    
    for (int i = 0; i < 0xFFFF; i++)
    {
        if (isInputBufferFull() == false)
        {
            break;
        }
    }
    
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 0xFFFF; j++)
        {
            if (isOutputBufferFull() == true)
            {
                break;
            }
        }
        
        if (ASM_Utility::InputPort(OUTPUT_BUFFER) == ACK)
        {
            break;
        }
        
        if (i == 99)
        {
            return false;
        }
    }
    
    ASM_Utility::OutputPort(INPUT_BUFFER, (mbCapsLock << 2) | (mbNumLock << 1) | (mbScrollLock));
    
    for (int i = 0; i < 0xFFFF; i++)
    {
        if (isInputBufferFull() == false)
        {
            break;
        }
    }
    
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 0xFFFF; j++)
        {
            if (isOutputBufferFull() == true)
            {
                break;
            }
        }
        
        if (ASM_Utility::InputPort(OUTPUT_BUFFER) == ACK)
        {
            break;
        }
        
        if (i == 99)
        {
            return false;
        }
    }
    
    return true;
}
bool KeyboardManager::convertScanCodeToAscii()
{
    if (mPauseProcessing > 0)
    {
        mPauseProcessing--;
        return false;
    }
    
    constexpr int EXTENDED_KEY = 0xE0;
    constexpr int PAUSE = 0xE1;
    if (mScanCode == PAUSE)
    {
        mAsciiCode = KEY_PAUSE;
        mFlags = KEY_FLAGS_DOWN;
        mPauseProcessing = 3;
        return true;
    }
    else if (mScanCode == EXTENDED_KEY)
    {
        mbExtendedCode = true;
        return false;
    }

    bool bUseCombinedKey = isCombinedCode();

    if (bUseCombinedKey == true)
    {
        mAsciiCode = mKeyMappingTable[mScanCode & 0x7F].CombinedCode;
    }
    else
    {
        mAsciiCode = mKeyMappingTable[mScanCode & 0x7F].NormalCode;
    }

    if (mbExtendedCode == true)
    {
        mFlags = KEY_FLAGS_EXTENDEDKEY;
        mbExtendedCode = false;
    }
    else
    {
        mFlags = 0;
    }

    if ((mScanCode & 0x80) == 0)
    {
        mFlags = KEY_FLAGS_DOWN;
    }

    updateCombinationKeyStatusAndLED();
    return true;
}
    
void KeyboardManager::getScanCode()
{
    while (isOutputBufferFull() == false)
    {
        ;
    }
    
    mScanCode = ASM_Utility::InputPort(OUTPUT_BUFFER);
}

void KeyboardManager::updateCombinationKeyStatusAndLED()
{
    bool bDown = false;
    BYTE downScanCode = 0;
    bool bLEDStatusChanged = false;

    if (mScanCode & 0x80)
    {
        downScanCode = mScanCode & 0x7F;
    }
    else
    {
        bDown = true;
        downScanCode = mScanCode;
    }

    if (downScanCode == 42 || downScanCode == 54)
    {
        mbShift = true;
    }
    else if (downScanCode == 58 && bDown == true)
    {
        mbCapsLock = !mbCapsLock;
        bLEDStatusChanged = true;
    }
    else if (downScanCode == 69 && bDown == true)
    {
        mbNumLock = !mbNumLock;
        bLEDStatusChanged = true;
    }
    else if (downScanCode == 70 && bDown == true)
    {
        mbScrollLock = !mbScrollLock;
        bLEDStatusChanged = true;
    }

    if (bLEDStatusChanged == true)
    {
        changeKeyboardLED();
    }
}