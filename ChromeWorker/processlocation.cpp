#include "processlocation.h"
#include "split.h"
#include <network/uri.hpp>
#include <network/uri/uri_builder.hpp>

std::string ProcessLocation(const std::string& RedirectUrl,const std::string& OriginalUrl)
{
    if(RedirectUrl.empty())
        return OriginalUrl;
    std::string Result = RedirectUrl;
    try
    {
        bool IsGood = false;
        try{
            network::uri RedirectUrlParsed(RedirectUrl);
            IsGood = true;
        }catch(...)
        {

        }
        if(!IsGood)
        {
            /*
                Starts with //
            */
            if((RedirectUrl.length() > 1 && RedirectUrl[0] == '/' && RedirectUrl[1] == '/'))
            {
                network::uri OriginalUrlParsed(OriginalUrl);
                Result = OriginalUrlParsed.scheme().to_string() + ":" + RedirectUrl;
            }
            /*
                Starts with letter
            */
            else if(!RedirectUrl.empty() && RedirectUrl.at(0)!='/')
            {

                network::uri OriginalUrlParsed(OriginalUrl);
                network::uri_builder builder(OriginalUrlParsed);

                if(OriginalUrlParsed.has_fragment())
                {
                    builder.clear_fragment();
                }

                if(OriginalUrlParsed.has_query())
                {
                    builder.clear_query();
                }

                std::vector<std::string> split_path = split(OriginalUrlParsed.path().to_string(),'/');
                split_path.erase(std::remove(split_path.begin(), split_path.end(), ""), split_path.end());
                if(!split_path.empty() && !OriginalUrl.empty() && OriginalUrl[OriginalUrl.length() - 1] != '/')
                    split_path.pop_back();
                split_path.push_back(RedirectUrl);

                std::stringstream ss;
                for(size_t i = 0; i < split_path.size(); ++i)
                {
                  if(i != 0)
                    ss << "/";
                  ss << split_path[i];
                }
                std::string NewPath = ss.str();


                if(OriginalUrlParsed.has_path())
                {
                    builder.clear_path();
                }


                Result = builder.uri().string() + "/" + NewPath;
            }
            /*
                Starts with /
            */
            else
            {
                network::uri OriginalUrlParsed(OriginalUrl);
                network::uri_builder builder(OriginalUrlParsed);

                if(OriginalUrlParsed.has_fragment())
                {
                    builder.clear_fragment();
                }
                if(OriginalUrlParsed.has_path())
                {
                    builder.clear_path();
                }
                if(OriginalUrlParsed.has_query())
                {
                    builder.clear_query();
                }

                Result = builder.uri().string() + RedirectUrl;
            }

        }
    }catch(...)
    {
        Result = RedirectUrl;
    }
    return Result;
}
