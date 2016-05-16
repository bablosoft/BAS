#include "browserpluginpath.h"
#include <QDir>
#include <QtGlobal>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    BrowserPluginPath::BrowserPluginPath(QObject *parent) :
        QObject(parent)
    {
    }
    void BrowserPluginPath::SetBrowserPluginPath()
    {
        QDir dir;
        qputenv("QTWEBKIT_PLUGIN_PATH",QString(QDir::cleanPath(dir.absolutePath() + QDir::separator() + "webkitplugins")).toUtf8());
    }
}
