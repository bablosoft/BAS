#include "scriptsuspender.h"
#include "every_cpp.h"



namespace BrowserAutomationStudioFramework
{
    ScriptSuspender::ScriptSuspender(QObject *parent) :
        IScriptSuspender(parent), MaxCount(100)
    {
        ResumeWatchTimer = new QTimer(this);
        TimerIndex = -1;
    }

    bool ScriptSuspender::Suspend(int milliseconds, IWorker *Worker)
    {
        if(Count() >= MaxCount)
            return false;

        Worker->setParent(this);
        Worker->GetBrowser()->OnSupend();

        Worker->SetBrowser(0);



        QDateTime now = QDateTime::currentDateTime();
        QPair<QDateTime,IWorker*> pair;
        pair.first = now.addMSecs(milliseconds);
        pair.second = Worker;
        Data.append(pair);
        UpdateTimerData();
        emit Suspended(Worker);
        return true;
    }

    void ScriptSuspender::UpdateTimerData()
    {
        ResumeWatchTimer->stop();
        ResumeWatchTimer->disconnect();

        QDateTime now = QDateTime::currentDateTime();
        QDateTime bestTime;
        TimerIndex = -1;
        bool foundBestTime = false;
        int len = Data.length();
        for(int i = 0;i<len;i++)
        {
            QDateTime time = Data.at(i).first;
            if(!foundBestTime || time < bestTime)
            {
                bestTime = time;
                foundBestTime = true;
                TimerIndex = i;
            }

        }
        if(foundBestTime)
        {
            int interval = now.msecsTo(bestTime);
            if(interval <= 1)
            {
               interval = 1;
            }
            ResumeWatchTimer->singleShot(interval,this,SLOT(OnTimer()));

        }
    }

    void ScriptSuspender::OnTimer()
    {
        if(TimerIndex<0)
            return;
        IWorker *NextWorker = Data.at(TimerIndex).second;
        NextWorkers.push_back(NextWorker);
        TimerIndex = -1;
        emit Resumed(NextWorker);
    }

    QPair<IWorker*,IScriptSuspender::WorkerStatus> ScriptSuspender::GetWorker()
    {
        QPair<IWorker*,IScriptSuspender::WorkerStatus> result;



        if(Count() == 0)
        {
            result.first = 0;
            result.second = IScriptSuspender::NotAvailable;
        }else
        {
            if(!NextWorkers.isEmpty())
            {
                IWorker *NextWorker = NextWorkers.takeFirst();
                int index = -1;
                int len = Count();
                for(int i = 0;i<len;i++)
                {
                    QPair<QDateTime,IWorker*> el = Data.at(i);
                    if(el.second == NextWorker)
                    {
                        index = i;
                        break;
                    }
                }
                result.first = NextWorker;
                result.second = IScriptSuspender::Ready;

                Data.removeAt(index);
                UpdateTimerData();

            }else
            {
                result.first = 0;
                result.second = IScriptSuspender::Wait;
            }

        }

        return result;
    }

    int ScriptSuspender::Count()
    {
        return Data.count();
    }

    void ScriptSuspender::SetMaxCount(int MaxCount)
    {
        this->MaxCount = MaxCount;
    }
}
