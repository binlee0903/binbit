#ifndef GDT_GUARD
#define GDT_GUARD

#include "types.h"

struct GDT
{
    WORD limit;
    QWORD baseAddress;
    
    // added for 16 byte align
    WORD padding;
    DWORD padding;
};

struct GDTEntryFor8Byte
{
    WORD lowLimit;
    WORD lowBaseAddress;
    
    
};

class GDTEntry
{
public:
    GDTEntry();
    ~GDTEntry() = default;
    
    

#endif