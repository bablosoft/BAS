#ifndef IWAITER_H
#define IWAITER_H
#include "engine_global.h"

#include <QObject>
#include "ibrowser.h"
#include "iwebelement.h"
#include "isolver.h"
#include "iengineresources.h"
#include "iresourcehandler.h"
#include "imultiworker.h"
#include "itimerproxy.h"

namespace BrowserAutomationStudioFramework
{

    class IWebElement;
    class IMultiWorker;
    class ENGINESHARED_EXPORT IWaiter : public QObject
    {
        Q_OBJECT

    public:
        explicit IWaiter(QObject *parent = 0);
        virtual void SetTimer(ITimerProxy *Timer) = 0;
    signals:

    public slots:
        virtual void WaitForSignal(const QObject *object_wait, const char * slot_signal ,const QObject *object_success,const char * slot_success,const QObject *object_fail,const char * slot_fail) = 0;
        virtual void WaitForSolver(ISolver * solver, const QString & id,const QObject *object_success,const char * slot_success,const QObject *object_fail,const char * slot_fail) = 0;
        virtual QString GetLastSolverResult() = 0;
        virtual QString GetLastSolverId() = 0;
        virtual void WaitForHandler(IEngineResources *res, const QString name, const QSet<QString>& refuse,const QObject *object_success,const char * slot_success,const QObject *object_fail,const char * slot_fail) = 0;
        virtual IResourceHandler *GetLastHandler() = 0;
        virtual void WaitForStageFinished(const QObject *object_stage,const char * signal_finished,const QObject *object_listener,const char * slot_finished) = 0;

        virtual void WaitForElement(IWebElement* Element, const QString& text,const QObject *object_success,const char * slot_success,const QObject *object_fail,const char * slot_fail) = 0;
        virtual void WaitInfinity(const QObject *object_wait, const char * slot_signal ,const QObject *object_success,const char * slot_success) = 0;

        virtual void Sleep(int milliseconds,const QObject *object_success,const char * slot_success) = 0;
        virtual void Abort() = 0;
        virtual void Stop() = 0;
        virtual bool IsActive() = 0;
        virtual bool IsResourceRefused() = 0;

        virtual void SetGeneralWaitTimeout(int timeout) = 0;
        virtual void SetSolverWaitTimeout(int timeout) = 0;
        virtual void SetGeneralWaitTimeoutNext(int timeout) = 0;
        virtual void SetSolverWaitTimeoutNext(int timeout) = 0;
        virtual int GetGeneralWaitTimeoutNext() = 0;
        virtual int GetSolverWaitTimeoutNext() = 0;

        virtual void SetSkipWaitHandlerMode() = 0;

    };

}

#endif // IWAITER_H
