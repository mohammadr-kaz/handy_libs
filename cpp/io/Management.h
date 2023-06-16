#ifndef HL_MANAGEMENT_H
#define HL_MANAGEMENT_H

#include "iostream"
#include <memory>
#include <array>

namespace hl::io
{
    enum FileType
    {
        SCALAR,
        VECTOR,
        ARRAY,
        IMAGE
    };

    std::string getCmdOutput(const char*);
    std::string getLocalRoot();
    FileType whatIsFileType(std::string);
    void throwException(std::string, std::string);
}

#endif
