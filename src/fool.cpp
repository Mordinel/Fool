#include "fool.h"

bool fool::WriteFile(std::filesystem::path inPath, std::filesystem::path outPath) {
    std::ifstream inFile(inPath);
    std::string inFileData;

    if (inFile && std::filesystem::is_regular_file(inPath)) {
        inFileData = std::string(
                std::istreambuf_iterator<char>(inFile),
                std::istreambuf_iterator<char>());
    } else {
        std::cerr << "Could not open " << inPath.string() << "!" << std::endl;
        return false;
    }

    if (!outPath.has_extension()) {
        std::cerr << outPath.string() << " does not have an extension!" << std::endl;
        return false;
    }

    std::string extension(outPath.extension());

    std::string magicHead;
    std::string magicTail;

    if (extension == ".gif") {
        magicHead = GIF_HEAD;

    } else if (extension == ".jpg" ||
               extension == ".jpe" ||
               extension == ".jpeg") {
        magicHead = JPG_HEAD;

    } else if (extension == ".png") {
        magicHead = PNG_HEAD;
        magicTail = PNG_TAIL;

    } else {
        std::cerr << extension << " is not a supported format!" << std::endl;
        return false;
    }

    std::ofstream outFile(outPath);

    if (outFile) {
        outFile << magicHead << inFileData << magicTail;
    } else {
        std::cerr << "could not open " << outPath.string() << " to write!" << std::endl;
        return false;
    }

    return true;
}

