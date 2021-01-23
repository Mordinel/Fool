#ifndef FOOL_H
#define FOOL_H

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

#include "signatures.h"

namespace fool {
    bool WriteFile(std::filesystem::path inPath, std::filesystem::path outPath);
};

#endif
