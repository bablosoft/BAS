#ifndef ISCRIPTMULTIWORKERREPORTDATA_H
#define ISCRIPTMULTIWORKERREPORTDATA_H
#include "engine_global.h"

#include <QObject>
#include <QHash>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IScriptMultiWorkerReportData : public QObject
    {
        Q_OBJECT
    public:
        explicit IScriptMultiWorkerReportData(QObject *parent = 0);

        virtual void Final(const QString& message) = 0;
        virtual void Start() = 0;
        virtual void Stop() = 0;

        virtual bool IsRunAtLeastOnce() = 0;
        virtual bool IsRunning() = 0;
        virtual int GetSuccessCount() = 0;
        virtual int GetSuccessAndRescuedCount() = 0;
        virtual QHash<QString,int> GetSuccessMessages() = 0;
        virtual QHash<QString,int> GetSuccessAndRescuedMessages() = 0;
        virtual int GetFailCount() = 0;
        virtual int GetFailAndRescuedCount() = 0;
        virtual QHash<QString,int> GetFailMessages() = 0;
        virtual QHash<QString,int> GetFailAndRescuedMessages() = 0;
        virtual QString GetFinal() = 0;
        virtual int GetSecondsSpent() = 0;
        virtual QHash<QString,QPair<int,int> > GetCaptchaStats() = 0;



    signals:

    public slots:
        virtual void CaptchaUsed(const QString& solver) = 0;
        virtual void CaptchaFailed(const QString& solver) = 0;

        virtual void Success(const QString& message) = 0;
        virtual void Fail(const QString& message) = 0;
        virtual void SuccessAndRescued(const QString& message) = 0;
        virtual void FailAndRescued(const QString& message) = 0;

    };
}

#endif // ISCRIPTMULTIWORKERREPORTDATA_H
