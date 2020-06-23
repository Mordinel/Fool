#include "fool.h"

Fool::Fool(char* inPath, char* outPath)
{
    this->inFile = NULL;
    this->outFile = NULL;
    this->magicTop = NULL;
    this->magicBottom = NULL;
    this->extension = NULL;

    setExtension(outPath);
}

/**
 * Sets the class field 'extension' to the file extension of the string passed in.
 * returns true if new extension is set.
 */
bool Fool::setExtension(char* str)
{
    int i;
    int extStart;
    int strLen;

    // if the extension isn't null, free the memory and set it to NULL
    if (this->extension != NULL) {
        std::free(this->extension);
        this->extension = NULL;
    }

    // get the starting index of the last '.' char in the string
    extStart = -1;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            extStart = i;
        }
    }

    // if there is no extension, return leaving extension = NULL
    if (extStart == -1) return false;

    strLen = std::strlen(str);
    this->extension = (char*)malloc(sizeof(char) * (strLen - extStart));

    for (i = 0; str[++extStart] != '\0'; i++) {
        this->extension[i] = str[extStart];
    }

    return true;
}
