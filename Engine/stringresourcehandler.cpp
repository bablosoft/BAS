#include "stringresourcehandler.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    StringResourceHandler::StringResourceHandler(QObject *parent) :
        ResourceHandlerAbstract(parent)
    {
    }

    QScriptValue StringResourceHandler::get()
    {
         return QScriptValue(Value);
    }

    QString StringResourceHandler::GetString()
    {
        return Value;
    }

    void StringResourceHandler::SetString(const QString & value)
    {
        Value = value;
    }
}
