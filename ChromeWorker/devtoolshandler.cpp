#include "devtoolshandler.h"
#include "log.h"

DevToolsHandler::DevToolsHandler()
{
    OpenAfterClose = false;
}

void DevToolsHandler::SetData(BrowserData *Data)
{
    this->Data = Data;
}

void DevToolsHandler::Timer()
{
    if(OpenAfterClose)
    {
        AfterCloseTimer--;
        if(AfterCloseTimer<0)
        {
            OpenAfterClose = false;
            CefWindowInfo window_info;

            window_info.SetAsChild(Data->_MainWindowHandle, rect);
            CefBrowserSettings browser_settings;

            Browser->GetHost()->ShowDevTools(window_info, Handler, browser_settings, Point);
        }
    }
}

void DevToolsHandler::OpenNewDevTools(CefPoint Point,CefRefPtr<DevToolsHandler> Handler,CefRefPtr<CefBrowser> Browser, RECT rect)
{
    OpenAfterClose = true;
    AfterCloseTimer = 10;

    this->Point = Point;
    this->Handler = Handler;
    this->Browser = Browser;
    this->rect = rect;
}
