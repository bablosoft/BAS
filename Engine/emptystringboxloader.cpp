#include "emptystringboxloader.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    EmptyStringBoxLoader::EmptyStringBoxLoader(QObject *parent) :
        IStringBoxLoader(parent)
    {
    }

    void EmptyStringBoxLoader::Load()
    {
        QStringList list;
        emit DataLoadedCompletely();
        emit Loaded(list);

    }
}
