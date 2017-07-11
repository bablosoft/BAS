#include "fixpagecontent.h"
#include <algorithm>
#include <regex>
#include "split.h"
#include "convertencoding.h"
#include "trim.h"
#include "startwith.h"
#include "log.h"

FixPageContent::FixPageContent()
{

}

std::string FixPageContent::ExtractMime(const std::string& ContentTypeHeader)
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

std::string FixPageContent::ExtractCharset(const std::string& ContentTypeHeader)
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

bool FixPageContent::IsUtf8(const std::string& Charset)
{
    if(Charset.empty())
        return false;
    std::string CharsetCopy = Charset;
    std::transform(CharsetCopy.begin(), CharsetCopy.end(), CharsetCopy.begin(), ::tolower);

    return CharsetCopy == "utf-8";
}

bool FixPageContent::NeedToFix(const std::string& ContentTypeHeader, const std::string& Url)
{
    std::string Charset = ExtractCharset(ContentTypeHeader);
    std::string Mime = ExtractMime(ContentTypeHeader);

    //bool IsOk = IsUtf8(Charset) || Mime != "text/html" && Charset.empty();
    bool IsOk = Mime != "text/html" && (Charset.empty() || starts_with(Mime,"image") || starts_with(Mime,"audio") || starts_with(Mime,"video"));
    return !IsOk;
}


bool FixPageContent::FixManifest(const std::string& ContentTypeHeader, std::string& PageContent, const std::string& Url)
{
    if(ExtractMime(ContentTypeHeader) == "text/html")
    {
        static std::regex ManifestReplace("\\<html[^\\<]*manifest\\s*=\\s*[\\'\\\"]?([^\\'\\\"]*)[\\'\\\"]?");

        try
        {
            std::smatch Match;
            if(std::regex_search(PageContent,Match,ManifestReplace))
            {
                PageContent = std::regex_replace (PageContent,ManifestReplace,"");
                return true;
            }
        }catch(...)
        {
            WORKER_LOG(std::string("[") + Url + std::string("]") + "Error during fix manifest");
        }
    }
    return false;
}


bool FixPageContent::FixCharset(const std::string& ContentTypeHeader, std::string& PageContent, const std::string& Url)
{

    if(!NeedToFix(ContentTypeHeader,Url))
        return false;

    WORKER_LOG(std::string("[") + Url + std::string("]") + std::string("Url needs correction"));
    std::string Charset = ExtractCharset(ContentTypeHeader);
    std::string Mime = ExtractMime(ContentTypeHeader);

    //Define regexp
    static std::regex MetaRegexp1("\\<\\s*meta\\s+charset\\s*\\=\\s*[\\'\\\"]?([^\\'\\\"\\/]*)[\\'\\\"]?\\s*\\/?\\>");
    static std::regex MetaRegexp2("\\<\\s*meta\\s+http\\-equiv\\s*\\=\\s*[\\'\\\"]?[cC][oO][nN][tT][eE][nN][tT]\\-[tT][yY][pP][eE][\\'\\\"]?\\s*content\\s*\\=\\s*[\\'\\\"]([^\\'\\\"]*)[\\'\\\"]\\s*\\/?\\>");
    static std::regex MetaRegexp3("\\<\\s*meta\\s+content\\s*\\=\\s*[\\'\\\"]([^\\'\\\"]*)[\\'\\\"]\\s*http\\-equiv\\s*\\=\\s*[\\'\\\"]?[cC][oO][nN][tT][eE][nN][tT]\\-[tT][yY][pP][eE][\\'\\\"]?\\s*\\/?\\>");
    //static std::regex FormRegexp1("\\<\\s*[Ff][Oo][Rr][Mm]\\s+(\\w+\\=\\\")");
    //static std::regex FormRegexp2("\\<\\s*[Ff][Oo][Rr][Mm]\\s+(\\w+\\=\\\\\\\")");
    static std::regex FormRegexp3("\\<\\s*[Ff][Oo][Rr][Mm]\\s+");
    static std::regex CSPRegexp("[cC][oO][nN][tT][eE][nN][tT]\\-[sS][eE][cC][uU][rR][iI][tT][yY]\\-[pP][oO][lL][iI][cC][yY]");
    static std::regex IntegrityRegexp("integrity\\s*\\=\\s*[\\'\\\"]?([^\\'\\\"\\/]*)[\\'\\\"]?");

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
                     WORKER_LOG(std::string("[") + Url + std::string("]") + std::string("Found charset by meta #1 ") + Charset);
                }
            }catch(...)
            {
                WORKER_LOG(std::string("[") + Url + std::string("]") + "Error during searching for meta #1");
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
                     WORKER_LOG(std::string("[") + Url + std::string("]") + std::string("Found charset by meta #2 ") + Charset);
                }
            }catch(...)
            {
                WORKER_LOG(std::string("[") + Url + std::string("]") + "Error during searching for meta #2");
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
                     WORKER_LOG(std::string("[") + Url + std::string("]") + std::string("Found charset by meta #3 ") + Charset);
                }
            }catch(...)
            {
                WORKER_LOG(std::string("[") + Url + std::string("]") + "Error during searching for meta #3");
            }
        }
    }

    if(Charset.empty())
    {
        WORKER_LOG(std::string(std::string("[") + Url + std::string("]") + "Can't find charset, asume it is utf-8"));
        Charset = "utf-8";
    }

    if(IsUtf8(Charset))
    {
        WORKER_LOG(std::string(std::string("[") + Url + std::string("]") + "Charset is utf-8"));
        Charset = "utf-8";
    }


    WORKER_LOG(std::string("[") + Url + std::string("]") + std::string("Fixing content with encoding ") + Charset);
    ConverterResult Result = convert_to_utf8(PageContent,Charset);

    WORKER_LOG(std::string("[") + Url + std::string("]") + std::string("Fix result ") + std::to_string(Result->WasSuccess));
    if(Result->WasSuccess)
    {

        if(IsUtf8(Charset) && !Result->Result.empty())
        {
            std::string bom;
            bom.push_back(0xef);
            bom.push_back(0xbb);
            bom.push_back(0xbf);
            Result->Result = bom + Result->Result;

            WORKER_LOG(std::string(std::string("[") + Url + std::string("]") + "Append BOM"));
        }


        PageContent.assign(Result->Result);

        //ReplaceMime if needed
        if(Mime == "text/html")
        {
            WORKER_LOG(std::string("[") + Url + std::string("]") + std::string("Mime is text/html so replacing meta"));
            try{
                PageContent = std::regex_replace (PageContent,MetaRegexp1,"<meta charset='utf-8'/>");
            }catch(...)
            {
                WORKER_LOG(std::string(std::string("[") + Url + std::string("]") + "Error during meta replace #1"));
            }

            try{
                PageContent = std::regex_replace (PageContent,MetaRegexp2,"<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />");
            }catch(...)
            {
                WORKER_LOG(std::string(std::string("[") + Url + std::string("]") + "Error during meta replace #2"));
            }

            try{
                PageContent = std::regex_replace (PageContent,MetaRegexp3,"<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />");
            }catch(...)
            {
                WORKER_LOG(std::string(std::string("[") + Url + std::string("]") + "Error during meta replace #3"));
            }

            try{
                PageContent = std::regex_replace (PageContent,CSPRegexp,"");
            }catch(...)
            {
                WORKER_LOG(std::string(std::string("[") + Url + std::string("]") + "Error during csp replace"));
            }

            if(!Charset.empty() && !IsUtf8(Charset))
            {
                WORKER_LOG(std::string(std::string("[") + Url + std::string("]") + "Fix charset111" + PageContent));

                try{
                    //PageContent = std::regex_replace (PageContent,FormRegexp2,std::string("<form accept-charset=\\\"") + Charset + std::string("\\\" $1"));
                    //PageContent = std::regex_replace (PageContent,FormRegexp1,std::string("<form accept-charset=\"") + Charset + std::string("\" $1"));
                    PageContent = std::regex_replace (PageContent,FormRegexp3,std::string("<form accept-charset=\"") + Charset + std::string("\" "));
                }
                catch(...)
                {
                    WORKER_LOG(std::string(std::string("[") + Url + std::string("]") + "Error form accept charset replace"));
                }
            }

            try{
                PageContent = std::regex_replace (PageContent,IntegrityRegexp,"");
            }catch(...)
            {
                WORKER_LOG(std::string(std::string("[") + Url + std::string("]") + "Error during integrity replace"));
            }




        }
        return true;
    }
    return false;
}

