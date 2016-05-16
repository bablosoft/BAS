#include "timeoutwaiterfactory.h"
#include "every_cpp.h"
#include "multitimerproxy.h"
namespace BrowserAutomationStudioFramework
{
    TimeoutWaiterFactory::TimeoutWaiterFactory(QObject *parent) :
        IWaiterFactory(parent)
    {
        _MultiTimer = 0;
    }
    void TimeoutWaiterFactory::SetMultiWorker(MultiTimer * _MultiTimer)
    {
        this->_MultiTimer = _MultiTimer;
    }
    IWaiter * TimeoutWaiterFactory::CreateWaiter()
    {
        TimeoutWaiter* res = new TimeoutWaiter();
        if(_MultiTimer)
        {
            MultiTimerProxy * Proxy = new MultiTimerProxy(res);
            connect(_MultiTimer,SIGNAL(Timeout(QDateTime)),Proxy,SLOT(timeoutSlot(QDateTime)));
            res->SetTimer(Proxy);
        }
        return res;
    }
}
