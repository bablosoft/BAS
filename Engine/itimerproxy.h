#ifndef ITIMERPROXY_H
#define ITIMERPROXY_H
#include "engine_global.h"

#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ITimerProxy : public QObject
    {
        Q_OBJECT
    public:
        explicit ITimerProxy(QObject *parent = 0);

    signals:

    public slots:
        virtual void stop() = 0;
        virtual void singleShot(int interval,const QObject* object, const char * slot_signal) = 0;
    };
}

#endif // ITIMERPROXY_H
