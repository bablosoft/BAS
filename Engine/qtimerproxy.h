#ifndef QTIMERPROXY_H
#define QTIMERPROXY_H
#include <QObject>
#include "engine_global.h"
#include "itimerproxy.h"

#include <QTimer>
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT QTimerProxy : public ITimerProxy
    {
        Q_OBJECT
        QTimer *Timer;
    public:
        explicit QTimerProxy(QObject *parent = 0);

    signals:

    public slots:
        virtual void stop();
        virtual void singleShot(int interval,const QObject* object, const char * slot_signal);
    };
}

#endif // QTIMERPROXY_H
