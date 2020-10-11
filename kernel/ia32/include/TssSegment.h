#ifndef TSS_SEGMENT_GUARD
#define TSS_SEGMENT_GUARD

#include "stdint.h"

#pragma pack(push, 1)

struct TssSegment final
{
	uint32_t Reserved1;
	uint64_t RSP[3];
	uint64_t Reserved2;
	uint64_t IST[7];
	uint64_t Reserved3;
	uint16_t Reserved4;
	uint16_t IOMapBaseAddress;
};

#pragma pack(pop)

#endif