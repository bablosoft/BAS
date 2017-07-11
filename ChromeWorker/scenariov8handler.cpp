#include "scenariov8handler.h"
#include "log.h"


ScenarioV8Handler::ScenarioV8Handler()
{
    Changed = false;
    ChangedExecute = false;
    IsInitialized = false;
    NeedRestart = None;
    IsEditStart = false;
    IsEditEnd = false;
    IsThreadNumberEditStart = false;
    IsSuccessNumberEditStart = false;
    IsFailNumberEditStart = false;
    IsClipboardGetRequest = false;
    IsClipboardSetRequest = false;
    IsRunFunctionStart = false;
    IsRunFunctionSeveralThreadsStart = false;
}


std::pair<ScenarioV8Handler::LastResultStruct, bool> ScenarioV8Handler::GetResult()
{
    std::lock_guard<std::mutex> lock(mut);

    std::pair<LastResultStruct, bool> r;
    r.first = LastResult;
    r.second = Changed;

    Changed = false;

    LastResult.LastResultCodeDiff.clear();
    LastResult.LastResultVariables.clear();
    LastResult.LastResultGlobalVariables.clear();
    LastResult.LastResultFunctions.clear();
    LastResult.LastResultResources.clear();

    return r;
}

std::pair<std::string, bool> ScenarioV8Handler::GetIsEditStart()
{
    std::lock_guard<std::mutex> lock(mut_editstart);

    std::pair<std::string, bool> r;
    r.first = EditStartScript;
    r.second = IsEditStart;

    IsEditStart = false;

    EditStartScript.clear();

    return r;
}

bool ScenarioV8Handler::GetIsEditEnd()
{
    std::lock_guard<std::mutex> lock(mut_editend);
    bool res = IsEditEnd;
    IsEditEnd = false;
    return res;
}



std::pair<std::string, bool> ScenarioV8Handler::GetExecuteCode()
{
    std::lock_guard<std::mutex> lock(mut_code);

    std::pair<std::string, bool> r;
    r.first = LastResultExecute;
    r.second = ChangedExecute;

    ChangedExecute = false;

    LastResultExecute.clear();

    return r;
}

bool ScenarioV8Handler::GetIsInitialized()
{
    std::lock_guard<std::mutex> lock(mut_initialized);

    return IsInitialized;
}

ScenarioV8Handler::RestartType ScenarioV8Handler::GetNeedRestart()
{
    std::lock_guard<std::mutex> lock(mut_restart);
    RestartType res = NeedRestart;
    NeedRestart = None;
    return res;
}


bool ScenarioV8Handler::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if(name == std::string("BrowserAutomationStudio_SendCode"))
    {
        if (arguments.size() == 6 && arguments[0]->IsString() && arguments[1]->IsString() && arguments[2]->IsString() && arguments[3]->IsString()&& arguments[4]->IsString()&& arguments[5]->IsString())
        {
            std::lock_guard<std::mutex> lock(mut);
            LastResult.LastResultCodeDiff = arguments[0]->GetStringValue().ToString();
            LastResult.LastResultFunctions = arguments[1]->GetStringValue().ToString();
            LastResult.LastResultResources = arguments[2]->GetStringValue().ToString();
            LastResult.LastResultVariables = arguments[3]->GetStringValue().ToString();
            LastResult.LastResultGlobalVariables = arguments[4]->GetStringValue().ToString();
            LastResult.LastResultLabels = arguments[5]->GetStringValue().ToString();
            Changed = true;
        }
    }else if(name == std::string("BrowserAutomationStudio_Initialized"))
    {
        std::lock_guard<std::mutex> lock(mut_initialized);
        IsInitialized = true;
    }else if(name == std::string("BrowserAutomationStudio_Execute"))
    {
        if (arguments.size() == 1 && arguments[0]->IsString())
        {
            std::lock_guard<std::mutex> lock(mut_code);
            LastResultExecute = arguments[0]->GetStringValue().ToString();
            ChangedExecute = true;
        }
    }
    else if(name == std::string("BrowserAutomationStudio_Restart"))
    {
        if (arguments.size() == 1)
        {
            std::lock_guard<std::mutex> lock(mut_restart);
            WORKER_LOG(std::string("BrowserAutomationStudio_Restart<<") + std::to_string(arguments[0]->GetBoolValue()));
            if(arguments[0]->GetBoolValue())
            {
                NeedRestart = Stop;
            }else
            {
                NeedRestart = Restart;
            }
        }
    }
    else if(name == std::string("BrowserAutomationStudio_EditStart"))
    {
        if (arguments.size() == 1)
        {
            std::lock_guard<std::mutex> lock(mut_editstart);
            EditStartScript = arguments[0]->GetStringValue().ToString();
            IsEditStart = true;
        }
    }else if(name == std::string("BrowserAutomationStudio_EditEnd"))
    {
        if (arguments.size() == 0)
        {
            std::lock_guard<std::mutex> lock(mut_editend);
            IsEditEnd = true;
        }
    }else if(name == std::string("BrowserAutomationStudio_ThreadNumberEdit"))
    {
        std::lock_guard<std::mutex> lock(mut_threadnumbereditstart);
        IsThreadNumberEditStart = true;
    }else if(name == std::string("BrowserAutomationStudio_SuccessNumberEdit"))
    {
        std::lock_guard<std::mutex> lock(mut_successnumbereditstart);
        IsSuccessNumberEditStart = true;
    }else if(name == std::string("BrowserAutomationStudio_FailNumberEdit"))
    {
        std::lock_guard<std::mutex> lock(mut_failnumbereditstart);
        IsFailNumberEditStart = true;
    }else if(name == std::string("BrowserAutomationStudio_RunFunction"))
    {
        std::lock_guard<std::mutex> lock(mut_runfunction);
        IsRunFunctionStart = true;
    }else if(name == std::string("BrowserAutomationStudio_RunFunctionSeveralThreads"))
    {
        std::lock_guard<std::mutex> lock(mut_runfunctionseveralthreads);
        IsRunFunctionSeveralThreadsStart = true;
    }else if(name == std::string("BrowserAutomationStudio_SetClipboard"))
    {
        if (arguments.size() == 1)
        {
            std::lock_guard<std::mutex> lock(mut_clipboard_set);
            clipboard_set = arguments[0]->GetStringValue().ToString();
            IsClipboardSetRequest = true;
        }
    }else if(name == std::string("BrowserAutomationStudio_GetClipboard"))
    {
        if (arguments.size() == 0)
        {
            std::lock_guard<std::mutex> lock(mut_clipboard_get);
            IsClipboardGetRequest = true;
        }
    }

    return true;
}

std::pair<std::string, bool> ScenarioV8Handler::GetClipboardSetRequest()
{
    std::lock_guard<std::mutex> lock(mut_clipboard_set);

    std::pair<std::string, bool> r;
    r.first = clipboard_set;
    r.second = IsClipboardSetRequest;

    IsClipboardSetRequest = false;

    clipboard_set.clear();

    return r;
}

bool ScenarioV8Handler::GetClipboardGetRequest()
{
    std::lock_guard<std::mutex> lock(mut_clipboard_get);
    bool res = IsClipboardGetRequest;
    IsClipboardGetRequest = false;
    return res;
}

bool ScenarioV8Handler::GetIsThreadNumberEditStart()
{
    std::lock_guard<std::mutex> lock(mut_threadnumbereditstart);
    bool res = IsThreadNumberEditStart;
    IsThreadNumberEditStart = false;
    return res;
}

bool ScenarioV8Handler::GetIsRunFunctionStart()
{
    std::lock_guard<std::mutex> lock(mut_runfunction);
    bool res = IsRunFunctionStart;
    IsRunFunctionStart = false;
    return res;
}

bool ScenarioV8Handler::GetIsRunFunctionSeveralThreadsStart()
{
    std::lock_guard<std::mutex> lock(mut_runfunctionseveralthreads);
    bool res = IsRunFunctionSeveralThreadsStart;
    IsRunFunctionSeveralThreadsStart = false;
    return res;
}

bool ScenarioV8Handler::GetIsSuccessNumberEditStart()
{
    std::lock_guard<std::mutex> lock(mut_successnumbereditstart);
    bool res = IsSuccessNumberEditStart;
    IsSuccessNumberEditStart = false;
    return res;

}

bool ScenarioV8Handler::GetIsFailNumberEditStart()
{
    std::lock_guard<std::mutex> lock(mut_failnumbereditstart);
    bool res = IsFailNumberEditStart;
    IsFailNumberEditStart = false;
    return res;

}
