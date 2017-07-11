#include "variablesextractor.h"
#include "log.h"
#include <regex>
#include "picojson.h"

std::string extract_variables(const std::string& code)
{
    std::string res_string;
    try
    {
        std::regex pieces_regex("VAR_([A-Z0-9_]+)");
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
            picojson::value::object res;
            res["name"] = picojson::value(s);
            json_array.push_back(picojson::value(res));
        }

        res_string = picojson::value(json_array).serialize();
        WORKER_LOG(std::string("extract_variables<<") + res_string);
    }catch(...)
    {

    }
    return res_string;
}

std::string extract_global_variables(const std::string& code)
{
    std::string res_string;
    try
    {
        std::regex pieces_regex("PSet\\(\\s*\\\"basglobal\\\"\\s*\\,\\s*(\\\"[^\\\"]+\\\")");
        std::smatch pieces_match;
        std::string::const_iterator SearchStart( code.cbegin() );

        std::vector<std::string> result_array;
        while(std::regex_search(SearchStart, code.cend(), pieces_match, pieces_regex))
        {
            std::ssub_match sub_match = pieces_match[1];
            std::string piece = sub_match.str();
            picojson::value val;
            picojson::parse(val,piece);
            result_array.push_back(val.get<std::string>());
            SearchStart += pieces_match.position() + pieces_match.length();
        }

        std::sort(result_array.begin(),result_array.end());
        result_array.erase(std::unique(result_array.begin(), result_array.end()), result_array.end());

        picojson::array json_array;
        for(std::string s:result_array)
        {
            picojson::value::object res;
            res["name"] = picojson::value(s);
            json_array.push_back(picojson::value(res));
        }

        res_string = picojson::value(json_array).serialize();
        WORKER_LOG(std::string("extract_global_variables<<") + res_string);
    }catch(...)
    {

    }
    return res_string;
}

