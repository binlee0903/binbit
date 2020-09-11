#ifndef _BUILD_IMAGE_H_
#define _BUILD_IMAGE_H_

#ifndef _STREAM_
#define _STREAM_

#include <iostream>
#include <fstream>

#endif

class Merger
{
public:
    Merger(char* image, char* bootLoaderFile, char* kernel32File, char* kernel64File);
    ~Merger();

    bool Build();

private:
    int UnifySector(std::fstream& file, int sectorSize);
    void WriteKernelInformation(unsigned short sectorCount, unsigned short kernelx86Count);
    int CopyFile(std::fstream& source, std::fstream& dest);

private:
    std::fstream mImage;
    std::fstream mBootLoaderFile;
    std::fstream mKernel32File;
    std::fstream mKernel64File;

    enum
    {
        SECTOR_SIZE = 512
    };

    int mSectorCount;
};

#endif