#ifndef GDT_GUARD
#define GDT_GUARD

#include "Console.h"
#include "stdint.h"
#include "GlobalTableDescriptor.h"
#include "SegmentDescriptor.h"
#include "TaskStateSegmentDescriptor.h"
#include "TssSegment.h"
#include "IDTTableDescriptor.h"

class GDTBlockManager final
{
public:
	GDTBlockManager(Console& console);
	~GDTBlockManager() = default;
	
	void AddSegmentDescriptor(
		uint32_t segmentSize,
		uint16_t lowerBaseAddress,
		uint8_t upperBaseAddress1,
		uint8_t typeAndFlags,
		uint8_t upperFlags,
		uint8_t upperBaseAddress2);
	
	void AddTssSegmentDescriptor(
		uint32_t segmentSize,
		uint64_t baseAddress,
		uint8_t typeAndFlags,
		uint8_t upperFlags,
		uint32_t reserved);
	
	void AddTssSegment(
		uint32_t reserved1,
		uint64_t rsp[3],
		uint64_t reserved2,
		uint64_t ist[7],
		uint64_t reserved3,
		uint16_t reserved4,
		uint16_t ioMapBaseAddress);
	
	void AddIDTDescriptor(
		uint64_t handlerOffset,
		uint16_t segmentSelector,
		uint16_t typeAndFlags,
		uint32_t reserved);

private:
	void copy(uint64_t* dest, uint64_t* source, int length);
	
	void loadGDT(uint64_t baseAddress);
	void loadTS(uint16_t baseAddress);
	void loadIDTR(uint64_t baseAddress);
	
private:
	uint64_t mGDTBlock;
	uint64_t mSize;
	
	Console& mConsole;
};

#endif