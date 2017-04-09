#include "mainhandler.h"
#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "match.h"
#include "multithreading.h"
#include "replaceall.h"
#include "startwith.h"
#include "randomid.h"
#include "startwith.h"
#include "picojson.h"
#include "browsereventsemulator.h"
#include <chrono>

using namespace std::placeholders;
using namespace std::chrono;

MainHandler::MainHandler()
{
    WORKER_LOG(std::string("MainHandlerCreaate<<") + std::to_string((int)this));

    NeedQuit = false;
    WaitForLoadEvent = false;
    Browser = 0;
    IsVisible = false;
    IsPopup = false;
    ConfirmResultTime = -1;
    ConfirmResultWait = false;
}

void MainHandler::SetHandlersManager(HandlersManager *_HandlersManager)
{
    this->_HandlersManager = _HandlersManager;
}


int MainHandler::GetBrowserId()
{
    if(!Browser)
        return -1;
    return Browser->GetIdentifier();
}


void MainHandler::SetData(BrowserData *Data)
{
    this->Data = Data;
}

void MainHandler::SetPostManager(PostManager *_PostManager)
{
    this->_PostManager = _PostManager;
}

void MainHandler::SetSettings(settings *Settings)
{
    this->Settings = Settings;
}

void MainHandler::SetIsPopup()
{
    this->IsPopup = true;
}

bool MainHandler::GetIsPopup()
{
    return IsPopup;
}


CefRefPtr<CefDisplayHandler> MainHandler::GetDisplayHandler()
{
    return this;
}

CefRefPtr<CefLifeSpanHandler> MainHandler::GetLifeSpanHandler()
{
    return this;
}

CefRefPtr<CefLoadHandler> MainHandler::GetLoadHandler()
{
    return this;
}

CefRefPtr<CefRequestHandler> MainHandler::GetRequestHandler()
{
    return this;
}

CefRefPtr<CefDialogHandler> MainHandler::GetDialogHandler()
{
    return this;
}

CefRefPtr<CefKeyboardHandler> MainHandler::GetKeyboardHandler()
{
    return this;
}

CefRefPtr<CefRenderHandler> MainHandler::GetRenderHandler()
{
    return this;
}

CefRefPtr<CefJSDialogHandler> MainHandler::GetJSDialogHandler()
{
    return this;
}

CefRefPtr<CefDownloadHandler> MainHandler::GetDownloadHandler()
{
    return this;
}


void MainHandler::OnBeforeDownload(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDownloadItem> download_item, const CefString& suggested_name, CefRefPtr<CefBeforeDownloadCallback> callback)
{
    bool Accept = true;
    if(!Data->AllowDownloads)
    {
        Accept = false;
    }else
    {
        std::string url = download_item->GetOriginalUrl();
        {
            //Check if can download
            LOCK_BROWSER_DATA
            for(std::pair<bool, std::string> p:Data->_RequestMask)
            {
                if(match(p.second,url))
                {
                    Accept = p.first;
                }
            }
            if(Accept)
            {
                //errase all info about previous download
                {
                    auto i = Data->_LoadedUrls.begin();
                    while (i != Data->_LoadedUrls.end())
                    {
                        if(starts_with(i->first,"download://"))
                        {
                            i = Data->_LoadedUrls.erase(i);
                        }else
                        {
                            ++i;
                        }
                    }
                }
                {
                    auto i = Data->_CachedData.begin();
                    while (i != Data->_CachedData.end())
                    {
                        if(starts_with(i->first,"download://"))
                        {
                            i = Data->_CachedData.erase(i);
                        }else
                        {
                            ++i;
                        }
                    }
                }
            }
        }
    }
    if(Accept)
    {
        std::string file = RandomId() + ".file";
        WORKER_LOG(std::string("OnBeforeDownload<<") + file);
        callback->Continue(file,false);
    }else
    {
        //WORKER_LOG(std::string("OnBeforeDownloadFiltered<<") + url);
    }


}

void MainHandler::OnDownloadUpdated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDownloadItem> download_item, CefRefPtr<CefDownloadItemCallback> callback)
{
    if(download_item->IsComplete())
    {
        WORKER_LOG(std::string("OnBeforeDownloadFinished<<") + download_item->GetFullPath().ToString());
        //Place info about downloaded file to cache
        {
            LOCK_BROWSER_DATA
            {
                std::pair<std::string, int> p;
                p.first = std::string("download://") + download_item->GetOriginalUrl().ToString();
                p.second = 200;
                Data->_LoadedUrls.push_back(p);
            }
            {
                std::pair<std::string, std::shared_ptr<std::vector<char> > > p;
                std::string url = std::string("download://") + download_item->GetOriginalUrl().ToString();
                p.first = url;
                p.second = std::make_shared<std::vector<char> >();
                std::string path = download_item->GetFullPath().ToString();
                p.second->assign(path.begin(),path.end());
                Data->_CachedData.push_back(p);
            }
        }
    }

}

bool MainHandler::OnJSDialog(CefRefPtr<CefBrowser> browser, const CefString& origin_url, JSDialogType dialog_type, const CefString& message_text, const CefString& default_prompt_text, CefRefPtr<CefJSDialogCallback> callback, bool& suppress_message)
{
    switch(dialog_type)
    {
        case JSDIALOGTYPE_PROMPT:
        {
            std::string res;
            {
                LOCK_PROMPT
                res = Data->_PromptResult;
            }
            WORKER_LOG(std::string("Prompt<<") + res);
            suppress_message = false;
            callback->Continue(true,res);
            return true;

        }break;
        case JSDIALOGTYPE_CONFIRM:
        {
            std::string message = message_text.ToString();
            bool NeedToWait = false;
            if(starts_with(message,std::string("BrowserAutomationStudio_Sleep")) && !ConfirmResult.get() && !ConfirmResultWait)
            {
                ReplaceAllInPlace(message,std::string("BrowserAutomationStudio_Sleep"),std::string());

                try{
                    int inc = std::stoi(message);
                    ConfirmResultTime = duration_cast< milliseconds >( system_clock::now().time_since_epoch() ).count() + inc;
                    ConfirmResultWait = true;
                    NeedToWait = true;
                }catch(...)
                {

                }
            }

            if(NeedToWait)
            {
                WORKER_LOG("SLEEP_START");
                ConfirmResult = callback;
                return true;
            }else
            {
                suppress_message = false;
                callback->Continue(true,"");
                return true;
            }

        }break;
        case JSDIALOGTYPE_ALERT:
        {
            suppress_message = true;
            return false;

        }break;
    }
}

void MainHandler::Timer()
{
    if(ConfirmResult.get() && ConfirmResultWait && duration_cast< milliseconds >( system_clock::now().time_since_epoch() ).count() >= ConfirmResultTime)
    {
        WORKER_LOG("SLEEP_END");
        ConfirmResult->Continue(true,"");
        ConfirmResult = 0;
        ConfirmResultWait = false;
        ConfirmResultTime = -1;
    }

}

bool MainHandler::OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser,const CefString& message_text, bool is_reload, CefRefPtr<CefJSDialogCallback> callback)
{
    callback->Continue(true,"");
    return true;
}


bool MainHandler::OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& event, CefEventHandle os_event)
{
    /*WORKER_LOG(std::string("CefKeyEvent<<") + std::string("type<<") + std::to_string(event.type)
                + std::string("<<modifiers<<") + std::to_string(event.modifiers)
                + std::string("<<windows_key_code<<") + std::to_string(event.windows_key_code)
                + std::string("<<native_key_code<<") + std::to_string(event.native_key_code)
                + std::string("<<character<<") + std::to_string(event.character)
                + std::string("<<unmodified_character<<") + std::to_string(event.unmodified_character)
                + std::string("<<focus_on_editable_field<<") + std::to_string(event.focus_on_editable_field)
                + std::string("<<is_system_key<<") + std::to_string(event.is_system_key)
               );*/
    return false;
}

CefRefPtr<CefResourceHandler> MainHandler::GetResourceHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request)
{
    std::string url = request->GetURL().ToString();
    if(starts_with(url,"blob:"))
    {
        return 0;
    }

    if(starts_with(url,"chrome-extension:"))
    {
        return 0;
    }



    CurlResourceHandler* h = new CurlResourceHandler(Data,_PostManager);
    h->SetTabNumber(_HandlersManager->FindTabIdByBrowserId(browser->GetIdentifier()));
    h->SetForceUtf8(Settings->ForceUtf8());
    h->SetProxiesReconnect(Settings->ProxiesReconnect());

    EventOnTimerCurlResources.push_back(h);
    CurlResourcesLength = EventOnTimerCurlResources.size();
    return EventOnTimerCurlResources.at(EventOnTimerCurlResources.size() - 1);
}

int MainHandler::GetResourceListLength()
{
    return CurlResourcesLength;
}

void MainHandler::CleanResourceHandlerList()
{
    //Delete expired handlers and run timer on existing
    int64 OldestRequest = 0;
    int i = 0;
    for (std::vector<CefRefPtr<CurlResourceHandler> >::iterator it=EventOnTimerCurlResources.begin();it!=EventOnTimerCurlResources.end();)
    {
        bool CanDelete = it->get()->GetCanDelete();
        if(CanDelete)
        {
            it = EventOnTimerCurlResources.erase(it);
        }
        else
        {
            if(it->get()->GetStartTime() < OldestRequest || OldestRequest == 0)
                OldestRequest = it->get()->GetStartTime();
            it->get()->Timer();
            ++it;
        }
        i++;
     }
    CurlResourcesLength = EventOnTimerCurlResources.size();

    for(auto f:EventOldestRequestTimeChanged)
    {
        f(OldestRequest,GetBrowserId());
    }
}


bool MainHandler::GetAuthCredentials(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, bool isProxy, const CefString& host, int port, const CefString& realm, const CefString& scheme, CefRefPtr<CefAuthCallback> callback)
{
    WORKER_LOG(std::string("GetAuthCredentials<<"));
    return false;
}

bool MainHandler::OnCertificateError(CefRefPtr<CefBrowser> browser,cef_errorcode_t cert_error,const CefString& request_url,CefRefPtr<CefSSLInfo> ssl_info,CefRefPtr<CefRequestCallback> callback)
{
    WORKER_LOG(std::string("OnCertificateError<<") + request_url.ToString());

    callback->Continue(true);
    return true;
}


bool MainHandler::OnFileDialog(CefRefPtr<CefBrowser> browser, FileDialogMode mode, const CefString& title, const CefString& default_file_path, const std::vector<CefString>& accept_filters, int selected_accept_filter, CefRefPtr<CefFileDialogCallback> callback)
{
    std::vector<CefString> res;
    {
        LOCK_BROWSER_DATA
        if(Data->_OpenFileName.length() > 0)
        {
            if(Data->_OpenFileName[0] == '[')
            {
                try
                {
                    picojson::value v;

                    std::string err = picojson::parse(v, Data->_OpenFileName);
                    if(err.empty())
                    {
                        for(picojson::value c: v.get<picojson::value::array>())
                        {
                            res.push_back(c.get<std::string>());
                        }
                    }
                }catch(...){}
            }else
                res.push_back(Data->_OpenFileName);
        }
    }
    callback->Continue(0,res);
    return true;
}

void MainHandler::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
{
    WORKER_LOG("OnTitleChange");

    SetWindowText(Data->_MainWindowHandle, std::wstring(title).c_str());
}

void MainHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
    if(browser->IsPopup() && !IsPopup)
    {
        WORKER_LOG("OnAfterCreatedBad<<" + std::to_string((int)browser->GetHost()->GetClient().get()));
        browser->GetHost()->CloseBrowser(true);
    }
    WORKER_LOG("OnAfterCreated<<" + std::to_string(browser->IsPopup()));

    this->Browser = browser;

    if(IsPopup)
    {
        Browser->GetHost()->WasResized();
        auto EventPopupCreatedCopy = EventPopupCreated;
        for(auto f: EventPopupCreatedCopy)
            f(this,browser);
    }

    if(IsVisible)
        Show();
}

bool MainHandler::GetIsVisible()
{
    return IsVisible;
}

void MainHandler::Hide()
{
    IsVisible = false;
    //RECT rect;
    //GetWindowRect(Data->MainWindowHandle,&rect);
    ShowWindow(Data->_MainWindowHandle, SW_HIDE);
    //MoveWindow(Data->MainWindowHandle,3000,3000,rect.right-rect.left,rect.bottom-rect.top,true);
}

void MainHandler::Show()
{
    IsVisible = true;
    //RECT rect;
    //GetWindowRect(Data->MainWindowHandle,&rect);
    ShowWindow(Data->_MainWindowHandle, SW_SHOW);
    //MoveWindow(Data->MainWindowHandle,0,0,rect.right-rect.left,rect.bottom-rect.top,true);
    SetForegroundWindow(Data->_MainWindowHandle);
    if(Browser)
        Browser->GetHost()->Invalidate(PET_VIEW);
}

bool MainHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
    WORKER_LOG("DoClose");
    return false;
}

void MainHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
    WORKER_LOG("OnBeforeClose");


    if(IsPopup)
    {
        auto EventPopupClosedCopy = EventPopupClosed;
        for(auto f: EventPopupClosedCopy)
            f(GetBrowserId());
    }
    Browser = 0;
}

bool MainHandler::OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name, CefLifeSpanHandler::WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, bool* no_javascript_access)
{
    WORKER_LOG(std::string("OnBeforePopup<<") + target_url.ToString());


    bool Accept = true;
    if(!Data->AllowPopups)
    {
        Accept = false;
    }else
    {
        std::string url = target_url.ToString();
        {
            LOCK_BROWSER_DATA
            for(std::pair<bool, std::string> p:Data->_RequestMask)
            {
                if(match(p.second,url))
                {
                    Accept = p.first;
                }
            }
        }
    }

    if(Accept)
    {
        windowInfo.SetAsWindowless(0,true);
        settings.windowless_frame_rate = 5;
        MainHandler * h = new MainHandler();
        h->SetHandlersManager(_HandlersManager);
        h->SetSettings(Settings);
        h->SetData(Data);
        h->SetPostManager(_PostManager);
        h->SetIsPopup();
        h->EventPopupCreated = EventPopupCreated;
        client = h;
    }

    return !Accept;
}

CefRequestHandler::ReturnValue MainHandler::OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefRequestCallback> callback)
{
    bool Accept = true;
    std::string url = request->GetURL().ToString();
    {
        LOCK_BROWSER_DATA
        for(std::pair<bool, std::string> p:Data->_RequestMask)
        {
            if(match(p.second,url))
            {
                Accept = p.first;
            }
        }
    }
    if(!Accept || Data->IsReset)
    {
        return RV_CANCEL;
    }

    CefRequest::HeaderMap ReqestHeaders;
    request->GetHeaderMap(ReqestHeaders);

    /*{
        LOCK_BROWSER_DATA
        for(std::shared_ptr<std::map<std::string,std::string> > Map: Data->_Headers.MatchAll(frame->GetURL().ToString(),TabNumber))
        {
            for(const auto& Header: *Map)
            {

            }
        }
        for (auto h : Data->_Headers)
        {
            WORKER_LOG(std::string("AvailableHeader<<") + h.first);
            ReqestHeaders.erase(h.first);
            ReqestHeaders.insert(std::make_pair(h.first, h.second));
        }
    }*/

    if(request->GetMethod().ToString() == std::string("POST"))
    {
        CefRefPtr<CefPostData> post = request->GetPostData();
        if(!post.get())
        {
            post = CefPostData::Create();
            request->SetPostData(post);
        }
        if(post->GetElementCount() == 0)
        {
            CefRefPtr<CefPostDataElement> el = CefPostDataElement::Create();
            std::string d("none=");
            el->SetToBytes(d.size(),d.c_str());
            post->AddElement(el);
        }
    }

    request->SetHeaderMap(ReqestHeaders);
    return RV_CONTINUE;
}

void MainHandler::OnResourceLoadComplete(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response, CefRequestHandler::URLRequestStatus status, int64 received_content_length)
{
    for(auto f:EventUrlLoaded)
        f(request->GetURL().ToString(),response->GetStatus(),GetBrowserId());
}




void MainHandler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl)
{
    WORKER_LOG(std::string("OnLoadError<<") + errorText.ToString() + std::string("<<") + failedUrl.ToString());

    /*if (errorCode == ERR_ABORTED)
      return;

    if(frame->IsMain())
    {
        SendTextResponce("<Messages><Load>1</Load></Messages>");
    }*/
}

void MainHandler::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode)
{
    WORKER_LOG(std::string("OnLoadEnd ") + std::to_string(frame->IsMain()) + std::string(" ") + frame->GetURL().ToString() + std::string(" ") + std::to_string(httpStatusCode) );
    if(frame->GetURL().ToString() == "about:blank")
    {
        Data->IsAboutBlankLoaded = true;
        return;
    }

    if(frame->IsMain())
    {
        if(httpStatusCode >= 200 && httpStatusCode < 300)
        {
           browser->GetMainFrame()->ExecuteJavaScript("if(document.body.style['background-color'].length === 0)document.body.style['background-color']='white';", browser->GetMainFrame()->GetURL(), 0);
           SendTextResponce("<Load>0</Load>");
           for(auto f:EventLoadSuccess)
               f(GetBrowserId());
        }else
        {
            {
                LOCK_BROWSER_DATA
                Data->_NextReferrer.clear();
            }
            SendTextResponce("<Load>1</Load>");
        }

    }
    WORKER_LOG("Loaded Data");
}

/*void MainHandler::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame)
{

}*/

void MainHandler::SendTextResponce(const std::string& text)
{
    for(auto f:EventSendTextResponce)
        f(text,GetBrowserId());
}

bool MainHandler::IsNeedQuit()
{
    return NeedQuit;
}

void MainHandler::CloseLastBrowser()
{
    //WORKER_LOG(std::string("CloseLastBrowser"));
    //if(!Browser)
        //return;
    //DestroyWindow(Browser->GetHost()->GetWindowHandle());
}

//CefRenderHandler
bool MainHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
    WORKER_LOG(std::string("GetViewRect<<") + std::to_string(Data->WidthBrowser) + std::string("<<") + std::to_string(Data->HeightBrowser));

    rect.x = 0;
    rect.y = 0;
    rect.width = Data->WidthBrowser;
    rect.height = Data->HeightBrowser;
    return true;
}
void MainHandler::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height)
{
    if(type == PET_VIEW)
    {
        for(auto f:EventPaint)
            f((char*)buffer, width, height, GetBrowserId());
    }
}

bool MainHandler::StartDragging(CefRefPtr<CefBrowser> browser,CefRefPtr<CefDragData> drag_data,DragOperationsMask allowed_ops,int x, int y)
{
    WORKER_LOG("StartDragging");
    Data->IsDrag = true;
    BrowserEventsEmulator::StartDrag(browser,drag_data,allowed_ops,x,y);
    return true;
}

void MainHandler::OnScrollOffsetChanged(CefRefPtr<CefBrowser> browser,double x,double y)
{
    WORKER_LOG(std::string("OFFSET<<") + std::to_string(x) + std::string("<<") + std::to_string(y));
    Data->ScrollX = x;
    Data->ScrollY = y;
}
