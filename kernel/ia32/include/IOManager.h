#ifndef IO_MANAGER_GUARD
#define IO_MANAGER_GUARD

#include "stdint.h"

class IOManager
{
public:
    IOManager()=default;
    ~IOManager()=default;

    uint8_t ReadPort(uint16_t portNumber);
    void WritePort(uint16_t portNumber, uint8_t data);

private:
    
};

#endif //IO_MANAGER_GUARD