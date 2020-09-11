#ifndef ASM_UTILITY_GUARD
#define ASM_UTILITY_GUARD

#include "types.h"

namespace ASM_Utility
{
    extern "C" BYTE InputPort(WORD port);
    extern "C" void OutputPort(WORD port, BYTE data);
}
#endif