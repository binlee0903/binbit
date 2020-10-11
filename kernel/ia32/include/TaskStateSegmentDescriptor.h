#ifndef TASK_STATE_SEGMENT_DESCRIPTOR
#define TASK_STATE_SEGMENT_DESCRIPTOR

#include "stdint.h"

#pragma pack(push, 1)

struct TaskStateSegmentDescriptor final
{
	uint16_t LowerSegmentSize;
	uint16_t LowerBaseAddress;
	uint8_t MiddleBaseAddress1;
	uint8_t TypeAndFlags;
	uint8_t MiddleSegmentSizeAndFlags;
	uint8_t MiddleBaseAddress2;
	uint32_t UpperBaseAddress;
	uint32_t Reserved;
};

#pragma pack(pop)

#endif // TASK_STATE_SEGMENT_DESCRIPTOR