#ifndef TRIM_H
#define TRIM_H

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

// trim from start
std::string &ltrim(std::string &s);

// trim from end
std::string &rtrim(std::string &s);

// trim from both ends
std::string &trim(std::string &s);

#endif // TRIM_H
