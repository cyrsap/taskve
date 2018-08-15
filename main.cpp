#include "Hasher.h"

#include <iostream>
#include <cstdio>

int main(int argc, char *argv[]) {

    size_t blockSize{1024 * 1024}; // default value
    std::string inputFileName{};
    std::string outputFileName{};
    // parsing arguments
    switch (argc) {
        case 4: {
            // read size;
            int sz {};
            if (sscanf(argv[3], "%d", &sz) != 1) {
                std::cerr << "Can't read block size in MB";
                return -1;
            }
            blockSize *= sz;
            // fallthrough
        }
        case 3:
            // read input file, read output file
            inputFileName = argv[1];
            outputFileName = argv[2];
            break;
        default:
            std::cerr << "Bad arguments" << std::endl;
            return -1;
    }

    Hasher hasher(inputFileName, outputFileName, blockSize);
    try {
        hasher.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }


    return 0;
}