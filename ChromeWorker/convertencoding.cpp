#include "convertencoding.h"
#include <iconv.h>
#include <algorithm>
#include <iterator>

ConverterResult convert(const std::string& text, const std::string& encoding_in, const std::string& encoding_out)
{
    std::vector<char> vtext;
    std::copy( text.begin(), text.end(), std::back_inserter(vtext));

    ConverterResult Result = std::make_shared<ConverterResultClass>();
    Result->WasSuccess = false;

    const char * pscr = vtext.data();
    size_t lsrc = vtext.size();
    std::vector<char> sout;
    sout.resize(lsrc * 6);
    char * pdst = sout.data();
    char * pdst_copy = pdst;
    size_t ldst = sout.size();

    iconv_t conv = iconv_open(encoding_out.c_str(),encoding_in.c_str());
    if((size_t)conv == -1)
    {
        return Result;
    }
    while(true)
    {
        int res = iconv(conv, &pscr, &lsrc, &pdst, &ldst);

        //Failure
        if(res == -1)
        {
            Result->WasSuccess = false;
            break;
        }

        //Determine length
        int len_converted = pdst - pdst_copy;

        //Append total result
        Result->Result.append(std::string(sout.data(),len_converted));

        //Success
        Result->WasSuccess = true;
        break;
    }
    iconv_close(conv);


    return Result;
}

ConverterResult convert_to_utf8(const std::string& text, const std::string& encoding_in)
{
    if(encoding_in == "utf-8")
    {
        ConverterResult Result = std::make_shared<ConverterResultClass>();
        Result->WasSuccess = true;
        Result->Result = text;
        return Result;
    }

    return convert(text,encoding_in,"UTF-8");
}
