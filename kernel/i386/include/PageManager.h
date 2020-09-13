#ifndef PAGE_MANAGER_GUARD
#define PAGE_MANAGER_GUARD

class PageManager
{
public:
    PageManager()=default;
    ~PageManager()=default;

    static void InitiallizePageTables();

    enum
    {
        PAGE_FLAG_NONE      = 0x00000000,
        PAGE_FLAG_P         = 0x00000001, // Present, Is valid Page?
        PAGE_FLAG_RW        = 0x00000002, // Read/Write
        PAGE_FLAG_US        = 0x00000004, // User/Supervisor, Page Privilege
        PAGE_FLAG_PWT       = 0x00000008, // Cache method
        PAGE_FLAG_PCD       = 0x00000010, // Cache switch
        PAGE_FLAG_A         = 0x00000020, // Is Accessed?
        PAGE_FLAG_D         = 0x00000040, // Is Writed?
        PAGE_FLAG_PS        = 0x00000080, // Page Size
        PAGE_FLAG_G         = 0x00000100, // Global
        PAGE_FLAG_PAT       = 0x00001000, // ??
        PAGE_FLAG_EXB       = 0x80000000, // Is Data area? or code?
        PAGE_FLAG_DEFAULT   = 0x00000001 | 0x00000002 // Presented, Read/Writeable
    };

private:
    #pragma pack(push, 1)

    struct Entry
    {
        unsigned int attributeAndLowerBaseAddress;
        unsigned int upperBaseAddressAndEXB;
    };

    #pragma pack(pop)

    static void setEntryData(Entry* entry, unsigned int lowerBaseAddress, unsigned int upperBaseAddress, unsigned int lowerFlags, unsigned int upperFlags);

    static Entry* const mPageMapLevel4;
    static Entry* const mPageDirPointer;
    static Entry* const mPageDir;
};

#endif