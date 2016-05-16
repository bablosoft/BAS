#include "qtimerproxy.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    QTimerProxy::QTimerProxy(QObject *parent) :
        ITimerProxy(parent)
    {
        Timer = new QTimer(this);
        Timer->setSingleShot(true);
    }

    void QTimerProxy::stop()
    {
        Timer->stop();
    }

    void QTimerProxy::singleShot(int interval,const QObject* object, const char * slot_signal)
    {
        Timer->singleShot(interval,object,slot_signal);
    }
}
