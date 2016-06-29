#ifndef TOOLBOXV8HANDLER_H
#define TOOLBOXV8HANDLER_H

#include "include/cef_app.h"
#include <functional>
#include <mutex>

class ToolboxV8Handler : public CefV8Handler
{
public:
    enum ExecuteType{OnlyExecute, OnlyAdd, AddAndExecute};
    struct ResultClass
    {
        std::string Name;
        std::string Code;
        ExecuteType HowToExecute;
        bool DisableIfAdd;
    };

private:
    std::vector<ResultClass> LastResult;

    bool IsInitialized;
    bool IsEditCancel;

    bool IsMaximize;
    bool IsMinimize;


    std::mutex mut;
    std::mutex mut_initialized;
    std::mutex mut_maximize;
    std::mutex mut_minimize;
    std::mutex mut_editcancel;


public:
    ToolboxV8Handler();
    bool GetIsInitialized();
    bool GetIsEditCancel();
    bool GetIsMaximize();
    bool GetIsMinimize();

    virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) OVERRIDE;
    std::pair<ResultClass, bool> GetResult();

private:
    IMPLEMENT_REFCOUNTING(ToolboxV8Handler);
};

#endif // TOOLBOXV8HANDLER_H
