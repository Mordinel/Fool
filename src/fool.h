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

    FILE* openFileIfPossible(char* path, const char* mode);
    FILE* openFileInReadModeIfPossible(char* path);
    FILE* openFileInWriteModeIfPossible(char* path);
    char* allocateMagicBytes(const char* bytes);
    bool setExtension(char* str);
    bool loadMagicBytes();
public:
    Fool(char* inPath, char* outPath);
    ~Fool();
    void SetInFile(char* inPath);
    void SetOutFile(char* outPath);
    bool WriteFile();
};

#endif
