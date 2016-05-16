#ifndef SCRIPTMULTIWORKERREPORTDATA_H
#define SCRIPTMULTIWORKERREPORTDATA_H
#include "engine_global.h"

#include <QObject>
#include <QDateTime>
#include "iscriptmultiworkerreportdata.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ScriptMultiWorkerReportData : public IScriptMultiWorkerReportData
    {
        Q_OBJECT
        QHash<QString,int> SuccessMessages;
        QHash<QString,int> FailMessages;
        QHash<QString,int> SuccessAndRescuedMessages;
        QHash<QString,int> FailAndRescuedMessages;
        int SuccessCount;
        int FailCount;
        int SuccessAndRescuedCount;
        int FailAndRescuedCount;
        QString FinalMessage;
        QDateTime ScriptStart;
        QDateTime ScriptEnd;
        QHash<QString,QPair<int,int> > CaptchaStats;
        bool Running;
        bool RunAtLeastOnce;

    public:
        explicit ScriptMultiWorkerReportData(QObject *parent);
        virtual void Final(const QString& message);
        virtual void Start();
        virtual void Stop();



        virtual bool IsRunning();
        virtual bool IsRunAtLeastOnce();
        virtual int GetSuccessCount();
        virtual int GetSuccessAndRescuedCount();
        virtual QHash<QString,int> GetSuccessMessages();
        virtual QHash<QString,int> GetSuccessAndRescuedMessages();
        virtual int GetFailCount();
        virtual int GetFailAndRescuedCount();
        virtual QHash<QString,int> GetFailMessages();
        virtual QHash<QString,int> GetFailAndRescuedMessages();
        virtual QString GetFinal();
        virtual int GetSecondsSpent();
        virtual QHash<QString,QPair<int,int> > GetCaptchaStats();
    signals:

    public slots:
        virtual void CaptchaUsed(const QString& solver);
        virtual void CaptchaFailed(const QString& solver);
        virtual void Success(const QString& message);
        virtual void Fail(const QString& message);
        virtual void SuccessAndRescued(const QString& message);
        virtual void FailAndRescued(const QString& message);

    };
}

#endif // SCRIPTMULTIWORKERREPORTDATA_H

