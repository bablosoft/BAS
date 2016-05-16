#ifndef SUBPROCESSNETWORKACCESSMANAGERFACTORY_H
#define SUBPROCESSNETWORKACCESSMANAGERFACTORY_H
#include "engine_global.h"

#include "inetworkaccessmanagerfactory.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT SubprocessNetworkAccessManagerFactory : public INetworkAccessManagerFactory
    {
        Q_OBJECT
    public:
        explicit SubprocessNetworkAccessManagerFactory(QObject *parent = 0);
        virtual INetworkAccessManager* CreateNetworkAccessManager();
    signals:

    public slots:

    };
}

#endif // SUBPROCESSNETWORKACCESSMANAGERFACTORY_H
