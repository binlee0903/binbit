#include "Merger.h"

int main(int argc, char* argv[])
{
    if (argc < 5)
    {
        std::cerr << "[ERROR] main : More arguments require" << std::endl;
        return 0;
    }

    std::cout << "[INFO] main : Start make image" << std::endl;

    Merger merger(argv[1], argv[2], argv[3], argv[4]);
    merger.Build();

    return 0;
}