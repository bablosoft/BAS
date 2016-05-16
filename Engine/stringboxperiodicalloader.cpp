#include "stringboxperiodicalloader.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    StringBoxPeriodicalLoader::StringBoxPeriodicalLoader(QObject *parent) :
        QObject(parent)
    {
        NeedToRenewInsteadOfReload = false;
        StartedRenew = false;
        NextRenewTime = QDateTime::currentDateTime();
        RenewInterval = -1;
        IsLoading = false;
        IsAllDataLoaded = false;
    }

    void StringBoxPeriodicalLoader::SetStringBoxProxy(IStringBoxProxy * Proxy)
    {
        this->Proxy = Proxy;
        connect(Proxy,SIGNAL(NeedToUpdate()),this,SLOT(NeedToUpdate()));
    }

    void StringBoxPeriodicalLoader::SetReloadInterval(int ReloadInterval)
    {
        this->ReloadInterval = ReloadInterval;
        if(ReloadInterval)
        {
            timerReload = new QTimer(this);
            timerReload->setSingleShot(true);
        }
    }

    int StringBoxPeriodicalLoader::GetSecsToNextReloadInterval()
    {
        if(RenewInterval < 0)
            return -1;
        QDateTime now = QDateTime::currentDateTime();
        int res = now.secsTo(NextRenewTime);
        if(res<0)
            return 0;
        return res;
    }

    void StringBoxPeriodicalLoader::SetRenewInterval(int RenewInterval)
    {
        this->RenewInterval = RenewInterval;
        if(RenewInterval > 0)
        {
            timerRenew = new QTimer(this);
            timerRenew->setSingleShot(true);
        }
    }

    void StringBoxPeriodicalLoader::DataLoaded()
    {
        IsLoading = false;
        if(ReloadInterval)
        {
            timerReload->singleShot(ReloadInterval,this,SLOT(NextReload()));
            if(RenewInterval > 0 && !StartedRenew)
            {
                StartedRenew = true;
                NextRenewTime = QDateTime::currentDateTime().addMSecs(RenewInterval);
                timerRenew->singleShot(RenewInterval,this,SLOT(SetNeedToRenewInsteadOfReload()));
            }
        }else if(RenewInterval > 0)
        {
            NextRenewTime = QDateTime::currentDateTime().addMSecs(RenewInterval);
            timerRenew->singleShot(RenewInterval,this,SLOT(NextRenew()));
        }
    }
    void StringBoxPeriodicalLoader::DataLoadedCompletely()
    {
        IsAllDataLoaded = true;
    }

    void StringBoxPeriodicalLoader::NextReload()
    {
        if(NeedToRenewInsteadOfReload)
        {
            NeedToRenewInsteadOfReload = false;
            IsLoading = true;
            Proxy->Reload();
        }else
        {
            IsLoading = true;
            Proxy->Load();
        }
    }

    void StringBoxPeriodicalLoader::NeedToUpdate()
    {
        if(!ReloadInterval && RenewInterval <= 0 && !IsLoading && !IsAllDataLoaded)
        {
            IsLoading = true;
            Proxy->Load();
        }
    }

    void StringBoxPeriodicalLoader::SetNeedToRenewInsteadOfReload()
    {
        NeedToRenewInsteadOfReload = true;
        StartedRenew = false;
    }

    void StringBoxPeriodicalLoader::NextRenew()
    {
        IsLoading = true;
        Proxy->Reload();
    }

    void StringBoxPeriodicalLoader::Start()
    {
        connect(Proxy,SIGNAL(DataLoaded(QStringList&)),this,SLOT(DataLoaded()));
        connect(Proxy,SIGNAL(DataLoadedCompletely()),this,SLOT(DataLoadedCompletely()));
        NextReload();
    }
}
