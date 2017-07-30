#include "versioninfo.h"
#include "aboutbrowserstudio.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    VersionInfo::VersionInfo(QObject *parent) :
        IVersionInfo(parent)
    {
    }

    int VersionInfo::MajorVersion()
    {
        return 20;
    }

    int VersionInfo::MinorVersion()
    {
        return 0;
    }

    int VersionInfo::BuildVersion()
    {
        return 3;
    }

    QString VersionInfo::VersionString()
    {
        return QString("%1.%2.%3").arg(MajorVersion()).arg(MinorVersion()).arg(BuildVersion());
    }

    void VersionInfo::SetServerName(const QString& ServerName)
    {
        this->ServerName = ServerName;
    }

    void VersionInfo::ShowAboutWindow()
    {

        AboutBrowserStudio about(VersionString(), ServerName);
        about.exec();
    }
}
