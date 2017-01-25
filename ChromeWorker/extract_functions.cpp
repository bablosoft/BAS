#include "extract_functions.h"

#include "log.h"
#include <regex>
#include "picojson.h"

std::string extract_functions(const std::string& code)
{
    std::string res_string;
    try
    {
        std::regex pieces_regex("function ([^\\(]+)\\(\\)");
        std::smatch pieces_match;
        std::string::const_iterator SearchStart( code.cbegin() );

        std::vector<std::string> result_array;
        while(std::regex_search(SearchStart, code.cend(), pieces_match, pieces_regex))
        {
            std::ssub_match sub_match = pieces_match[1];
            std::string piece = sub_match.str();
            result_array.push_back(piece);
            SearchStart += pieces_match.position() + pieces_match.length();
        }

        std::sort(result_array.begin(),result_array.end());
        result_array.erase(std::unique(result_array.begin(), result_array.end()), result_array.end());

        picojson::array json_array;
        for(std::string s:result_array)
        {
            if(s!="OnApplicationStart")
            {
                picojson::value::object res;
                res["name"] = picojson::value(s);
                json_array.push_back(picojson::value(res));
            }
        }

        res_string = picojson::value(json_array).serialize();
        WORKER_LOG(std::string("extract_functions<<") + res_string);
    }catch(...)
    {

    }
    return res_string;
}
