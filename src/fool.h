#ifndef FOOL_H
#define FOOL_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <unistd.h>

#include "signatures.h"

class Fool {
private:
    FILE* inFile;
    FILE* outFile;
    char* magicTop;
    char* magicBottom;
    char* extension;

    bool openFileIfPossible(char* path, FILE* file);
    bool setExtension(char* str);
    void allocateMagicBytes(char* magicBytes, const char* bytes);
    bool loadMagicBytes();
public:
    Fool(char* inPath, char* outPath);
    ~Fool();
    bool SetInFile(char* inPath);
    bool SetOutFile(char* outPath);
    bool WriteFile();
};

#endif
