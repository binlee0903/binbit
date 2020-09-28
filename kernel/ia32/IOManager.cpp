#include "include/IOManager.h"

uint8_t IOManager::ReadPort(uint8_t portNumber)
{
    uint16_t receivedValue = 0;

    __asm__ __volatile__
    (
        "mov ax, %1;"
        "in %0, ax;"
        "ret;"
        : "=r" (receivedValue)
        : "r" (portNumber)
        : "rax"
    );

    return receivedValue;
}

void IOManager::WritePort(uint8_t portNumber, uint16_t data)
{
    __asm__ __volatile__
    (
        "out %0, %1;"
        :
        : "r" (portNumber), "r" (data)
    );
}