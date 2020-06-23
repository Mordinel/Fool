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
    setExtension(outPath);
}

/**
 * frees memory and closes files.
 */
Fool::~Fool()
{
    if (this->inFile != NULL) {
        std::fclose(this->inFile);
    }

    if (this->outFile != NULL) {
        std::fclose(this->outFile);
    }

    if (this->magicTop != NULL) {
        std::free(this->magicTop);
    }

    if (this->magicBottom != NULL) {
        std::free(this->magicBottom);
    }

    if (this->extension != NULL){
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
bool Fool::openFileIfPossible(char* path, FILE* file)
{
    // if the file isn't null, close it and set it to NULL
    if (file != NULL) {
        std::fclose(file);
        file = NULL;
    }

    // if the file at path is there and readable, open it in read mode
    if(std::access(path, (F_OK|R_OK)) == -1) {
        file = NULL;
        return false;
    } else {
        file = std::fopen(path, "r");
        return true;
    }
}

/**
 * Allocates the memory needed for the magic bytes.
 */
void Fool::allocateMagicBytes(char* magicBytes, char* bytes)
{
    int bytesLen;

    if (magicBytes != NULL) {
        std::free(magicBytes);
        magicBytes = NULL;
    }

    bytesLen = std::strLen(bytes);
    magicBytes = (char*)malloc(sizeof(char) * bytesLen);
    std::strncpy(magicBytes, bytes, bytesLen);
}

/**
 * Loads magic bytes into the magicTop and magicBottom buffers based on the class field extension.
 */
bool Fool::loadMagicBytes()
{
    int i;
    bool ret = true;

    // if magicTop or magicBottom is not null, free it and set it to null;
    if (this->magicTop != NULL) {
        std::free(this->magicTop);
        this->magicTop = NULL:
    }
    if (this->magicBottom != NULL) {
        std::free(this->magicBottom);
        this->magicBottom = NULL;
    }

    // if extension isn't set, return false
    if (this->extension == NULL) {
        return false;
    }

    int extensionLen = std::strlen(this->extension);
    
    // convert the extension string to lowercase.
    char* extensionLower = (char*)malloc(sizeof(char) * extensionLen);
    for (i = 0; i < extensionLen; i++) {
        extensionLower[i] = std::tolower(this->extension[i]);
    }

    // allocate magic bytes based on the extension string.
    if (std::strncmp(extensionLower, "gif", 4)) {
        allocateMagicBytes(this->magicTop, GIF_BYTES);

    } else if (std::strncmp(extensionLower, "jpg", 4) ||
               std::strncmp(extensionLower, "jpe", 4) ||
               std::strncmp(extensionLower, "jpeg", 5)) {
        allocateMagicBytes(this->magicTop, JPG_BYTES);

    } else if (std::strncmp(extensionLower, "png", 4)) {
        allocateMagicBytes(this->magicTop, PNG_BYTES);
        allocateMagicBytes(this->magicBottom, PNG_TRAILER);

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
bool Fool::SetInFile(char* inPath)
{
    return openFileIfPossible(inPath, this->inFile);
}

/**
 * Setter for out file.
 * Return true if setExtension and openFileIfPossible succeed.
 */
bool Fool::SetOutFile(char* outPath)
{
    if (setExtension(outPath) &&
        openFileIfPossible(outPath, this->outFile)) {
        return true; 
    }

    return false;
}

/**
 * Attempts to write the new file with the chosen magic bytes.
 */
bool Fool::WriteFile()
{
    int i;
    int c;

    loadMagicBytes();

    // if the magic top bytes, infile or outfile are null, return false, file can't be written.
    if (this->magicTop == NULL ||
        this->inFile == NULL ||
        this->outFile == NULL) {
        return false;
    }

    // write the magic top bytes to the outfile.
    for (i = 0; (c = magicTop[i]) != '\0'; i++) {
        std::fputc(c, this->outFile);
    }

    // write the infile bytes to the outfile.
    while((c = std::fgetc(this->inFile)) != '\0') {
        std::fputc(c, this->outFile);
    }

    // if there is magic bottom bytes to be writ, write them to the outfile.
    if (magicBottom != NULL) {
        for (i = 0; (c = magicBottom[i]) != '\0'; i++) {
            std::fputc(c, this->outFile);
        }
    }
    
    return true;
}

