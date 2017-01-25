#ifndef TIMEOUTWAITER_H
#define TIMEOUTWAITER_H
#include "engine_global.h"

#include "iwaiter.h"
#include <QTimer>
#include <QEventLoop>
#include "waiterconnector.h"
#include "itimerproxy.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT TimeoutWaiter : public IWaiter
    {
        Q_OBJECT

        WaiterConnector * ConnectorSuccess;
        WaiterConnector * ConnectorFail;
        int Iterator;
        IWebElement * WebElement;
        QString Text;
        ITimerProxy *Timer;
        //QTimer *Timer;
        bool IsAborted;
        IResourceHandler *ResourceHandler;
        IEngineResources * EngineResources;
        QString SolverResult;
        QString SolverId;

        ISolver *Solver;
        QSet<QString> Refuse;
        bool ResourceRefused;
        int GeneralWait;
        int SolverWait;
        int GeneralWaitNext;
        int SolverWaitNext;
        ITimerProxy *GetTimer();
        bool SkipWaitHandlerMode;
        //QTimer *GetTimer();

        int GetGeneralWait();
        int GetSolverWait();
    public:
        explicit TimeoutWaiter(QObject *parent = 0);
        virtual void SetTimer(ITimerProxy *Timer);
    signals:

    public slots:
        virtual void WaitForSignal(const QObject *object_wait, const char * slot_signal ,const QObject *object_success,const char * slot_success,const QObject *object_fail,const char * slot_fail);
        virtual void WaitForSolver(ISolver * solver, const QString & id,const QObject *object_success,const char * slot_success,const QObject *object_fail,const char * slot_fail);
        virtual QString GetLastSolverResult();
        virtual QString GetLastSolverId();
        virtual void WaitForHandler(IEngineResources *res, const QString name, const QSet<QString>& refuse, const QObject *object_success,const char * slot_success,const QObject *object_fail,const char * slot_fail);
        virtual IResourceHandler *GetLastHandler();
        virtual void WaitForStageFinished(const QObject *object_stage,const char * signal_finished,const QObject *object_listener,const char * slot_finished);
        virtual void WaitForElement(IWebElement* Element, const QString& text,const QObject *object_success,const char * slot_success,const QObject *object_fail,const char * slot_fail);
        virtual void Sleep(int milliseconds,const QObject *object_success,const char * slot_success);
        virtual void Abort();
        virtual void Stop();
        virtual bool IsActive();
        virtual void WaitInfinity(const QObject *object_wait, const char * slot_signal ,const QObject *object_success,const char * slot_success);
        virtual bool IsResourceRefused();
        virtual void SetGeneralWaitTimeout(int timeout);
        virtual void SetSolverWaitTimeout(int timeout);
        virtual void SetGeneralWaitTimeoutNext(int timeout);
        virtual void SetSolverWaitTimeoutNext(int timeout);
        virtual int GetGeneralWaitTimeoutNext();
        virtual int GetSolverWaitTimeoutNext();
        virtual void SetSkipWaitHandlerMode();
    private slots:
        void WaitForElementIteration();
        void WaitForElementRespond(const QString& res);
        void WaitForHandlerIteration();
        void ObtainSolverResult(const QString& val, const QString& id, bool res, const QString& solver_id);
        void RestoreConnectors();
        void DisconnectFromSolver();
    };
}

#endif // TIMEOUTWAITER_H
