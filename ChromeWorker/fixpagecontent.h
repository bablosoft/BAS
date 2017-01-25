#ifndef FIXPAGECONTENT_H
#define FIXPAGECONTENT_H

#include <string>

class FixPageContent
{
private:
    std::string ExtractCharset(const std::string& ContentTypeHeader);
    std::string ExtractMime(const std::string& ContentTypeHeader);
    bool IsUtf8(const std::string& Charset);
public:
    FixPageContent();

    //false means, that content correction definitely will not need
    //true means, that content correction MAYBE will need
    //Url param is just for log
    bool NeedToFix(const std::string& ContentTypeHeader, const std::string& Url);

    //Result value indicates if html changed.
    //Url param is just for log
    bool FixManifest(const std::string& ContentTypeHeader, std::string& PageContent, const std::string& Url);

    //Result value indicates if PageContent changed.
    //Url param is just for log
    bool FixCharset(const std::string& ContentTypeHeader, std::string& PageContent, const std::string& Url);
};

#endif // FIXPAGECONTENT_H
