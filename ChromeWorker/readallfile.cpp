#include "readallfile.h"
#include <fstream>

std::vector<char> ReadAllBytes(const std::string& filename)
{
    std::ifstream ifs(filename.c_str(), std::ios::binary|std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();

    std::vector<char>  result(pos);

    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);

    return result;
}
