#ifndef STRINGBOXPROXY_H
#define STRINGBOXPROXY_H
#include "engine_global.h"

#include "istringboxproxy.h"
#include "istringbox.h"
#include "istringboxloader.h"
#include <QStringList>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT StringBoxProxy : public IStringBoxProxy
    {
        Q_OBJECT
        bool FilterIncome;
        QStringList LastPortion;
        QStringList LastPortionCollect;
        IStringBoxLoader * Loader;
        IStringBox * Box;

        bool Mix;
        void AddToBox(QStringList& list);
        bool DontGiveUp;
        bool FirstTimeLoaded;
    public:
        explicit StringBoxProxy(QObject *parent = 0);

    signals:

    public slots:
        void SetFilterIncome(bool filter);
        void SetStringBoxLoader(IStringBoxLoader * Loader);
        void SetStringBox(IStringBox * Box);
        virtual void Load();
        void SetMix(bool mix);
        bool GetMix();
        void SetDontGiveUp(bool DontGiveUp);
        bool GetDontGiveUp();
        virtual void Reload();
        virtual void ReloadOnDemad();
      
    private slots:
        void Loaded(QStringList &list);
        void DataLoadedCompletelySlot();
    };
}

#endif // STRINGBOXPROXY_H
