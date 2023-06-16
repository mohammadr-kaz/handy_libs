#include "Management.h"

using namespace hl;

std::string io::getCmdOutput(const char* cmd) 
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) 
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) 
    {
        result += buffer.data();
    }
    return result;
}

std::string io::getLocalRoot() 
{
    std::string output = getCmdOutput("git rev-parse --show-toplevel");
    return output.substr(0, output.size()-1);
}

io::FileType io::whatIsFileType(std::string dir)
{
    std::string extension = dir.substr(dir.find_last_of(".") + 1);
    if (extension == "jpg")
        return FileType::IMAGE;
    else if (extension == "csv")
        return FileType::ARRAY;
}

void io::throwException(std::string lib, std::string message)
{
    throw std::invalid_argument(std::string("MIIOVE ERROR --- Library: ") + lib + "\n" + message);
}