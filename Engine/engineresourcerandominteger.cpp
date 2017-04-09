#include "engineresourcerandominteger.h"
#include "integerresourcehandler.h"
#include "every_cpp.h"



namespace BrowserAutomationStudioFramework
{
    EngineResourceRandomInteger::EngineResourceRandomInteger(QObject *parent) :
        EngineResourceAbstract(parent),Active(true)
    {
    }

    void EngineResourceRandomInteger::SetMinValue(int Value)
    {
        this->MinValue = Value;
    }

    void EngineResourceRandomInteger::SetMaxValue(int Value)
    {
        this->MaxValue = Value;
    }


    IResourceHandler* EngineResourceRandomInteger::GetHandler(const QSet<QString>& refuse)
    {
        IntegerResourceHandler *handler = new IntegerResourceHandler();
        if(Active)
        {

            int max, min;
            if(MinValue>MaxValue)
            {
                max = MinValue;
                min = MaxValue;
            }else
            {
                max = MaxValue;
                min = MinValue;
            }
            handler->SetInteger(qrand() % ((max + 1) - min) + min);
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
    QList<QScriptValue> EngineResourceRandomInteger::GetAllData()
    {
        return QList<QScriptValue>();
    }

    QList<QScriptValue> EngineResourceRandomInteger::GetRandomSubarrayData(int size)
    {
        return QList<QScriptValue>();
    }
    QScriptValue EngineResourceRandomInteger::GetAtIndex(int index)
    {
        return QScriptValue(QScriptValue::NullValue);
    }
    int EngineResourceRandomInteger::GetTotalLength()
    {
        return 0;
    }

    void EngineResourceRandomInteger::Success()
    {

    }
    void EngineResourceRandomInteger::Fail()
    {

    }
    void EngineResourceRandomInteger::Die()
    {
        //Active = false;
    }
    void EngineResourceRandomInteger::Reload()
    {
        Active = true;
    }
    void EngineResourceRandomInteger::Insert(const QString& value, bool onlywrite)
    {

    }
    void EngineResourceRandomInteger::Sync()
    {

    }
    void EngineResourceRandomInteger::SetAtIndex(int index, const QString& val)
    {

    }

}
