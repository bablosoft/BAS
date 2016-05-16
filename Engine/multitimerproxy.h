#ifndef MULTITIMERPROXY_H
#define MULTITIMERPROXY_H
#include <QObject>
#include "engine_global.h"
#include "itimerproxy.h"
#include <QDateTime>

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT MultiTimerProxy : public ITimerProxy
    {
        Q_OBJECT
        QDateTime NextTimeout;
        bool FireNext;
        bool NewConnect;
    public:
        explicit MultiTimerProxy(QObject *parent = 0);
        ~MultiTimerProxy();
    signals:
        void timeoutSignal();
    public slots:
        void timeoutSlot(const QDateTime& Now);
        virtual void stop();
        virtual void singleShot(int interval,const QObject* object, const char * slot_signal);

    };
}

#endif // MULTITIMERPROXY_H
