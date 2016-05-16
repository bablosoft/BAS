#include "integerresourcehandler.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    IntegerResourceHandler::IntegerResourceHandler(QObject *parent) :
        ResourceHandlerAbstract(parent)
    {
    }

    QScriptValue IntegerResourceHandler::get()
    {
         return QScriptValue(Value);
    }

    int IntegerResourceHandler::GetInteger()
    {
        return Value;
    }

    void IntegerResourceHandler::SetInteger(int value)
    {
        Value = value;
    }
}
