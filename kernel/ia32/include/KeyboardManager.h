#ifndef KEYBOARD_MANAGER_GUARD
#define KEYBOARD_MANAGER_GUARD

#include "IOManager.h"

class KeyboardManager
{
public:
    KeyboardManager();

    char GetKey();

private:
    bool setKeyboardLED(bool bScroll, bool bCaps, bool bNum);
    char getKey();

private:
    bool activateKeyboard();
    bool isCombinationKeyPressed();
    bool isInputBufferFull();
    bool isOutputBufferFull();
    bool waitForKeyboardResponse();
    bool waitForInputBufferAvailable();

private:
    IOManager mIOManager;

private:
    char    mKey;
    uint8_t mScancode;
    uint8_t mKeyStatus;

    enum 
    {
        KEY_ACTION_NONE,
        KEY_ACTION_DOWN
    };

    enum
    {
        KEYBOARD_RESPONSE = 0xFA,
        KEYBOARD_STATUS_REG = 0x64,
        KEYBOARD_CONTROL_REG = 0x64,
        INPUT_BUFFER = 0x60,
        OUTPUT_BUFFER = 0x60,
        KEY_MAPPING_TABLE_COUNT = 89
    };

    enum
    {
        KEY_NONE        =   0x00,
        KEY_ENTER       =   '\n',
        KEY_TAB         =   '\t',
        KEY_ESC         =   0x1B,
        KEY_BACKSPACE   =   0x08,
        KEY_CTRL        =   0x81,
        KEY_LSHIFT      =   0x82,
        KEY_RSHIFT      =   0x83,
        KEY_PRINTSCREEN =   0x84,
        KEY_LALT        =   0x85,
        KEY_CAPSLOCK    =   0x86,
        KEY_F1          =   0x87,
        KEY_F2          =   0x88,
        KEY_F3          =   0x89,
        KEY_F4          =   0x8A,
        KEY_F5          =   0x8B,
        KEY_F6          =   0x8C,
        KEY_F7          =   0x8D,
        KEY_F8          =   0x8E,
        KEY_F9          =   0x8F,
        KEY_F10         =   0x90,
        KEY_NUMLOCK     =   0x91,
        KEY_SCROLLLOCK  =   0x92,
        KEY_HOME        =   0x93,
        KEY_UP          =   0x94,
        KEY_PAGEUP      =   0x95,
        KEY_LEFT        =   0x96,
        KEY_CENTER      =   0x97,
        KEY_RIGHT       =   0x98,
        KEY_END         =   0x99,
        KEY_DOWN        =   0x9A,
        KEY_PAGEDOWN    =   0x9B,
        KEY_INS         =   0x9C,
        KEY_DEL         =   0x9D,
        KEY_F11         =   0x9E,
        KEY_F12         =   0x9F,
        KEY_PAUSE       =   0xA0,
    };

private:
    struct AsciiConvertTable
    {
        uint8_t NormalCode;
        uint8_t CombinationCode;
    };
    
    const AsciiConvertTable mConvertTable[KEY_MAPPING_TABLE_COUNT];
};

#endif