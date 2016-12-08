#ifndef JAVASCRIPTEXTENSIONS_H
#define JAVASCRIPTEXTENSIONS_H

#include <string>

class JavaScriptExtensions
{
public:
    JavaScriptExtensions();

    std::string GetReferrerExtension(const std::string& Referrer);
    std::string GetReferrerEmptyExtension();
    std::string GetUserAgentExtension(const std::string& UserAgent);
    std::string GetUserAgentEmptyExtension();
    std::string GetLanguage(const std::string& Language);
    std::string GetEmptyLanguage();

    std::string GetBasicExtension(bool IsRecord);
    std::string GetJqueryExtension();
};

#endif // JAVASCRIPTEXTENSIONS_H
