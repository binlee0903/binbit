#include "Merger.h"

using namespace std;

Merger::Merger(char* image, char* bootLoaderFile, char* kernel32File, char* kernel64File)
    : mImage(image, ios_base::binary | ios_base::in | ios_base::out | ios_base::trunc)
    , mBootLoaderFile(bootLoaderFile, ios_base::binary | ios_base::in)
    , mKernel32File(kernel32File, ios_base::binary | ios_base::in)
    , mKernel64File(kernel64File, ios_base::binary | ios_base::in)
    , mSectorCount(0)
{
    if (!mImage.is_open() && !mBootLoaderFile.is_open() && !mKernel32File.is_open() && !mKernel64File.is_open())
    {
        cerr << "[ERROR] Merger Constructor : Failed to open files" << endl;
        mSectorCount = -1;
    }
}

Merger::~Merger()
{
    mImage.close();
    mBootLoaderFile.close();
    mKernel32File.close();
    mKernel64File.close();
}

bool Merger::Build()
{
    if (mSectorCount == -1)
    {
        return false;
    }

    int sectorCount;
    int bootLoaderSize;

    cout << "[INFO] Merger::Build : Copy bootLoader file" << endl;

    bootLoaderSize = CopyFile(mBootLoaderFile, mImage);
    sectorCount = UnifySector(mImage, bootLoaderSize);

    int kernel32Size;
    int kernel32SectorCount;

    cout << "[INFO] Merger::Build : Copy 32 bit kernel file" << endl;

    kernel32Size = CopyFile(mKernel32File, mImage);
    kernel32SectorCount = UnifySector(mImage, kernel32Size);
    sectorCount += kernel32SectorCount;

    int kernel64Size;
    int kernel64SectorCount;

    cout << "[INFO] Merger::Build : Copy 64 bit kernel file" << endl;

    kernel64Size = CopyFile(mKernel64File, mImage);
    kernel64SectorCount = UnifySector(mImage, kernel64Size);
    sectorCount += kernel64SectorCount;

    cout << "[INFO] Merger::Build : Put information of kernel" << endl;

    WriteKernelInformation(sectorCount, kernel32SectorCount);

    return true;
}

int Merger::UnifySector(fstream& file, int sourceSize)
{
    int diffrence = sourceSize % SECTOR_SIZE;
    char temp = 0;

    if (diffrence != 0)
    {
        diffrence = SECTOR_SIZE - diffrence;

        for (int i = 0; i < diffrence; i++)
        {
            file.write(&temp, 1);
        }
    }

    return (sourceSize + diffrence) / SECTOR_SIZE;
}

void Merger::WriteKernelInformation(unsigned short sectorCount, unsigned short kernelx86Count)
{
    mImage.seekg(336);

    if (mImage.fail())
    {
        mImage.clear();

        cerr << "[ERROR] WriteKernelInformation : Merger.cpp(89)" << endl;
        return;
    }

    mImage.write(reinterpret_cast<char*>(&sectorCount), 2);

    mImage.write(reinterpret_cast<char*>(&kernelx86Count), 2);
}

int Merger::CopyFile(std::fstream& source, std::fstream& dest)
{
    int size = 0;
    char temp = 0;

    while (true)
    {
        source.read(&temp, 1);

        if (source.eof())
        {
            return size;
        }

        dest.write(&temp, 1);
        size += 1;
    }

    return size;
}