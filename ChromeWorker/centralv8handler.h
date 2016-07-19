#ifndef CENTRALV8HANDLER_H
#define CENTRALV8HANDLER_H


#include "include/cef_app.h"
#include <functional>
#include <mutex>

class CentralV8Handler : public CefV8Handler
{
    std::mutex url_mut;
    std::string url;
    bool url_changed;

    std::mutex close_mut;
    bool close;

public:
    CentralV8Handler();
    virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) OVERRIDE;
    std::pair<std::string, bool> GetLoadUrl();
    bool GetClose();
private:
    IMPLEMENT_REFCOUNTING(CentralV8Handler);
};

#endif // CENTRALV8HANDLER_H
