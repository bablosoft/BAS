#include "cookievisitor.h"
#include "converter.h"
#include "log.h"



CookieVisitor::CookieVisitor()
{

}

picojson::value CookieVisitor::SerializeTime(cef_time_t time)
{
    picojson::value::object res;

    res["year"] = picojson::value(std::to_string(time.year));
    res["month"] = picojson::value(std::to_string(time.month));
    res["day_of_week"] = picojson::value(std::to_string(time.day_of_week));
    res["day_of_month"] = picojson::value(std::to_string(time.day_of_month));
    res["hour"] = picojson::value(std::to_string(time.hour));
    res["minute"] = picojson::value(std::to_string(time.minute));
    res["second"] = picojson::value(std::to_string(time.second));
    res["millisecond"] = picojson::value(std::to_string(time.millisecond));

    return picojson::value(res);
}

cef_time_t CookieVisitor::DeserializeTime(picojson::value::object val)
{
    cef_time_t res;

    res.year = std::stoi(val["year"].get<std::string>());
    res.month = std::stoi(val["month"].get<std::string>());
    res.day_of_week = std::stoi(val["day_of_week"].get<std::string>());
    res.day_of_month = std::stoi(val["day_of_month"].get<std::string>());
    res.hour = std::stoi(val["hour"].get<std::string>());
    res.minute = std::stoi(val["minute"].get<std::string>());
    res.second = std::stoi(val["second"].get<std::string>());
    res.millisecond = std::stoi(val["millisecond"].get<std::string>());

    return res;
}

picojson::value::object CookieVisitor::SerializeCookie(const CefCookie& cookie)
{

    picojson::value::object cookie_json;
    try{

        std::wstring value(cookie.value.str,cookie.value.length);
        std::wstring key(cookie.name.str,cookie.name.length);
        std::wstring url(cookie.domain.str,cookie.domain.length);
        std::wstring path(cookie.path.str,cookie.path.length);

        cookie_json["value"] = picojson::value(ws2s(value));
        cookie_json["name"] = picojson::value(ws2s(key));
        cookie_json["domain"] = picojson::value(ws2s(url));
        cookie_json["path"] = picojson::value(ws2s(path));
        cookie_json["creation"] = picojson::value(SerializeTime(cookie.creation));
        cookie_json["expires"] = picojson::value(SerializeTime(cookie.expires));
        cookie_json["has_expires"] = picojson::value(std::to_string(cookie.has_expires));
        cookie_json["httponly"] = picojson::value(std::to_string(cookie.httponly));
        cookie_json["last_access"] = picojson::value(SerializeTime(cookie.last_access));
        cookie_json["secure"] = picojson::value(std::to_string(cookie.secure));
    }catch(...)
    {

    }
    return cookie_json;
}

void CookieVisitor::DeserializeCookie(picojson::value::object& object,CefCookie& data)
{
    try
    {
        std::wstring name = s2ws(object["name"].get<std::string>());
        std::wstring value = s2ws(object["value"].get<std::string>());
        std::wstring domain = s2ws(object["domain"].get<std::string>());
        std::wstring path = s2ws(object["path"].get<std::string>());

        cef_string_utf16_set(name.data(),name.size(),&data.name,true);
        cef_string_utf16_set(value.data(),value.size(),&data.value,true);
        cef_string_utf16_set(domain.data(),domain.size(),&data.domain,true);
        cef_string_utf16_set(path.data(),path.size(),&data.path,true);

        data.creation = DeserializeTime(object["creation"].get<picojson::value::object>());
        data.expires = DeserializeTime(object["expires"].get<picojson::value::object>());
        data.last_access = DeserializeTime(object["last_access"].get<picojson::value::object>());
        data.has_expires = std::stoi(object["has_expires"].get<std::string>());
        data.httponly = std::stoi(object["httponly"].get<std::string>());
        data.secure = std::stoi(object["secure"].get<std::string>());
    }catch(...)
    {

    }
}

CefCookie CookieVisitor::GetEmptyCookie()
{
    CefCookie res;
    std::string str =  "{\"creation\":{\"day_of_month\":\"1\",\"day_of_week\":\"0\",\"hour\":\"1\",\"millisecond\":\"1\",\"minute\":\"1\",\"month\":\"1\",\"second\":\"1\",\"year\":\"2010\"},\"domain\":\".basnotcorrecturl.com\",\"expires\":{\"day_of_month\":\"1\",\"day_of_week\":\"1\",\"hour\":\"1\",\"millisecond\":\"1\",\"minute\":\"1\",\"month\":\"1\",\"second\":\"1\",\"year\":\"2030\"},\"has_expires\":\"1\",\"httponly\":\"1\",\"last_access\":{\"day_of_month\":\"1\",\"day_of_week\":\"0\",\"hour\":\"1\",\"millisecond\":\"1\",\"minute\":\"1\",\"month\":\"1\",\"second\":\"1\",\"year\":\"2011\"},\"name\":\"basnone\",\"path\":\"\/\",\"secure\":\"0\",\"value\":\"basnone\"}";
    picojson::value v;
    picojson::parse(v, str);
    DeserializeCookie(v.get<picojson::value::object>(),res);
    return res;
}

void CookieVisitor::SetUrlToVisit(const std::string& UrlToVisit)
{
    this->UrlToVisit = UrlToVisit;
}

bool CookieVisitor::Visit(const CefCookie& cookie, int count, int total, bool& deleteCookie)
{
    deleteCookie = false;

    std::wstring name(cookie.value.str,cookie.value.length);

    if(ws2s(name) != std::string("basnone"))
    {
        bool DoPush = true;
        if(!UrlToVisit.empty())
        {
            std::wstring domain(cookie.domain.str,cookie.domain.length);
            std::string domain_string = ws2s(domain);
            if(!domain_string.empty())
            {
                if(domain_string[0] == '.')
                    domain_string.erase(domain_string.begin());

                std::size_t pos = UrlToVisit.find(domain_string);
                if(pos == std::string::npos)
                {
                    DoPush = false;
                }
            }
        }
        if(DoPush)
            cookies_json.push_back(picojson::value(SerializeCookie(cookie)));
    }

    if(count >= total - 1)
    {
        for(auto f:EventCookiesLoaded)
            f();
    }
    return true;
}

void CookieVisitor::ClearBuffer()
{
    cookies_json.clear();
}

std::string CookieVisitor::GetBuffer()
{
    return picojson::value(cookies_json).serialize();
}
