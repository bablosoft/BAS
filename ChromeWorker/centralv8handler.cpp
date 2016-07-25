#include "centralv8handler.h"

CentralV8Handler::CentralV8Handler()
{
    url_changed = false;
    settings_changed = false;
    close = false;
}

bool CentralV8Handler::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if(name == std::string("BrowserAutomationStudio_OpenUrl"))
    {
        if (arguments.size() == 1 && arguments[0]->IsString())
        {
            std::lock_guard<std::mutex> lock(url_mut);
            url = arguments[0]->GetStringValue().ToString();
            url_changed = true;
        }
    }

    if(name == std::string("BrowserAutomationStudio_SetOptions"))
    {
        if (arguments.size() == 1 && arguments[0]->IsString())
        {
            std::lock_guard<std::mutex> lock(settings_mut);
            settings = arguments[0]->GetStringValue().ToString();
            settings_changed = true;
        }
    }

    if(name == std::string("BrowserAutomationStudio_Close"))
    {
        if (arguments.size() == 0)
        {
            std::lock_guard<std::mutex> lock(close_mut);
            close = true;
        }
    }
    return true;
}

std::pair<std::string, bool> CentralV8Handler::GetLoadUrl()
{
    std::lock_guard<std::mutex> lock(url_mut);

    std::pair<std::string, bool> r;
    r.first = url;
    r.second = url_changed;

    url_changed = false;

    url.clear();

    return r;
}

std::pair<std::string, bool> CentralV8Handler::GetSettings()
{
    std::lock_guard<std::mutex> lock(settings_mut);

    std::pair<std::string, bool> r;
    r.first = settings;
    r.second = settings_changed;

    settings_changed = false;

    settings.clear();

    return r;
}

bool CentralV8Handler::GetClose()
{
    std::lock_guard<std::mutex> lock(close_mut);

    bool r = close;
    close = false;


    return r;
}
