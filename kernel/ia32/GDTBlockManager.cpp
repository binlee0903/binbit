#include "include/GDTBlockManager.h"
#include "include/InterruptHandler.h"

GDTBlockManager::GDTBlockManager(Console& console)
	: mTableIndex(GDT_START_ADDRESS)
	, mConsole(console)
{	
	AddGlobalTableDescriptor(sizeof(SegmentDescriptor) * 3 + sizeof(TaskStateSegmentDescriptor) - 1,
							GDT_START_ADDRESS + sizeof(GlobalTableDescriptor));
	AddSegmentDescriptor(0, 0, 0, 0); // NULL Descriptor
	AddSegmentDescriptor(0, 0xFFFFF, 0x9A, 0xAF); // Code Descriptor
	AddSegmentDescriptor(0, 0xFFFFF, 0x92, 0xAF); // Data Descriptor
	AddTssSegmentDescriptor(mTableIndex + sizeof(TaskStateSegmentDescriptor), sizeof(TssSegment) - 1, 0x89, 0x80);
	AddTssSegment(0xFFFF);
	
	AddGlobalTableDescriptor(100 * sizeof(IDTTableDescriptor) - 1, IDT_START_ADDRESS + sizeof(GlobalTableDescriptor));
		
	for (int i = 0; i < 100; i++)
	{
		AddIDTDescriptor(reinterpret_cast<uint64_t>(Interrupt::dummy), 0x08, 0x01, 0x8E);
	}
	
	loadGDT(GDT_START_ADDRESS);
	loadTS(0x18); // offset of tss segment in gdt
	loadIDTR(IDT_START_ADDRESS);
}

void GDTBlockManager::AddGlobalTableDescriptor(
	uint16_t size,
	uint64_t baseAddress)
{
	GlobalTableDescriptor* desc = reinterpret_cast<GlobalTableDescriptor*>(mTableIndex);
	desc->Size = size;
	desc->BaseAddress = baseAddress;
	desc->Padding1 = 0;
	desc->Padding2 = 0;
	
	mTableIndex += sizeof(GlobalTableDescriptor);
}

void GDTBlockManager::AddSegmentDescriptor(
	uint32_t baseAddress,
	uint32_t limit,
	uint8_t lowerFlags,
	uint8_t upperFlags)
{
	SegmentDescriptor* desc = reinterpret_cast<SegmentDescriptor*>(mTableIndex);
	desc->LowerSegmentSize = limit & 0xFFFF;
	desc->LowerBaseAddress = baseAddress & 0xFFFF;
	desc->UpperBaseAddress1 = (baseAddress >> 16) & 0xFF;
	desc->TypeAndFlags = lowerFlags;
	desc->UpperSegmentSizeAndFlags = ((limit >> 16) & 0xFF) | upperFlags;
	desc->UpperBaseAddress2 = (baseAddress >> 24) & 0xFF;
	
	mTableIndex += sizeof(SegmentDescriptor);
}

void GDTBlockManager::AddTssSegmentDescriptor(
	uint64_t baseAddress,
	uint32_t limit,
	uint8_t lowerFlags,
	uint8_t upperFlags)
{
	TaskStateSegmentDescriptor* desc = reinterpret_cast<TaskStateSegmentDescriptor*>(mTableIndex);
	desc->LowerSegmentSize = limit & 0xFFFF;
	desc->LowerBaseAddress = baseAddress & 0xFFFF;
	desc->MiddleBaseAddress1 = (baseAddress >> 16) & 0xFF;
	desc->TypeAndFlags = lowerFlags;
	desc->MiddleSegmentSizeAndFlags = ((limit >> 16) & 0xFF) | upperFlags;
	desc->MiddleBaseAddress2 = (baseAddress >> 24) & 0xFF;
	desc->UpperBaseAddress = (baseAddress >> 32);
	desc->Reserved = 0;
	
	mTableIndex += sizeof(TaskStateSegmentDescriptor);
}

void GDTBlockManager::AddTssSegment(
	uint16_t ioMapBaseAddress)
{
	TssSegment* segment = reinterpret_cast<TssSegment*>(mTableIndex);
	segment->Reserved1 = 0;
	segment->Reserved2 = 0;
	segment->IST[0] = 0x800000;
	segment->Reserved3 = 0;
	segment->Reserved4 = 0;
	segment->IOMapBaseAddress = ioMapBaseAddress;
	
	mTableIndex += sizeof(TssSegment);
}

void GDTBlockManager::AddIDTDescriptor(
	uint64_t handlerOffset,
	uint16_t segmentSelector,
	uint8_t ist,
	uint8_t flags)
{
	IDTTableDescriptor* desc = reinterpret_cast<IDTTableDescriptor*>(mTableIndex);
	desc->HandlerOffset1 = handlerOffset & 0xFFFF;
	desc->SegmentSelector = segmentSelector;
	desc->IST = ist & 0x3;
	desc->TypeAndFlags = flags;
	desc->HandlerOffset2 = (handlerOffset >> 16) & 0xFFFF;
	desc->HandlerOffset3 = (handlerOffset >> 32);
	desc->Reserved = 0;
	
	mTableIndex += sizeof(IDTTableDescriptor);
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