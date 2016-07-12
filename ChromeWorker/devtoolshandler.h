#ifndef DEVTOOLSHANDLER_H
#define DEVTOOLSHANDLER_H
#include "include/cef_client.h"
#include "browserdata.h"
#include "handlersmanager.h"
#include "mainlayout.h"

class DevToolsHandler : public CefClient
{

    CefPoint Point;
    HandlersManager *_HandlersManager = 0;
    RECT rect;
    BrowserData *Data;
    MainLayout *Layout;

    bool OpenAfterClose;
    bool DoClose;

    int AfterCloseTimer;
    int DevToolsBrowserId;

public:
    DevToolsHandler();

    void SetData(BrowserData *Data);
    void SetLayout(MainLayout *Layout);
    void SetHandlersManager(HandlersManager *_HandlersManager);
    void OpenDevTools();
    void OpenDevTools(CefPoint Point);
    void CloseDevTools();
    void Timer();
private:
    IMPLEMENT_REFCOUNTING(DevToolsHandler);
};

#endif // DEVTOOLSHANDLER_H
