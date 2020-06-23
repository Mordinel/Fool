#ifndef FOOL_H
#define FOOL_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cunistd>
#include <cctype>

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
    void loadMagicBytes();
public:
    Fool(char* inPath, char* outPath);
    ~Fool();
    void SetInPath(char* inPath);
    void SetOutPath(char* outPath);
    void WriteFile();
};

#endif
