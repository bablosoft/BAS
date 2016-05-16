#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <string>
#include <map>

class Translate
{
    static std::string Language;
    static std::map<std::wstring,std::wstring> KeysRu;

public:
    static std::wstring Tr(std::wstring key);
    static void SetLanguage(std::string lang);
};

#endif // TRANSLATE_H
