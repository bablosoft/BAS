#include "mainapp.h"
#include <string>
#include <thread>
#include "log.h"
#include "picojson.h"
#include "converter.h"
#include "match.h"
#include "base64.h"
#include "javascriptextensions.h"
#include "browsereventsemulator.h"
#include "include/base/cef_bind.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/cef_parser.h"
#include "include/wrapper/cef_helpers.h"
#include "xml_encoder.h"
#include "lodepng.h"
#include "multithreading.h"
#include "modulesdata.h"
#include "readallfile.h"
#include "toolboxpreprocessor.h"
#include "clipboard.h"
#include "urlnormalize.h"
#include "chromecommandlineparser.h"
#include "replaceall.h"
#include "split.h"

using namespace std::placeholders;
MainApp * App;

MainApp::MainApp()
{
    _HandlersManager = std::make_shared<HandlersManager>();
    IsLastCommandNull = true;
    TypeTextTaskIsActive = false;
    TypeTextIsFirstLetter = true;
    IsWaitingForLoad = false;
    ResourcesChanged = true;
    InspectFrameSearching = false;
    TypeTextLastTime = 0;
    LastMouseTrack = 0;
    ImageWidth = 0;
    ImageHeight = 0;
    ParentWidth = 0;
    ParentHeight = 0;
    App = this;
    IsMouseMoveSimulation = false;
    NeedRenderNextFrame = false;
    SkipBeforeRenderNextFrame = 0;
    Speed = 15.0f;
    RunElementCommandCallbackOnNextTimer = -1;
    TypeTextDelayCurrent = 0;

}

void MainApp::SetData(BrowserData *Data)
{
    this->Data = Data;
}

void MainApp::SetSettings(settings *Settings)
{
    this->Settings = Settings;
}

void MainApp::SetLayout(MainLayout *Layout)
{
    this->Layout = Layout;
}

BrowserData * MainApp::GetData()
{
    return Data;
}

std::vector<std::string> MainApp::GetAllPopupsUrls()
{
    return _HandlersManager->GetAllUrls();
}


CefRefPtr<CefBrowserProcessHandler> MainApp::GetBrowserProcessHandler()
{
    return this;
}

CefRefPtr<CefRenderProcessHandler> MainApp::GetRenderProcessHandler()
{
    return this;
}


void MainApp::OnContextInitialized()
{
    _HandlersManager->Init1(new MainHandler(),
                            std::bind(&MainApp::SendTextResponce,this,_1),
                            std::bind(&MainApp::UrlLoaded,this,_1,_2),
                            std::bind(&MainApp::LoadSuccessCallback,this),
                            std::bind(&MainApp::Paint,this,_1,_2,_3),
                            std::bind(&MainApp::OldestRequestTimeChanged,this,_1));

    _HandlersManager->GetHandler()->SetSettings(Settings);
    _HandlersManager->GetHandler()->SetData(Data);

    dhandler = new DevToolsHandler();
    dhandler->SetData(Data);
    dhandler->SetLayout(Layout);
    dhandler->SetHandlersManager(_HandlersManager.get());
    cookievisitor = new CookieVisitor();
}

void MainApp::OldestRequestTimeChanged(int64 OldestTime)
{
    Data->OldestRequestTime = OldestTime;
}

void MainApp::Paint(char * data, int width, int height)
{
    if(NeedRenderNextFrame && SkipBeforeRenderNextFrame <= 1)
    {
        NeedRenderNextFrame = false;
        SkipBeforeRenderNextFrame = 0;
        std::vector<unsigned char> out;
        std::vector<unsigned char> in;
        int w = 0;
        int h = 0;
        for(int j = 0;j<height;j++)
        {
            if(j>RenderY && j<RenderY + RenderHeight)
            {
                h++;
            }
            for(int i = 0;i<width;i++)
            {

                if(i>RenderX && i<RenderX + RenderWidth && j>RenderY && j<RenderY + RenderHeight)
                {
                    if(h==1)
                        w++;
                    in.push_back((unsigned char)data[i*4+j*width*4 + 2]);
                    in.push_back((unsigned char)data[i*4+j*width*4 + 1]);
                    in.push_back((unsigned char)data[i*4+j*width*4 + 0]);
                    in.push_back((unsigned char)data[i*4+j*width*4 + 3]);
                }
            }

        }


        lodepng::encode(out,(unsigned const char *)(in.data()),w,h);
        std::string base64 = base64_encode(out.data(),out.size());
        if(IsElementRender)
        {
            WORKER_LOG(std::string("Render result element <<") + base64);
            FinishedLastCommand(base64);
        }
        else
        {
            WORKER_LOG(std::string("Render result screen <<") + base64);

            xml_encode(base64);
            SendTextResponce(std::string("<Messages><Render>") + base64 + std::string("</Render></Messages>"));
        }
    }
    if(_HandlersManager->GetHandler()->GetIsVisible() || _HandlersManager->GetHandler()->GetIsPopup())
    {
        ImageData.assign(data, data + width * height * 4);
        ImageWidth = width;
        ImageHeight = height;
        InvalidateRect(Data->_MainWindowHandle,NULL,false);
    }
}

char* MainApp::GetImageData()
{
    return ImageData.data();
}

std::pair<int,int> MainApp::GetImageSize()
{
    std::pair<int,int> res;
    res.first = ImageWidth;
    res.second = ImageHeight;
    return res;
}


void MainApp::UrlLoaded(const std::string& url, int status)
{
    WORKER_LOG(std::string("UrlLoaded<<") + url + std::string("<<") + std::to_string(status));
    if(status == 0)
        return;

    LOCK_BROWSER_DATA

    auto new_end = std::remove_if(Data->_LoadedUrls.begin(), Data->_LoadedUrls.end(),
                                  [&url](const std::pair<std::string, int>& pair)
                                  { return url == pair.first; });

    Data->_LoadedUrls.erase(new_end, Data->_LoadedUrls.end());
    std::pair<std::string, int> pair;
    pair.first = url;
    pair.second = status;
    Data->_LoadedUrls.push_back(pair);
}

void MainApp::LoadCallback(const std::string& page)
{
    IsWaitingForLoad = true;
    if(!_HandlersManager->GetBrowser())
    {
        NextLoadPage = page;
        AfterReadyToCreateBrowser(true);
    }else
    {
        WORKER_LOG(std::string("LoadCallback use old ") + page);
        CefRefPtr< CefFrame > Frame = _HandlersManager->GetBrowser()->GetMainFrame();
        Frame->LoadURL(page);
    }
    SendTextResponce("<Messages><LoadedInstant></LoadedInstant></Messages>");


}

void MainApp::IsChangedCallback()
{
    if(BrowserScenario)
    {
        BrowserScenario->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_IsChanged()"),BrowserScenario->GetMainFrame()->GetURL(), 0);
    }
}

void MainApp::ResetCallback()
{
    WORKER_LOG("ResetCallback");
    Data->IsReset = true;
    _HandlersManager->Reset();

    if(_HandlersManager->GetBrowser())
    {
        Data->IsAboutBlankLoaded = false;
        CefRefPtr< CefFrame > Frame = _HandlersManager->GetBrowser()->GetMainFrame();
        Frame->LoadURL("about:blank");
    }
    else
    {
        Data->IsAboutBlankLoaded = true;
    }
}

void MainApp::ResetCallbackFinalize()
{
    //Delete cookies
    CefRefPtr<CefCookieManager> CookieManager = CefCookieManager::GetGlobalManager(NULL);
    CookieManager->DeleteCookies("","",0);

    {
        LOCK_BROWSER_DATA

        //Clear Cache
        Data->_CachedData.clear();
        Data->_RequestMask.clear();
        Data->_LoadedUrls.clear();
        Data->_CacheMask.clear();

        //Proxy
        Data->_Proxy.Clear();

        //Open file name
        Data->_OpenFileName.clear();

        //Startup script
        Data->_StartupScript.Clear();

        //Headers
        Data->_Headers.Clear();

        //Resolution
        Data->WidthBrowser = 1024;
        Data->HeightBrowser = 600;
    }

    {
        LOCK_DOMAIN_CLEAR
        Data->DomainClearData.clear();
        Data->NeedClear = true;
    }

    /*{
        LOCK_LOCAL_STORAGE
        Data->_LocalStorageData.Clear();
    }
    _HandlersManager->UpdateLocalStorageString("[]");*/


    {
        LOCK_GEOLOCATION
        Data->GeolocationSelected = false;
    }

    {
        LOCK_TIMEZONE
        Data->TimezoneSelected = false;
    }

    if(_HandlersManager->GetBrowser())
    {
        _HandlersManager->GetBrowser()->GetHost()->WasResized();
        _HandlersManager->GetBrowser()->GetHost()->Invalidate(PET_VIEW);
    }

    Layout->Update(Data->WidthBrowser,Data->HeightBrowser,Data->WidthAll,Data->HeightAll);
    Data->IsReset = false;

    SendTextResponce("<Messages><Reset/></Messages>");
}

void MainApp::SetOpenFileNameCallback(const std::string& value)
{
    {
        LOCK_BROWSER_DATA
        Data->_OpenFileName = value;
    }
    SendTextResponce("<Messages><SetOpenFileName>1</SetOpenFileName></Messages>");
}

void MainApp::SetStartupScriptCallback(const std::string& value,const std::string& target)
{
    {
        LOCK_BROWSER_DATA
        Data->_StartupScript.Set(value, target);
    }
    SendTextResponce("<Messages><SetStartupScript></SetStartupScript></Messages>");
}


void MainApp::SetPromptResultCallback(const std::string& value)
{
    {
        LOCK_PROMPT
        Data->_PromptResult = value;
    }
    SendTextResponce("<Messages><SetPromptResult>1</SetPromptResult></Messages>");
}

void MainApp::SetHttpAuthResultCallback(const std::string& login,const std::string& password)
{
    {
        LOCK_HTTP_AUTH
        Data->_HttpAuthLogin = login;
        Data->_HttpAuthPassword = password;
    }
    SendTextResponce("<Messages><SetHttpAuthResult>1</SetHttpAuthResult></Messages>");
}

void MainApp::GetCookiesForUrlCallback(const std::string& value)
{
    WORKER_LOG("GetCookiesForUrlCallback");
    std::string cookies;
    if(_HandlersManager->GetBrowser())
    {
        CefRefPtr<CefCookieManager> CookieManager = CefCookieManager::GetGlobalManager(NULL);
        CefCookie cookie = CookieVisitor::GetEmptyCookie();
        bool CookieSet = CookieManager->SetCookie("http://basnotcorrecturl.com",cookie,0);
        WORKER_LOG(std::string("Empty cookie set<<") + std::to_string(CookieSet));
        cookievisitor->ClearBuffer();
        cookievisitor->SetUrlToVisit(value);
        cookievisitor->EventCookiesLoaded.clear();
        cookievisitor->EventCookiesLoaded.push_back(std::bind(&MainApp::GetCookiesForUrlCompleteCallback,this));
        if(!CookieManager->VisitAllCookies(cookievisitor))
        {
            SendTextResponce(std::string("<Messages><GetCookiesForUrl>") + cookies + std::string("</GetCookiesForUrl></Messages>"));
            return;
        }
        return;
    }
    SendTextResponce(std::string("<Messages><GetCookiesForUrl>") + cookies + std::string("</GetCookiesForUrl></Messages>"));
}

void MainApp::GetCookiesForUrlCompleteCallback()
{
    WORKER_LOG("GetCookiesForUrlCompleteCallback");
    std::string cookies = cookievisitor->GetBuffer();
    xml_encode(cookies);
    SendTextResponce(std::string("<Messages><GetCookiesForUrl>") + cookies + std::string("</GetCookiesForUrl></Messages>"));
}

void MainApp::SaveCookiesCallback()
{
    WORKER_LOG("SaveCookiesCallback");
    std::string cookies;
    if(_HandlersManager->GetBrowser())
    {
        CefRefPtr<CefCookieManager> CookieManager = CefCookieManager::GetGlobalManager(NULL);
        CefCookie cookie = CookieVisitor::GetEmptyCookie();
        bool CookieSet = CookieManager->SetCookie("http://basnotcorrecturl.com",cookie,0);
        WORKER_LOG(std::string("Empty cookie set<<") + std::to_string(CookieSet));
        cookievisitor->ClearBuffer();
        cookievisitor->SetUrlToVisit("");
        cookievisitor->EventCookiesLoaded.clear();
        cookievisitor->EventCookiesLoaded.push_back(std::bind(&MainApp::SaveCookiesCompleteCallback,this));
        if(!CookieManager->VisitAllCookies(cookievisitor))
        {
            SendTextResponce(std::string("<Messages><SaveCookies>") + cookies + std::string("</SaveCookies></Messages>"));
        }
        return;
    }
    SendTextResponce(std::string("<Messages><SaveCookies>") + cookies + std::string("</SaveCookies></Messages>"));
}

void MainApp::SaveCookiesCompleteCallback()
{
    WORKER_LOG("SaveCookiesCompleteCallback");
    std::string cookies = cookievisitor->GetBuffer();
    xml_encode(cookies);
    SendTextResponce(std::string("<Messages><SaveCookies>") + cookies + std::string("</SaveCookies></Messages>"));
}

void MainApp::RestoreLocalStorageCallback(const std::string& value)
{
    /*{
        LOCK_LOCAL_STORAGE
        Data->_LocalStorageData.Parse(value);
    }
    _HandlersManager->UpdateLocalStorageString(value);*/
    SendTextResponce(std::string("<Messages><RestoreLocalStorage></RestoreLocalStorage></Messages>"));
}

void MainApp::RestoreCookiesCallback(const std::string& value)
{
    CefRefPtr<CefCookieManager> CookieManager = CefCookieManager::GetGlobalManager(NULL);
    CookieManager->DeleteCookies("","",0);
    picojson::value v;
    std::string err = picojson::parse(v, value);
    if(err.empty())
    {
        for(picojson::value c: v.get<picojson::value::array>())
        {
            picojson::value::object o = c.get<picojson::value::object>();
            std::string url = o["domain"].get<std::string>();
            CefCookie cookie;
            CookieVisitor::DeserializeCookie(o, cookie);

            WORKER_LOG(std::to_string(CookieManager->SetCookie("http://" + url,cookie,NULL)));
        }
    }

    SendTextResponce(std::string("<Messages><RestoreCookies></RestoreCookies></Messages>"));
}

void MainApp::ResizeCallback(int width, int height)
{
    if(_HandlersManager->GetBrowser())
    {
        _HandlersManager->GetBrowser()->GetHost()->WasResized();
        _HandlersManager->GetBrowser()->GetHost()->Invalidate(PET_VIEW);
    }
    SendTextResponce("<Messages><Resize></Resize></Messages>");
}

void MainApp::ForceUpdateWindowPositionWithParent()
{
   ParentWidth = 0;
   ParentHeight = 0;
   UpdateWindowPositionWithParent();
}

void MainApp::UpdateWindowPositionWithParent()
{

    if(Data->_ParentWindowHandle && Layout->IsMinimized)
    {
        RECT rc;
        GetClientRect(Data->_ParentWindowHandle, &rc);
        int ParentWidthPrev = ParentWidth;
        int ParentHeightPrev = ParentHeight;
        ParentWidth = rc.right - rc.left;
        ParentHeight = rc.bottom - rc.top;
        if(ParentWidthPrev != ParentWidth || ParentHeightPrev != ParentHeight)
        {
            MoveWindow(Data->_MainWindowHandle,0,0,ParentWidth,ParentHeight,true);
        }
    }
}

void MainApp::SetWindowCallback(const std::string& Window)
{
    WORKER_LOG(std::string("SetWindowCallback<<") + Window);
    Data->_ParentWindowHandle = (HWND)std::stoi(Window);
    Layout->MinimizeOrMaximize(Data->_MainWindowHandle,Data->_ParentWindowHandle);
    if(Settings->Maximized())
        Layout->MinimizeOrMaximize(Data->_MainWindowHandle,Data->_ParentWindowHandle);
    ForceUpdateWindowPositionWithParent();
}



void MainApp::LoadSuccessCallback()
{
    if(IsWaitingForLoad)
    {
        BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
        IsWaitingForLoad = false;
    }
}

void MainApp::MouseClickCallback(int x, int y)
{
    WORKER_LOG("MouseClickCallback");
    if(_HandlersManager->GetBrowser())
    {
        BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
        LastCommand.CommandName = "_mouseclick";
        LastCommand.CommandParam1 = std::to_string(x);
        LastCommand.CommandParam2 = std::to_string(y);
        IsLastCommandNull = false;
        _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_ScrollToCoordinates(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(")"),_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);
    }else
    {
        SendTextResponce("<Messages><MouseClick></MouseClick></Messages>");
    }
}

void MainApp::MouseClickUpCallback(int x, int y)
{
    WORKER_LOG("MouseClickUpCallback");
    if(_HandlersManager->GetBrowser())
    {
        BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
        LastCommand.CommandName = "_mouseclickup";
        LastCommand.CommandParam1 = std::to_string(x);
        LastCommand.CommandParam2 = std::to_string(y);
        IsLastCommandNull = false;
        _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_ScrollToCoordinates(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(")"),_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);
    }else
    {
        SendTextResponce("<Messages><MouseClickUp></MouseClickUp></Messages>");
    }
}


void MainApp::MouseClickDownCallback(int x, int y)
{
    WORKER_LOG("MouseClickDownCallback");
    if(_HandlersManager->GetBrowser())
    {
        BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
        LastCommand.CommandName = "_mouseclickdown";
        LastCommand.CommandParam1 = std::to_string(x);
        LastCommand.CommandParam2 = std::to_string(y);
        IsLastCommandNull = false;
        _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_ScrollToCoordinates(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(")"),_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);
    }else
    {
        SendTextResponce("<Messages><MouseClickDown></MouseClickDown></Messages>");
    }
}


void MainApp::PopupCloseCallback(int index)
{
    if(!_HandlersManager->CloseByIndex(index))
        SendTextResponce("<Messages><PopupClose></PopupClose></Messages>");
}

void MainApp::PopupSelectCallback(int index)
{
    _HandlersManager->SwitchByIndex(index);
    SendTextResponce("<Messages><PopupSelect></PopupSelect></Messages>");
}

void MainApp::MouseMoveCallback(int x, int y)
{
    WORKER_LOG(std::string("MouseMoveCallback<<") + std::to_string(x) + std::string("<<") + std::to_string(y));
    if(_HandlersManager->GetBrowser())
    {
        BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
        LastCommand.CommandName = "_mousemove";
        LastCommand.CommandParam1 = std::to_string(x);
        LastCommand.CommandParam2 = std::to_string(y);
        MouseStartX = Data->CursorX;
        MouseStartY = Data->CursorY;
        MouseEndX = x;
        MouseEndY = y;
        IsLastCommandNull = false;
        _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_ScrollToCoordinates(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(")"),_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);


    }else
    {
        SendTextResponce("<Messages><MouseMove></MouseMove></Messages>");
    }
}

void MainApp::ScrollCallback(int x, int y)
{
    WORKER_LOG(std::string("ScrollCallback<<x<<") + std::to_string(x) + std::string("<<y<<") + std::to_string(y));
    if(_HandlersManager->GetBrowser())
    {
        BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
        LastCommand.CommandName = "_scroll";
        LastCommand.CommandParam1 = std::to_string(x);
        LastCommand.CommandParam2 = std::to_string(y);
        IsLastCommandNull = false;
        _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_ScrollToCoordinates(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(")"),_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);
    }else
    {
        SendTextResponce("<Messages><Scroll></Scroll></Messages>");
    }
}

void MainApp::DebugVariablesResultCallback(const std::string & data)
{
    if(BrowserScenario)
        BrowserScenario->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_UpdateVariablesResult(") + picojson::value(data).serialize() + std::string(")"),BrowserScenario->GetMainFrame()->GetURL(), 0);

    SendTextResponce("<Messages><DebugVariablesResult></DebugVariablesResult></Messages>");
}

void MainApp::RenderCallback(int x, int y, int width, int height)
{
    WORKER_LOG(std::string("RenderCallback<<x<<") + std::to_string(x) + std::string("<<y<<") + std::to_string(y) + std::string("<<width<<") + std::to_string(width) + std::string("<<height<<") + std::to_string(height));
    if(_HandlersManager->GetBrowser())
    {
        BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
        LastCommand.CommandName = "_render";
        RenderX = x;
        RenderY = y;
        RenderWidth = width;
        RenderHeight = height;

        IsLastCommandNull = false;
        _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_ScrollToCoordinates(") + std::to_string(x + width/2) + std::string(",") + std::to_string(y + width/2) + std::string(")"),_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);
    }else
    {
        SendTextResponce("<Messages><Render></Render></Messages>");
    }
}


void MainApp::CreateTooboxBrowser()
{
    if(BrowserToolbox)
        return;

    if(!Data->IsRecord)
        return;
    thandler = new ToolboxHandler();

    CefWindowInfo window_info;

    RECT r =  Layout->GetToolboxRectangle(GetData()->WidthBrowser,GetData()->HeightBrowser,GetData()->WidthAll,GetData()->HeightAll);
    window_info.SetAsChild(Data->_MainWindowHandle,r);

    CefBrowserSettings browser_settings;
    CefRequestContextSettings settings;
    CefRefPtr<CefRequestContext> Context = CefRequestContext::CreateContext(settings,NULL);
    BrowserToolbox = CefBrowserHost::CreateBrowserSync(window_info, thandler, "about:blank", browser_settings, Context);
    std::string ToolboxScript = ReadAllString("html/toolbox/index.html");
    ToolboxPreprocess(Data->_ModulesData, ToolboxScript);
    BrowserToolbox->GetMainFrame()->LoadString(ToolboxScript, "file:///html/toolbox/index.html");

    Layout->ToolBoxHandle = BrowserToolbox->GetHost()->GetWindowHandle();
}

void MainApp::CreateScenarioBrowser()
{
    if(BrowserScenario)
        return;
    if(!Data->IsRecord)
        return;
    shandler = new ScenarioHandler();

    CefWindowInfo window_info;

    RECT r =  Layout->GetDevToolsRectangle(GetData()->WidthBrowser,GetData()->HeightBrowser,GetData()->WidthAll,GetData()->HeightAll);

    window_info.SetAsChild(Data->_MainWindowHandle,r);

    CefBrowserSettings browser_settings;
    CefRequestContextSettings settings;
    CefRefPtr<CefRequestContext> Context = CefRequestContext::CreateContext(settings,NULL);
    BrowserScenario = CefBrowserHost::CreateBrowserSync(window_info, shandler, "file:///html/scenario/index.html", browser_settings, Context);
    std::string ScenarioScript = ReadAllString("html/scenario/index.html");
    ScenarioPreprocess(Data->_ModulesData, ScenarioScript);
    BrowserScenario->GetMainFrame()->LoadString(ScenarioScript, "file:///html/scenario/index.html");

    Layout->ScenarioHandle = BrowserScenario->GetHost()->GetWindowHandle();

}

void MainApp::CreateCentralBrowser()
{
    if(BrowserCentral)
        return;
    if(!Data->IsRecord)
        return;
    chandler = new CentralHandler();

    CefWindowInfo window_info;

    RECT r =  Layout->GetCentralRectangle(GetData()->WidthBrowser,GetData()->HeightBrowser,GetData()->WidthAll,GetData()->HeightAll);

    window_info.SetAsChild(Data->_MainWindowHandle,r);

    CefBrowserSettings browser_settings;
    CefRequestContextSettings settings;
    CefRefPtr<CefRequestContext> Context = CefRequestContext::CreateContext(settings,NULL);
    std::string page = std::string("file:///html/central/index_") + Lang + std::string(".html");

    BrowserCentral = CefBrowserHost::CreateBrowserSync(window_info, chandler, page, browser_settings, Context);

    Layout->CentralHandle = BrowserCentral->GetHost()->GetWindowHandle();
    Layout->ShowCentralBrowser(false);

}

/*void PrintDictionary(CefRefPtr<CefDictionaryValue> Dictionary, int tab)
{
    CefDictionaryValue::KeyList Keys;
    Dictionary->GetKeys(Keys);
    std::string tab_string;
    for(int i = 0;i<tab;i++)
        tab_string += " ";
    for(auto s:Keys)
    {
        WORKER_LOG(tab_string + s.ToString()+ std::string("<<") + std::to_string(Dictionary->GetValue(s)->GetType()));
        switch(Dictionary->GetValue(s)->GetType())
        {
            case VTYPE_BOOL:
                WORKER_LOG(tab_string + std::string("   ") + std::to_string(Dictionary->GetValue(s)->GetBool()));break;
            case VTYPE_INT:
                WORKER_LOG(tab_string + std::string("   ") + std::to_string(Dictionary->GetValue(s)->GetInt()));break;
            case VTYPE_DOUBLE:
                WORKER_LOG(tab_string + std::string("   ") + std::to_string(Dictionary->GetValue(s)->GetDouble()));break;
            case VTYPE_DICTIONARY:
                PrintDictionary(Dictionary->GetValue(s)->GetDictionary(),tab + 3);break;
            case VTYPE_STRING:
                WORKER_LOG(tab_string + std::string("   ") + Dictionary->GetValue(s)->GetString().ToString());break;
        }
    }
}*/


void MainApp::AfterReadyToCreateBrowser(bool Reload)
{
    WORKER_LOG(std::string("LoadCallback create new ") + NextLoadPage);

    CefWindowInfo window_info;

    window_info.SetAsWindowless(0,true);

    CefBrowserSettings browser_settings;
    browser_settings.windowless_frame_rate = 5;

    std::wstring wencoding = L"UTF-8";
    cef_string_utf16_set(wencoding.data(),wencoding.size(),&browser_settings.default_encoding,true);

    //CefRequestContextSettings settings;
    //CefRefPtr<CefRequestContext> Context = CefRequestContext::CreateContext(settings,NULL);
    CefRefPtr<CefRequestContext> Context = CefRequestContext::GetGlobalContext();

    {
        CefRefPtr<CefValue> Value = CefValue::Create();
        CefRefPtr<CefDictionaryValue> Dictionary = CefDictionaryValue::Create();

        WORKER_LOG("System Proxy");
        Dictionary->SetString("mode","direct");

        CefString Error;
        Value->SetDictionary(Dictionary);
        Context->SetPreference("proxy",Value,Error);
        WORKER_LOG(std::string("Error setting proxy<<") + Error.ToString());

    }

    //PrintDictionary(Context->GetAllPreferences(true),3);

    if(Reload || !_HandlersManager->GetBrowser())
    {
        WORKER_LOG("!!!CREATENEWBROWSER!!!");
        _HandlersManager->Init2(CefBrowserHost::CreateBrowserSync(window_info, _HandlersManager->GetHandler(), NextLoadPage, browser_settings, Context));

        Layout->BrowserHandle = _HandlersManager->GetBrowser()->GetHost()->GetWindowHandle();
        //ToggleDevTools();
        CreateTooboxBrowser();
        CreateScenarioBrowser();
        CreateCentralBrowser();
    }else
    {
        WORKER_LOG("!!!OPTIMIZEDRELOAD!!!");
        _HandlersManager->GetBrowser()->GetMainFrame()->LoadURL(NextLoadPage);
    }
}

void MainApp::TimezoneCallback(int offset)
{
    {
        LOCK_TIMEZONE
        if(offset > 99999)
        {
            Data->TimezoneSelected = false;
        }else
        {
            Data->TimezoneSelected = true;
            Data->Timezone = offset;
        }
    }
    SendTextResponce("<Messages><Timezone></Timezone></Messages>");
}

void MainApp::GeolocationCallback(float latitude, float longitude)
{
    {
        LOCK_GEOLOCATION
        if(latitude > 99999)
        {
            Data->GeolocationSelected = false;
        }else
        {
            Data->GeolocationSelected = true;
            Data->Longitude = longitude;
            Data->Latitude = latitude;
        }
    }
    SendTextResponce("<Messages><Geolocation></Geolocation></Messages>");

}

void MainApp::VisibleCallback(bool visible)
{
    WORKER_LOG(std::string("VisibleCallback ") + std::to_string(visible));
    if(visible)
        _HandlersManager->GetHandler()->Show();
    else
        _HandlersManager->GetHandler()->Hide();
}

void MainApp::Hide()
{
    _HandlersManager->GetHandler()->Hide();
}

void MainApp::ToggleDevTools()
{
    WORKER_LOG("ToggleDevTools");
    if(!_HandlersManager->GetBrowser())
        return;
    if(!Data->IsRecord)
        return;

    dhandler->OpenDevTools();
}

void MainApp::InspectAt(int x, int y)
{
    WORKER_LOG(std::string("Inspect At<<") + std::to_string(x) + std::string("<<") + std::to_string(y));
    if(!_HandlersManager->GetBrowser())
        return;

    dhandler->OpenDevTools(CefPoint(x,y));
}

void MainApp::MouseMoveAt(int x, int y)
{
    clock_t CurrentTime = clock();
    float time_spent = float( CurrentTime - LastMouseTrack ) /  CLOCKS_PER_SEC;

    if(InspectFrameSearching && time_spent < 3)
        return;
    if(time_spent < 0.1)
        return;

    InspectFrameSearching = true;
    InspectFrameChain.clear();
    InspectX = x;
    InspectY = y;
    LastMouseTrack = CurrentTime;

    if(_HandlersManager->GetBrowser())
    {
        //WORKER_LOG(std::string("BrowserAutomationStudio_InspectElement<<") + std::to_string(x) + std::string(",") + std::to_string(y));
        _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_InspectElement(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(")"),_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);
    }

}

void MainApp::MouseLeave()
{
    {
        LOCK_BROWSER_DATA
        Data->_Inspect.active = false;
    }
    RECT r = Layout->GetBrowserOuterRectangle(GetData()->WidthBrowser,GetData()->HeightBrowser,GetData()->WidthAll,GetData()->HeightAll);
    InvalidateRect(Data->_MainWindowHandle,&r,false);
}

void MainApp::SetProxyCallback(const std::string& server, int Port, bool IsHttp, const std::string& username, const std::string& password, const std::string& target)
{
    ProxyData NewProxy;
    WORKER_LOG(std::string("SetProxyCallback ") + server + std::string(" ") + std::to_string(Port) + std::string(" ") + target);
    if(!server.empty())
    {
        NewProxy.Server = server;
        NewProxy.Port = Port;
        NewProxy.ProxyType = (IsHttp)?ProxyData::Http:ProxyData::Socks5;
        NewProxy.UserName = username;
        NewProxy.Password = password;
        NewProxy.IsNull = false;
    }
    {
        LOCK_BROWSER_DATA
        Data->_Proxy.Set(NewProxy,target);
    }
    SendTextResponce("<Messages><SetProxy></SetProxy></Messages>");
}

void MainApp::AddHeaderCallback(const std::string& key,const std::string& value, const std::string& target)
{
    {
        LOCK_BROWSER_DATA
        std::shared_ptr<std::map<std::string,std::string> > Headers = Data->_Headers.Get(target);
        if(!Headers.get())
        {
            Headers = std::make_shared<std::map<std::string,std::string> >();
        }
        if(value.empty())
            Headers->erase(key);
        else
            Headers->insert(std::pair<std::string,std::string>(key, value));
        Data->_Headers.Set(Headers,target);
    }
    SendTextResponce("<Messages><AddHeader></AddHeader></Messages>");
}

void MainApp::SetUserAgentCallback(const std::string& value)
{
    /*{
        LOCK_BROWSER_DATA
        if(value.empty())
            Data->_Headers.erase("User-Agent");
        else
            Data->_Headers["User-Agent"] = value;
    }*/
    //SendTextResponce("<Messages><SetUserAgent>1</SetUserAgent></Messages>");
}

void MainApp::CleanHeaderCallback()
{
    {
        LOCK_BROWSER_DATA
        Data->_Headers.Clear();
    }
    SendTextResponce("<Messages><CleanHeader></CleanHeader></Messages>");
}

void MainApp::GetUrlCallback()
{
    std::string url;

    if(_HandlersManager->GetBrowser())
    {
        url = _HandlersManager->GetBrowser()->GetMainFrame()->GetURL();
    }
    xml_encode(url);
    SendTextResponce(std::string("<Messages><GetUrl>") + url + std::string("</GetUrl></Messages>"));
}

void MainApp::OnBeforeCommandLineProcessing(const CefString& process_type,CefRefPtr<CefCommandLine> command_line)
{
    command_line->AppendSwitch("--single-process");
    command_line->AppendSwitch("--high-dpi-support");

    //command_line->AppendSwitch("--disable-gpu");
    //command_line->AppendSwitch("--disable-gpu-compositing");
    //command_line->AppendSwitch("--disable-gpu-vsync");

    for(auto p:ParseChromeCommandLine())
    {

        if(p.second.length()>0)
        {
            WORKER_LOG("ChromeCommandLine<<" + p.first + "=" + p.second);
            command_line->AppendSwitchWithValue(p.first,p.second);
        }else
        {
            if(!Data->IsRecord || p.first != "--disable-threaded-compositing")
            {
                WORKER_LOG("ChromeCommandLine<<" + p.first);
                command_line->AppendSwitch(p.first);
            }
        }
    }



    if(Settings->UseFlash())
        command_line->AppendSwitch("--enable-system-flash");
}

bool MainApp::IsNeedQuit()
{
    if(!_HandlersManager->GetHandler())
        return false;

    return _HandlersManager->GetHandler()->IsNeedQuit();
}

void MainApp::SendTextResponce(const std::string& text)
{
    for(auto f:EventSendTextResponce)
        f(text);
}


void MainApp::AddCacheMaskAllowCallback(const std::string& value)
{
    WORKER_LOG(std::string("AddCacheMaskAllowCallback<<") + value);
    std::pair<bool, std::string> data;
    data.first = true;
    data.second = value;
    {
        LOCK_BROWSER_DATA
        Data->_CacheMask.push_back(data);
    }
    SendTextResponce("<Messages><AddCacheMaskAllow/></Messages>");
}
void MainApp::AddCacheMaskDenyCallback(const std::string& value)
{
    WORKER_LOG(std::string("AddCacheMaskDenyCallback<<") + value);
    std::pair<bool, std::string> data;
    data.first = false;
    data.second = value;
    {
        LOCK_BROWSER_DATA
        Data->_CacheMask.push_back(data);
    }
    SendTextResponce("<Messages><AddCacheMaskDeny/></Messages>");
}
void MainApp::AddRequestMaskAllowCallback(const std::string& value)
{
    WORKER_LOG(std::string("AddRequestMaskAllowCallback<<") + value);
    std::pair<bool, std::string> data;
    data.first = true;
    data.second = value;
    {
        LOCK_BROWSER_DATA
        Data->_RequestMask.push_back(data);
    }
    SendTextResponce("<Messages><AddRequestMaskAllow/></Messages>");
}
void MainApp::AddRequestMaskDenyCallback(const std::string& value)
{
    WORKER_LOG(std::string("AddRequestMaskDenyCallback<<") + value);
    std::pair<bool, std::string> data;
    data.first = false;
    data.second = value;
    {
        LOCK_BROWSER_DATA
        Data->_RequestMask.push_back(data);
    }
    SendTextResponce("<Messages><AddRequestMaskDeny/></Messages>");
}
void MainApp::ClearCacheMaskCallback()
{
    WORKER_LOG(std::string("ClearCacheMaskCallback<<"));
    {
        LOCK_BROWSER_DATA
        Data->_CacheMask.clear();
    }
    SendTextResponce("<Messages><ClearCacheMask/></Messages>");
}
void MainApp::ClearRequestMaskCallback()
{
    WORKER_LOG(std::string("ClearRequestMaskCallback<<"));
    {
        LOCK_BROWSER_DATA
        Data->_RequestMask.clear();
    }
    SendTextResponce("<Messages><ClearRequestMask/></Messages>");
}
void MainApp::ClearLoadedUrlCallback()
{
    WORKER_LOG(std::string("ClearLoadedUrlCallback<<"));
    {
        LOCK_BROWSER_DATA
        Data->_LoadedUrls.clear();
    }
    SendTextResponce("<Messages><ClearLoadedUrl/></Messages>");
}
void MainApp::ClearCachedDataCallback()
{
    WORKER_LOG(std::string("ClearCachedDataCallback<<"));\
    {
        LOCK_BROWSER_DATA
        Data->_CachedData.clear();
    }
    SendTextResponce("<Messages><ClearCachedData/></Messages>");
}
void MainApp::ClearAllCallback()
{
    WORKER_LOG(std::string("ClearAllCallback<<"));
    {
        LOCK_BROWSER_DATA
        Data->_CacheMask.clear();
        Data->_RequestMask.clear();
        Data->_LoadedUrls.clear();
        Data->_CachedData.clear();
    }
    SendTextResponce("<Messages><ClearAll/></Messages>");
}
void MainApp::ClearMasksCallback()
{
    WORKER_LOG(std::string("ClearMasksCallback<<"));
    {
        LOCK_BROWSER_DATA
        Data->_CacheMask.clear();
        Data->_RequestMask.clear();
    }
    SendTextResponce("<Messages><ClearMasks/></Messages>");
}
void MainApp::ClearDataCallback()
{
    WORKER_LOG(std::string("ClearDataCallback<<"));
    {
        LOCK_BROWSER_DATA
        Data->_LoadedUrls.clear();
        Data->_CachedData.clear();
    }
    SendTextResponce("<Messages><ClearData/></Messages>");
}
void MainApp::WaitCodeCallback()
{
    if(!_HandlersManager->GetBrowser())
    {
        NextLoadPage = "about:blank";
        AfterReadyToCreateBrowser(true);
    }
    CreateTooboxBrowser();
    CreateScenarioBrowser();
    Layout->UpdateState(MainLayout::Ready);
    if(BrowserToolbox)
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript("BrowserAutomationStudio_HideWaiting()",BrowserToolbox->GetMainFrame()->GetURL(), 0);
    if(BrowserScenario)
        BrowserScenario->GetMainFrame()->ExecuteJavaScript("BrowserAutomationStudio_NotRunningTask()",BrowserScenario->GetMainFrame()->GetURL(), 0);

    Layout->UpdateTabs();
}

void MainApp::StartSectionCallback(int Id)
{
    if(!_HandlersManager->GetBrowser())
    {
        NextLoadPage = "about:blank";
        AfterReadyToCreateBrowser(true);
    }
    CreateTooboxBrowser();
    CreateScenarioBrowser();
    Layout->UpdateState(MainLayout::Ready);
    if(BrowserToolbox)
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript("BrowserAutomationStudio_HideWaiting()",BrowserToolbox->GetMainFrame()->GetURL(), 0);
    if(BrowserScenario)
        BrowserScenario->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_NotRunningTask(") + std::to_string(Id) + std::string(")"),BrowserScenario->GetMainFrame()->GetURL(), 0);

    Layout->UpdateTabs();
}

void MainApp::ScriptFinishedCallback()
{
    WORKER_LOG("ScriptFinishedCallback");
    Layout->UpdateState(MainLayout::Finished);
    if(BrowserToolbox)
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript("BrowserAutomationStudio_HideWaiting()",BrowserToolbox->GetMainFrame()->GetURL(), 0);
    if(BrowserScenario)
        BrowserScenario->GetMainFrame()->ExecuteJavaScript("BrowserAutomationStudio_RunningTask()",BrowserScenario->GetMainFrame()->GetURL(), 0);
    Hide();
}

void MainApp::FindCacheByMaskBase64Callback(const std::string& value)
{
    WORKER_LOG(std::string("FindCacheByMaskBase64Callback<<") + value);
    std::string res = "";
    {
        LOCK_BROWSER_DATA
        for(std::pair<std::string, std::shared_ptr<std::vector<char> > > pair:Data->_CachedData)
        {
            if(match(value,pair.first) || match(urlnormalize(value),urlnormalize(pair.first)))
            {
                res = base64_encode((unsigned char const *)pair.second->data(),pair.second->size());
                break;
            }
        }
    }
    xml_encode(res);
    SendTextResponce(std::string("<Messages><FindCacheByMaskBase64>") + res + ("</FindCacheByMaskBase64></Messages>"));
}
void MainApp::FindStatusByMaskCallback(const std::string& value)
{
    WORKER_LOG(std::string("FindStatusByMaskCallback<<") + value);
    std::string res = "0";
    {
        LOCK_BROWSER_DATA
        for(std::pair<std::string, int> url:Data->_LoadedUrls)
        {
            if(match(value,url.first) || match(urlnormalize(value),urlnormalize(url.first)))
            {
                res = std::to_string(url.second);
                break;
            }
        }
    }
    SendTextResponce(std::string("<Messages><FindStatusByMask>") + res + ("</FindStatusByMask></Messages>"));
}

void MainApp::GetLoadStatsCallback()
{
    int is_loading = 0;
    if(_HandlersManager->GetBrowser())
        is_loading = _HandlersManager->GetBrowser()->IsLoading();


    SendTextResponce(std::string("<Messages><GetLoadStats>") + std::to_string(is_loading) + "," + std::to_string(Data->OldestRequestTime) + std::string("</GetLoadStats></Messages>"));
    return;
}


void MainApp::FindCacheByMaskStringCallback(const std::string& value)
{

    WORKER_LOG(std::string("FindCacheByMaskStringCallback<<") + value);
    std::string res = "";
    {
        LOCK_BROWSER_DATA
        for(std::pair<std::string, std::shared_ptr<std::vector<char> > > pair:Data->_CachedData)
        {
            if(match(value,pair.first) || match(urlnormalize(value),urlnormalize(pair.first)))
            {
                res = std::string(pair.second->begin(),pair.second->end());
                break;
            }
        }
    }
    xml_encode(res);
    SendTextResponce(std::string("<Messages><FindCacheByMaskString>") + res + std::string("</FindCacheByMaskString></Messages>"));
}
void MainApp::IsUrlLoadedByMaskCallback(const std::string& value)
{
    WORKER_LOG(std::string("IsUrlLoadedByMaskCallback<<") + value);
    std::string res = "0";
    {
        LOCK_BROWSER_DATA
        for(std::pair<std::string, int> url:Data->_LoadedUrls)
        {
            if(match(value,url.first) || match(urlnormalize(value),urlnormalize(url.first)))
            {
                res = "1";
                break;
            }
        }
    }
    SendTextResponce(std::string("<Messages><IsUrlLoadedByMask>") + res + ("</IsUrlLoadedByMask></Messages>"));

}

void MainApp::SetCodeCallback(const std::string & code)
{
    Code = code;
    if(code.empty())
        Code = " ";
    Variables = extract_variables(code);
    Functions = extract_functions(code);
    std::string AdditionalResourcesPrev = AdditionalResources;
    AdditionalResources = extract_resources(code);
    if(AdditionalResourcesPrev!=AdditionalResources)
        ResourcesChanged = true;
}

void MainApp::SetResourceCallback(const std::string & resources)
{
    Resources = resources;
    ResourcesChanged = true;
}

void MainApp::CrushCallback()
{
    *((unsigned int*)0) = 0xDEAD;
}

void MainApp::SetInitialStateCallback(const std::string & lang)
{
    Lang = lang;
}

void MainApp::SetNextActionCallback(const std::string& NextActionId)
{
    if(scenariov8handler && scenariov8handler->GetIsInitialized())
    {
        if(BrowserScenario)
            BrowserScenario->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_NotRunningTask(") + NextActionId + std::string(")"),BrowserScenario->GetMainFrame()->GetURL(), 0);
    }else
    {
        SetNextActionId = NextActionId;
    }
}

void MainApp::ClearElementCommand()
{
    WORKER_LOG("ClearElementCommand");
    IsLastCommandNull = true;
    ExecuteFrameChain.clear();
    ExecuteFrameSearching = false;
    ExecuteFrameScrolling = false;
    ExecuteFrameScrollingSwitch = false;
    ExecuteSearchCoordinatesX = 0;
    ExecuteSearchCoordinatesY = 0;
    RunElementCommandCallbackOnNextTimer = -1;
    TypeTextTaskIsActive = false;
    IsMouseMoveSimulation = false;
}


void MainApp::ElementCommandCallback(const ElementCommand &Command)
{
    WORKER_LOG(std::string("ElementCommandCallback<<"));
    RunElementCommandCallbackOnNextTimer = -1;
    LastCommand = Command;
    IsLastCommandNull = false;

    //Check if need to search for frame
    bool NeedToSearchInFrames = false;
    picojson::array FrameSearchPath;
    for(ExecuteFrameSearchingLength = 0;ExecuteFrameSearchingLength<LastCommand.Path.size();ExecuteFrameSearchingLength++)
    {
        std::string NextCommand = LastCommand.Path.at(ExecuteFrameSearchingLength).first;

        if(NextCommand == "frame_css")
        {
            FrameSearchPath.clear();
            FrameSearchPath.push_back(picojson::value("css"));
            FrameSearchPath.push_back(picojson::value(LastCommand.Path.at(ExecuteFrameSearchingLength).second));
            NeedToSearchInFrames = true;
            break;
        }else if(NextCommand == "frame_match")
        {
            FrameSearchPath.clear();
            FrameSearchPath.push_back(picojson::value("match"));
            FrameSearchPath.push_back(picojson::value(LastCommand.Path.at(ExecuteFrameSearchingLength).second));
            NeedToSearchInFrames = true;
            break;
        }else if(NextCommand == "frame_element")
        {
            NeedToSearchInFrames = true;
            break;
        }else
        {
            FrameSearchPath.push_back(picojson::value(NextCommand));
            FrameSearchPath.push_back(picojson::value(LastCommand.Path.at(ExecuteFrameSearchingLength).second));
        }
    }



    if(NeedToSearchInFrames)
    {
        WORKER_LOG("NeedToSearchInFrames");
        //On first searching
        if(!ExecuteFrameSearching)
        {
            ExecuteFrameChain.clear();
            ExecuteSearchCoordinatesX = 0;
            ExecuteSearchCoordinatesY = 0;
            ExecuteFrameScrolling = Command.CommandName == "system_click"
                    || Command.CommandName == "check"
                    || Command.CommandName == "system_click_down"
                    || Command.CommandName == "system_click_up"
                    || Command.CommandName == "move"
                    || Command.CommandName == "type"
                    || Command.CommandName == "clear"
                    || Command.CommandName == "set"
                    || Command.CommandName == "set_integer"
                    || Command.CommandName == "set_random"
                    || Command.CommandName == "random_point"
                    || Command.CommandName == "render_base64"
                    || Command.CommandName == "focus"
                    || Command.CommandName == "render_base64";
            ExecuteFrameScrollingSwitch = false;
            //ExecuteInnerFrameScrolling = ExecuteFrameScrolling;
        }
        ExecuteFrameSearching = true;

        std::string script;

        std::string path = picojson::value(picojson::value(FrameSearchPath).serialize()).serialize();
        if(ExecuteFrameScrolling)
        {
            ExecuteFrameScrollingSwitch = !ExecuteFrameScrollingSwitch;
        }else
        {
            ExecuteFrameScrollingSwitch = false;
        }

        if(ExecuteFrameScrollingSwitch)
        {
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + path + std::string(");BrowserAutomationStudio_ScrollToElement(el);}");
        }else
        {
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + path + std::string(");if(!el){browser_automation_studio_frame_find_result(0,0,'','','','',0,0,false);return;};"
                "var rect = el.getBoundingClientRect();"
                "var frame_index=Array.prototype.slice.call(document.querySelectorAll('iframe, frame')).indexOf(el);if(frame_index<0)frame_index=0;"
                "var r = BrowserAutomationStudio_GetInternalBoundingRect(el);"
                "browser_automation_studio_frame_find_result(parseInt(rect.left),parseInt(rect.top),el.getAttribute('name')||'',el.getAttribute('src')||'',el.outerHTML||'',frame_index,r.left,r.top,true);}");
        }
        script = std::string("(function(){") + script + std::string("})()");
        //WORKER_LOG(script);
        CefRefPtr<CefFrame> Frame;
        if(ExecuteFrameChain.empty())
            Frame = _HandlersManager->GetBrowser()->GetMainFrame();
        else
            Frame = _HandlersManager->GetBrowser()->GetFrame(ExecuteFrameChain.at(ExecuteFrameChain.size()-1).FrameData.frame_id);

        Frame->ExecuteJavaScript(script.c_str(),Frame->GetURL(), 0);

        return;
    }

    ExecuteFrameSearching = false;
    ExecuteFrameScrolling = false;
    ExecuteFrameScrollingSwitch = false;


    WORKER_LOG("ExecuteFrame stage finished");
    WORKER_LOG(std::to_string(ExecuteSearchCoordinatesX));
    WORKER_LOG(std::to_string(ExecuteSearchCoordinatesY));



    if(_HandlersManager->GetBrowser())
    {
        std::string script;
        if(Command.CommandName == "xml")
        {
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(!el){browser_automation_studio_result('BAS_NOT_EXISTS');return;};var res = '';if(el){res = el.outerHTML}browser_automation_studio_result(res);}");
        }else if(Command.CommandName == "text")
        {
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(!el){browser_automation_studio_result('BAS_NOT_EXISTS');return;};var res = '';try{if(el){if(el.tagName.toLowerCase()=='input'||el.tagName.toLowerCase()=='textarea')res=el.value;else res=el.textContent}}catch(e){}browser_automation_studio_result(res);}");
        }else if(Command.CommandName == "script")
        {
            std::string script_escaped = picojson::value(LastCommand.CommandParam1).serialize();
            script = std::string("{var positionx=") + std::to_string(ExecuteSearchCoordinatesX) + std::string(";positiony=") + std::to_string(ExecuteSearchCoordinatesY) + std::string(";var scrollx=") + std::to_string(Data->ScrollX) + std::string(";scrolly=") + std::to_string(Data->ScrollY) + std::string(";var self = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(!self){browser_automation_studio_result('');return;};var obj=null;try{obj = eval(") + script_escaped + std::string(");}catch(e){}var res='';if(typeof(obj)!='undefined'&&obj !== null){res=obj.toString()}browser_automation_studio_result(res);}");
        }else if(Command.CommandName == "click")
        {
            BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(!el){browser_automation_studio_result('BAS_NOT_EXISTS');return;};if(el)el.click();browser_automation_studio_result('');}");
        }else if(Command.CommandName == "system_click" || Command.CommandName == "check" || Command.CommandName == "system_click_down" || Command.CommandName == "system_click_up")
        {
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");BrowserAutomationStudio_ScrollToElement(el);}");
        }else if(Command.CommandName == "move")
        {
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");BrowserAutomationStudio_ScrollToElement(el);}");
        }else if(Command.CommandName == "fill")
        {
            BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
            std::string text_escaped = picojson::value(LastCommand.CommandParam1).serialize();
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(!el){browser_automation_studio_result('BAS_NOT_EXISTS');return;};if(el){el.value = ") + text_escaped + std::string("};browser_automation_studio_result('');}");
        }else if(Command.CommandName == "type")
        {
            BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
            TypeText = ReplaceAll(LastCommand.CommandParam1,"\r\n","<RETURN>");
            TypeText = ReplaceAll(TypeText,"\n","<RETURN>");

            TypeTextDelay = std::stoi(LastCommand.CommandParam2);
            if(LastCommand.Path.size()>0)
            {
                script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");BrowserAutomationStudio_ScrollToElement(el);}");
            }
            else
            {
                TypeTextTaskIsActive = true;
                TypeTextIsFirstLetter = false;
                TypeTextLastTime = 0;
                TypeTextState.Clear();
            }
        }else if(Command.CommandName == "clear")
        {
            BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
            TypeText = "<CONTROL>a<DELETE>";
            TypeTextDelay = 100;
            if(LastCommand.Path.size()>0)
            {
                script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");BrowserAutomationStudio_ScrollToElement(el);}");
            }
            else
            {
                TypeTextTaskIsActive = true;
                TypeTextIsFirstLetter = false;
                TypeTextLastTime = 0;
                TypeTextState.Clear();
            }
        }else if(Command.CommandName == "exist")
        {
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");var res;if(el)res='1';else res='0';browser_automation_studio_result(res);}");
        }else if(Command.CommandName == "submit")
        {
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(!el){browser_automation_studio_result('BAS_NOT_EXISTS');return;};if(el)el.submit();browser_automation_studio_result('');}");
        }else if(Command.CommandName == "style")
        {
            std::string style_escaped = picojson::value(LastCommand.CommandParam1).serialize();
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(!el){browser_automation_studio_result('BAS_NOT_EXISTS');return;};var res='';if(el)res=window.getComputedStyle(el)[") + style_escaped + std::string("];browser_automation_studio_result(res);}");
        }
        else if(Command.CommandName == "set")
        {
            LastCommand.StageId = 0;
            std::string set_escaped = picojson::value(LastCommand.CommandParam1).serialize();
            std::string proc = std::string("{var option_list = el.querySelectorAll(\"option\");"
                    "keys = \"<HOME>\";"
                    "for(var i = 0;i<option_list.length;i++)"
                    "{"
                      "var option = option_list.item(i);"
                      "if(option.innerHTML === ") + set_escaped + std::string(")break;"
                      "keys += \"<<DOWN>>\";"
                    "}"
                    "keys += \"<<RETURN>>\";}"
                     );
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(!el){browser_automation_studio_result('BAS_NOT_EXISTS');return;};var keys='';if(el){") + proc + std::string("}browser_automation_studio_result(keys);}");

        }else if(Command.CommandName == "set_integer")
        {
            LastCommand.StageId = 0;
            std::string proc = std::string("{var option_list = el.querySelectorAll(\"option\");"
                    "keys = \"<HOME>\";"
                    "for(var i = 0;i<") + LastCommand.CommandParam1 + std::string(";i++)"
                    "{"
                      "keys += \"<<DOWN>>\";"
                    "}"
                    "keys += \"<<RETURN>>\";}"
                     );
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(!el){browser_automation_studio_result('BAS_NOT_EXISTS');return;};var keys='';if(el){") + proc + std::string("}browser_automation_studio_result(keys);}");

        }else if(Command.CommandName == "set_random")
        {
            LastCommand.StageId = 0;
            std::string proc = std::string("{var option_list = el.querySelectorAll(\"option\");"
                    "keys = \"<HOME>\";"
                    "var index = Math.floor((Math.random() * option_list.length));"
                    "for(var i = 0;i<option_list.length;i++)"
                    "{"
                      "var option = option_list.item(i);"
                      "if(i === index)break;"
                      "keys += \"<<DOWN>>\";"
                    "}"
                    "keys += \"<<RETURN>>\";}"
                     );
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(!el){browser_automation_studio_result('BAS_NOT_EXISTS');return;};var keys='';if(el){") + proc + std::string("}browser_automation_studio_result(keys);}");
        }else if(Command.CommandName == "random_point")
        {
            LastCommand.StageId = 0;
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");BrowserAutomationStudio_ScrollToElement(el);}");
        }else if(Command.CommandName == "attr")
        {
            std::string attr_escaped = picojson::value(LastCommand.CommandParam1).serialize();
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(!el){browser_automation_studio_result('BAS_NOT_EXISTS');return;};var res='';var attr=") + attr_escaped + std::string(";if(el){if(el.hasAttribute(attr))res=el.getAttribute(attr);}browser_automation_studio_result(res);}");
        }else if(Command.CommandName == "set_attr")
        {
            std::string attr_escaped = picojson::value(LastCommand.CommandParam1).serialize();
            std::string val_escaped = picojson::value(LastCommand.CommandParam2).serialize();
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(!el){browser_automation_studio_result('BAS_NOT_EXISTS');return;};var attr=") + attr_escaped + std::string(";var val=") + val_escaped + std::string(";if(el){if(val.length === 0)el.removeAttribute(attr);else el.setAttribute(attr,val);}browser_automation_studio_result('');}");
        }else if(Command.CommandName == "length")
        {
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(!el){browser_automation_studio_result('BAS_NOT_EXISTS');return;};var res = '';if(el){res = el.length;}browser_automation_studio_result(res);}");
        }else if(Command.CommandName == "render_base64")
        {
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");BrowserAutomationStudio_ScrollToElement(el);}");
        }else if(Command.CommandName == "focus")
        {
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");BrowserAutomationStudio_ScrollToElement(el);}");
        }
        if(!script.empty())
        {
            script = std::string("(function(){") + script + std::string("})()");
            WORKER_LOG(std::string("EXEC<<") + script);
            if(Command.FrameUrl.empty())
            {
                CefRefPtr<CefFrame> Frame;

                if(ExecuteFrameChain.empty())
                    Frame = _HandlersManager->GetBrowser()->GetMainFrame();
                else
                    Frame = _HandlersManager->GetBrowser()->GetFrame(ExecuteFrameChain.at(ExecuteFrameChain.size()-1).FrameData.frame_id);

                Frame->ExecuteJavaScript(script.c_str(),Frame->GetURL(), 0);
            }
            else
            {
                std::vector<int64> identifiers;
                _HandlersManager->GetBrowser()->GetFrameIdentifiers(identifiers);
                WORKER_LOG(std::string("FRAME_NUMBER ") + std::to_string(identifiers.size()));

                bool done = false;
                for(int64 id:identifiers)
                {
                    WORKER_LOG(std::string("FRAME_URL ") + std::to_string(identifiers.size()));

                    if(match(Command.FrameUrl,_HandlersManager->GetBrowser()->GetFrame(id)->GetURL().ToString()))
                    {
                        WORKER_LOG(std::string("ExecutingInFrame<<") + _HandlersManager->GetBrowser()->GetFrame(id)->GetURL().ToString());
                        _HandlersManager->GetBrowser()->GetFrame(id)->ExecuteJavaScript(script.c_str(),_HandlersManager->GetBrowser()->GetFrame(id)->GetURL(), 0);
                        done = true;
                        break;
                    }
                }
                if(!done)
                {
                    SendTextResponce(std::string("<Messages><Element ID=\"") + Command.CommandId + std::string("\"><") + Command.CommandName + std::string(">") + std::string("</") + Command.CommandName + ("></Element></Messages>"));
                    WORKER_LOG(std::string("ElementCommandCallbackDefault>>FailedToFindFrame"));
                }

            }
        }
    }else
    {
        SendTextResponce(std::string("<Messages><Element ID=\"") + Command.CommandId + std::string("\"><") + Command.CommandName + std::string(">") + std::string("</") + Command.CommandName + ("></Element></Messages>"));
        WORKER_LOG(std::string("ElementCommandCallbackDefault>>"));
    }
}

void MainApp::CefMessageLoop()
{
    if(SkipBeforeRenderNextFrame > 1)
    {
        SkipBeforeRenderNextFrame--;
        if(SkipBeforeRenderNextFrame<=1 && _HandlersManager->GetBrowser())
        {
            _HandlersManager->GetBrowser()->GetHost()->Invalidate(PET_VIEW);
        }

    }
}

void MainApp::Timer()
{
    if(RunElementCommandCallbackOnNextTimer >= 0)
    {
        if(RunElementCommandCallbackOnNextTimer == 0)
        {
            WORKER_LOG("Execute last command");
            if(!IsLastCommandNull)
                ElementCommandCallback(LastCommand);
        }else
        {
            RunElementCommandCallbackOnNextTimer --;
        }
    }

    ExecuteTypeText();

    ExecuteMouseMove();

    {
        LOCK_V8_HANDLER
        if(v8handler)
            HandleMainBrowserEvents();
    }

    {
        LOCK_V8_HANDLER
        if(v8handler)
            HandleFrameFindEvents();
    }

    if(toolboxv8handler)
        HandleToolboxBrowserEvents();

    if(scenariov8handler)
        HandleScenarioBrowserEvents();

    if(central8handler)
        HandleCentralBrowserEvents();

    if(dhandler)
        dhandler->Timer();

    _HandlersManager->Timer();

    if(_HandlersManager->GetHandler())
    {
        //CefPostTask(TID_IO, base::Bind(&MainHandler::CleanResourceHandlerList, _HandlersManager->GetHandler()));
        if(_HandlersManager->GetHandler()->GetResourceListLength() == 0 && Data->IsReset && Data->IsAboutBlankLoaded)
        {
            ResetCallbackFinalize();
        }
    }

    if(_HandlersManager->CheckIsClosed())
    {
        SendTextResponce("<Messages><PopupClose></PopupClose></Messages>");
    }

    UpdateWindowPositionWithParent();
}

void MainApp::HandleCentralBrowserEvents()
{
    std::pair<std::string, bool> res = central8handler->GetLoadUrl();
    if(res.second)
    {
        std::string url = res.first;
        if(url.length() >= 7 && url[0] == 'f'&& url[1] == 'i'&& url[2] == 'l'&& url[3] == 'e'&& url[4] == ':'&& url[5] == '/'&& url[6] == '/')
        {
            url = url.substr(7,url.length() - 7);
            WORKER_LOG(std::string("OpenScriptExample<<") + url);
            xml_encode(url);
            SendTextResponce(std::string("<Messages><LoadScript>") + url + std::string("</LoadScript></Messages>"));

        }else
        {
            WORKER_LOG(std::string("LoadUrlFromCentralBrowser<<") + res.first);
            ShellExecute(0, 0, s2ws(res.first).c_str(), 0, 0 , SW_SHOW );
        }
    }

    if(central8handler->GetClose())
    {
        Layout->HideCentralBrowser();
    }

    res = central8handler->GetSettings();
    if(res.second)
    {
        std::string settings = res.first;
        WORKER_LOG(std::string("Settings updated") + settings);
        Settings->Deserialize(settings);
        Restart();
    }
}

void MainApp::HandleScenarioBrowserEvents()
{
    if(scenariov8handler->GetIsInitialized() && !Code.empty())
    {
        std::string script = std::string("BrowserAutomationStudio_Parse(") + picojson::value(Code.data()).serialize() + std::string(")");
        BrowserScenario->GetMainFrame()->ExecuteJavaScript(script,BrowserScenario->GetMainFrame()->GetURL(), 0);
        Code.clear();
    }

    if(scenariov8handler->GetIsInitialized() && !SetNextActionId.empty())
    {
        if(BrowserScenario)
            BrowserScenario->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_NotRunningTask(") + SetNextActionId + std::string(")"),BrowserScenario->GetMainFrame()->GetURL(), 0);
        SetNextActionId.clear();
    }

    std::pair<std::string, bool> res = scenariov8handler->GetResult();
    if(res.second)
    {
        std::string new_code = res.first;
        WORKER_LOG(std::string("HandleScenarioBrowserEvents<<") + new_code);
        Variables = extract_variables(new_code);
        Functions = extract_functions(new_code);
        std::string AdditionalResourcesPrev = AdditionalResources;
        AdditionalResources = extract_resources(new_code);
        if(AdditionalResourcesPrev != AdditionalResources)
            ResourcesChanged = true;
        xml_encode(new_code);
        SendTextResponce(std::string("<Messages><ReceivedCode>") + new_code + std::string("</ReceivedCode></Messages>"));
        if(!DelayedSend.empty())
        {
            SendTextResponce(DelayedSend);
            DelayedSend.clear();
        }
    }

    std::pair<std::string, bool> res2 = scenariov8handler->GetExecuteCode();
    if(res2.second)
    {
        Layout->UpdateState(MainLayout::Hold);
        if(BrowserToolbox)
            BrowserToolbox->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_ShowWaiting(") + picojson::value(res2.first).serialize() + std::string(")"),BrowserToolbox->GetMainFrame()->GetURL(), 0);
        std::string CodeSend = res2.first;
        WORKER_LOG(std::string("GetExecuteCode<<") + CodeSend);
        xml_encode(CodeSend);
        SendTextResponce(std::string("<Messages><WaitCode>") + CodeSend + std::string("</WaitCode></Messages>"));
    }

    std::pair<std::string, bool> res6 = scenariov8handler->GetClipboardSetRequest();
    if(res6.second)
    {
        write_clipboard(res6.first);
    }

    if(scenariov8handler->GetClipboardGetRequest())
    {
        std::string res = read_clipboard();
        std::string script = std::string("BrowserAutomationStudio_GetClipboardResult(") + picojson::value(res).serialize() + std::string(")");
        if(BrowserScenario)
            BrowserScenario->GetMainFrame()->ExecuteJavaScript(script,BrowserScenario->GetMainFrame()->GetURL(), 0);
    }

    std::pair<std::string, bool> res5 = scenariov8handler->GetIsEditStart();
    if(res5.second)
    {
        std::string data = res5.first;
        WORKER_LOG(std::string("EditStart<<") + data);
        std::string script = std::string("BrowserAutomationStudio_EditStart(") + picojson::value(data).serialize() + std::string(")");
        if(BrowserToolbox)
            BrowserToolbox->GetMainFrame()->ExecuteJavaScript(script,BrowserToolbox->GetMainFrame()->GetURL(), 0);
    }

    bool res4 = scenariov8handler->GetIsEditEnd();
    if(res4)
    {
        WORKER_LOG(std::string("EditEnd<<"));
        std::string script = std::string("BrowserAutomationStudio_EditEnd()");
        if(BrowserToolbox)
            BrowserToolbox->GetMainFrame()->ExecuteJavaScript(script,BrowserToolbox->GetMainFrame()->GetURL(), 0);
    }

    if(scenariov8handler->GetIsThreadNumberEditStart() && BrowserToolbox)
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript("BrowserAutomationStudio_ThreadNumberEdit()",BrowserToolbox->GetMainFrame()->GetURL(), 0);

    if(scenariov8handler->GetIsSuccessNumberEditStart() && BrowserToolbox)
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript("BrowserAutomationStudio_SuccessNumberEdit()",BrowserToolbox->GetMainFrame()->GetURL(), 0);

    if(scenariov8handler->GetIsFailNumberEditStart() && BrowserToolbox)
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript("BrowserAutomationStudio_FailNumberEdit()",BrowserToolbox->GetMainFrame()->GetURL(), 0);

    if(scenariov8handler->GetIsRunFunctionStart() && BrowserToolbox)
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript("BrowserAutomationStudio_RunFunction()",BrowserToolbox->GetMainFrame()->GetURL(), 0);

    ScenarioV8Handler::RestartType res3 = scenariov8handler->GetNeedRestart();

    if(res3 == ScenarioV8Handler::Restart)
        Restart();
    else if(res3 == ScenarioV8Handler::Stop)
        Terminate();

}

void MainApp::HandleToolboxBrowserEvents()
{
    std::pair<ToolboxV8Handler::ResultClass,bool> res = toolboxv8handler->GetResult();

    if(res.second)
    {
        if(BrowserScenario)
        {
            int id = std::rand();
            std::string scriptscenario;
            if(Layout->State == MainLayout::Ready)
            {
                if(res.first.Name.length() == 0 || res.first.Name.at(0) != '_')
                {
                    Layout->UpdateState(MainLayout::Hold);
                    std::string CodeSend;
                    if(res.first.HowToExecute != ToolboxV8Handler::OnlyAdd)
                    {
                        CodeSend += res.first.Code;
                    }
                    CodeSend += std::string(" \n section_end()!");
                    if(BrowserToolbox)
                        BrowserToolbox->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_ShowWaiting(") + picojson::value(CodeSend).serialize() + std::string(")"),BrowserToolbox->GetMainFrame()->GetURL(), 0);
                    xml_encode(CodeSend);
                    std::string DelayedSendCode = std::string("<Messages><WaitCode>") + CodeSend + std::string("</WaitCode></Messages>");
                    if(res.first.HowToExecute == ToolboxV8Handler::OnlyExecute)
                    {
                        SendTextResponce(DelayedSendCode);
                        DelayedSend.clear();
                    }
                    else
                        DelayedSend = DelayedSendCode;

                    scriptscenario += "BrowserAutomationStudio_RunningTask();";

                }
            }

            if(res.first.HowToExecute != ToolboxV8Handler::OnlyExecute)
            {
                std::string script = "BrowserAutomationStudio_AddTask(";
                std::string Name;
                if(res.first.HowToExecute == ToolboxV8Handler::OnlyAdd && res.first.DisableIfAdd)
                {
                    Name += "_";
                }
                Name += res.first.Name;
                script.append(picojson::value(Name).serialize());
                script.append(",");
                script.append(picojson::value(res.first.Code).serialize());
                script.append(",");
                script.append(std::to_string(id));
                script.append(");");
                WORKER_LOG(std::string("ScenarioExecuteCode<<") + script);
                scriptscenario += script;
            }

            if(!scriptscenario.empty())
                BrowserScenario->GetMainFrame()->ExecuteJavaScript(scriptscenario,BrowserScenario->GetMainFrame()->GetURL(), 0);
        }
    }

    if(toolboxv8handler->GetIsEditCancel())
    {
        std::string script = std::string("BrowserAutomationStudio_EditCancel()");
        WORKER_LOG("BrowserAutomationStudio_EditCancel<<");
        if(BrowserScenario)
            BrowserScenario->GetMainFrame()->ExecuteJavaScript(script,BrowserScenario->GetMainFrame()->GetURL(), 0);
    }

    if(toolboxv8handler->GetIsInterrupt())
    {
        WORKER_LOG("BrowserAutomationStudio_Interrupt<<");
        SendTextResponce("<Messages><Interrupt></Interrupt></Messages>");
    }

    if(toolboxv8handler->GetIsInitialized() && (ResourcesChanged))
    {
        std::string script = std::string("BrowserAutomationStudio_SetResources(") + picojson::value(Resources.data()).serialize() + "," + picojson::value(AdditionalResources.data()).serialize() + std::string(")");
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript(script,BrowserToolbox->GetMainFrame()->GetURL(), 0);
        ResourcesChanged = false;
    }

    if(toolboxv8handler->GetIsInitialized() && !Variables.empty())
    {
        std::string script = std::string("BrowserAutomationStudio_SetVariables(") + picojson::value(Variables.data()).serialize() + std::string(")");
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript(script,BrowserToolbox->GetMainFrame()->GetURL(), 0);
        Variables.clear();
    }

    if(toolboxv8handler->GetIsInitialized() && !Functions.empty())
    {
        std::string script = std::string("BrowserAutomationStudio_SetFunctions(") + picojson::value(Functions.data()).serialize() + std::string(")");
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript(script,BrowserToolbox->GetMainFrame()->GetURL(), 0);
        Functions.clear();
    }

    if(toolboxv8handler->GetIsMaximize())
    {
        if(BrowserToolbox)
        {
            Layout->MaximizeToolbox(GetData()->WidthBrowser,GetData()->HeightBrowser,GetData()->WidthAll,GetData()->HeightAll);
            BrowserToolbox->GetMainFrame()->ExecuteJavaScript("BrowserAutomationStudio_MaximizeCallback()",BrowserToolbox->GetMainFrame()->GetURL(), 0);

        }
    }

    if(toolboxv8handler->GetIsMinimize())
    {
        if(BrowserToolbox)
        {
            Layout->MinimizeToolbox(GetData()->WidthBrowser,GetData()->HeightBrowser,GetData()->WidthAll,GetData()->HeightAll);
        }
    }

    {
        std::pair<std::string, bool> res = toolboxv8handler->GetLoadUrl();
        if(res.second)
        {
            WORKER_LOG(std::string("LoadUrlFromUrlBrowser<<") + res.first);
            ShellExecute(0, 0, s2ws(res.first).c_str(), 0, 0 , SW_SHOW );
        }
    }

}

void MainApp::UpdateScrolls(std::string& data)
{
    std::string str = data;

    std::size_t pos = str.find(",");
    if(pos != std::string::npos)
    {
        std::string part = str.substr(0,pos);
        str = str.substr(pos + 1,str.length() - pos - 1);
        if(ExecuteFrameChain.empty())
            Data->ScrollX = std::stoi(part);
    }

    pos = str.find(",");
    if(pos != std::string::npos)
    {
        std::string part = str.substr(0,pos);
        str = str.substr(pos + 1,str.length() - pos - 1);
        if(ExecuteFrameChain.empty())
            Data->ScrollY = std::stoi(part);
    }
    data = str;
}


void MainApp::HandleFrameFindEvents()
{
    if(RunElementCommandCallbackOnNextTimer != -1)
        return;

    std::pair<InspectResult,bool> res = v8handler->GetFrameFindResult();
    bool success = true;

    if(res.second && !res.first.active && !IsLastCommandNull && ExecuteFrameSearching && LastCommand.CommandName == std::string("exist"))
    {
        IsLastCommandNull = true;
        v8handler->SetResultProcessed();
        std::string data = "0";
        FinishedLastCommand(data);
        return;
    }

    if(res.second && !res.first.active && !IsLastCommandNull && ExecuteFrameSearching && LastCommand.CommandName == std::string("script"))
    {
        IsLastCommandNull = true;
        v8handler->SetResultProcessed();
        std::string data = "";
        FinishedLastCommand(data);
        return;
    }

    if(res.second && !IsLastCommandNull && ExecuteFrameSearching)
    {
        success = false;
        if(res.first.active)
        {
            if(_HandlersManager->GetBrowser())
            {
                //WORKER_LOG(std::to_string(res.first.FrameData.is_frame));
                //WORKER_LOG(std::string(res.first.FrameData.frame_url));
                //WORKER_LOG(std::string(res.first.FrameData.frame_name));
                //WORKER_LOG(std::to_string(res.first.FrameData.frame_index));

                res.first.FrameData.frame_depth = ExecuteFrameChain.size() + 1;
                res.first.FrameData.parent_frame_id = -1;
                if(!ExecuteFrameChain.empty())
                    res.first.FrameData.parent_frame_id = ExecuteFrameChain.at(ExecuteFrameChain.size() - 1).FrameData.frame_id;

                int64 id = _HandlersManager->FindFrameId(res.first.FrameData);
                res.first.FrameData.frame_id = id;

                //WORKER_LOG(std::string("IDDDDDDDDDDDDDDDDDD") + std::to_string(id));

                if(id >= 0)
                {
                    ExecuteSearchCoordinatesX+=res.first.FrameData.x_with_padding;
                    ExecuteSearchCoordinatesY+=res.first.FrameData.y_with_padding;
                    //WORKER_LOG(std::string("ExecuteSearchCoordinatesX ") + std::to_string(ExecuteSearchCoordinatesX));


                    ExecuteFrameChain.push_back(res.first);
                    LastCommand.Path.erase(LastCommand.Path.begin(),LastCommand.Path.begin() + ExecuteFrameSearchingLength + 1);
                    ElementCommandCallback(LastCommand);
                    success = true;

                }
            }
        }
    }
    if(!success && !IsLastCommandNull)
    {
        RunElementCommandCallbackOnNextTimer = 100;
    }
}

void MainApp::HandleMainBrowserEvents()
{
    /*{
        std::pair<std::vector<LocalStorageDataItem>,bool> res = v8handler->GetLocalStorage();
        if(res.second)
        {
            LOCK_LOCAL_STORAGE
            for(LocalStorageDataItem Item:res.first)
                Data->_LocalStorageData.Set(Item);
        }
        if(res.second)
        {
            for(LocalStorageDataItem Item:res.first)
                _HandlersManager->UpdateLocalStorageItem(Item);
        }
    }*/

    std::pair<std::string,bool> res = v8handler->GetResult();
    if(res.second && IsLastCommandNull)
    {
        v8handler->SetResultProcessed();
        WORKER_LOG(std::string("CommandNull<<") + LastCommand.CommandName + std::string("<<") + std::to_string(LastCommand.StageId));
    }

    if(res.second && !IsLastCommandNull)
    {
        IsLastCommandNull = true;

        WORKER_LOG(std::string("Command<<") + LastCommand.CommandName + std::string("<<") + std::to_string(LastCommand.StageId) + std::string("<<") + res.first);

        if(res.first == "BAS_NOT_EXISTS")
        {
            RunElementCommandCallbackOnNextTimer = 100;
        }else if(ExecuteFrameScrollingSwitch)
        {
            UpdateScrolls(res.first);

            WORKER_LOG("Frame Scrolling Done");
            v8handler->SetResultProcessed();
            ElementCommandCallback(LastCommand);
            //RunElementCommandCallbackOnNextTimer = 100;

        }else  if(LastCommand.CommandName == std::string("_mouseclick") || LastCommand.CommandName == std::string("_mouseclickup") || LastCommand.CommandName == std::string("_mouseclickdown"))
        {


            UpdateScrolls(res.first);
            std::size_t pos = res.first.find(",");
            int x = -1, y = -1;
            if(pos != std::string::npos)
            {
                std::string x_string = res.first.substr(0,pos);
                std::string y_string = res.first.substr(pos + 1,res.first.length() - pos - 1);
                x = std::stoi(x_string);
                y = std::stoi(y_string);
            }

            if(!BrowserEventsEmulator::IsPointOnScreen(x,y,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser))
            {
                IsLastCommandNull = false;
            }else
            {
                int type = 0;
                std::string resp;
                if(LastCommand.CommandName == std::string("_mouseclickup"))
                {
                    type = 1;
                    resp = "<Messages><MouseClickUp></MouseClickUp></Messages>";
                }else if(LastCommand.CommandName == std::string("_mouseclickdown"))
                {
                    type = 2;
                    resp = "<Messages><MouseClickDown></MouseClickDown></Messages>";
                }else
                {
                    type = 0;
                    resp = "<Messages><MouseClick></MouseClick></Messages>";
                }

                v8handler->SetResultProcessed();
                BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
                BrowserEventsEmulator::MouseClick(_HandlersManager->GetBrowser(),x,y,GetScrollPosition(),type,Data->IsMousePress,Data->IsDrag);
                SendTextResponce(resp);
                WORKER_LOG(std::string("EVENTFLAG_LEFT_MOUSE_BUTTON>>"));
            }
        }else if(LastCommand.CommandName == std::string("_mousemove"))
        {
            UpdateScrolls(res.first);

            std::size_t pos = res.first.find(",");
            int x = -1, y = -1;
            if(pos != std::string::npos)
            {
                std::string x_string = res.first.substr(0,pos);
                std::string y_string = res.first.substr(pos + 1,res.first.length() - pos - 1);
                x = std::stoi(x_string);
                y = std::stoi(y_string);
            }
            MouseEndX = x - Data->ScrollX;
            MouseEndY = y - Data->ScrollY;
            if(!BrowserEventsEmulator::IsPointOnScreen(x,y,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser))
            {
                IsLastCommandNull = false;
            }else
            {
                v8handler->SetResultProcessed();
                BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
                IsMouseMoveSimulation = true;
                if(Settings->EmulateMouse())
                {
                    int t1,t2;
                    BrowserEventsEmulator::MouseMove(_HandlersManager->GetBrowser(), IsMouseMoveSimulation, MouseStartX, MouseStartY, MouseEndX, MouseEndY, t1, t2, 0, 0, 0, 0, 0, 0, true, true,Data->IsMousePress,Data->IsDrag);
                }
            }
        }else if(LastCommand.CommandName == std::string("_scroll"))
        {
            UpdateScrolls(res.first);

            /*std::size_t pos = res.first.find(",");
            int x = -1, y = -1;
            if(pos != std::string::npos)
            {
                std::string x_string = res.first.substr(0,pos);
                std::string y_string = res.first.substr(pos + 1,res.first.length() - pos - 1);
                x = std::stoi(x_string);
                y = std::stoi(y_string);
            }

            if(!BrowserEventsEmulator::IsPointOnScreen(x,y,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser))
            {
                IsLastCommandNull = false;
            }else
            {
                v8handler->SetResultProcessed();
                SendTextResponce("<Messages><Scroll></Scroll></Messages>");
            }*/

            v8handler->SetResultProcessed();
            SendTextResponce("<Messages><Scroll></Scroll></Messages>");


        }else if(LastCommand.CommandName == std::string("_render"))
        {
            UpdateScrolls(res.first);

            std::size_t pos = res.first.find(",");
            int x = -1, y = -1;
            if(pos != std::string::npos)
            {
                std::string x_string = res.first.substr(0,pos);
                std::string y_string = res.first.substr(pos + 1,res.first.length() - pos - 1);
                x = std::stoi(x_string);
                y = std::stoi(y_string);
            }
            x += ExecuteSearchCoordinatesX + Data->ScrollX;
            y += ExecuteSearchCoordinatesY + Data->ScrollY;

            //if(!BrowserEventsEmulator::IsPointOnScreen(x,y,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser))
            if(false)
            {
                IsLastCommandNull = false;
            }else
            {
                WORKER_LOG(std::string("Start Rendering screen>>"));

                v8handler->SetResultProcessed();
                RenderX = RenderX - Data->ScrollX;
                RenderY = RenderY - Data->ScrollY;
                IsElementRender = false;
                NeedRenderNextFrame = true;
                SkipBeforeRenderNextFrame = 10;
                if(_HandlersManager->GetBrowser())
                    _HandlersManager->GetBrowser()->GetHost()->Invalidate(PET_VIEW);
            }


        }else if(LastCommand.CommandName == std::string("random_point") && LastCommand.StageId == 0)
        {
            UpdateScrolls(res.first);

            v8handler->SetResultProcessed();
            LastCommand.StageId = 1;
            //WORKER_LOG("ExecuteSearchCoordinatesY");
            //WORKER_LOG(std::to_string(ExecuteSearchCoordinatesY));
            //WORKER_LOG(std::to_string(Data->ScrollY));

            std::string get_point;
            if(Settings->EmulateMouse())
            {
                get_point = std::string("var x=0;for(var i=0;i<10;i++){x+=Math.random()*((rect.right-2-rect.left+1)/10);};x=Math.floor(x)+rect.left+1;if(x>rect.right-1)x=rect.right-1;if(x<rect.left+1)x=rect.left+1;"
                                        "var y=0;for(var i=0;i<10;i++){y+=Math.random()*((rect.bottom-2-rect.top+1)/10);};y=Math.floor(y)+rect.top+1;if(y>rect.bottom-1)y=rect.bottom-1;if(y<rect.top+1)y=rect.top+1;");
            }else
            {
                get_point = std::string("var x=Math.floor((rect.right + rect.left)/2);"
                                        "var y=Math.floor((rect.bottom + rect.top)/2);");
            }
            std::string script = std::string("{"
                                 "var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");"
                                 "if(!el){browser_automation_studio_result('BAS_NOT_EXISTS');return;}"
                                 "var items=el.getClientRects();if(items.length == 0){browser_automation_studio_result('BAS_NOT_EXISTS');return;};"
                                 "var rect=items[Math.floor(Math.random()*items.length)];")
                                 + get_point +
                                 std::string("x+=") + std::to_string(ExecuteSearchCoordinatesX + Data->ScrollX) + std::string(";"
                                 "y+=") + std::to_string(ExecuteSearchCoordinatesY + Data->ScrollY) + std::string(";"
                                 "var res=x+','+y;"
                                 "browser_automation_studio_result(res);}");
            script = std::string("(function(){") + script + std::string("})()");



            //WORKER_LOG(std::string("EXEC11<<") + script);
            CefRefPtr<CefFrame> Frame;
            if(ExecuteFrameChain.empty())
                Frame = _HandlersManager->GetBrowser()->GetMainFrame();
            else
                Frame = _HandlersManager->GetBrowser()->GetFrame(ExecuteFrameChain.at(ExecuteFrameChain.size()-1).FrameData.frame_id);

            Frame->ExecuteJavaScript(script,Frame->GetURL(),1);

            IsLastCommandNull = false;


        }/*else if(LastCommand.CommandName == std::string("random_point") && LastCommand.StageId == 1)
        {
            std::size_t pos = res.first.find(",");
            int x = -1, y = -1;
            if(pos != std::string::npos)
            {
                std::string x_string = res.first.substr(0,pos);
                std::string y_string = res.first.substr(pos + 1,res.first.length() - pos - 1);
                x = std::stoi(x_string);
                y = std::stoi(y_string);
            }
            WORKER_LOG(std::string("Check<<") + std::to_string(x));
            if(!BrowserEventsEmulator::IsPointOnScreen(x,y,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser))
            {
                IsLastCommandNull = false;
            }else
            {
                v8handler->SetResultProcessed();
                std::string data = res.first;
                xml_encode(data);
                FinishedLastCommand(data);
                WORKER_LOG(std::string("ElementCommandCallback>>"));
            }
        }*/else if(LastCommand.CommandName == std::string("system_click") || LastCommand.CommandName == std::string("check") || LastCommand.CommandName == std::string("system_click_up") || LastCommand.CommandName == std::string("system_click_down"))
        {
            UpdateScrolls(res.first);

            std::size_t pos = res.first.find(",");
            int x = -1, y = -1;
            if(pos != std::string::npos)
            {
                std::string x_string = res.first.substr(0,pos);
                std::string y_string = res.first.substr(pos + 1,res.first.length() - pos - 1);
                x = std::stoi(x_string);
                y = std::stoi(y_string);
            }
            x += ExecuteSearchCoordinatesX + Data->ScrollX;
            y += ExecuteSearchCoordinatesY + Data->ScrollY;

            if(!BrowserEventsEmulator::IsPointOnScreen(x,y,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser))
            {
                IsLastCommandNull = false;
            }else
            {
                v8handler->SetResultProcessed();
                WORKER_LOG(std::string("system_click>>") + std::to_string(x) + std::string(">>") + std::to_string(y));

                int type = 0;
                if(LastCommand.CommandName == std::string("system_click_up"))
                {
                    type = 1;
                }else if(LastCommand.CommandName == std::string("system_click_down"))
                {
                    type = 2;
                }

                BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
                BrowserEventsEmulator::MouseClick(_HandlersManager->GetBrowser(),x,y,GetScrollPosition(),type,Data->IsMousePress,Data->IsDrag);
                FinishedLastCommand("");
            }
        }else if(LastCommand.CommandName == std::string("render_base64"))
        {
            UpdateScrolls(res.first);

            int left = -1, top = -1, right = -1, bottom = -1, centerx = -1, centery = -1;
            WORKER_LOG(std::string("render_base64<<") + res.first);

            std::string str = res.first;

            std::size_t pos = str.find(",");
            if(pos != std::string::npos)
            {
                std::string part = str.substr(0,pos);
                str = str.substr(pos + 1,str.length() - pos - 1);
                centerx = std::stoi(part);
            }

            pos = str.find(",");
            if(pos != std::string::npos)
            {
                std::string part = str.substr(0,pos);
                str = str.substr(pos + 1,str.length() - pos - 1);
                centery = std::stoi(part);
            }

            pos = str.find(",");
            if(pos != std::string::npos)
            {
                std::string part = str.substr(0,pos);
                str = str.substr(pos + 1,str.length() - pos - 1);
                left = std::stoi(part);
            }

            pos = str.find(",");
            if(pos != std::string::npos)
            {
                std::string part = str.substr(0,pos);
                str = str.substr(pos + 1,str.length() - pos - 1);
                top = std::stoi(part);
            }

            pos = str.find(",");
            if(pos != std::string::npos)
            {
                std::string part = str.substr(0,pos);
                str = str.substr(pos + 1,str.length() - pos - 1);
                right = std::stoi(part);
            }

            bottom = std::stoi(str);

            left += ExecuteSearchCoordinatesX;
            top += ExecuteSearchCoordinatesY;
            right += ExecuteSearchCoordinatesX;
            bottom += ExecuteSearchCoordinatesY;

            /*if(!BrowserEventsEmulator::IsPointOnScreen(left + Data->ScrollX,top + Data->ScrollY,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser)
                || !BrowserEventsEmulator::IsPointOnScreen(right + Data->ScrollX,bottom + Data->ScrollY,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser)*/
            if(false)
            {
                IsLastCommandNull = false;
            }else
            {
                WORKER_LOG("NeedRenderNextFrame");
                v8handler->SetResultProcessed();
                RenderX = left;
                RenderY = top;
                RenderWidth = right - left;
                RenderHeight = bottom - top;
                IsElementRender = true;
                NeedRenderNextFrame = true;
                SkipBeforeRenderNextFrame = 10;
                if(_HandlersManager->GetBrowser())
                    _HandlersManager->GetBrowser()->GetHost()->Invalidate(PET_VIEW);
            }
        }else if(LastCommand.CommandName == std::string("focus"))
        {
            UpdateScrolls(res.first);

            WORKER_LOG(std::string("focus1111<<") + res.first);
            v8handler->SetResultProcessed();
            std::string data = res.first;
            xml_encode(data);
            FinishedLastCommand(data);

        }else if(LastCommand.CommandName == std::string("move"))
        {
            UpdateScrolls(res.first);
            //WORKER_LOG(res.first);

            std::size_t pos = res.first.find(",");
            int x = -1, y = -1;
            if(pos != std::string::npos)
            {
                std::string x_string = res.first.substr(0,pos);
                std::string y_string = res.first.substr(pos + 1,res.first.length() - pos - 1);
                x = std::stoi(x_string);
                y = std::stoi(y_string);
            }
            x += ExecuteSearchCoordinatesX + Data->ScrollX;
            y += ExecuteSearchCoordinatesY + Data->ScrollY;

            if(!BrowserEventsEmulator::IsPointOnScreen(x,y,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser))
            {
                //WORKER_LOG("Failed to move");
                IsLastCommandNull = false;
            }else
            {
                v8handler->SetResultProcessed();
                WORKER_LOG(std::string("move>>") + std::to_string(x) + std::string(">>") + std::to_string(y));
                BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
                LastCommand.CommandName = "move";
                LastCommand.CommandParam1 = std::to_string(x);
                LastCommand.CommandParam2 = std::to_string(y);
                MouseStartX = Data->CursorX;
                MouseStartY = Data->CursorY;
                MouseEndX = x - Data->ScrollX;
                MouseEndY = y - Data->ScrollY;
                IsMouseMoveSimulation = true;
                if(Settings->EmulateMouse())
                {
                    int t1,t2;
                    BrowserEventsEmulator::MouseMove(_HandlersManager->GetBrowser(), IsMouseMoveSimulation, MouseStartX, MouseStartY, MouseEndX, MouseEndY, t1, t2, 0, 0, 0, 0, 0, 0, true,true,Data->IsMousePress,Data->IsDrag);
                }
            }

        }
        else if(LastCommand.CommandName == std::string("type") || LastCommand.CommandName == std::string("clear") || (LastCommand.CommandName == std::string("set") && LastCommand.StageId == 1 || LastCommand.CommandName == std::string("set_integer") && LastCommand.StageId == 1 || LastCommand.CommandName == std::string("set_random") && LastCommand.StageId == 1))
        {
            UpdateScrolls(res.first);

            WORKER_LOG(std::string("StartTyping<<"));

            if(res.first.length() == 0)
            {
                //Element not found
                v8handler->SetResultProcessed();
                FinishedLastCommand("");
            }else
            {
                BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
                std::size_t pos = res.first.find(",");
                int x = -1, y = -1;
                if(pos != std::string::npos)
                {
                    std::string x_string = res.first.substr(0,pos);
                    std::string y_string = res.first.substr(pos + 1,res.first.length() - pos - 1);
                    x = std::stoi(x_string);
                    y = std::stoi(y_string);
                }
                x += ExecuteSearchCoordinatesX + Data->ScrollX;
                y += ExecuteSearchCoordinatesY + Data->ScrollY;

                if(!BrowserEventsEmulator::IsPointOnScreen(x,y,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser))
                {
                    IsLastCommandNull = false;
                }else
                {
                    v8handler->SetResultProcessed();
                    TypeTextX = x;
                    TypeTextY = y;
                    TypeTextTaskIsActive = true;
                    TypeTextIsFirstLetter = true;
                    TypeTextState.Clear();
                    ExecuteTypeText();
                }
            }
        }else if(LastCommand.CommandName == std::string("set") && LastCommand.StageId == 0 || LastCommand.CommandName == std::string("set_integer") && LastCommand.StageId == 0 || LastCommand.CommandName == std::string("set_random") && LastCommand.StageId == 0)
        {
            UpdateScrolls(res.first);
            IsLastCommandNull = false;

            v8handler->SetResultProcessed();
            BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
            TypeText = res.first;
            TypeTextDelay = 30;
            LastCommand.StageId = 1;
            std::string script = std::string("(function(){var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");BrowserAutomationStudio_ScrollToElement(el)})()");
            if(!script.empty())
            {
                WORKER_LOG(std::string("EXEC<<") + script);
                CefRefPtr<CefFrame> Frame;
                if(ExecuteFrameChain.empty())
                    Frame = _HandlersManager->GetBrowser()->GetMainFrame();
                else
                    Frame = _HandlersManager->GetBrowser()->GetFrame(ExecuteFrameChain.at(ExecuteFrameChain.size()-1).FrameData.frame_id);

                Frame->ExecuteJavaScript(script,Frame->GetURL(),1);
            }
        }
        else
        {
            v8handler->SetResultProcessed();
            std::string data = res.first;
            xml_encode(data);
            FinishedLastCommand(data);
            WORKER_LOG(std::string("ElementCommandCallback>>"));
        }
    }

    std::pair<InspectResult,bool> res2 = v8handler->GetInspectResult();
    if(res2.second)
    {
        bool ShowInspectResults = false;
        if(!res2.first.FrameData.is_frame)
        {
            WORKER_LOG(std::string("not a frame"));

            //Not frame set result
            ShowInspectResults = true;
        }else
        {
            res2.first.FrameData.frame_depth = InspectFrameChain.size() + 1;

            WORKER_LOG(std::string("Inspect frame. frame_index<<") + std::to_string(res2.first.FrameData.frame_index) + std::string(" frame_name<<") + std::string(res2.first.FrameData.frame_name)+ std::string(" frame_depth<<") + std::to_string(res2.first.FrameData.frame_depth)+ std::string(" frame_url<<") + std::string(res2.first.FrameData.frame_url) );

            //It is Frame! Add to chain and inspect next
            int x = res2.first.FrameData.x_with_padding;
            int y = res2.first.FrameData.y_with_padding;
            for(InspectResult chain:InspectFrameChain)
            {
                x += chain.FrameData.x_with_padding;
                y += chain.FrameData.y_with_padding;
            }

            if(_HandlersManager->GetBrowser())
            {
                res2.first.FrameData.parent_frame_id = -1;
                if(!InspectFrameChain.empty())
                    res2.first.FrameData.parent_frame_id = InspectFrameChain.at(InspectFrameChain.size() - 1).FrameData.frame_id;
                int64 ID = _HandlersManager->FindFrameId(res2.first.FrameData);
                res2.first.FrameData.frame_id = ID;

                //WORKER_LOG(std::string("IDDDD ") + std::to_string(ID));
                if(ID < 0)
                {
                    //Frame not found
                    ShowInspectResults = true;
                }else
                {
                    InspectFrameChain.push_back(res2.first);

                    //WORKER_LOG(std::string("BrowserAutomationStudio_InspectElement <<") + std::to_string(InspectX - x) + std::string(" <<") + std::to_string(InspectY - y) );

                    _HandlersManager->GetBrowser()->GetFrame(ID)->ExecuteJavaScript(std::string("BrowserAutomationStudio_InspectElement(") + std::to_string(InspectX - x) + std::string(",") + std::to_string(InspectY - y) + std::string(")"),_HandlersManager->GetBrowser()->GetFrame(ID)->GetURL(), 0);
                }
            }

        }

        if(ShowInspectResults)
        {

            std::string label;
            std::string css;
            std::string css2;
            std::string css3;
            std::string match;
            std::string xpath;
            WORKER_LOG(std::string("End inspect ") +std::to_string(InspectFrameChain.size()) + " " + std::to_string(res2.first.active));

            if(!res2.first.active && InspectFrameChain.size() > 0)
            {
                res2.first = InspectFrameChain[InspectFrameChain.size() - 1];
                InspectFrameChain.pop_back();
            }

            for(InspectResult chain:InspectFrameChain)
            {
                res2.first.x += chain.FrameData.x_with_padding;
                res2.first.y += chain.FrameData.y_with_padding;
                label += chain.label + " >FRAME>";
                css += chain.css + " >FRAME>";
                css2 += chain.css2 + " >FRAME>";
                css3 += chain.css3 + " >FRAME>";
                match += chain.match + ">FRAME>";
                xpath += chain.xpath + " >FRAME>";
            }
            res2.first.label = label + res2.first.label;
            res2.first.css = css + res2.first.css;
            res2.first.css2 = css2 + res2.first.css2;
            res2.first.css3 = css3 + res2.first.css3;
            res2.first.match = match + res2.first.match;
            res2.first.xpath = xpath + res2.first.xpath;

            {
                LOCK_BROWSER_DATA
                Data->_Inspect = res2.first;
            }

            InspectFrameSearching = false;
        }


        RECT r = Layout->GetBrowserOuterRectangle(GetData()->WidthBrowser,GetData()->HeightBrowser,GetData()->WidthAll,GetData()->HeightAll);
        InvalidateRect(Data->_MainWindowHandle,&r,false);
    }

}

std::pair<int,int> MainApp::GetScrollPosition()
{
    std::pair<int,int> res;
    res.first = Data->ScrollX;
    res.second = Data->ScrollY;
    return res;
}


void MainApp::FinishedLastCommand(const std::string& data)
{
    SendTextResponce(std::string("<Messages><Element ID=\"") + LastCommand.CommandId + std::string("\"><") + LastCommand.CommandName + std::string(">") + data + std::string("</") + LastCommand.CommandName + ("></Element></Messages>"));
}

void MainApp::ExecuteMouseMove()
{
    if(!IsMouseMoveSimulation)
        return;
    if(!_HandlersManager->GetBrowser())
        return;

    int CursorX = Data->CursorX;
    int CursorY = Data->CursorY;

    if(Settings->EmulateMouse())
        BrowserEventsEmulator::MouseMove(_HandlersManager->GetBrowser(), IsMouseMoveSimulation, MouseStartX, MouseStartY, MouseEndX, MouseEndY , CursorX, CursorY, Speed, Data->WidthBrowser, Data->HeightBrowser, 6.0f, 2.5f, 0.0f, false, true,Data->IsMousePress,Data->IsDrag);
    else
        BrowserEventsEmulator::MouseMoveLine(_HandlersManager->GetBrowser(), IsMouseMoveSimulation, MouseStartX, MouseStartY, MouseEndX, MouseEndY , CursorX, CursorY, Speed, Data->WidthBrowser, Data->HeightBrowser,Data->IsMousePress,Data->IsDrag);
    Data->CursorX = CursorX;
    Data->CursorY = CursorY;

    RECT r = Layout->GetBrowserOuterRectangle(GetData()->WidthBrowser,GetData()->HeightBrowser,GetData()->WidthAll,GetData()->HeightAll);
    InvalidateRect(Data->_MainWindowHandle,&r,false);

    if(!IsMouseMoveSimulation)
    {
        if(LastCommand.CommandName == "move")
            FinishedLastCommand("");
        else
            SendTextResponce("<Messages><MouseMove></MouseMove></Messages>");
    }
}

void MainApp::ExecuteTypeText()
{
    if(!TypeTextTaskIsActive)
        return;
    clock_t CurrentTime = clock();
    if(!TypeTextIsFirstLetter && float( CurrentTime - TypeTextLastTime ) /  CLOCKS_PER_SEC < (float)TypeTextDelayCurrent / 1000.0f)
        return;
    TypeTextLastTime = CurrentTime;

    if(TypeTextIsFirstLetter)
    {
        BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
        BrowserEventsEmulator::MouseClick(_HandlersManager->GetBrowser(),TypeTextX,TypeTextY,GetScrollPosition(),0,Data->IsMousePress,Data->IsDrag);
        WORKER_LOG(std::string("TypeTextIsFirstLetter<<") + std::to_string(TypeTextX) + std::string("<<") + std::to_string(TypeTextY));
        TypeTextIsFirstLetter = false;
        if(TypeTextDelay == 0)
        {
            for(int i = 0;i<100;i++)
            {
                BrowserEventsEmulator::Key(_HandlersManager->GetBrowser(),TypeText,TypeTextState,Data->CursorX,Data->CursorY);
                if(TypeText.length() == 0 && TypeTextState.IsClear())
                {
                    TypeTextTaskIsActive = false;
                    FinishedLastCommand("");
                    return;
                }
            }
            return;
        }else
        {
            TypeTextDelayCurrent = TypeTextDelay + (rand()) % ((int)(TypeTextDelay * 1.6)) - (int)(TypeTextDelay * 0.8);
        }
        return;
    }

    if(TypeTextDelay == 0)
    {
        //Print all letters
        for(int i = 0;i<100;i++)
        {
            BrowserEventsEmulator::Key(_HandlersManager->GetBrowser(),TypeText,TypeTextState,Data->CursorX,Data->CursorY);
            if(TypeText.length() == 0 && TypeTextState.IsClear())
            {
                TypeTextTaskIsActive = false;
                FinishedLastCommand("");
                return;
            }
        }
        return;
    }else
    {
        //Print one letter
        BrowserEventsEmulator::Key(_HandlersManager->GetBrowser(),TypeText,TypeTextState,Data->CursorX,Data->CursorY);
        TypeTextDelayCurrent = TypeTextDelay + (rand()) % ((int)(TypeTextDelay * 1.6)) - (int)(TypeTextDelay * 0.8);
    }

    if(TypeText.length() == 0 && TypeTextState.IsClear())
    {
        TypeTextTaskIsActive = false;
        FinishedLastCommand("");
    }
}

void MainApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
    /*if(!frame->IsMain())
        return;*/


    //Toolbox Browser
    if(BrowserToolbox.get() && BrowserToolbox->GetIdentifier() == browser->GetIdentifier())
    {
        WORKER_LOG("OnContextCreated<<ToolboxBrowser");
        if(frame->IsMain())
            toolboxv8handler = new ToolboxV8Handler();
        CefRefPtr<CefV8Value> object = context->GetGlobal();
        object->SetValue("BrowserAutomationStudio_Append", CefV8Value::CreateFunction("BrowserAutomationStudio_Append", toolboxv8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_Initialized", CefV8Value::CreateFunction("BrowserAutomationStudio_Initialized", toolboxv8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_EditCancel", CefV8Value::CreateFunction("BrowserAutomationStudio_EditCancel", toolboxv8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_Maximize", CefV8Value::CreateFunction("BrowserAutomationStudio_Maximize", toolboxv8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_Minimize", CefV8Value::CreateFunction("BrowserAutomationStudio_Minimize", toolboxv8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_OpenUrl", CefV8Value::CreateFunction("BrowserAutomationStudio_OpenUrl", toolboxv8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_Interrupt", CefV8Value::CreateFunction("BrowserAutomationStudio_Interrupt", toolboxv8handler), V8_PROPERTY_ATTRIBUTE_NONE);

        object->SetValue("_K", CefV8Value::CreateString(Lang), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("_Z", CefV8Value::CreateInt(Settings->Zoom()), V8_PROPERTY_ATTRIBUTE_NONE);
        return;
    }

    //Scenario Browser
    if(BrowserScenario.get() && BrowserScenario->GetIdentifier() == browser->GetIdentifier())
    {
        WORKER_LOG("OnContextCreated<<BrowserScenario");
        CefRefPtr<CefV8Value> object = context->GetGlobal();
        if(frame->IsMain())
            scenariov8handler = new ScenarioV8Handler();
        object->SetValue("BrowserAutomationStudio_SendCode", CefV8Value::CreateFunction("BrowserAutomationStudio_SendCode", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_Initialized", CefV8Value::CreateFunction("BrowserAutomationStudio_Initialized", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_Execute", CefV8Value::CreateFunction("BrowserAutomationStudio_Execute", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_Restart", CefV8Value::CreateFunction("BrowserAutomationStudio_Restart", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_EditStart", CefV8Value::CreateFunction("BrowserAutomationStudio_EditStart", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_EditEnd", CefV8Value::CreateFunction("BrowserAutomationStudio_EditEnd", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_ThreadNumberEdit", CefV8Value::CreateFunction("BrowserAutomationStudio_ThreadNumberEdit", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_RunFunction", CefV8Value::CreateFunction("BrowserAutomationStudio_RunFunction", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_SuccessNumberEdit", CefV8Value::CreateFunction("BrowserAutomationStudio_SuccessNumberEdit", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_FailNumberEdit", CefV8Value::CreateFunction("BrowserAutomationStudio_FailNumberEdit", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_SetClipboard", CefV8Value::CreateFunction("BrowserAutomationStudio_SetClipboard", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_GetClipboard", CefV8Value::CreateFunction("BrowserAutomationStudio_GetClipboard", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("_K", CefV8Value::CreateString(Lang), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("_Z", CefV8Value::CreateInt(Settings->Zoom()), V8_PROPERTY_ATTRIBUTE_NONE);
        return;
    }

    //Central Browser
    if(BrowserCentral.get() && BrowserCentral->GetIdentifier() == browser->GetIdentifier())
    {
        WORKER_LOG("OnContextCreated<<BrowserCentral");
        CefRefPtr<CefV8Value> object = context->GetGlobal();
        if(frame->IsMain())
            central8handler = new CentralV8Handler();
        object->SetValue("BrowserAutomationStudio_OpenUrl", CefV8Value::CreateFunction("BrowserAutomationStudio_OpenUrl", central8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_Close", CefV8Value::CreateFunction("BrowserAutomationStudio_Close", central8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_SetOptions", CefV8Value::CreateFunction("BrowserAutomationStudio_SetOptions", central8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("_K", CefV8Value::CreateString(Lang), V8_PROPERTY_ATTRIBUTE_NONE);
        return;
    }



    //Main Browser
    //if(_HandlersManager->GetBrowser() && _HandlersManager->GetBrowser()->GetIdentifier() == browser->GetIdentifier())
    {
        WORKER_LOG(std::string("OnContextCreated<<MainBrowser<<") + std::to_string(browser->GetIdentifier()) + "<<" + std::to_string(frame->IsMain()) + "<<" + frame->GetURL().ToString());
        CefRefPtr<CefV8Value> object = context->GetGlobal();

        _HandlersManager->NewContextCreated(browser->GetIdentifier());

        {
            LOCK_V8_HANDLER
            if(!v8handler)
                v8handler = new V8Handler(Data);
            object->SetValue("browser_automation_studio_result", CefV8Value::CreateFunction("browser_automation_studio_result", v8handler), V8_PROPERTY_ATTRIBUTE_NONE);
            object->SetValue("browser_automation_studio_inspect_result", CefV8Value::CreateFunction("browser_automation_studio_inspect_result", v8handler), V8_PROPERTY_ATTRIBUTE_NONE);
            object->SetValue("browser_automation_studio_frame_find_result", CefV8Value::CreateFunction("browser_automation_studio_frame_find_result", v8handler), V8_PROPERTY_ATTRIBUTE_NONE);
            //object->SetValue("BrowserAutomationStudio_SaveLocalStorage", CefV8Value::CreateFunction("BrowserAutomationStudio_SaveLocalStorage", v8handler), V8_PROPERTY_ATTRIBUTE_NONE);
            object->SetValue("BrowserAutomationStudio_DomainDataNeedClear", CefV8Value::CreateFunction("BrowserAutomationStudio_DomainDataNeedClear", v8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        }

        JavaScriptExtensions extensions;
        std::string jscode;
        jscode += GetAllBrowserDataCode(GetData()->_ModulesData);

        {
            LOCK_BROWSER_DATA
            std::string UserAgent;
            std::string AcceptLanguage;

            for(std::shared_ptr<std::map<std::string,std::string> > HeadersMap: Data->_Headers.MatchAll(frame->GetURL().ToString(),_HandlersManager->FindTabIdByBrowserId(browser->GetIdentifier())))
            {
                for(const auto& Header: *HeadersMap)
                {
                    if(Header.first == "User-Agent")
                    {
                        UserAgent = Header.second;
                    }else if(Header.first == "Accept-Language")
                    {
                        AcceptLanguage = Header.second;
                    }
                }
            }
            if(!UserAgent.empty())
            {
                jscode += extensions.GetUserAgentExtension(UserAgent);
            }else
            {
                jscode += extensions.GetUserAgentEmptyExtension();
            }

            if(!AcceptLanguage.empty())
            {
                jscode += extensions.GetLanguage(AcceptLanguage);
            }else
            {
                jscode += extensions.GetEmptyLanguage();
            }

            //WORKER_LOG(std::string("Data->_NextReferrer") + Data->_NextReferrer + "; " + frame->GetURL().ToString());

            if(!frame->GetURL().ToString().empty())
            {
                if(!Data->_NextReferrer.empty())
                {
                    jscode += extensions.GetReferrerExtension(Data->_NextReferrer);
                }else
                {
                    jscode += extensions.GetReferrerEmptyExtension();
                }
                Data->_NextReferrer.clear();
            }
        }

        {
            LOCK_BROWSER_DATA
            std::string StartupScript = Data->_StartupScript.Match(frame->GetURL().ToString(),_HandlersManager->FindTabIdByBrowserId(browser->GetIdentifier()));
            if(!StartupScript.empty())
            {
                if(!jscode.empty())
                    jscode += ";";
                jscode += "try{";
                jscode += StartupScript;
                jscode += "}catch(e){};";
            }

        }

        /*{
            LOCK_LOCAL_STORAGE
            if(!jscode.empty())
                jscode += ";";
            jscode += "try{";
            jscode += "BrowserAutomationStudio_RestoreLocalStorage(";
            jscode += picojson::value(Data->_LocalStorageData.Get()).serialize();
            jscode += ");";
            jscode += "}catch(e){};";
        }*/

        {
            LOCK_TIMEZONE
            if(Data->TimezoneSelected)
            {
                if(!jscode.empty())
                    jscode += ";";
                jscode += "try{";
                jscode += "BrowserAutomationStudio_SetTimezone(";
                jscode += picojson::value(std::to_string(Data->Timezone)).serialize();
                jscode += ");";
                jscode += "}catch(e){};";
            }else
            {
                if(!jscode.empty())
                    jscode += ";";
                jscode += "try{";
                jscode += "BrowserAutomationStudio_TimezoneRestore();";
                jscode += "}catch(e){};";
            }
        }

        {
            LOCK_GEOLOCATION
            if(Data->GeolocationSelected)
            {
                if(!jscode.empty())
                    jscode += ";";
                jscode += "try{";
                jscode += "BrowserAutomationStudio_SetGeolocation(";
                jscode += picojson::value(std::to_string(Data->Latitude)).serialize();
                jscode += ",";
                jscode += picojson::value(std::to_string(Data->Longitude)).serialize();
                jscode += ");";
                jscode += "}catch(e){};";
            }else
            {
                if(!jscode.empty())
                    jscode += ";";
                jscode += "try{";
                jscode += "BrowserAutomationStudio_GeolocationRestore();";
                jscode += "}catch(e){};";
            }
        }

        if(!jscode.empty())
        {
            CefRefPtr<CefV8Value> retval;
            CefRefPtr<CefV8Exception> exc;
            context->Eval(jscode + ";0;",retval,exc);
            //frame->ExecuteJavaScript(jscode, frame->GetURL(), NULL);
        }
        if(frame->IsMain())
        {
            Data->ScrollX = 0;
            Data->ScrollY = 0;
        }
    }
}

void MainApp::OnWebKitInitialized()
{
    WORKER_LOG(std::string("OnWebKitInitialized>>"));

    JavaScriptExtensions extensions;
    std::string extensionCode = extensions.GetBasicExtension(Data->IsRecord);
    CefRegisterExtension("v8/browser_automation_studio", extensionCode, NULL);
}

void MainApp::ScrollUp()
{
    if(_HandlersManager->GetBrowser())
    {
        KeyState TypeTextState;
        std::string KeyText = "<MOUSESCROLLUP>";
        BrowserEventsEmulator::Key(_HandlersManager->GetBrowser(),KeyText,TypeTextState,Data->CursorX,Data->CursorY);
    }
}
void MainApp::ScrollDown()
{
    if(_HandlersManager->GetBrowser())
    {
        KeyState TypeTextState;
        std::string KeyText = "<MOUSESCROLLDOWN>";

        BrowserEventsEmulator::Key(_HandlersManager->GetBrowser(),KeyText,TypeTextState,Data->CursorX,Data->CursorY);
    }
}
void MainApp::ScrollLeft()
{
    if(_HandlersManager->GetBrowser())
        _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript("BrowserAutomationStudio_ScrollLeft()",_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);
}
void MainApp::ScrollRight()
{
    if(_HandlersManager->GetBrowser())
        _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript("BrowserAutomationStudio_ScrollRight()",_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);
}

void MainApp::EmulateClick(int x, int y)
{
    if(BrowserToolbox)
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_Click(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(")"),BrowserToolbox->GetMainFrame()->GetURL(), 0);
}

void MainApp::EmulateMove(int x, int y)
{
    if(BrowserToolbox)
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_Move(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(")"),BrowserToolbox->GetMainFrame()->GetURL(), 0);
}

void MainApp::EmulateDrag(int x, int y)
{
    if(BrowserToolbox)
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_Drag(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(")"),BrowserToolbox->GetMainFrame()->GetURL(), 0);
}

void MainApp::EmulateDrop(int x, int y)
{
    if(BrowserToolbox)
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_Drop(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(")"),BrowserToolbox->GetMainFrame()->GetURL(), 0);
}

void MainApp::EmulateMoveAndClick(int x, int y)
{
    if(BrowserToolbox)
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_MoveAndClick(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(")"),BrowserToolbox->GetMainFrame()->GetURL(), 0);
}

void MainApp::AddTab()
{
    if(BrowserToolbox)
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_AddTab()"),BrowserToolbox->GetMainFrame()->GetURL(), 0);
}

void MainApp::SelectTab(int i)
{
    if(BrowserToolbox)
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_SelectTab(") + std::to_string(i) + std::string(")"),BrowserToolbox->GetMainFrame()->GetURL(), 0);
}

void MainApp::CloseTab(int i)
{
    if(BrowserToolbox)
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_CloseTab(") + std::to_string(i) + std::string(")"),BrowserToolbox->GetMainFrame()->GetURL(), 0);
}

void MainApp::Terminate()
{
    SendTextResponce("<Messages><Terminate/></Messages>");
}

void MainApp::Restart()
{
    SendTextResponce("<Messages><Restart/></Messages>");
}

//Element Subtasks

void MainApp::ExecuteElementFunction(const std::string& FuncName)
{
    if(BrowserToolbox)
    {
        std::string serialize;
        {
            LOCK_BROWSER_DATA
            serialize = Data->_Inspect.Serialize();
        }
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_") + FuncName + std::string("(") + serialize + std::string(",0)"),BrowserToolbox->GetMainFrame()->GetURL(), 0);
    }
}

void MainApp::ExecuteElementLoopFunction(const std::string& FuncName)
{
    if(BrowserToolbox)
    {
        std::string serialize;
        {
            LOCK_BROWSER_DATA
            serialize = Data->_Inspect.Serialize();
        }
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_") + FuncName + std::string("(") + serialize + std::string(",1)"),BrowserToolbox->GetMainFrame()->GetURL(), 0);
    }
}

void MainApp::LoadSettingsPage()
{
    if(BrowserCentral)
    {
        std::string page = std::string("file:///html/central/index_settings.html?d=") + CefURIEncode(Settings->Serialize(),true).ToString();
        BrowserCentral->GetMainFrame()->LoadURL(page);
        Layout->ShowCentralBrowser(true);
    }

}
