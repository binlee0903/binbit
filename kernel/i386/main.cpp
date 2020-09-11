#include "./include/PageManager.h"
#include "./include/KernelLoader.h"
#include "./include/tool.h"

void main()
{
    KernelLoader kernelLoader;
    PageManager pageManager;
    
    if (!kernelLoader.CheckMemorySize())
    {
        while (true)
        {
            ;
        }
    }
    
    kernelLoader.InitializeKernelAreaMemory();

    pageManager.InitiallizePageTables();

    unsigned int registers[4];
    kernelLoader.GetCPUID(Tool::CPUID_FLAG_CPUVENDER_NAME, registers);

    char venderName[13];
    *(unsigned int*)venderName = registers[1];
    *((unsigned int*)venderName + 1) = registers[3];
    *((unsigned int*)venderName + 2) = registers[2];
    
    kernelLoader.PrintCPUVender();
    
    kernelLoader.Copy64bitKernelTo2MB();

    kernelLoader.Execute64bitMode();
}