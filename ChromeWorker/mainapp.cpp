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
#include "include/wrapper/cef_helpers.h"
#include "xml_encoder.h"
#include "lodepng.h"
#include "multithreading.h"
#include "modulesdata.h"
#include "readallfile.h"
#include "toolboxpreprocessor.h"

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
    TypeTextLastTime = 0;
    LastMouseTrack = 0;
    ImageWidth = 0;
    ImageHeight = 0;
    ParentWidth = 0;
    ParentHeight = 0;
    App = this;
    IsMouseMoveSimulation = false;
    NeedRenderNextFrame = false;
    Speed = 15.0f;
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
                            std::bind(&MainApp::Paint,this,_1,_2,_3));

    _HandlersManager->GetHandler()->SetSettings(Settings);
    _HandlersManager->GetHandler()->SetData(Data);

    dhandler = new DevToolsHandler();
    dhandler->SetData(Data);
    dhandler->SetLayout(Layout);
    dhandler->SetHandlersManager(_HandlersManager.get());
    cookievisitor = new CookieVisitor();
}

void MainApp::Paint(char * data, int width, int height)
{
    if(NeedRenderNextFrame)
    {
        NeedRenderNextFrame = false;
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
            worker_log(std::string("Render result element <<") + base64);
            FinishedLastCommand(base64);
        }
        else
        {
            worker_log(std::string("Render result screen <<") + base64);

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
    worker_log(std::string("UrlLoaded<<") + url + std::string("<<") + std::to_string(status));
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
        worker_log(std::string("LoadCallback use old ") + page);
        CefRefPtr< CefFrame > Frame = _HandlersManager->GetBrowser()->GetMainFrame();
        Frame->LoadURL(page);
    }
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
    worker_log("ResetCallback");
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

        //Headers
        Data->_Headers.clear();

        //Resolution
        Data->WidthBrowser = 1024;
        Data->HeightBrowser = 600;
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
    worker_log("GetCookiesForUrlCallback");
    std::string cookies;
    if(_HandlersManager->GetBrowser())
    {
        CefRefPtr<CefCookieManager> CookieManager = CefCookieManager::GetGlobalManager(NULL);
        CefCookie cookie = CookieVisitor::GetEmptyCookie();
        bool CookieSet = CookieManager->SetCookie("http://basnotcorrecturl.com",cookie,0);
        worker_log(std::string("Empty cookie set<<") + std::to_string(CookieSet));
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
    worker_log("GetCookiesForUrlCompleteCallback");
    std::string cookies = cookievisitor->GetBuffer();
    xml_encode(cookies);
    SendTextResponce(std::string("<Messages><GetCookiesForUrl>") + cookies + std::string("</GetCookiesForUrl></Messages>"));
}

void MainApp::SaveCookiesCallback()
{
    worker_log("SaveCookiesCallback");
    std::string cookies;
    if(_HandlersManager->GetBrowser())
    {
        CefRefPtr<CefCookieManager> CookieManager = CefCookieManager::GetGlobalManager(NULL);
        CefCookie cookie = CookieVisitor::GetEmptyCookie();
        bool CookieSet = CookieManager->SetCookie("http://basnotcorrecturl.com",cookie,0);
        worker_log(std::string("Empty cookie set<<") + std::to_string(CookieSet));
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
    worker_log("SaveCookiesCompleteCallback");
    std::string cookies = cookievisitor->GetBuffer();
    xml_encode(cookies);
    SendTextResponce(std::string("<Messages><SaveCookies>") + cookies + std::string("</SaveCookies></Messages>"));
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

            worker_log(std::to_string(CookieManager->SetCookie("http://" + url,cookie,NULL)));
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
    worker_log(std::string("SetWindowCallback<<") + Window);
    Data->_ParentWindowHandle = (HWND)std::stoi(Window);
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
    worker_log("MouseClickCallback");
    if(_HandlersManager->GetBrowser())
    {
        BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
        LastCommand.CommandName = "_mouseclick";
        LastCommand.CommandParam1 = std::to_string(x);
        LastCommand.CommandParam2 = std::to_string(y);
        IsLastCommandNull = false;
        _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_ScrollTo(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(")"),_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);
    }else
    {
        SendTextResponce("<Messages><MouseClick></MouseClick></Messages>");
    }
}

void MainApp::MouseMoveCallback(int x, int y)
{
    worker_log(std::string("MouseMoveCallback<<") + std::to_string(x) + std::string("<<") + std::to_string(y));
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
        _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_ScrollTo(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(")"),_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);


    }else
    {
        SendTextResponce("<Messages><MouseMove></MouseMove></Messages>");
    }
}

void MainApp::ScrollCallback(int x, int y)
{
    worker_log(std::string("ScrollCallback<<x<<") + std::to_string(x) + std::string("<<y<<") + std::to_string(y));
    if(_HandlersManager->GetBrowser())
    {
        BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
        LastCommand.CommandName = "_scroll";
        LastCommand.CommandParam1 = std::to_string(x);
        LastCommand.CommandParam2 = std::to_string(y);
        IsLastCommandNull = false;
        _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_ScrollTo(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(")"),_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);
    }else
    {
        SendTextResponce("<Messages><Scroll></Scroll></Messages>");
    }
}

void MainApp::RenderCallback(int x, int y, int width, int height)
{
    worker_log(std::string("RenderCallback<<x<<") + std::to_string(x) + std::string("<<y<<") + std::to_string(y) + std::string("<<width<<") + std::to_string(width) + std::string("<<height<<") + std::to_string(height));
    if(_HandlersManager->GetBrowser())
    {
        BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
        LastCommand.CommandName = "_render";
        RenderX = x;
        RenderY = y;
        RenderWidth = width;
        RenderHeight = height;

        IsLastCommandNull = false;
        _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_ScrollTo(") + std::to_string(x + width/2) + std::string(",") + std::to_string(y + width/2) + std::string(")"),_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);
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
    Layout->ScenarioHandle = BrowserScenario->GetHost()->GetWindowHandle();

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
        worker_log(tab_string + s.ToString()+ std::string("<<") + std::to_string(Dictionary->GetValue(s)->GetType()));
        switch(Dictionary->GetValue(s)->GetType())
        {
            case VTYPE_BOOL:
                worker_log(tab_string + std::string("   ") + std::to_string(Dictionary->GetValue(s)->GetBool()));break;
            case VTYPE_INT:
                worker_log(tab_string + std::string("   ") + std::to_string(Dictionary->GetValue(s)->GetInt()));break;
            case VTYPE_DOUBLE:
                worker_log(tab_string + std::string("   ") + std::to_string(Dictionary->GetValue(s)->GetDouble()));break;
            case VTYPE_DICTIONARY:
                PrintDictionary(Dictionary->GetValue(s)->GetDictionary(),tab + 3);break;
            case VTYPE_STRING:
                worker_log(tab_string + std::string("   ") + Dictionary->GetValue(s)->GetString().ToString());break;
        }
    }
}*/


void MainApp::AfterReadyToCreateBrowser(bool Reload)
{
    worker_log(std::string("LoadCallback create new ") + NextLoadPage);

    CefWindowInfo window_info;

    window_info.SetAsWindowless(0,true);

    CefBrowserSettings browser_settings;
    browser_settings.windowless_frame_rate = 5;

    std::string encoding("utf-8");
    std::wstring wencoding = s2ws(encoding);
    cef_string_utf16_set(wencoding.data(),wencoding.size(),&browser_settings.default_encoding,true);

    //CefRequestContextSettings settings;
    //CefRefPtr<CefRequestContext> Context = CefRequestContext::CreateContext(settings,NULL);
    CefRefPtr<CefRequestContext> Context = CefRequestContext::GetGlobalContext();

    {
        CefRefPtr<CefValue> Value = CefValue::Create();
        CefRefPtr<CefDictionaryValue> Dictionary = CefDictionaryValue::Create();

        worker_log("System Proxy");
        Dictionary->SetString("mode","direct");

        CefString Error;
        Value->SetDictionary(Dictionary);
        Context->SetPreference("proxy",Value,Error);
        worker_log(std::string("Error setting proxy<<") + Error.ToString());

    }

    //PrintDictionary(Context->GetAllPreferences(true),3);

    if(Reload || !_HandlersManager->GetBrowser())
    {
        worker_log("!!!CREATENEWBROWSER!!!");
        _HandlersManager->Init2(CefBrowserHost::CreateBrowserSync(window_info, _HandlersManager->GetHandler(), NextLoadPage, browser_settings, Context));

        Layout->BrowserHandle = _HandlersManager->GetBrowser()->GetHost()->GetWindowHandle();
        //ToggleDevTools();
        CreateTooboxBrowser();
        CreateScenarioBrowser();
    }else
    {
        worker_log("!!!OPTIMIZEDRELOAD!!!");
        _HandlersManager->GetBrowser()->GetMainFrame()->LoadURL(NextLoadPage);
    }
}

void MainApp::VisibleCallback(bool visible)
{
    worker_log(std::string("VisibleCallback ") + std::to_string(visible));
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
    worker_log("ToggleDevTools");
    if(!_HandlersManager->GetBrowser())
        return;
    if(!Data->IsRecord)
        return;

    dhandler->OpenDevTools();
}

void MainApp::InspectAt(int x, int y)
{
    worker_log(std::string("Inspect At<<") + std::to_string(x) + std::string("<<") + std::to_string(y));
    if(!_HandlersManager->GetBrowser())
        return;

    dhandler->OpenDevTools(CefPoint(x,y));
}

void MainApp::MouseMoveAt(int x, int y)
{
    clock_t CurrentTime = clock();
    if(float( CurrentTime - LastMouseTrack ) /  CLOCKS_PER_SEC < 0.1)
        return;

    LastMouseTrack = CurrentTime;
    if(_HandlersManager->GetBrowser())
        _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_InspectElement(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(")"),_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);
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

void MainApp::SetProxyCallback(const std::string& server, int Port, bool IsHttp, const std::string& username, const std::string& password)
{
    ProxyData NewProxy;
    worker_log(std::string("SetProxyCallback ") + server + std::string(" ") + std::to_string(Port));
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
        Data->_Proxy = NewProxy;
    }
    SendTextResponce("<Messages><SetProxy></SetProxy></Messages>");
}

void MainApp::AddHeaderCallback(const std::string& key,const std::string& value)
{
    /*if(value.empty())
        Data->Headers.erase(key);
    else*/
    {
        LOCK_BROWSER_DATA
        Data->_Headers[key] = value;
    }
    SendTextResponce("<Messages><AddHeader></AddHeader></Messages>");
}

void MainApp::SetUserAgentCallback(const std::string& value)
{
    {
        LOCK_BROWSER_DATA
        if(value.empty())
            Data->_Headers.erase("User-Agent");
        else
            Data->_Headers["User-Agent"] = value;
    }
    SendTextResponce("<Messages><SetUserAgent>1</SetUserAgent></Messages>");
}

void MainApp::CleanHeaderCallback()
{
    {
        LOCK_BROWSER_DATA
        Data->_Headers.clear();
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
    worker_log(std::string("AddCacheMaskAllowCallback<<") + value);
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
    worker_log(std::string("AddCacheMaskDenyCallback<<") + value);
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
    worker_log(std::string("AddRequestMaskAllowCallback<<") + value);
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
    worker_log(std::string("AddRequestMaskDenyCallback<<") + value);
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
    worker_log(std::string("ClearCacheMaskCallback<<"));
    {
        LOCK_BROWSER_DATA
        Data->_CacheMask.clear();
    }
    SendTextResponce("<Messages><ClearCacheMask/></Messages>");
}
void MainApp::ClearRequestMaskCallback()
{
    worker_log(std::string("ClearRequestMaskCallback<<"));
    {
        LOCK_BROWSER_DATA
        Data->_RequestMask.clear();
    }
    SendTextResponce("<Messages><ClearRequestMask/></Messages>");
}
void MainApp::ClearLoadedUrlCallback()
{
    worker_log(std::string("ClearLoadedUrlCallback<<"));
    {
        LOCK_BROWSER_DATA
        Data->_LoadedUrls.clear();
    }
    SendTextResponce("<Messages><ClearLoadedUrl/></Messages>");
}
void MainApp::ClearCachedDataCallback()
{
    worker_log(std::string("ClearCachedDataCallback<<"));\
    {
        LOCK_BROWSER_DATA
        Data->_CachedData.clear();
    }
    SendTextResponce("<Messages><ClearCachedData/></Messages>");
}
void MainApp::ClearAllCallback()
{
    worker_log(std::string("ClearAllCallback<<"));
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
    worker_log(std::string("ClearMasksCallback<<"));
    {
        LOCK_BROWSER_DATA
        Data->_CacheMask.clear();
        Data->_RequestMask.clear();
    }
    SendTextResponce("<Messages><ClearMasks/></Messages>");
}
void MainApp::ClearDataCallback()
{
    worker_log(std::string("ClearDataCallback<<"));
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
    if(BrowserScenario)
        BrowserScenario->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_NotRunningTask(") + std::to_string(Id) + std::string(")"),BrowserScenario->GetMainFrame()->GetURL(), 0);

    Layout->UpdateTabs();
}

void MainApp::ScriptFinishedCallback()
{
    worker_log("ScriptFinishedCallback");
    Layout->UpdateState(MainLayout::Finished);
    if(BrowserScenario)
        BrowserScenario->GetMainFrame()->ExecuteJavaScript("BrowserAutomationStudio_RunningTask()",BrowserScenario->GetMainFrame()->GetURL(), 0);
    Hide();
}

void MainApp::FindCacheByMaskBase64Callback(const std::string& value)
{
    worker_log(std::string("FindCacheByMaskBase64Callback<<") + value);
    std::string res = "";
    {
        LOCK_BROWSER_DATA
        for(std::pair<std::string, std::shared_ptr<std::vector<char> > > pair:Data->_CachedData)
        {
            if(match(value,pair.first))
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
    worker_log(std::string("FindStatusByMaskCallback<<") + value);
    std::string res = "0";
    {
        LOCK_BROWSER_DATA
        for(std::pair<std::string, int> url:Data->_LoadedUrls)
        {
            if(match(value,url.first))
            {
                res = std::to_string(url.second);
                break;
            }
        }
    }
    SendTextResponce(std::string("<Messages><FindStatusByMask>") + res + ("</FindStatusByMask></Messages>"));
}
void MainApp::FindCacheByMaskStringCallback(const std::string& value)
{
    worker_log(std::string("FindCacheByMaskStringCallback<<") + value);
    std::string res = "";
    {
        LOCK_BROWSER_DATA
        for(std::pair<std::string, std::shared_ptr<std::vector<char> > > pair:Data->_CachedData)
        {
            if(match(value,pair.first))
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
    worker_log(std::string("IsUrlLoadedByMaskCallback<<") + value);
    std::string res = "0";
    {
        LOCK_BROWSER_DATA
        for(std::pair<std::string, int> url:Data->_LoadedUrls)
        {
            if(match(value,url.first))
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

void MainApp::SetInitialStateCallback(const std::string & lang, int IsVisible)
{
    Lang = lang;
}

void MainApp::ElementCommandCallback(const ElementCommand &Command)
{
    worker_log(std::string("ElementCommandCallback<<"));
    LastCommand = Command;
    IsLastCommandNull = false;
    if(_HandlersManager->GetBrowser())
    {
        std::string script;
        if(Command.CommandName == "xml")
        {
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");var res = '';if(el){res = el.outerHTML}browser_automation_studio_result(res);}");
        }else if(Command.CommandName == "text")
        {
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");var res = '';try{if(el){if(el.tagName.toLowerCase()=='input'||el.tagName.toLowerCase()=='textarea')res=el.value;else res=el.textContent}}catch(e){}browser_automation_studio_result(res);}");
        }else if(Command.CommandName == "script")
        {
            std::string script_escaped = picojson::value(LastCommand.CommandParam1).serialize();
            script = std::string("{var self = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");var obj=null;try{obj = eval(") + script_escaped + std::string(");}catch(e){}var res='';if(typeof(obj)!='undefined'&&obj !== null){res=obj.toString()}browser_automation_studio_result(res);}");
        }else if(Command.CommandName == "click")
        {
            BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(el)el.click();browser_automation_studio_result('');}");
        }else if(Command.CommandName == "system_click" || Command.CommandName == "check" || Command.CommandName == "focus")
        {
            if(Command.CommandName == std::string("focus") && LastCommand.Path.size() == 0)
            {
                FinishedLastCommand("");
                return;
            }else
            {
                script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(el){var rect = el.getBoundingClientRect();BrowserAutomationStudio_ScrollToRelative(rect.left + rect.width/2,rect.top + rect.height/2);}else browser_automation_studio_result('');}");
            }
        }else if(Command.CommandName == "move")
        {
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(el){var rect = el.getBoundingClientRect();BrowserAutomationStudio_ScrollToRelative(rect.left + rect.width/2,rect.top + rect.height/2);}else browser_automation_studio_result('');}");
        }else if(Command.CommandName == "fill")
        {
            BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
            std::string text_escaped = picojson::value(LastCommand.CommandParam1).serialize();
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(el){el.value = ") + text_escaped + std::string("};browser_automation_studio_result('');}");
        }else if(Command.CommandName == "type")
        {
            BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
            TypeText = LastCommand.CommandParam1;
            TypeTextDelay = std::stoi(LastCommand.CommandParam2);
            if(LastCommand.Path.size()>0)
            {
                script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(el){var rect = el.getBoundingClientRect();BrowserAutomationStudio_ScrollToRelative(rect.left + rect.width/2,rect.top + rect.height/2);}else browser_automation_studio_result('');}");
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
                script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(el){var rect = el.getBoundingClientRect();BrowserAutomationStudio_ScrollToRelative(rect.left + rect.width/2,rect.top + rect.height/2);}else browser_automation_studio_result('');}");
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
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(el)el.submit();browser_automation_studio_result('');}");
        }else if(Command.CommandName == "style")
        {
            std::string style_escaped = picojson::value(LastCommand.CommandParam1).serialize();
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");var res='';if(el)res=window.getComputedStyle(el)[") + style_escaped + std::string("];browser_automation_studio_result(res);}");
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
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");var keys='';if(el){") + proc + std::string("}browser_automation_studio_result(keys);}");

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
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");var keys='';if(el){") + proc + std::string("}browser_automation_studio_result(keys);}");

        }else if(Command.CommandName == "set_random")
        {
            LastCommand.StageId = 0;
            std::string proc = std::string("{var option_list = el.querySelectorAll(\"option\");"
                    "keys = \"<HOME>\";"
                    "for(var i = 0;i<option_list.length;i++)"
                    "{"
                      "var option = option_list.item(i);"
                      "var index = Math.floor((Math.random() * option_list.length));"
                      "if(i === index)break;"
                      "keys += \"<<DOWN>>\";"
                    "}"
                    "keys += \"<<RETURN>>\";}"
                     );
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");var keys='';if(el){") + proc + std::string("}browser_automation_studio_result(keys);}");
        }else if(Command.CommandName == "attr")
        {
            std::string attr_escaped = picojson::value(LastCommand.CommandParam1).serialize();
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");var res='';var attr=") + attr_escaped + std::string(";if(el){if(el.hasAttribute(attr))res=el.getAttribute(attr);}browser_automation_studio_result(res);}");
        }else if(Command.CommandName == "set_attr")
        {
            std::string attr_escaped = picojson::value(LastCommand.CommandParam1).serialize();
            std::string val_escaped = picojson::value(LastCommand.CommandParam2).serialize();
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");var attr=") + attr_escaped + std::string(";var val=") + val_escaped + std::string(";if(el){if(val.length === 0)el.removeAttribute(attr);else el.setAttribute(attr,val);}browser_automation_studio_result('');}");
        }else if(Command.CommandName == "length")
        {
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");var res = '';if(el){res = el.length;}browser_automation_studio_result(res);}");
        }else if(Command.CommandName == "render_base64")
        {
            script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(el){var rect = el.getBoundingClientRect();BrowserAutomationStudio_ScrollToRelative(rect.left + rect.width/2,rect.top + rect.height/2, el);}else browser_automation_studio_result('');}");
        }
        if(!script.empty())
        {
            worker_log(std::string("EXEC<<") + script);
            if(Command.FrameId.empty())
                _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript(script.c_str(),_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);
            else
            {
                std::vector<int64> identifiers;
                _HandlersManager->GetBrowser()->GetFrameIdentifiers(identifiers);

                bool done = false;
                for(int64 id:identifiers)
                {
                    if(match(Command.FrameId,_HandlersManager->GetBrowser()->GetFrame(id)->GetURL().ToString()))
                    {
                        worker_log(std::string("ExecutingInFrame<<") + _HandlersManager->GetBrowser()->GetFrame(id)->GetURL().ToString());
                        _HandlersManager->GetBrowser()->GetFrame(id)->ExecuteJavaScript(script.c_str(),_HandlersManager->GetBrowser()->GetFrame(id)->GetURL(), 0);
                        done = true;
                        break;
                    }
                }
                if(!done)
                {
                    SendTextResponce(std::string("<Messages><Element ID=\"") + Command.CommandId + std::string("\"><") + Command.CommandName + std::string(">") + std::string("</") + Command.CommandName + ("></Element></Messages>"));
                    worker_log(std::string("ElementCommandCallbackDefault>>FailedToFindFrame"));
                }

            }
        }
    }else
    {
        SendTextResponce(std::string("<Messages><Element ID=\"") + Command.CommandId + std::string("\"><") + Command.CommandName + std::string(">") + std::string("</") + Command.CommandName + ("></Element></Messages>"));
        worker_log(std::string("ElementCommandCallbackDefault>>"));
    }
}

void MainApp::Timer()
{
    ExecuteTypeText();

    ExecuteMouseMove();

    {
        LOCK_V8_HANDLER
        if(v8handler)
            HandleMainBrowserEvents();
    }

    if(toolboxv8handler)
        HandleToolboxBrowserEvents();

    if(scenariov8handler)
        HandleScenarioBrowserEvents();

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

    UpdateWindowPositionWithParent();
}

void MainApp::HandleScenarioBrowserEvents()
{
    if(scenariov8handler->GetIsInitialized() && !Code.empty())
    {
        std::string script = std::string("BrowserAutomationStudio_Parse(") + picojson::value(Code.data()).serialize() + std::string(")");
        BrowserScenario->GetMainFrame()->ExecuteJavaScript(script,BrowserScenario->GetMainFrame()->GetURL(), 0);
        Code.clear();
    }

    std::pair<std::string, bool> res = scenariov8handler->GetResult();
    if(res.second)
    {
        std::string new_code = res.first;
        worker_log(std::string("HandleScenarioBrowserEvents<<") + new_code);
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
        std::string CodeSend = res2.first;
        worker_log(std::string("GetExecuteCode<<") + CodeSend);
        xml_encode(CodeSend);
        SendTextResponce(std::string("<Messages><WaitCode>") + CodeSend + std::string("</WaitCode></Messages>"));
    }

    std::pair<std::string, bool> res5 = scenariov8handler->GetIsEditStart();
    if(res5.second)
    {
        std::string data = res5.first;
        worker_log(std::string("EditStart<<") + data);
        std::string script = std::string("BrowserAutomationStudio_EditStart(") + picojson::value(data).serialize() + std::string(")");
        if(BrowserToolbox)
            BrowserToolbox->GetMainFrame()->ExecuteJavaScript(script,BrowserToolbox->GetMainFrame()->GetURL(), 0);
    }

    bool res4 = scenariov8handler->GetIsEditEnd();
    if(res4)
    {
        worker_log(std::string("EditEnd<<"));
        std::string script = std::string("BrowserAutomationStudio_EditEnd()");
        if(BrowserToolbox)
            BrowserToolbox->GetMainFrame()->ExecuteJavaScript(script,BrowserToolbox->GetMainFrame()->GetURL(), 0);
    }

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
                worker_log(std::string("ScenarioExecuteCode<<") + script);
                BrowserScenario->GetMainFrame()->ExecuteJavaScript(script.c_str(),BrowserScenario->GetMainFrame()->GetURL(), 0);
            }

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
                    xml_encode(CodeSend);
                    std::string DelayedSendCode = std::string("<Messages><WaitCode>") + CodeSend + std::string("</WaitCode></Messages>");
                    if(res.first.HowToExecute == ToolboxV8Handler::OnlyExecute)
                    {
                        SendTextResponce(DelayedSendCode);
                        DelayedSend.clear();
                    }
                    else
                        DelayedSend = DelayedSendCode;

                    BrowserScenario->GetMainFrame()->ExecuteJavaScript("BrowserAutomationStudio_RunningTask()",BrowserScenario->GetMainFrame()->GetURL(), 0);
                }
            }


        }
    }

    if(toolboxv8handler->GetIsEditCancel())
    {
        std::string script = std::string("BrowserAutomationStudio_EditCancel()");
        worker_log("BrowserAutomationStudio_EditCancel<<");
        if(BrowserScenario)
            BrowserScenario->GetMainFrame()->ExecuteJavaScript(script,BrowserScenario->GetMainFrame()->GetURL(), 0);

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
}

void MainApp::HandleMainBrowserEvents()
{
    std::pair<std::string,bool> res = v8handler->GetResult();
    if(res.second && IsLastCommandNull)
    {
        v8handler->SetResultProcessed();
        worker_log(std::string("CommandNull<<") + LastCommand.CommandName + std::string("<<") + std::to_string(LastCommand.StageId));
    }

    if(res.second && !IsLastCommandNull)
    {
        IsLastCommandNull = true;

        worker_log(std::string("Command<<") + LastCommand.CommandName + std::string("<<") + std::to_string(LastCommand.StageId));

        if(LastCommand.CommandName == std::string("_mouseclick"))
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

            if(!BrowserEventsEmulator::IsPointOnScreen(x,y,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser))
            {
                IsLastCommandNull = false;
            }else
            {
                v8handler->SetResultProcessed();
                BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
                BrowserEventsEmulator::MouseClick(_HandlersManager->GetBrowser(),x,y,GetScrollPosition());
                SendTextResponce("<Messages><MouseClick></MouseClick></Messages>");
                worker_log(std::string("EVENTFLAG_LEFT_MOUSE_BUTTON>>"));
            }
        }else if(LastCommand.CommandName == std::string("_mousemove"))
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
            MouseEndX = x;
            MouseEndY = y;
            if(!BrowserEventsEmulator::IsPointOnScreen(MouseEndX,MouseEndY,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser))
            {
                IsLastCommandNull = false;
            }else
            {
                v8handler->SetResultProcessed();
                BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
                IsMouseMoveSimulation = true;
            }
        }else if(LastCommand.CommandName == std::string("_scroll"))
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

            if(!BrowserEventsEmulator::IsPointOnScreen(x,y,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser))
            {
                IsLastCommandNull = false;
            }else
            {
                v8handler->SetResultProcessed();
                SendTextResponce("<Messages><Scroll></Scroll></Messages>");
            }


        }else if(LastCommand.CommandName == std::string("_render"))
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

            if(!BrowserEventsEmulator::IsPointOnScreen(x,y,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser))
            {
                IsLastCommandNull = false;
            }else
            {
                worker_log(std::string("Start Rendering screen>>"));

                v8handler->SetResultProcessed();
                RenderX = RenderX - Data->ScrollX;
                RenderY = RenderY - Data->ScrollY;
                IsElementRender = false;
                NeedRenderNextFrame = true;
                if(_HandlersManager->GetBrowser())
                    _HandlersManager->GetBrowser()->GetHost()->Invalidate(PET_VIEW);
            }


        }else if(LastCommand.CommandName == std::string("system_click") || LastCommand.CommandName == std::string("check") || LastCommand.CommandName == std::string("focus"))
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

            if(!BrowserEventsEmulator::IsPointOnScreen(x,y,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser))
            {
                IsLastCommandNull = false;
            }else
            {
                v8handler->SetResultProcessed();
                worker_log(std::string("system_click>>") + std::to_string(x) + std::string(">>") + std::to_string(y));

                BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
                if(LastCommand.CommandName != std::string("focus"))
                {
                    BrowserEventsEmulator::MouseClick(_HandlersManager->GetBrowser(),x,y,GetScrollPosition());
                }
                FinishedLastCommand("");
            }
        }else if(LastCommand.CommandName == std::string("render_base64"))
        {
            int left = -1, top = -1, right = -1, bottom = -1, centerx = -1, centery = -1;
            worker_log(std::string("render_base64<<") + res.first);

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

            if(!BrowserEventsEmulator::IsPointOnScreen(left,top,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser)
                || !BrowserEventsEmulator::IsPointOnScreen(right,bottom,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser)
            )
            {
                IsLastCommandNull = false;
            }else
            {
                worker_log("NeedRenderNextFrame");
                v8handler->SetResultProcessed();
                RenderX = left - Data->ScrollX;
                RenderY = top - Data->ScrollY;
                RenderWidth = right - left;
                RenderHeight = bottom - top;
                IsElementRender = true;
                NeedRenderNextFrame = true;
                if(_HandlersManager->GetBrowser())
                    _HandlersManager->GetBrowser()->GetHost()->Invalidate(PET_VIEW);
            }
        }else if(LastCommand.CommandName == std::string("move"))
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

            if(!BrowserEventsEmulator::IsPointOnScreen(x,y,Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser))
            {
                IsLastCommandNull = false;
            }else
            {
                v8handler->SetResultProcessed();
                worker_log(std::string("move>>") + std::to_string(x) + std::string(">>") + std::to_string(y));
                BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
                LastCommand.CommandName = "move";
                LastCommand.CommandParam1 = std::to_string(x);
                LastCommand.CommandParam2 = std::to_string(y);
                MouseStartX = Data->CursorX;
                MouseStartY = Data->CursorY;
                MouseEndX = x;
                MouseEndY = y;
                IsMouseMoveSimulation = true;
            }

        }
        else if(LastCommand.CommandName == std::string("type") || LastCommand.CommandName == std::string("clear") || (LastCommand.CommandName == std::string("set") && LastCommand.StageId == 1 || LastCommand.CommandName == std::string("set_integer") && LastCommand.StageId == 1 || LastCommand.CommandName == std::string("set_random") && LastCommand.StageId == 1))
        {
            worker_log(std::string("StartTyping<<"));

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
            v8handler->SetResultProcessed();
            BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
            TypeText = res.first;
            TypeTextDelay = 30;
            LastCommand.StageId = 1;
            std::string script = std::string("{var el = BrowserAutomationStudio_FindElement(") + LastCommand.SerializePath() + std::string(");if(el){var rect = el.getBoundingClientRect();BrowserAutomationStudio_ScrollToRelative(rect.left + rect.width/2,rect.top + rect.height/2);}else browser_automation_studio_result('');}");
            if(!script.empty())
            {
                worker_log(std::string("EXEC<<") + script);
                _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript(script.c_str(),_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);
            }
            IsLastCommandNull = false;
        }
        else
        {
            v8handler->SetResultProcessed();
            std::string data = res.first;
            xml_encode(data);
            FinishedLastCommand(data);
            worker_log(std::string("ElementCommandCallback>>"));
        }
    }

    std::pair<InspectResult,bool> res2 = v8handler->GetInspectResult();
    if(res2.second)
    {
        {
            LOCK_BROWSER_DATA
            Data->_Inspect = res2.first;
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
    BrowserEventsEmulator::MouseMove(_HandlersManager->GetBrowser(), IsMouseMoveSimulation, MouseStartX, MouseStartY, MouseEndX, MouseEndY , CursorX, CursorY, Speed, Data->ScrollX, Data->ScrollY, Data->WidthBrowser, Data->HeightBrowser);
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
    if(!TypeTextIsFirstLetter && float( CurrentTime - TypeTextLastTime ) /  CLOCKS_PER_SEC < (float)TypeTextDelay / 1000.0f)
        return;
    TypeTextLastTime = CurrentTime;

    if(TypeTextIsFirstLetter)
    {
        BrowserEventsEmulator::SetFocus(_HandlersManager->GetBrowser());
        BrowserEventsEmulator::MouseClick(_HandlersManager->GetBrowser(),TypeTextX,TypeTextY,GetScrollPosition());
        worker_log(std::string("TypeTextIsFirstLetter<<") + std::to_string(TypeTextX) + std::string("<<") + std::to_string(TypeTextY));
        TypeTextIsFirstLetter = false;
        return;
    }

    //Print letter
    BrowserEventsEmulator::Key(_HandlersManager->GetBrowser(),TypeText,TypeTextState);

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
        worker_log("OnContextCreated<<ToolboxBrowser");
        if(frame->IsMain())
            toolboxv8handler = new ToolboxV8Handler();
        CefRefPtr<CefV8Value> object = context->GetGlobal();
        object->SetValue("BrowserAutomationStudio_Append", CefV8Value::CreateFunction("BrowserAutomationStudio_Append", toolboxv8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_Initialized", CefV8Value::CreateFunction("BrowserAutomationStudio_Initialized", toolboxv8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_EditCancel", CefV8Value::CreateFunction("BrowserAutomationStudio_EditCancel", toolboxv8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_Maximize", CefV8Value::CreateFunction("BrowserAutomationStudio_Maximize", toolboxv8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_Minimize", CefV8Value::CreateFunction("BrowserAutomationStudio_Minimize", toolboxv8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("_K", CefV8Value::CreateString(Lang), V8_PROPERTY_ATTRIBUTE_NONE);
        return;
    }

    //Scenario Browser
    if(BrowserScenario.get() && BrowserScenario->GetIdentifier() == browser->GetIdentifier())
    {
        worker_log("OnContextCreated<<BrowserScenario");
        CefRefPtr<CefV8Value> object = context->GetGlobal();
        if(frame->IsMain())
            scenariov8handler = new ScenarioV8Handler();
        object->SetValue("BrowserAutomationStudio_SendCode", CefV8Value::CreateFunction("BrowserAutomationStudio_SendCode", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_Initialized", CefV8Value::CreateFunction("BrowserAutomationStudio_Initialized", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_Execute", CefV8Value::CreateFunction("BrowserAutomationStudio_Execute", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_Restart", CefV8Value::CreateFunction("BrowserAutomationStudio_Restart", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_EditStart", CefV8Value::CreateFunction("BrowserAutomationStudio_EditStart", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("BrowserAutomationStudio_EditEnd", CefV8Value::CreateFunction("BrowserAutomationStudio_EditEnd", scenariov8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        object->SetValue("_K", CefV8Value::CreateString(Lang), V8_PROPERTY_ATTRIBUTE_NONE);
        return;
    }


    //Main Browser
    //if(_HandlersManager->GetBrowser() && _HandlersManager->GetBrowser()->GetIdentifier() == browser->GetIdentifier())
    {
        worker_log(std::string("OnContextCreated<<MainBrowser<<") + std::to_string(browser->GetIdentifier()) + "<<" + std::to_string(frame->IsMain()));
        CefRefPtr<CefV8Value> object = context->GetGlobal();

        _HandlersManager->NewContextCreated(browser->GetIdentifier());

        {
            LOCK_V8_HANDLER
            if(!v8handler)
                v8handler = new V8Handler();
            object->SetValue("browser_automation_studio_result", CefV8Value::CreateFunction("browser_automation_studio_result", v8handler), V8_PROPERTY_ATTRIBUTE_NONE);
            object->SetValue("browser_automation_studio_inspect_result", CefV8Value::CreateFunction("browser_automation_studio_inspect_result", v8handler), V8_PROPERTY_ATTRIBUTE_NONE);
        }

        JavaScriptExtensions extensions;
        std::string jscode;
        jscode += GetAllBrowserDataCode(GetData()->_ModulesData);

        {
            LOCK_BROWSER_DATA
            if(Data->_Headers.find("User-Agent")!=Data->_Headers.end())
            {
                jscode += extensions.GetUserAgentExtension(Data->_Headers["User-Agent"]);
            }

            if(Data->_Headers.find("Accept-Language")!=Data->_Headers.end())
            {
                jscode += extensions.GetLanguage(Data->_Headers["Accept-Language"]);
            }
        }

        if(!jscode.empty())
            frame->ExecuteJavaScript(jscode, frame->GetURL(), NULL);
        Data->ScrollX = 0;
        Data->ScrollY = 0;
    }
}

void MainApp::OnWebKitInitialized()
{
    worker_log(std::string("OnWebKitInitialized>>"));

    JavaScriptExtensions extensions;
    std::string extensionCode = extensions.GetBasicExtension();
    CefRegisterExtension("v8/browser_automation_studio", extensionCode, NULL);
}

void MainApp::ScrollUp()
{
    if(_HandlersManager->GetBrowser())
        _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript("BrowserAutomationStudio_ScrollUp()",_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);
}
void MainApp::ScrollDown()
{
    if(_HandlersManager->GetBrowser())
        _HandlersManager->GetBrowser()->GetMainFrame()->ExecuteJavaScript("BrowserAutomationStudio_ScrollDown()",_HandlersManager->GetBrowser()->GetMainFrame()->GetURL(), 0);
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

void MainApp::EmulateMoveAndClick(int x, int y)
{
    if(BrowserToolbox)
        BrowserToolbox->GetMainFrame()->ExecuteJavaScript(std::string("BrowserAutomationStudio_MoveAndClick(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(")"),BrowserToolbox->GetMainFrame()->GetURL(), 0);
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
