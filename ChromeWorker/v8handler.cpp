#include "v8handler.h"
#include "log.h"
#include <thread>
V8Handler::V8Handler()
{
    Changed = false;
    ChangedInspect = false;
}

std::pair<std::string,bool> V8Handler::GetResult()
{
    std::lock_guard<std::mutex> lock(mut);

    std::pair<std::string,bool> r;
    r.first = Result;
    r.second = Changed;
    //Changed = false;
    return r;
}

void V8Handler::SetResultProcessed()
{
    std::lock_guard<std::mutex> lock(mut);
    Changed = false;
}

std::pair<InspectResult,bool> V8Handler::GetInspectResult()
{
    std::lock_guard<std::mutex> lock(mut_inspect);

    std::pair<InspectResult,bool> r;
    r.first = _InspectResult;
    r.second = ChangedInspect;
    _InspectResult.css.clear();
    _InspectResult.match.clear();
    _InspectResult.label.clear();
    ChangedInspect = false;
    return r;
}


bool V8Handler::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if(name == std::string("browser_automation_studio_result"))
    {
        if (arguments.size() == 1 && arguments[0]->IsString())
        {
            std::lock_guard<std::mutex> lock(mut);
            Result = arguments[0]->GetStringValue().ToString();
            Changed = true;
        }else if (arguments.size() == 1 && (arguments[0]->IsUndefined() || arguments[0]->IsNull()))
        {
            std::lock_guard<std::mutex> lock(mut);
            Result = "";
            Changed = true;
        } if (arguments.size() == 1 && (arguments[0]->IsInt()))
        {
            std::lock_guard<std::mutex> lock(mut);
            Result = std::to_string(arguments[0]->GetIntValue());
            Changed = true;
        }
    }else if(name == std::string("browser_automation_studio_inspect_result"))
    {
        std::lock_guard<std::mutex> lock(mut_inspect);

        _InspectResult.x = arguments[0]->GetIntValue();
        _InspectResult.y = arguments[1]->GetIntValue();
        _InspectResult.width = arguments[2]->GetIntValue();
        _InspectResult.height = arguments[3]->GetIntValue();

        _InspectResult.label = arguments[4]->GetStringValue().ToString();
        _InspectResult.css = arguments[5]->GetStringValue().ToString();
        _InspectResult.css2 = arguments[6]->GetStringValue().ToString();
        _InspectResult.css3 = arguments[7]->GetStringValue().ToString();
        _InspectResult.match = arguments[8]->GetStringValue().ToString();
        _InspectResult.mousex = arguments[9]->GetIntValue();
        _InspectResult.mousey = arguments[10]->GetIntValue();
        _InspectResult.active = arguments[11]->GetBoolValue();

        ChangedInspect = true;
    }
    return true;
}

