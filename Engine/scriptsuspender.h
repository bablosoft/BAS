#ifndef SCRIPTSUSPENDER_H
#define SCRIPTSUSPENDER_H
#include "engine_global.h"

#include <QObject>
#include <QList>
#include <QPair>
#include <QDateTime>
#include <QTimer>
#include "iscriptsuspender.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ScriptSuspender : public IScriptSuspender
    {
        Q_OBJECT
        int MaxCount;
        QTimer* ResumeWatchTimer;
        QList<QPair<QDateTime,IWorker*> >Data;
        void UpdateTimerData();
        int TimerIndex;
        QList<IWorker*> NextWorkers;
    public:
        explicit ScriptSuspender(QObject *parent = 0);
        virtual bool Suspend(int milliseconds, IWorker *Worker);
        virtual QPair<IWorker*,IScriptSuspender::WorkerStatus> GetWorker();
        virtual int Count();
        virtual void SetMaxCount(int MaxCount);
    signals:

    private slots:
        virtual void OnTimer();
    };
}

#endif // SCRIPTSUSPENDER_H
