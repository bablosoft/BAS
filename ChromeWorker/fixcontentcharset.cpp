#include "fixcontentcharset.h"
#include <algorithm>
#include <regex>
#include "split.h"
#include "convertencoding.h"
#include "trim.h"
#include "log.h"

FixContentCharset::FixContentCharset()
{

}

std::string FixContentCharset::ExtractMime(const std::string& ContentTypeHeader)
{
    std::string res;
    std::vector<std::string> MimeTypeSplit = split(ContentTypeHeader,';');
    if(MimeTypeSplit.size() > 1)
        res = MimeTypeSplit[0];
    else
        res = ContentTypeHeader;

    std::transform(res.begin(), res.end(), res.begin(), ::tolower);
    return trim(res);
}

std::string FixContentCharset::ExtractCharset(const std::string& ContentTypeHeader)
{
    try
    {
        std::smatch Match;
        std::regex Regexp("[cC][hH][aA][rR][sS][eE][tT]\\s*\\=\\s*([a-zA-Z\\-0-9_]+)");
        std::regex_search(ContentTypeHeader,Match,Regexp);
        if(Match.empty())
        {
            return std::string();
        }else
            return Match[1];
    }catch(...)
    {

    }
    return std::string();
}

bool FixContentCharset::IsUtf8(const std::string& Charset)
{
    if(Charset.empty())
        return false;
    std::string CharsetCopy = Charset;
    std::transform(CharsetCopy.begin(), CharsetCopy.end(), CharsetCopy.begin(), ::tolower);

    return CharsetCopy == "utf-8";
}

bool FixContentCharset::NeedToFix(const std::string& ContentTypeHeader, const std::string& Url)
{
    std::string Charset = ExtractCharset(ContentTypeHeader);
    std::string Mime = ExtractMime(ContentTypeHeader);

    bool IsOk = IsUtf8(Charset) || Mime != "text/html" && Charset.empty();
    return !IsOk;
}

bool FixContentCharset::Fix(const std::string& ContentTypeHeader, std::string& PageContent, const std::string& Url)
{
    if(!NeedToFix(ContentTypeHeader,Url))
        return false;

    worker_log(std::string("[") + Url + std::string("]") + std::string("Url needs correction"));
    std::string Charset = ExtractCharset(ContentTypeHeader);
    std::string Mime = ExtractMime(ContentTypeHeader);

    //Define regexp
    static std::regex MetaRegexp1("\\<\\s*meta\\s+charset\\s*\\=\\s*[\\'\\\"]?([^\\'\\\"\\/]*)[\\'\\\"]?\\s*\\/?\\>");
    static std::regex MetaRegexp2("\\<\\s*meta\\s+http\\-equiv\\s*\\=\\s*[\\'\\\"]?[cC][oO][nN][tT][eE][nN][tT]\\-[tT][yY][pP][eE][\\'\\\"]?\\s*content\\s*\\=\\s*[\\'\\\"]([^\\'\\\"]*)[\\'\\\"]\\s*\\/?\\>");
    static std::regex MetaRegexp3("\\<\\s*meta\\s+content\\s*\\=\\s*[\\'\\\"]([^\\'\\\"]*)[\\'\\\"]\\s*http\\-equiv\\s*\\=\\s*[\\'\\\"]?[cC][oO][nN][tT][eE][nN][tT]\\-[tT][yY][pP][eE][\\'\\\"]?\\s*\\/?\\>");

    //Find charset by content if not present in header
    if(Mime == "text/html")
    {
        if(Charset.empty())
        {
            try
            {
                std::smatch Match;
                if(std::regex_search(PageContent,Match,MetaRegexp1))
                {
                     Charset = Match[1];
                     worker_log(std::string("[") + Url + std::string("]") + std::string("Found charset by meta #1 ") + Charset);
                }
            }catch(...)
            {
                worker_log(std::string("[") + Url + std::string("]") + "Error during searching for meta #1");
            }
        }

        if(Charset.empty())
        {
            try
            {
                std::smatch Match;
                if(std::regex_search(PageContent,Match,MetaRegexp2))
                {
                     Charset = ExtractCharset(Match[1]);
                     worker_log(std::string("[") + Url + std::string("]") + std::string("Found charset by meta #2 ") + Charset);
                }
            }catch(...)
            {
                worker_log(std::string("[") + Url + std::string("]") + "Error during searching for meta #2");
            }
        }

        if(Charset.empty())
        {
            try
            {
                std::smatch Match;
                if(std::regex_search(PageContent,Match,MetaRegexp3))
                {
                     Charset = ExtractCharset(Match[1]);
                     worker_log(std::string("[") + Url + std::string("]") + std::string("Found charset by meta #3 ") + Charset);
                }
            }catch(...)
            {
                worker_log(std::string("[") + Url + std::string("]") + "Error during searching for meta #3");
            }
        }
    }

    if(Charset.empty())
    {
        worker_log(std::string(std::string("[") + Url + std::string("]") + "Can't find charset, asume it is utf-8, do nothing"));
        return false;
    }

    if(IsUtf8(Charset))
    {
        worker_log(std::string(std::string("[") + Url + std::string("]") + "Charset is utf-8, do nothing"));
        return false;
    }


    worker_log(std::string("[") + Url + std::string("]") + std::string("Fixing content with encoding ") + Charset);
    ConverterResult Result = convert_to_utf8(PageContent,Charset);
    worker_log(std::string("[") + Url + std::string("]") + std::string("Fix result ") + std::to_string(Result->WasSuccess));
    if(Result->WasSuccess)
    {
        PageContent.assign(Result->Result);

        //ReplaceMime if needed
        if(Mime == "text/html")
        {
            worker_log(std::string("[") + Url + std::string("]") + std::string("Mime is text/html so replacing meta"));
            try{
                PageContent = std::regex_replace (PageContent,MetaRegexp1,"<meta charset='utf-8'/>");
            }catch(...)
            {
                worker_log(std::string(std::string("[") + Url + std::string("]") + "Error during meta replace #1"));
            }

            try{
                PageContent = std::regex_replace (PageContent,MetaRegexp2,"<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />");
            }catch(...)
            {
                worker_log(std::string(std::string("[") + Url + std::string("]") + "Error during meta replace #2"));
            }

            try{
                PageContent = std::regex_replace (PageContent,MetaRegexp3,"<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />");
            }catch(...)
            {
                worker_log(std::string(std::string("[") + Url + std::string("]") + "Error during meta replace #3"));
            }


        }
        return true;
    }
    return false;
}

