#ifndef DEVTOOLSHANDLER_H
#define DEVTOOLSHANDLER_H
#include "include/cef_client.h"
#include "browserdata.h"

class DevToolsHandler : public CefClient
{

    CefPoint Point;
    CefRefPtr<DevToolsHandler> Handler;
    CefRefPtr<CefBrowser> Browser;
    RECT rect;
    BrowserData *Data;

    bool OpenAfterClose;
    int AfterCloseTimer;
public:
    DevToolsHandler();

    void SetData(BrowserData *Data);

    void OpenNewDevTools(CefPoint Point,CefRefPtr<DevToolsHandler> Handler,CefRefPtr<CefBrowser> Browser, RECT rect);
    void Timer();
private:
    IMPLEMENT_REFCOUNTING(DevToolsHandler);
};

#endif // DEVTOOLSHANDLER_H
