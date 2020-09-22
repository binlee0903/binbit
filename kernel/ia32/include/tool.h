#ifndef ASM_UTILITY_GUARD
#define ASM_UTILITY_GUARD

#include "stdint.h"

namespace tool
{
    extern "C" uint8_t InputPort(uint16_t port);
    extern "C" void OutputPort(uint16_t port, uint8_t data);
}
#endif