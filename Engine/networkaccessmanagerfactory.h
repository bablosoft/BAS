#ifndef NETWORKACCESSMANAGERFACTORY_H
#define NETWORKACCESSMANAGERFACTORY_H
#include "engine_global.h"

#include "inetworkaccessmanagerfactory.h"


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT NetworkAccessManagerFactory : public INetworkAccessManagerFactory
    {
        Q_OBJECT
    public:
        explicit NetworkAccessManagerFactory(QObject *parent = 0);
        virtual INetworkAccessManager* CreateNetworkAccessManager();
    signals:

    public slots:

    };
}
#endif // NETWORKACCESSMANAGERFACTORY_H
