#ifndef STRINGBOXWATCHER_H
#define STRINGBOXWATCHER_H
#include "engine_global.h"

#include "iresourcewatcher.h"
#include "istringbox.h"
#include "istringboxproxy.h"
#include "stringboxperiodicalloader.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT StringBoxWatcher : public IResourceWatcher
    {
        Q_OBJECT
            QString Name;
            IStringBox *StringBox;
            StringBoxPeriodicalLoader *PeriodicalLoader;
            bool Disabled;
        public:
            explicit StringBoxWatcher(QObject *parent = 0);
            void SetStringBox(IStringBox * StringBox);
            void SetStringBoxPeriodicalLoader(StringBoxPeriodicalLoader * PeriodicalLoader);


            virtual int GetRenewInSeconds();
            virtual int GetReadyCount();
            virtual QString GetName();
            void SetName(const QString& Name);

            virtual bool IsDisabled();
        signals:

        public slots:
            virtual void Disable();

    };
}

#endif // STRINGBOXWATCHER_H
