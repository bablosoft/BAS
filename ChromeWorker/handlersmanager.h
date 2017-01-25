#ifndef HANDLERSMANAGER_H
#define HANDLERSMANAGER_H

#include <vector>
#include <map>
#include <memory>
#include "include/cef_app.h"
#include "mainhandler.h"
#include "inspectresult.h"
#include "localstoragedata.h"

class MainHandler;

class HandlersManager
{
    struct HandlerUnitClass
    {
        CefRefPtr<MainHandler> Handler;
        CefRefPtr<CefBrowser> Browser;
        int BrowserId = -1;
        bool IsActive = true;
        bool DontUseAsActive = false;
        bool IsContextCreated = false;
        bool ForceShow = false;
    };
    using HandlerUnit = std::shared_ptr<HandlerUnitClass>;

    std::vector<HandlerUnit> HandlerUnits;
    HandlerUnit OriginalHandler;

    std::map<int,int> MapBrowserIdToTabNumber;

    /* Callbacks */
    void PopupCreated(CefRefPtr<MainHandler> new_handler,CefRefPtr<CefBrowser> new_browser);
    void PopupRemoved(int BrowserId);
    void SendTextResponce(const std::string& text, int BrowserId);
    void UrlLoaded(const std::string& url, int status, int BrowserId);
    void LoadSuccess(int BrowserId);
    void Paint(char * data, int width, int height, int BrowserId);
    void OldestRequestTimeChanged(int64 OldestTime, int BrowserId);


    int CurrentBrowserId = -1;
    int DevToolsBorwserId = -1;


    CefRefPtr<MainHandler> Handler;
    CefRefPtr<CefBrowser> Browser;

    std::function<void(const std::string&)> SendTextResponceCallback;
    std::function<void(const std::string&, int)> UrlLoadedCallback;
    std::function<void()> LoadSuccessCallback;
    std::function<void(char*,int,int)> PaintCallback;
    std::function<void(int64)> OldestRequestTimeChangedCallback;

    std::vector<int> NewContextCreatedIds;

    void UpdateCurrent();

    bool IsClosedCurrent = false;
    bool IsWaitForClosedCurrent = false;

    void UpdateMapBrowserIdToTabNumber();

public:
    void Reset();
    void Timer();
    MainHandler* GetHandler();
    CefBrowser* GetBrowser();
    int64 FindFrameId(const FrameInspectResult& Inspect);
    void NewContextCreated(int ContextId);
    void Init1(CefRefPtr<MainHandler> Handler,
               std::function<void(const std::string&)> SendTextResponceCallback,
               std::function<void(const std::string&, int)> UrlLoadedCallback,
               std::function<void()> LoadSuccessCallback,
               std::function<void(char*,int,int)> PaintCallback,
               std::function<void(int64)> OldestRequestTimeChangedCallback
               );
    void Init2(CefRefPtr<CefBrowser> Browser);

    std::vector<std::function<void()> > EventNeedToCloseDevTools;
    void SetDevToolsBorwserId(int DevToolsBorwserId);

    std::vector<std::string> GetAllUrls();
    bool CloseByIndex(int index);
    void SwitchByIndex(int index);
    bool CheckIsClosed();
    int FindTabIdByBrowserId(int BrowserId);
    void UpdateLocalStorageItem(const LocalStorageDataItem& item);
    void UpdateLocalStorageString(const std::string& data);

};

#endif // HANDLERSMANAGER_H
