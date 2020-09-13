#ifndef KERNEL_LOADER_GUARD
#define KERNEL_LOADER_GUARD

class KernelLoader
{
public:
    KernelLoader()=default;
	~KernelLoader()=default;

    static void         Execute64bitMode();

private:
    static void                PrintCPUVender();               // print cpu vender to console

    static void                InitializeKernelAreaMemory();   // init memory to 0
    static char*               IntegerToString(int target, char* string); // INCOMPLETE
    static void                Copy64bitKernelTo2MB();         // Copy IA-32e Kernel to 0x200000

    static bool                CheckIA32Support();
    static bool                CheckMemorySize();              // check memory size == 64MB

    enum
    {
        SECTOR_SIZE = 512
    };

    static unsigned int* m64KernelStartAddress; // 64 bit kernel start address(=0x100000)
    static const unsigned int* m64KernelEndAddress; // 64 bit kernel end address(=0x600000)
    static const unsigned int* mMaxOSMemorySize; // OS's max memory size(=0x4000000)
    static unsigned int mCalculatedMemorySize; // pc's total memory size
};

#endif // KERNEL_LOADER_GURAD