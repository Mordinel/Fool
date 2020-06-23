#include <iostream>
#include "fool.h"

int main(int argc, char* argv[]) 
{
    Fool* fool;
    if (argc != 3) {
        fprintf(stderr, "Usage:\n\t%s <in file> <out file.extension>\n", argv[0]);
        return 1;
    }

    fool = new Fool(argv[1], argv[2]);

    if(!fool->WriteFile()) {
        fprintf(stderr, "Failed\n");
        return 1;
    }

    return 0;
}
