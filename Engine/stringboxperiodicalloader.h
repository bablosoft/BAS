#ifndef STRINGBOXPERIODICALLOADER_H
#define STRINGBOXPERIODICALLOADER_H
#include "engine_global.h"

#include <QObject>
#include "istringboxproxy.h"
#include <QTimer>
#include <QTime>
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT StringBoxPeriodicalLoader : public QObject
    {
        Q_OBJECT
        IStringBoxProxy * Proxy;
        QTimer * timerReload;
        QTimer * timerRenew;
        int ReloadInterval;
        int RenewInterval;
        bool NeedToRenewInsteadOfReload;
        bool StartedRenew;
        QDateTime NextRenewTime;
        bool IsLoading;
        bool IsAllDataLoaded;

    public:
        explicit StringBoxPeriodicalLoader(QObject *parent = 0);

    signals:

    public slots:
        void SetStringBoxProxy(IStringBoxProxy * Proxy);
        void SetReloadInterval(int ReloadInterval);
        void SetRenewInterval(int RenewInterval);
        void Start();
        int GetSecsToNextReloadInterval();


    private slots:
        void NextReload();
        void NextRenew();
        void SetNeedToRenewInsteadOfReload();
        void DataLoaded();
        void DataLoadedCompletely();
        void NeedToUpdate();
    };
}

#endif // STRINGBOXPERIODICALLOADER_H
