#ifndef COOKIEVISITOR_H
#define COOKIEVISITOR_H

#include "include/cef_client.h"
#include "log.h"
#include <functional>
#include "picojson.h"

class CookieVisitor : public CefCookieVisitor
{
    picojson::array cookies_json;

    static picojson::value SerializeTime(cef_time_t time);
    static cef_time_t DeserializeTime(picojson::value::object val);

    std::string UrlToVisit;

public:
    CookieVisitor();

    static picojson::value::object SerializeCookie(const CefCookie& cookie);
    static void DeserializeCookie(picojson::value::object& object,CefCookie& data);
    static CefCookie GetEmptyCookie();

    void ClearBuffer();
    void SetUrlToVisit(const std::string& UrlToVisit);
    std::string GetBuffer();
    virtual bool Visit(const CefCookie& cookie, int count, int total, bool& deleteCookie) OVERRIDE;
    std::vector<std::function<void()> > EventCookiesLoaded;
private:
    IMPLEMENT_REFCOUNTING(CookieVisitor);
};

#endif // COOKIEVISITOR_H
