#ifndef GLOBAL_TABLE_DESCRIPTOR
#define GLOBAL_TABLE_DESCRIPTOR

#include "stdint.h"

#pragma pack(push, 1)

struct GlobalTableDescriptor final
{
	uint16_t Size;
	uint64_t BaseAddress;
	uint16_t Padding;
	uint32_t Padding2;
};

#pragma pack(pop)

#endif // GLOBAL_TABLE_DESCRIPTOR