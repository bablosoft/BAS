#ifndef MAINHANDLER_H
#define MAINHANDLER_H

#include "include/cef_client.h"
#include "include/cef_urlrequest.h"
#include "browserdata.h"
#include <functional>
#include "curlresourcehandler.h"
#include <atomic>


class MainHandler : public CefClient, public CefDisplayHandler, public CefLifeSpanHandler, public CefLoadHandler, public CefRequestHandler, public CefDialogHandler, public CefKeyboardHandler, public CefRenderHandler
{
    bool NeedQuit;
    bool WaitForLoadEvent;
    CefRefPtr<CefBrowser> Browser;
    bool IsVisible;
    BrowserData * Data;
public:
    MainHandler();
    bool GetIsVisible();
    void SetData(BrowserData *Data);
    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE;
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE;
    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE;
    virtual CefRefPtr<CefRequestHandler> GetRequestHandler() OVERRIDE;
    virtual CefRefPtr<CefDialogHandler> GetDialogHandler() OVERRIDE;
    virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() OVERRIDE;
    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE;

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
    virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame) OVERRIDE;


    // CefRequestHandler methods:
    virtual ReturnValue OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefRequestCallback> callback) OVERRIDE;
    virtual bool OnResourceResponse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response) OVERRIDE;
    virtual void OnResourceRedirect(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefString& new_url) OVERRIDE;
    virtual CefRefPtr<CefResourceHandler> GetResourceHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request) OVERRIDE;
    virtual bool GetAuthCredentials(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, bool isProxy, const CefString& host, int port, const CefString& realm, const CefString& scheme, CefRefPtr<CefAuthCallback> callback) OVERRIDE;
    virtual bool OnCertificateError(CefRefPtr<CefBrowser> browser,cef_errorcode_t cert_error,const CefString& request_url,CefRefPtr<CefSSLInfo> ssl_info,CefRefPtr<CefRequestCallback> callback) OVERRIDE;

    //CefDialogHandler
    virtual bool OnFileDialog(CefRefPtr<CefBrowser> browser, FileDialogMode mode, const CefString& title, const CefString& default_file_path, const std::vector<CefString>& accept_filters, int selected_accept_filter, CefRefPtr<CefFileDialogCallback> callback) OVERRIDE;

    //CefRenderHandler
    virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) OVERRIDE;
    virtual void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height) OVERRIDE;
    virtual void OnScrollOffsetChanged(CefRefPtr<CefBrowser> browser,double x,double y) OVERRIDE;

    bool IsNeedQuit();
    void Hide();
    void Show();
    void CloseLastBrowser();
    void CleanResourceHandlerList();
    int GetResourceListLength();

    //Events
    std::vector<std::function<void(const std::string&)> > EventSendTextResponce;
    std::vector<std::function<void(const std::string&, int)> > EventUrlLoaded;
    std::vector<std::function<void()> > EventClosedProgrammatically;
    std::vector<std::function<void()> > EventLoadSuccess;
    std::vector<std::function<void(char*,int,int)> > EventPaint;
    std::vector<CefRefPtr<CurlResourceHandler> > EventOnTimerCurlResources;
    std::atomic_int CurlResourcesLength;

private:
    void SendTextResponce(const std::string&);
    IMPLEMENT_REFCOUNTING(MainHandler);

};

#endif // MAINHANDLER_H
