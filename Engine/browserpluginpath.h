#ifndef BROWSERPLUGINPATH_H
#define BROWSERPLUGINPATH_H
#include "engine_global.h"

#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT BrowserPluginPath : public QObject
    {
        Q_OBJECT
    public:
        explicit BrowserPluginPath(QObject *parent = 0);
        void SetBrowserPluginPath();
    signals:

    public slots:

    };
}

#endif // BROWSERPLUGINPATH_H
