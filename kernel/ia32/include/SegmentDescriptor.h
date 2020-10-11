#ifndef SEGMENT_DESCRIPTOR_GUARD
#define SEGMENT_DESCRIPTOR_GUARD

#include "stdint.h"

#pragma pack(push, 1)

struct SegmentDescriptor final
{
	uint16_t LowerSegmentSize;
	uint16_t LowerBaseAddress;
	uint8_t UpperBaseAddress1;
	uint8_t TypeAndFlags;
	uint8_t UpperSegmentSizeAndFlags;
	uint8_t UpperBaseAddress2;
};

#pragma pack(pop)

#endif // SEGMENT_DESCRIPTOR_GUARD