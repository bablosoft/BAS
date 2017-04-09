#ifndef MAINHANDLER_H
#define MAINHANDLER_H

#include "include/cef_client.h"
#include "include/cef_urlrequest.h"
#include "browserdata.h"
#include <functional>
#include "curlresourcehandler.h"
#include <atomic>
#include "settings.h"
#include "log.h"
#include "refcountpublic.h"
#include "handlersmanager.h"
#include "postmanager.h"

class HandlersManager;

class MainHandler : public CefClient, public CefDownloadHandler, public CefDisplayHandler, public CefLifeSpanHandler, public CefLoadHandler, public CefRequestHandler, public CefDialogHandler, public CefKeyboardHandler, public CefRenderHandler, public CefJSDialogHandler
{
    bool NeedQuit;
    bool WaitForLoadEvent;
    bool IsPopup;
    CefRefPtr<CefBrowser> Browser;
    bool IsVisible;
    BrowserData * Data;
    PostManager * _PostManager;
    settings * Settings;

    int GetBrowserId();
    CefRefPtr<CefJSDialogCallback> ConfirmResult;
    long long ConfirmResultTime;
    bool ConfirmResultWait;
    HandlersManager *_HandlersManager = 0;

public:
    MainHandler();
    bool GetIsVisible();
    void SetData(BrowserData *Data);
    void SetPostManager(PostManager *_PostManager);
    void SetSettings(settings *Settings);
    void SetIsPopup();
    bool GetIsPopup();
    void SetHandlersManager(HandlersManager *_HandlersManager);


    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE;
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE;
    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE;
    virtual CefRefPtr<CefRequestHandler> GetRequestHandler() OVERRIDE;
    virtual CefRefPtr<CefDialogHandler> GetDialogHandler() OVERRIDE;
    virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() OVERRIDE;
    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE;
    virtual CefRefPtr<CefJSDialogHandler> GetJSDialogHandler() OVERRIDE;
    virtual CefRefPtr<CefDownloadHandler> GetDownloadHandler() OVERRIDE;

    //CefDownloadHandler
    virtual void OnBeforeDownload(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDownloadItem> download_item, const CefString& suggested_name, CefRefPtr<CefBeforeDownloadCallback> callback) OVERRIDE;
    virtual void OnDownloadUpdated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDownloadItem> download_item, CefRefPtr<CefDownloadItemCallback> callback) OVERRIDE;

    // CefJSDialogHandler methods:
    virtual bool OnJSDialog(CefRefPtr<CefBrowser> browser, const CefString& origin_url, JSDialogType dialog_type, const CefString& message_text, const CefString& default_prompt_text, CefRefPtr<CefJSDialogCallback> callback, bool& suppress_message) OVERRIDE;
    virtual bool OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser,const CefString& message_text, bool is_reload, CefRefPtr<CefJSDialogCallback> callback) OVERRIDE;


    // CefKeyboardHandler methods:
    virtual bool OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& event, CefEventHandle os_event) OVERRIDE;

    // CefDisplayHandler methods:
    virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) OVERRIDE;

    // CefLifeSpanHandler methods:
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name, CefLifeSpanHandler::WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, bool* no_javascript_access) OVERRIDE;

    // CefLoadHandler methods:
    virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) OVERRIDE;
    virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) OVERRIDE;
    //virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame) OVERRIDE;


    // CefRequestHandler methods:
    virtual ReturnValue OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefRequestCallback> callback) OVERRIDE;
    virtual void OnResourceLoadComplete(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response, CefRequestHandler::URLRequestStatus status, int64 received_content_length) OVERRIDE;
    virtual CefRefPtr<CefResourceHandler> GetResourceHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request) OVERRIDE;
    virtual bool GetAuthCredentials(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, bool isProxy, const CefString& host, int port, const CefString& realm, const CefString& scheme, CefRefPtr<CefAuthCallback> callback) OVERRIDE;
    virtual bool OnCertificateError(CefRefPtr<CefBrowser> browser,cef_errorcode_t cert_error,const CefString& request_url,CefRefPtr<CefSSLInfo> ssl_info,CefRefPtr<CefRequestCallback> callback) OVERRIDE;

    //CefDialogHandler
    virtual bool OnFileDialog(CefRefPtr<CefBrowser> browser, FileDialogMode mode, const CefString& title, const CefString& default_file_path, const std::vector<CefString>& accept_filters, int selected_accept_filter, CefRefPtr<CefFileDialogCallback> callback) OVERRIDE;

    //CefRenderHandler
    virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) OVERRIDE;
    virtual void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height) OVERRIDE;
    virtual void OnScrollOffsetChanged(CefRefPtr<CefBrowser> browser,double x,double y) OVERRIDE;
    virtual bool StartDragging(CefRefPtr<CefBrowser> browser,CefRefPtr<CefDragData> drag_data,DragOperationsMask allowed_ops,int x, int y) OVERRIDE;


    bool IsNeedQuit();
    void Hide();
    void Show();
    void Timer();
    void CloseLastBrowser();
    void CleanResourceHandlerList();
    int GetResourceListLength();

    //Events
    std::vector<std::function<void(const std::string&, int)> > EventSendTextResponce;
    std::vector<std::function<void(const std::string&, int, int)> > EventUrlLoaded;
    std::vector<std::function<void(int)> > EventLoadSuccess;
    std::vector<std::function<void(char*,int,int,int)> > EventPaint;
    std::vector<std::function<void(CefRefPtr<MainHandler>,CefRefPtr<CefBrowser>)> > EventPopupCreated;
    std::vector<std::function<void(int)> > EventPopupClosed;
    std::vector<std::function<void(int64,int)> > EventOldestRequestTimeChanged;
    std::vector<CefRefPtr<CurlResourceHandler> > EventOnTimerCurlResources;
    std::atomic_int CurlResourcesLength;

private:
    void SendTextResponce(const std::string&);

private:
    IMPLEMENT_REFCOUNTING_NONE();
};

#endif // MAINHANDLER_H
