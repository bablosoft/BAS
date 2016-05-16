#include "toolboxv8handler.h"

ToolboxV8Handler::ToolboxV8Handler()
{
    IsInitialized = false;
    IsEditCancel = false;
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

bool ToolboxV8Handler::GetIsEditCancel()
{
    std::lock_guard<std::mutex> lock(mut_editcancel);
    bool res = IsEditCancel;
    IsEditCancel = false;

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

            LastResult.push_back(res);
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
    }
    return true;
}

