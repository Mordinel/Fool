#include "fool.h"

/**
 * Sets all class fields to the default values.
 */
Fool::Fool(char* inPath, char* outPath)
{
    this->inFile = NULL;
    this->outFile = NULL;
    this->magicTop = NULL;
    this->magicBottom = NULL;
    this->extension = NULL;

    SetInFile(inPath);
    SetOutFile(outPath);
}

/**
 * frees memory and closes files.
 */
Fool::~Fool()
{
    if (this->inFile != 0) {
        std::fclose(this->inFile);
    }

    if (this->outFile != 0) {
        std::fclose(this->outFile);
    }

    if (this->magicTop != 0) {
        std::free(this->magicTop);
    }

    if (this->magicBottom != 0) {
        std::free(this->magicBottom);
    }

    if (this->extension != 0){
        std::free(this->extension);
    }
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
    if (this->extension != 0) {
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

    // allocate new memory for the extension string
    strLen = std::strlen(str);
    this->extension = (char*)malloc(sizeof(char) * (strLen - extStart));

    for (i = 0; str[++extStart] != '\0'; i++) {
        this->extension[i] = str[extStart];
    }

    return true;
}

/**
 * Opens file at path if possible and returns true if file opened successfully.
 */
FILE* Fool::openFileIfPossible(char* path, const char* mode)
{
    if (mode[0] == 'r') {
        return openFileInReadModeIfPossible(path);
    }

    return openFileInWriteModeIfPossible(path);
}

/**
 * Attempts to open the file at path in read mode, returns true if success.
 */
FILE* Fool::openFileInReadModeIfPossible(char* path)
{
    FILE* file;

    if (access(path, R_OK) == 0) {
        file = std::fopen(path, "r");
    } else {
        file = NULL;
    }

    return file;
}

/**
 * Attempts to open the file at path in write mode, returns true if success.
 */
FILE* Fool::openFileInWriteModeIfPossible(char* path)
{
    return std::fopen(path, "w");
}

/**
 * Allocates the memory needed for the magic bytes.
 */
char* Fool::allocateMagicBytes(const char* bytes)
{
    int bytesLen = std::strlen(bytes);
    char* magicBytes = (char*)malloc(sizeof(char) * bytesLen);
    std::strncpy(magicBytes, bytes, bytesLen);

    return magicBytes;
}

/**
 * Loads magic bytes into the magicTop and magicBottom buffers based on the class field extension.
 */
bool Fool::loadMagicBytes()
{
    int i;
    bool ret = true;

    // if magicTop or magicBottom is not null, free it and set it to null;
    if (this->magicTop != 0) {
        std::free(this->magicTop);
        this->magicTop = NULL;
    }
    if (this->magicBottom != 0) {
        std::free(this->magicBottom);
        this->magicBottom = NULL;
    }

    // if extension isn't set, return false
    if (this->extension == 0) {
        return false;
    }

    int extensionLen = std::strlen(this->extension);

    // convert the extension string to lowercase.
    char* extensionLower = (char*)malloc(sizeof(char) * extensionLen);
    for (i = 0; i < extensionLen; i++) {
        extensionLower[i] = std::tolower(this->extension[i]);
    }

    // allocate magic bytes based on the extension string.
    if (std::strncmp(extensionLower, "gif", 4) == 0) {
        this->magicTop = allocateMagicBytes(GIF_BYTES);

    } else if (std::strncmp(extensionLower, "jpg", 4) == 0 ||
               std::strncmp(extensionLower, "jpe", 4) == 0 ||
               std::strncmp(extensionLower, "jpeg", 5) == 0) {
        this->magicTop = allocateMagicBytes(JPG_BYTES);

    } else if (std::strncmp(extensionLower, "png", 4) == 0) {
        this->magicTop = allocateMagicBytes(PNG_BYTES);
        this->magicBottom = allocateMagicBytes(PNG_TRAILER);

    } else {
        ret = false;
    }

    std::free(extensionLower);

    return ret;
}

/**
 * Setter for in file
 * Returns the return value of the openFileIfPossible function.
 */
void Fool::SetInFile(char* inPath)
{
    if (this->inFile != 0) {
        std::fclose(this->inFile);
        this->inFile = NULL;
    }

    this->inFile = openFileIfPossible(inPath, "r");
}

/**
 * Setter for out file.
 * Return true if setExtension and openFileIfPossible succeed.
 */
void Fool::SetOutFile(char* outPath)
{
    if (this->outFile != 0) {
        std::fclose(this->outFile);
        this->outFile = NULL;
    }

    this->outFile = openFileIfPossible(outPath, "w");
    setExtension(outPath);
}

/**
 * Attempts to write the new file with the chosen magic bytes.
 */
bool Fool::WriteFile()
{
    int i;
    int c;

    if (!loadMagicBytes()) return false;

    // if the magic top bytes, infile or outfile are null, return false, file can't be written.
    if (this->magicTop == 0 ||
        this->inFile == 0 ||
        this->outFile == 0) {
        return false;
    }

    // write the magic top bytes to the outfile.
    for (i = 0; (c = magicTop[i]) != '\0'; i++) {
        std::fputc(c, this->outFile);
    }

    // write the infile bytes to the outfile.
    while((c = std::fgetc(this->inFile)) != EOF) {
        std::fputc(c, this->outFile);
    }

    // if there is magic bottom bytes to be writ, write them to the outfile.
    if (magicBottom != 0) {
        for (i = 0; (c = magicBottom[i]) != '\0'; i++) {
            std::fputc(c, this->outFile);
        }
    }
    
    return true;
}

