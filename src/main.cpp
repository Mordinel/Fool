#include <iostream>
#include "fool.h"

int main(int argc, char* argv[]) 
{
    int exit_code = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage:\n%s <in file> <out file.extension>\n", argv[0]);
        return 1;
    }

    Fool fool(argv[1], argv[2]);

    if(!fool.WriteFile()) {
        fprintf(stderr, "Could not complete action. Fix your permissions or use a supported file extension.\n");
        std::remove(argv[2]);
        exit_code = 1;
    }

    return exit_code;
}
