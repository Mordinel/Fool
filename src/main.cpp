#include <iostream>
#include <string>

#include "fool.h"

int main(int argc, char* argv[]) 
{
    int exitCode = 1;

    if (argc != 3) {
        std::cerr << "Usage:\n" << argv[0] << " <in file> <out file.extension>" << std::endl;
        return exitCode;
    }

    if (fool::WriteFile(argv[1], argv[2])) {
        exitCode = 0; // succeeded
    } else {
        exitCode = 1; // failed
    }

    return exitCode;
}
