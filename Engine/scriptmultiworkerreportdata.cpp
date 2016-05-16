#include "scriptmultiworkerreportdata.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    ScriptMultiWorkerReportData::ScriptMultiWorkerReportData(QObject *parent) :
        IScriptMultiWorkerReportData(parent)
    {
        SuccessCount = 0;
        FailCount = 0;
        SuccessAndRescuedCount = 0;
        FailAndRescuedCount = 0;
        Running = false;
        RunAtLeastOnce = false;
    }

    void ScriptMultiWorkerReportData::Success(const QString& message)
    {
        if(!Running)
            return;
        SuccessCount++;
        if(SuccessMessages.contains(message))
        {
            SuccessMessages[message]++;
        }else
        {
            SuccessMessages[message] = 1;
        }
    }

    void ScriptMultiWorkerReportData::SuccessAndRescued(const QString& message)
    {
        if(!Running)
            return;
        SuccessAndRescuedCount++;
        if(SuccessAndRescuedMessages.contains(message))
        {
            SuccessAndRescuedMessages[message]++;
        }else
        {
            SuccessAndRescuedMessages[message] = 1;
        }
    }

    void ScriptMultiWorkerReportData::Fail(const QString& message)
    {
        if(!Running)
            return;
        FailCount++;
        if(FailMessages.contains(message))
        {
            FailMessages[message]++;
        }else
        {
            FailMessages[message] = 1;
        }
    }

    void ScriptMultiWorkerReportData::FailAndRescued(const QString& message)
    {
        if(!Running)
            return;
        FailAndRescuedCount++;
        if(FailAndRescuedMessages.contains(message))
        {
            FailAndRescuedMessages[message]++;
        }else
        {
            FailAndRescuedMessages[message] = 1;
        }
    }

    void ScriptMultiWorkerReportData::Final(const QString& message)
    {
        if(!Running)
            return;
        FinalMessage = message;
    }
    void ScriptMultiWorkerReportData::Start()
    {
        RunAtLeastOnce = true;
        Running = true;
        SuccessCount = 0;
        FailCount = 0;
        SuccessAndRescuedCount = 0;
        FailAndRescuedCount = 0;
        SuccessMessages.clear();
        FailMessages.clear();
        SuccessAndRescuedMessages.clear();
        FailAndRescuedMessages.clear();
        CaptchaStats.clear();
        ScriptStart = QDateTime::currentDateTime();
    }

    void ScriptMultiWorkerReportData::Stop()
    {
        if(Running)
        {
            ScriptEnd = QDateTime::currentDateTime();
            Running = false;
        }
    }

    void ScriptMultiWorkerReportData::CaptchaUsed(const QString& solver)
    {
        if(!Running)
            return;
        if(CaptchaStats.contains(solver))
        {
            QPair<int,int> pair = CaptchaStats[solver];
            pair.first++;
            CaptchaStats[solver] = pair;
        }else
        {
            QPair<int,int> pair;
            pair.first = 1;
            pair.second = 0;
            CaptchaStats[solver] = pair;
        }
    }
    void ScriptMultiWorkerReportData::CaptchaFailed(const QString& solver)
    {
        if(!Running)
            return;
        if(CaptchaStats.contains(solver))
        {
            QPair<int,int> pair = CaptchaStats[solver];
            pair.second++;
            CaptchaStats[solver] = pair;
        }else
        {
            QPair<int,int> pair;
            pair.first = 0;
            pair.second = 1;
            CaptchaStats[solver] = pair;
        }
    }

    int ScriptMultiWorkerReportData::GetSuccessCount()
    {
        return SuccessCount;
    }
    QHash<QString,int> ScriptMultiWorkerReportData::GetSuccessMessages()
    {
        return SuccessMessages;
    }
    int ScriptMultiWorkerReportData::GetFailCount()
    {
        return FailCount;
    }
    QHash<QString,int> ScriptMultiWorkerReportData::GetFailMessages()
    {
        return FailMessages;
    }

    int ScriptMultiWorkerReportData::GetSuccessAndRescuedCount()
    {
        return SuccessAndRescuedCount;
    }
    QHash<QString,int> ScriptMultiWorkerReportData::GetSuccessAndRescuedMessages()
    {
        return SuccessAndRescuedMessages;
    }
    int ScriptMultiWorkerReportData::GetFailAndRescuedCount()
    {
        return FailAndRescuedCount;
    }
    QHash<QString,int> ScriptMultiWorkerReportData::GetFailAndRescuedMessages()
    {
        return FailAndRescuedMessages;
    }

    QString ScriptMultiWorkerReportData::GetFinal()
    {
        return FinalMessage;
    }
    int ScriptMultiWorkerReportData::GetSecondsSpent()
    {
        if(!RunAtLeastOnce)
        {
            return 0;
        }

        QDateTime end;
        if(Running)
            end = QDateTime::currentDateTime();
        else
            end = ScriptEnd;
        return ScriptStart.secsTo(end);
    }

    bool ScriptMultiWorkerReportData::IsRunAtLeastOnce()
    {
        return RunAtLeastOnce;
    }

    bool ScriptMultiWorkerReportData::IsRunning()
    {
        return Running;
    }

    QHash<QString,QPair<int,int> > ScriptMultiWorkerReportData::GetCaptchaStats()
    {
        return CaptchaStats;
    }
}
