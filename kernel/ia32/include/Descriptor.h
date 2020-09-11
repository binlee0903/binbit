#ifndef DESCRIPTOR_GUARD
#define DESCRIPTOR_GUARD

#include "types.h"

class Descriptor
{
public:
    Descriptor();
    ~Descriptor() = default;
    
    void PushGDTEntry(GDTEntry* entry);
    
    
private:
    constexpr QWORD mGDTStartAddress = 0x142000;
};

#endif