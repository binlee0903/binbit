a#include "./include/PageManager.h"
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
	
    kernelLoader.PrintCPUVender();
    
    kernelLoader.Copy64bitKernelTo2MB();

    kernelLoader.Execute64bitMode();
	
	kernelLoader.PrintLine("Failed load 64bit mode execute infinite loop");
	
	while (true)
	{
		;
	}
}