#ifndef V8HANDLER_H
#define V8HANDLER_H

#include "include/cef_app.h"
#include <functional>
#include <mutex>
#include "inspectresult.h"

class V8Handler : public CefV8Handler
{
    std::mutex mut;
    std::mutex mut_inspect;
    std::string Result;
    InspectResult _InspectResult;
    bool Changed;
    bool ChangedInspect;
public:
    V8Handler();
    virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) OVERRIDE;
    std::pair<std::string,bool> GetResult();
    void SetResultProcessed();
    std::pair<InspectResult,bool> GetInspectResult();

private:
    IMPLEMENT_REFCOUNTING(V8Handler);
};

#endif // V8HANDLER_H

