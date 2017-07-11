#include "toolboxv8handler.h"

ToolboxV8Handler::ToolboxV8Handler()
{
    IsInitialized = false;
    IsInterrupt = false;
    IsEditCancel = false;
    IsMaximize = false;
    IsMinimize = false;
    IsInterfaceState = false;
    url_changed = false;
    ChangedExecute = false;
}

std::pair<std::string, bool> ToolboxV8Handler::GetExecuteCode()
{
    std::lock_guard<std::mutex> lock(mut_code);

    std::pair<std::string, bool> r;
    r.first = LastResultExecute;
    r.second = ChangedExecute;

    ChangedExecute = false;

    LastResultExecute.clear();

    return r;
}


std::pair<std::string, bool> ToolboxV8Handler::GetInterfaceState()
{
    std::lock_guard<std::mutex> lock(mut_interface);

    std::pair<std::string, bool> r;
    r.second = IsInterfaceState;
    if(IsInterfaceState)
    {
        r.first = interfacestate;
        interfacestate.clear();
        IsInterfaceState = false;
    }
    return r;
}


std::pair<ToolboxV8Handler::ResultClass, bool> ToolboxV8Handler::GetResult()
{
    std::lock_guard<std::mutex> lock(mut);

    std::pair<ResultClass, bool> r;
    r.second = !LastResult.empty();
    if(!LastResult.empty())
    {
        r.first = LastResult.at(0);
        LastResult.erase(LastResult.begin());
    }
    return r;
}

bool ToolboxV8Handler::GetIsInitialized()
{
    std::lock_guard<std::mutex> lock(mut_initialized);

    return IsInitialized;
}

bool ToolboxV8Handler::GetIsMaximize()
{
    std::lock_guard<std::mutex> lock(mut_maximize);
    bool res = IsMaximize;
    IsMaximize = false;
    return res;
}

bool ToolboxV8Handler::GetIsMinimize()
{
    std::lock_guard<std::mutex> lock(mut_minimize);
    bool res = IsMinimize;
    IsMinimize = false;
    return res;
}

bool ToolboxV8Handler::GetIsEditCancel()
{
    std::lock_guard<std::mutex> lock(mut_editcancel);
    bool res = IsEditCancel;
    IsEditCancel = false;

    return res;
}

bool ToolboxV8Handler::GetIsInterrupt()
{
    std::lock_guard<std::mutex> lock(mut_interrupt);
    bool res = IsInterrupt;
    IsInterrupt = false;

    return res;
}

bool ToolboxV8Handler::GetClearHighlight()
{
    bool res = ClearHighlight;
    ClearHighlight = false;

    return res;
}


bool ToolboxV8Handler::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if(name == std::string("BrowserAutomationStudio_Append"))
    {
        if (arguments.size() >= 3 && arguments[0]->IsString() && arguments[1]->IsString() && arguments[2]->IsInt())
        {
            std::lock_guard<std::mutex> lock(mut);
            ResultClass res;
            res.Name = arguments[0]->GetStringValue().ToString();
            res.Code = arguments[1]->GetStringValue().ToString();
            switch(arguments[2]->GetIntValue())
            {
                case 0: res.HowToExecute = OnlyExecute; break;
                case 1: res.HowToExecute = OnlyAdd; break;
                case 2: res.HowToExecute = AddAndExecute; break;
            }
            res.DisableIfAdd = true;
            if(arguments.size() > 3)
                res.DisableIfAdd = arguments[3]->GetBoolValue();

            if(arguments.size() > 4)
                res.Id = arguments[4]->GetStringValue().ToString();

            LastResult.push_back(res);
        }
    }else if(name == std::string("BrowserAutomationStudio_Execute"))
    {
        if (arguments.size() == 1 && arguments[0]->IsString())
        {
            std::lock_guard<std::mutex> lock(mut_code);
            LastResultExecute = arguments[0]->GetStringValue().ToString();
            ChangedExecute = true;
        }
    }else if(name == std::string("BrowserAutomationStudio_Initialized"))
    {
        std::lock_guard<std::mutex> lock(mut_initialized);
        IsInitialized = true;
    }
    else if(name == std::string("BrowserAutomationStudio_EditCancel"))
    {
        std::lock_guard<std::mutex> lock(mut_editcancel);
        IsEditCancel = true;
    }else if(name == std::string("BrowserAutomationStudio_Maximize"))
    {
        std::lock_guard<std::mutex> lock(mut_maximize);
        IsMaximize = true;
    }else if(name == std::string("BrowserAutomationStudio_Minimize"))
    {
        std::lock_guard<std::mutex> lock(mut_minimize);
        IsMinimize = true;
    }else if(name == std::string("BrowserAutomationStudio_Interrupt"))
    {
        std::lock_guard<std::mutex> lock(mut_interrupt);
        IsInterrupt = true;
    }else if(name == std::string("BrowserAutomationStudio_OpenUrl"))
    {
        if (arguments.size() == 1 && arguments[0]->IsString())
        {
            std::lock_guard<std::mutex> lock(url_mut);
            url = arguments[0]->GetStringValue().ToString();
            url_changed = true;
        }
    }else if(name == std::string("BrowserAutomationStudio_SaveInterfaceState"))
    {
        if (arguments.size() == 1 && arguments[0]->IsString())
        {
            std::lock_guard<std::mutex> lock(mut_interface);
            interfacestate = arguments[0]->GetStringValue().ToString();
            IsInterfaceState = true;
        }
    }else if(name == std::string("BrowserAutomationStudio_ClearHighlight"))
    {
        if (arguments.size() == 0)
        {
            ClearHighlight = true;
        }
    }



    return true;
}

std::pair<std::string, bool> ToolboxV8Handler::GetLoadUrl()
{
    std::lock_guard<std::mutex> lock(url_mut);

    std::pair<std::string, bool> r;
    r.first = url;
    r.second = url_changed;

    url_changed = false;

    url.clear();

    return r;
}
