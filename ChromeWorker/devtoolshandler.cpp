#include "devtoolshandler.h"
#include "log.h"

DevToolsHandler::DevToolsHandler()
{
    OpenAfterClose = false;
    DoClose = false;
    DevToolsBrowserId = -1;
}

void DevToolsHandler::SetData(BrowserData *Data)
{
    this->Data = Data;
}

void DevToolsHandler::SetLayout(MainLayout *Layout)
{
    this->Layout = Layout;
}


void DevToolsHandler::SetHandlersManager(HandlersManager *_HandlersManager)
{
    this->_HandlersManager = _HandlersManager;
    this->_HandlersManager->EventNeedToCloseDevTools.push_back(std::bind(&DevToolsHandler::CloseDevTools,this));
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

            _HandlersManager->GetBrowser()->GetHost()->ShowDevTools(window_info, this, browser_settings, Point);

        }
    }

    if(DoClose)
    {
        AfterCloseTimer--;
        if(AfterCloseTimer<0)
        {
            DoClose = false;
            DevToolsBrowserId = -1;
            //OpenDevTools();
        }
    }
}

void DevToolsHandler::OpenDevTools()
{
    if(DevToolsBrowserId > 0)
        return;
    CefWindowInfo window_info;
    RECT rect = Layout->GetDevToolsRectangle(Data->WidthBrowser,Data->HeightBrowser,Data->WidthAll,Data->HeightAll);
    window_info.SetAsChild(Data->_MainWindowHandle, rect);
    CefBrowserSettings browser_settings;
    _HandlersManager->GetBrowser()->GetHost()->ShowDevTools(window_info, this, browser_settings, CefPoint(0,0));
    DevToolsBrowserId = _HandlersManager->GetBrowser()->GetIdentifier();
    //_HandlersManager->SetDevToolsBorwserId(DevToolsBrowserId);
}

void DevToolsHandler::OpenDevTools(CefPoint Point)
{
    if(DoClose)
        return;

    if(OpenAfterClose)
        return;

    RECT rect = Layout->GetDevToolsRectangle(Data->WidthBrowser,Data->HeightBrowser,Data->WidthAll,Data->HeightAll);
    HWND HDevTools = Layout->GetDevToolsHandle();
    if(HDevTools)
    {
        DestroyWindow(HDevTools);
    }

    OpenAfterClose = true;
    AfterCloseTimer = 10;

    this->Point = Point;
    this->rect = rect;

    DevToolsBrowserId = _HandlersManager->GetBrowser()->GetIdentifier();
    //_HandlersManager->SetDevToolsBorwserId(DevToolsBrowserId);
}

void DevToolsHandler::CloseDevTools()
{
    if(DoClose)
        return;

    if(OpenAfterClose)
        return;

    if(DevToolsBrowserId < 0)
        return;

    HWND HDevTools = Layout->GetDevToolsHandle();
    if(HDevTools)
    {
        DestroyWindow(HDevTools);
        DoClose = true;
        AfterCloseTimer = 10;
    }



}
