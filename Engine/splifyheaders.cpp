#include "splifyheaders.h"

#include <algorithm>
#include <fstream>
#include <streambuf>
#include <regex>

#include <mimetic/mimetic.h>




std::string SimplifyHeader(const std::string& Header)
{
    std::string Data = Header;
    std::smatch Match;
    std::regex Expression("\\=\\?[^\\?]+\\?([qQbB])\\?([^\\?]+)\\?\\=");

    while (std::regex_search (Data,Match,Expression))
    {
        std::string Encoding = Match[1];
        std::string EncodedData = Match[2];

        std::string DecodedData;
        if(Encoding == "q" || Encoding == "Q")
        {
            mimetic::code(EncodedData.begin(), EncodedData.end(), mimetic::QP::Decoder(), std::back_inserter(DecodedData) );
        }else if(Encoding == "b" || Encoding == "B")
        {
            mimetic::code(EncodedData.begin(), EncodedData.end(), mimetic::Base64::Decoder(), std::back_inserter(DecodedData) );
        }else
        {
            DecodedData = EncodedData;
        }


        Data = Data.replace(Match.position(),Match.length(),DecodedData);
    }
    return Data;
}

void SimplifyEmail(mimetic::MimeEntity* pMe, std::string& Data, bool WasFrom = false, bool WasTo = false, bool WasSubject = false)
{

    mimetic::Header& h = pMe->header();
    if(h.hasField("from") && !WasFrom)
    {
        Data += "From: ";

        {
            std::stringstream stream;
            stream<<h.from();
            Data += SimplifyHeader(stream.str());
        }
        Data += "\n";
        WasFrom = true;
    }
    if(h.hasField("to") && !WasTo)
    {
        Data += "To: ";
        {
            std::stringstream stream;
            stream<<h.to();
            Data += SimplifyHeader(stream.str());
        }
        Data += "\n";
        WasTo = true;
    }
    if(h.hasField("subject") && !WasSubject)
    {
        Data += "Subject: ";
        {
            std::stringstream stream;
            stream<<h.subject();
            Data += SimplifyHeader(stream.str());
        }
        Data += "\n";
        WasSubject = true;
    }

    if(pMe->body().length() > 0)
    {
        if(h.contentTransferEncoding().mechanism() == mimetic::ContentTransferEncoding::quoted_printable)
        {
            pMe->body().code(mimetic::QP::Decoder());
        }
        if(h.contentTransferEncoding().mechanism() == mimetic::ContentTransferEncoding::base64)
        {
            pMe->body().code(mimetic::Base64::Decoder());
        }
        Data += "\n";
        Data += "\n";
        {
            std::stringstream stream;
            stream<<pMe->body();
            Data += stream.str();
        }
    }

    mimetic::MimeEntityList::iterator mbit = pMe->body().parts().begin(),meit = pMe->body().parts().end();
    for(;mbit!=meit;++mbit)
        SimplifyEmail(*mbit, Data,  WasFrom, WasTo, WasSubject);
}


std::string SimplifyEmail(const std::string& Mail)
{
    std::string Result;

    try
    {
        std::stringstream s;
        s<<Mail;
        mimetic::MimeEntity me(s);

        SimplifyEmail(&me,Result);
    }catch(...)
    {
        return Mail;
    }

    return Result;
}
