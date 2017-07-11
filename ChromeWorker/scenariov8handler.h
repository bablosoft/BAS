#ifndef SCENARIOV8HANDLER_H
#define SCENARIOV8HANDLER_H

#include "include/cef_app.h"
#include <functional>
#include <mutex>

class ScenarioV8Handler : public CefV8Handler
{
public:
    enum RestartType{None, Restart, Stop};
    struct LastResultStruct
    {
        std::string LastResultCodeDiff;
        std::string LastResultVariables;
        std::string LastResultGlobalVariables;
        std::string LastResultFunctions;
        std::string LastResultResources;
        std::string LastResultLabels;
    };
private:
    LastResultStruct LastResult;

    std::string LastResultExecute;
    bool Changed;
    bool ChangedExecute;
    RestartType NeedRestart;

    bool IsEditStart;
    bool IsEditEnd;
    std::string EditStartScript;

    std::mutex mut;
    std::mutex mut_initialized;
    std::mutex mut_code;
    std::mutex mut_restart;
    std::mutex mut_editstart;
    std::mutex mut_editend;
    std::mutex mut_runfunction;
    std::mutex mut_runfunctionseveralthreads;

    bool IsThreadNumberEditStart;
    bool IsSuccessNumberEditStart;
    bool IsFailNumberEditStart;
    bool IsRunFunctionStart;
    bool IsRunFunctionSeveralThreadsStart;


    std::mutex mut_threadnumbereditstart;
    std::mutex mut_successnumbereditstart;
    std::mutex mut_failnumbereditstart;

    std::mutex mut_clipboard_get;
    std::mutex mut_clipboard_set;

    bool IsClipboardGetRequest;
    bool IsClipboardSetRequest;

    std::string clipboard_set;



    bool IsInitialized;

public:

    ScenarioV8Handler();
    virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) OVERRIDE;
    std::pair<LastResultStruct, bool> GetResult();
    std::pair<std::string, bool> GetExecuteCode();
    RestartType GetNeedRestart();
    bool GetIsInitialized();
    bool GetIsEditEnd();
    bool GetIsThreadNumberEditStart();
    bool GetIsSuccessNumberEditStart();
    bool GetIsFailNumberEditStart();
    bool GetIsRunFunctionStart();
    bool GetIsRunFunctionSeveralThreadsStart();
    std::pair<std::string, bool> GetIsEditStart();
    std::pair<std::string, bool> GetClipboardSetRequest();
    bool GetClipboardGetRequest();


private:
    IMPLEMENT_REFCOUNTING(ScenarioV8Handler);
};

#endif // SCENARIOV8HANDLER_H
