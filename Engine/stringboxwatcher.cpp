#include "stringboxwatcher.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    StringBoxWatcher::StringBoxWatcher(QObject *parent) :
        IResourceWatcher(parent)
    {
        Disabled = false;
    }

    void StringBoxWatcher::SetStringBox(IStringBox * StringBox)
    {
        this->StringBox = StringBox;
        connect(StringBox,SIGNAL(destroyed()),this,SLOT(Disable()));
    }

    void StringBoxWatcher::SetStringBoxPeriodicalLoader(StringBoxPeriodicalLoader * PeriodicalLoader)
    {
        this->PeriodicalLoader = PeriodicalLoader;
    }

    int StringBoxWatcher::GetRenewInSeconds()
    {
        return PeriodicalLoader->GetSecsToNextReloadInterval();
    }


    int StringBoxWatcher::GetReadyCount()
    {
        return StringBox->GetTotalLength();
    }

    QString StringBoxWatcher::GetName()
    {
        return Name;
    }

    void StringBoxWatcher::SetName(const QString& Name)
    {
        this->Name = Name;
    }

    void StringBoxWatcher::Disable()
    {
        Disabled = true;
    }

    bool StringBoxWatcher::IsDisabled()
    {
        return Disabled;
    }
}
