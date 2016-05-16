#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <locale>
#include <codecvt>

std::string ws2s(const std::wstring& wstr);
std::wstring s2ws(const std::string& str);

#endif // CONVERTER_H

