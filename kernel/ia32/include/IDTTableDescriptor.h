#ifndef IDT_TABLE_DESCRIPTOR
#define IDT_TABLE_DESCRIPTOR

#include "stdint.h"

#pragma pack(push, 1)

struct IDTTableDescriptor
{
	uint16_t HandlerOffset1;
	uint16_t SegmentSelector;
	uint8_t IST;
	uint8_t TypeAndFlags;
	uint16_t HandlerOffset2;
	uint32_t HandlerOffset3;
	uint32_t Reserved;
};

#pragma pack(pop)

#endif