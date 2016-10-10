#include "randomid.h"
#include <iterator>
#include <algorithm>

std::string RandomId()
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ std::rand() % max_index ];
    };
    std::string str(10,0);
    std::generate_n( str.begin(), 10, randchar );
    return str;
}
