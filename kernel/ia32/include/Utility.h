#ifndef UTILITY_GUARD
#define UTILITY_GUARD

class Utility
{
public:
    Utility();

    void                Print(const char* str);     // print string in one line and no '\n'
    void                PrintLine(const char* str); // print string in one line

    void                InitializeMemory(int* startAddress, const int* endAddress); // init memory to 0
    char*               IntegerToString(int target, char* string); // INCOMPLETE
    void                Copy64bitKernelTo2MB();      // Copy IA-32e Kernel to 0x200000
    bool                CheckMemorySize();           // check memory size == 64MB

    inline int*         Get64BitKernelStartAddress()    const { return m64KernelStartAddress; }
    inline const int*   Get64BitKernelEndAddress()      const { return m64KernelEndAddress; }

private:
    enum
    {
        SECTOR_SIZE = 512
    };

    char* const              mVideoMemory;

    int*          m64KernelStartAddress; // 64 bit kernel start address(=0x100000)
    const int*    m64KernelEndAddress;   // 64 bit kernel end address(=0x600000)
    const int*    mMaxOSMemorySize;      // OS's max memory size(=0x4000000)

    unsigned short int  mCharacterCount;       // print function's helper variable
    unsigned short int  mLineCount;            // same
    
    unsigned int        mMemorySize;           // pc's total memory size
};

#endif // UTILITY_GUARD