#ifndef V8HANDLER_H
#define V8HANDLER_H

#include "include/cef_app.h"
#include <functional>
#include <mutex>
#include "inspectresult.h"
#include "localstoragedata.h"
#include "browserdata.h"
#include "multithreading.h"

class V8Handler : public CefV8Handler
{
    std::mutex mut;
    std::mutex mut_inspect;
    std::mutex mut_local_storage;
    std::mutex mut_frame_find;

    std::string Result;
    std::vector<LocalStorageDataItem> NewLocalStorage;
    InspectResult _InspectResult;
    InspectResult _FrameFindResult;
    bool Changed;
    bool ChangedInspect;
    bool ChangedLocalStorage;
    bool ChangedFrameFind;
    BrowserData* Data;
public:
    V8Handler(BrowserData* Data);

    virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) OVERRIDE;
    std::pair<std::string,bool> GetResult();
    std::pair<std::vector<LocalStorageDataItem>,bool> GetLocalStorage();
    void SetResultProcessed();
    std::pair<InspectResult,bool> GetInspectResult();
    std::pair<InspectResult,bool> GetFrameFindResult();

private:
    IMPLEMENT_REFCOUNTING(V8Handler);
};

#endif // V8HANDLER_H

