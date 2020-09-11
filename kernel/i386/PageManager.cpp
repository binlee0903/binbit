#include "./include/PageManager.h"

void PageManager::InitiallizePageTables()
{
    setEntryData(mPageMapLevel4, 0x101000, 0x00, PAGE_FLAG_DEFAULT, PAGE_FLAG_NONE);


    constexpr int MAX_ENTRY_COUNT = 512;

    for (int i = 1; i < MAX_ENTRY_COUNT; i++)
    {
        setEntryData(&mPageMapLevel4[i], 0, 0, 0, 0);
    }

    constexpr int MAX_PAGEDIRECTORY_POINTER_COUNT = 64;
    constexpr int ENTRY_SIZE = 4096;

    for (int i = 0; i < MAX_PAGEDIRECTORY_POINTER_COUNT; i++)
    {
        setEntryData(&mPageDirPointer[i], 0x102000 + (i * ENTRY_SIZE), 0x00, PAGE_FLAG_DEFAULT, PAGE_FLAG_NONE);
    }

    for (int i = MAX_PAGEDIRECTORY_POINTER_COUNT; i < MAX_ENTRY_COUNT; i++)
    {
        setEntryData(&mPageDirPointer[i], 0, 0, 0, 0);
    }

    constexpr int PAGE_DIR_TABLE_COUNT = 64;
    constexpr int PAGE_DEFAULT_SIZE = 0x200000;

    for (int i = 0, mappingAddress = 0; i < MAX_ENTRY_COUNT * PAGE_DIR_TABLE_COUNT; i++, mappingAddress += PAGE_DEFAULT_SIZE)
    {
        setEntryData(&mPageDir[i], mappingAddress, (i * (PAGE_DEFAULT_SIZE >> 20)) >> 12, PAGE_FLAG_DEFAULT | PAGE_FLAG_PS, PAGE_FLAG_NONE);
    }
}

void PageManager::setEntryData(PTENTRY* entry, unsigned int lowerBaseAddress, unsigned int upperBaseAddress, unsigned int lowerFlags, unsigned int upperFlags)
{
    entry->attributeAndLowerBaseAddress = lowerBaseAddress | lowerFlags;
    entry->upperBaseAddressAndEXB = (upperBaseAddress & 0xFF) | upperFlags;
}