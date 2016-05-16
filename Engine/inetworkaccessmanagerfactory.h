#ifndef INETWORKACCESSMANAGERFACTORY_H
#define INETWORKACCESSMANAGERFACTORY_H
#include "engine_global.h"

#include <QObject>
#include "inetworkaccessmanager.h"

namespace BrowserAutomationStudioFramework
{
    class INetworkAccessManager;
    class ENGINESHARED_EXPORT INetworkAccessManagerFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit INetworkAccessManagerFactory(QObject *parent = 0);
        virtual INetworkAccessManager* CreateNetworkAccessManager() = 0;
    signals:

    public slots:

    };
}

#endif // INETWORKACCESSMANAGERFACTORY_H
