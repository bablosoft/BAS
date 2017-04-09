#include "engineresourcefixedinteger.h"
#include "integerresourcehandler.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    EngineResourceFixedInteger::EngineResourceFixedInteger(QObject *parent) :
        EngineResourceAbstract(parent),Active(true)
    {
    }

    void EngineResourceFixedInteger::SetValue(int Value)
    {
        this->Value = Value;
    }


    IResourceHandler* EngineResourceFixedInteger::GetHandler(const QSet<QString>& refuse)
    {
        IntegerResourceHandler *handler = new IntegerResourceHandler();
        if(Active)
        {
            handler->SetInteger(Value);
            connect(handler,SIGNAL(DieSignal()),this,SLOT(Die()));
            connect(handler,SIGNAL(SuccessSignal()),this,SLOT(Success()));
            connect(handler,SIGNAL(FailSignal()),this,SLOT(Fail()));
            handler->SetHandlerStatus(IResourceHandler::Ready);
        }else
        {
            handler->SetHandlerStatus(IResourceHandler::NotAvailable);
        }
        return handler;
    }

    QList<QScriptValue> EngineResourceFixedInteger::GetRandomSubarrayData(int size)
    {
        if(size > 0)
            return QList<QScriptValue>() << QScriptValue(Value);
        return QList<QScriptValue>();
    }
    QScriptValue EngineResourceFixedInteger::GetAtIndex(int index)
    {
        if(index == 0)
        {
            return QScriptValue(Value);
        }
        return QScriptValue(QScriptValue::NullValue);
    }

    void EngineResourceFixedInteger::SetAtIndex(int index, const QString& val)
    {

    }


    int EngineResourceFixedInteger::GetTotalLength()
    {
        return 1;
    }

    QList<QScriptValue> EngineResourceFixedInteger::GetAllData()
    {
        return QList<QScriptValue>() << QScriptValue(Value);
    }

    void EngineResourceFixedInteger::Success()
    {

    }

    void EngineResourceFixedInteger::Fail()
    {

    }
    void EngineResourceFixedInteger::Die()
    {
        //Active = false;
    }
    void EngineResourceFixedInteger::Reload()
    {
        Active = true;
    }

    void EngineResourceFixedInteger::Insert(const QString& value, bool onlywrite)
    {

    }

    void EngineResourceFixedInteger::Sync()
    {

    }

}
