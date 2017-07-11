#include "substagemanager.h"

SubstageManager::SubstageManager()
{

}

void SubstageManager::AddSubstage(int Id, qint64 MaxSuccessLeft, qint64 MaxFailureLeft, qint64 ThreadsWorking, QList<BrowserAutomationStudioFramework::IBrowser *> Browsers)
{
    Substage s;
    s.Id = Id;
    s.MaxFailureLeft = MaxFailureLeft;
    s.MaxSuccessLeft = MaxSuccessLeft;
    s.ThreadsWorking = ThreadsWorking;
    s.Browsers = Browsers;
    Stages[Id] = s;
}

QList<BrowserAutomationStudioFramework::IWorker *> * SubstageManager::GetWorkers(int Id)
{
    if(!Stages.contains(Id))
        return 0;

    Substage &s = Stages[Id];
    return &s.Workers;

}

QList<BrowserAutomationStudioFramework::IBrowser *> *SubstageManager::GetBrowsers(int Id)
{
    if(!Stages.contains(Id))
        return 0;

    Substage &s = Stages[Id];
    return &s.Browsers;

}


QList<BrowserAutomationStudioFramework::IWorker *> SubstageManager::GetAllWorkers()
{
    QList<BrowserAutomationStudioFramework::IWorker *> res;
    for(Substage s:Stages)
    {
        for(BrowserAutomationStudioFramework::IWorker * w:s.Workers)
        {
            res.append(w);
        }
    }
    return res;
}

int SubstageManager::TotalWorkers()
{
    int res = 0;
    for(Substage s:Stages)
    {
        res += s.Workers.length();
    }
    return res;
}

QList<BrowserAutomationStudioFramework::IBrowser *> SubstageManager::GetAllBrowsers()
{
    QList<BrowserAutomationStudioFramework::IBrowser *> res;
    for(Substage s:Stages)
    {
        for(BrowserAutomationStudioFramework::IBrowser * b:s.Browsers)
        {
            res.append(b);
        }
    }
    return res;
}


void SubstageManager::Success(int Id)
{
    if(!Stages.contains(Id))
        return;

    Substage &s = Stages[Id];
    s.MaxSuccessLeft --;
}

void SubstageManager::Failure(int Id)
{
    if(!Stages.contains(Id))
        return;

    Substage &s = Stages[Id];
    s.MaxFailureLeft --;
}

void SubstageManager::Die(int Id)
{
    if(!Stages.contains(Id))
        return;

    Substage &s = Stages[Id];
    s.IsDead = true;
}


bool SubstageManager::CreateThread(int Id)
{
    if(!Stages.contains(Id))
        return false;

    Substage &s = Stages[Id];
    bool CanCreateThread = s.MaxSuccessLeft > 0 && s.MaxFailureLeft > 0 && !s.IsDead;
    if(!CanCreateThread)
    {
        s.ThreadsWorking --;
    }

    return CanCreateThread;
}

void SubstageManager::EndThread(int Id)
{
    if(!Stages.contains(Id))
        return;
    Substage &s = Stages[Id];
    s.ThreadsWorking --;
}

void SubstageManager::RemoveStage(int Id)
{
    if(!Stages.contains(Id))
        return;

    Stages.remove(Id);
}


bool SubstageManager::NeedToFinishStage(int Id)
{
    if(!Stages.contains(Id))
        return true;

    Substage &s = Stages[Id];
    bool NeedToFinish = s.ThreadsWorking <= 0;
    /*if(NeedToFinish)
    {
        Stages.remove(Id);
    }*/

    //qDebug()<<s.ThreadsWorking<<NeedToFinish;

    return NeedToFinish;
}

void SubstageManager::Clear()
{
    Stages.clear();
}
