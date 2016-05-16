#ifndef ISCRIPTSUSPENDER_H
#define ISCRIPTSUSPENDER_H

#include "engine_global.h"

#include <QObject>
#include <QPair>
#include "iworker.h"

namespace BrowserAutomationStudioFramework
{
    class IWorker;
    class ENGINESHARED_EXPORT IScriptSuspender : public QObject
    {
        Q_OBJECT
    public:
        enum WorkerStatus{Ready = 0,Wait = 1,NotAvailable = 2};

        explicit IScriptSuspender(QObject *parent = 0);
        virtual bool Suspend(int milliseconds, IWorker *Worker) = 0;
        virtual QPair<IWorker*,WorkerStatus> GetWorker() = 0;
        virtual int Count() = 0;
        virtual void SetMaxCount(int MaxCount) = 0;
    signals:
        void Suspended(IWorker *Worker);
        void Resumed(IWorker *Worker);
    public slots:

    };
}

#endif // ISCRIPTSUSPENDER_H
