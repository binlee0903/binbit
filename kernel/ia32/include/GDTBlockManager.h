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
	
	void AddGlobalTableDescriptor(
		uint16_t size,
		uint64_t baseAddress
	);
	
	void AddSegmentDescriptor(
		uint32_t baseAddress,
		uint32_t limit,
		uint8_t lowerFlags,
		uint8_t upperFlags
	);
	
	void AddTssSegmentDescriptor(
		uint64_t baseAddress,
		uint32_t limit,
		uint8_t lowerFlags,
		uint8_t upperFlags
	);
	
	void AddTssSegment(
		uint16_t ioMapBaseAddress);
	
	void AddIDTDescriptor(
		uint64_t handlerOffset,
		uint16_t segmentSelector,
		uint8_t ist,
		uint8_t flags
	);

private:
	void loadGDT(uint64_t baseAddress);
	void loadTS(uint16_t baseAddress);
	void loadIDTR(uint64_t baseAddress);
	
private:
	Console& mConsole;
	uint64_t mTableIndex;
	
	enum
	{
		GDT_START_ADDRESS = 0x142000,
		IDT_START_ADDRESS = 0x1420A0
	};
};

#endif