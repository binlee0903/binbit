#ifndef IO_MANAGER_GUARD
#define IO_MANAGER_GUARD

#include "stdint.h"

class IOManager
{
public:
    IOManager()=default;
    ~IOManager()=default;

    uint8_t ReadPort(uint8_t portNumber);
    void WritePort(uint8_t portNumber, uint16_t data);

private:
    
};

#endif //IO_MANAGER_GUARD