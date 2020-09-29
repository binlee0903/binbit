#include "include/IOManager.h"

uint8_t IOManager::ReadPort(uint16_t portNumber)
{
    uint8_t receivedValue = 0;

    __asm__ __volatile__
    (
        "mov dx, %1;"
        "in al, dx;"
		"mov %0, al;"
        : "+r" (receivedValue)
        : "r" (portNumber)
        : "rax", "rdx"
    );

    return receivedValue;
}

void IOManager::WritePort(uint16_t portNumber, uint8_t data)
{
    __asm__ __volatile__
    (
		"mov dx, %1;"
		"mov al, %0;"
        "out dx, al;"
        : "+r" (data)
        : "r" (portNumber)
		: "rax", "rdx"
    );
}