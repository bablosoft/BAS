#include "engineresourceabstract.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    EngineResourceAbstract::EngineResourceAbstract(QObject *parent) :
        IEngineResource(parent)
    {
    }

    void EngineResourceAbstract::SetInfo(const QString& key, const QString& value)
    {
        InfoHash[key] = value;
    }

    QString EngineResourceAbstract::GetInfo(const QString& key)
    {
        return InfoHash[key];
    }
}
