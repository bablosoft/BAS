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
         int index = Value.indexOf(QChar(0));
         if(index>=0)
         {
             return QScriptValue(Value.mid(0,index));
         }
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
