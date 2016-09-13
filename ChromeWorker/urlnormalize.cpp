#include "urlnormalize.h"
#include <network/uri.hpp>
#include "include/cef_parser.h"


std::string urlnormalize(const std::string& url)
{
    std::string Normalize1;
    try{
        network::uri Url(url);
        Normalize1 = Url.normalize(network::uri_comparison_level::syntax_based).string();
    }catch(...)
    {
        Normalize1 = url;
    }

    return CefURIDecode(Normalize1,true,UU_URL_SPECIAL_CHARS_EXCEPT_PATH_SEPARATORS).ToString();

}
