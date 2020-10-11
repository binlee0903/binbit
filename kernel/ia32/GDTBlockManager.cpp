#include "include/GDTBlockManager.h"
#include "include/GlobalTableDescriptor.h"
#include "include/SegmentDescriptor.h"
#include "include/TaskStateSegmentDescriptor.h"
#include "include/TssSegment.h"
#include "include/IDTTableDescriptor.h"
#include "include/InterruptHandler.h"

extern "C" void test()
{
	while (true)
	{
		;
	}
}

GDTBlockManager::GDTBlockManager(Console& console)
	: mGDTBlock(0x142000)
	, mSize(0x142000)
	, mConsole(console)
{
	GlobalTableDescriptor* desc = reinterpret_cast<GlobalTableDescriptor*>(mGDTBlock);
	desc->Size = sizeof(SegmentDescriptor) * 3 + sizeof(TaskStateSegmentDescriptor) - 1;
	desc->BaseAddress = mGDTBlock + sizeof(GlobalTableDescriptor);
	mSize += sizeof(GlobalTableDescriptor);
		
	AddSegmentDescriptor(0, 0, 0, 0, 0, 0); // NULL Descriptor
	AddSegmentDescriptor(0xFFFFF, 0, 0, 0x9A, 0xA0, 0); // Code Descriptor
	AddSegmentDescriptor(0xFFFFF, 0, 0, 0x92, 0xA0, 0); // Data Descriptor
		
	uint64_t tssBaseAddress = mSize + sizeof(TaskStateSegmentDescriptor);
	char str[20];
	Interrupt::itoa(tssBaseAddress, str);
	mConsole.PrintLine(str);
		
	AddTssSegmentDescriptor((sizeof(TssSegment) - 1), tssBaseAddress, 0x89, 0x80, 0);
		
	uint64_t rsp[3] = {0, 0, 0};
	uint64_t ist[7] = {0x800000, 0, 0, 0, 0, 0, 0};
	AddTssSegment(0, rsp, 0, ist, 0, 0, 0xFFFF);
		
	GlobalTableDescriptor* idtDesc = reinterpret_cast<GlobalTableDescriptor*>(mSize);
	idtDesc->Size = 100 * sizeof(IDTTableDescriptor) - 1;
	idtDesc->BaseAddress = 0x1420A0 + sizeof(GlobalTableDescriptor);
	mSize += sizeof(GlobalTableDescriptor);
		
	for (int i = 0; i < 100; i++)
	{
		AddIDTDescriptor(reinterpret_cast<uint64_t>(test), 0x08, 0x8601, 0);
	}
		
	loadGDT(mGDTBlock);
	loadTS(0x18); // offset of tss segment in gdt
	loadIDTR(0x1420A0);
}

void GDTBlockManager::AddSegmentDescriptor(
	uint32_t segmentSize,
	uint16_t lowerBaseAddress,
	uint8_t upperBaseAddress1,
	uint8_t typeAndFlags,
	uint8_t upperFlags,
	uint8_t upperBaseAddress2)
{
	SegmentDescriptor* desc = reinterpret_cast<SegmentDescriptor*>(mSize);
	desc->LowerSegmentSize = segmentSize & 0xFFFF;
	desc->LowerBaseAddress = lowerBaseAddress;
	desc->UpperBaseAddress1 = upperBaseAddress1;
	desc->TypeAndFlags = typeAndFlags;
	desc->UpperSegmentSizeAndFlags = ((segmentSize >> 16) & 0xFF) | upperFlags;
	desc->UpperBaseAddress2 = upperBaseAddress2;
	
	mSize += sizeof(SegmentDescriptor);
}

void GDTBlockManager::AddTssSegmentDescriptor(
	uint32_t segmentSize,
	uint64_t baseAddress,
	uint8_t typeAndFlags,
	uint8_t upperFlags,
	uint32_t reserved)
{
	TaskStateSegmentDescriptor* desc = reinterpret_cast<TaskStateSegmentDescriptor*>(mSize);
	desc->LowerSegmentSize = segmentSize & 0xFFFF;
	desc->LowerBaseAddress = baseAddress & 0xFFFF;
	desc->MiddleBaseAddress1 = (baseAddress >> 16) & 0xFF;
	desc->TypeAndFlags = typeAndFlags;
	desc->MiddleSegmentSizeAndFlags = ((segmentSize >> 16) & 0xFF) | upperFlags;
	desc->MiddleBaseAddress2 = (baseAddress >> 24) & 0xFF;
	desc->UpperBaseAddress = (baseAddress >> 32);
	desc->Reserved = 0;
	
	mSize += sizeof(TaskStateSegmentDescriptor);
}

void GDTBlockManager::AddTssSegment(
	uint32_t reserved1,
	uint64_t rsp[3],
	uint64_t reserved2,
	uint64_t ist[7],
	uint64_t reserved3,
	uint16_t reserved4,
	uint16_t ioMapBaseAddress)
{
	TssSegment* segment = reinterpret_cast<TssSegment*>(mSize);
	segment->Reserved1 = 0;
	copy(segment->RSP, rsp, 3);
	segment->Reserved2 = 0;
	copy(segment->IST, ist, 7);
	segment->Reserved3 = 0;
	segment->Reserved4 = 0;
	segment->IOMapBaseAddress = ioMapBaseAddress;
	
	mSize += sizeof(TssSegment);
}

void GDTBlockManager::AddIDTDescriptor(
	uint64_t handlerOffset,
	uint16_t segmentSelector,
	uint16_t typeAndFlags,
	uint32_t reserved)
{
	IDTTableDescriptor* desc = reinterpret_cast<IDTTableDescriptor*>(mSize);
	desc->HandlerOffset1 = handlerOffset & 0xFFFF;
	desc->SegmentSelector = segmentSelector;
	desc->TypeAndFlags = typeAndFlags;
	desc->HandlerOffset2 = (handlerOffset >> 16) & 0xFFFF;
	desc->HandlerOffset3 = (handlerOffset >> 32) & 0xFFFFFFFF;
	desc->Reserved = reserved;
	
	mSize += sizeof(IDTTableDescriptor);
}

void GDTBlockManager::copy(uint64_t* dest, uint64_t* source, int length)
{
	for (int i = 0; i < length; i++)
	{
		dest[i] = source[i];
	}
}

void GDTBlockManager::loadGDT(uint64_t baseAddress)
{
	__asm__ __volatile__
	(
		"mov rdi, %0;"
		"lgdt [rdi];"
		:
		: "r" (baseAddress)
		: "rdi"
	);
}

void GDTBlockManager::loadTS(uint16_t baseAddress)
{
	__asm__ __volatile__
	(
		"mov di, %0;"
		"ltr di;"
		:
		: "r" (baseAddress)
		: "rdi"
	);
}

void GDTBlockManager::loadIDTR(uint64_t baseAddress)
{
	__asm__ __volatile__
	(
		"mov rdi, %0;"
		"lidt [rdi];"
		:
		: "r" (baseAddress)
		: "rdi"
	);
}