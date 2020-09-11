#ifndef KERNEL_LOADER_GUARD
#define KERNEL_LOADER_GUARD

class KernelLoader
{
public:
    KernelLoader();

    void                Execute64bitMode();

    void                PrintCPUVender();               // print cpu vender to console

    void                InitializeKernelAreaMemory();   // init memory to 0
    char*               IntegerToString(int target, char* string); // INCOMPLETE
    void                Copy64bitKernelTo2MB();         // Copy IA-32e Kernel to 0x200000

    bool                CheckIA32Support();
    bool                CheckMemorySize();              // check memory size == 64MB

    void                GetCPUID(unsigned int flag, unsigned int* result);

	void 				Print(const char* str);
	void 				PrintLine(const char* str);
	
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

#endif // KERNEL_LOADER_GURAD