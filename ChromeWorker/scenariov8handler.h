#ifndef SCENARIOV8HANDLER_H
#define SCENARIOV8HANDLER_H

#include "include/cef_app.h"
#include <functional>
#include <mutex>

class ScenarioV8Handler : public CefV8Handler
{
public:
    enum RestartType{None, Restart, Stop};
private:
    std::string LastResult;
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

    bool IsInitialized;

public:

    ScenarioV8Handler();
    virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) OVERRIDE;
    std::pair<std::string, bool> GetResult();
    std::pair<std::string, bool> GetExecuteCode();
    RestartType GetNeedRestart();
    bool GetIsInitialized();
    bool GetIsEditEnd();
    std::pair<std::string, bool> GetIsEditStart();


private:
    IMPLEMENT_REFCOUNTING(ScenarioV8Handler);
};

#endif // SCENARIOV8HANDLER_H
