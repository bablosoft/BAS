#ifndef MULTITIMER_H
#define MULTITIMER_H

#include <QObject>
#include "engine_global.h"
#include "itimerproxy.h"
#include <QTimer>
#include <QDateTime>

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT  MultiTimer : public QObject
    {
        Q_OBJECT

        QTimer *Timer;
    public:
        explicit MultiTimer(QObject *parent = 0);
    signals:
        void Timeout(const QDateTime& Now);
    private slots:
        void TimeoutSlot();
    };
}

#endif // MULTITIMER_H
