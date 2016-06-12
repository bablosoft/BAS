#ifndef FIXCONTENTCHARSET_H
#define FIXCONTENTCHARSET_H

#include <string>

class FixContentCharset
{
private:
    std::string ExtractCharset(const std::string& ContentTypeHeader);
    std::string ExtractMime(const std::string& ContentTypeHeader);
    bool IsUtf8(const std::string& Charset);
public:
    FixContentCharset();

    //false means, that content correction definitely will not need
    //true means, that content correction MAYBE will need
    //Url param is just for log
    bool NeedToFix(const std::string& ContentTypeHeader, const std::string& Url);

    //Result value indicates if PageContent changed.
    //Url param is just for log
    bool Fix(const std::string& ContentTypeHeader, std::string& PageContent, const std::string& Url);
};

#endif // FIXCONTENTCHARSET_H
