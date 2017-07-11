#ifndef IBROWSERFACTORY_H
#define IBROWSERFACTORY_H
#include "engine_global.h"

#include <QObject>
#include "ibrowser.h"
#include "inetworkaccessmanagerfactory.h"

namespace BrowserAutomationStudioFramework
{
    class IBrowser;
    class INetworkAccessManagerFactory;
    class ENGINESHARED_EXPORT IBrowserFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit IBrowserFactory(QObject *parent = 0);
        virtual void ClearAll() = 0;
        virtual void Clear(QList<IBrowser*>* Browsers) = 0;
        virtual QList<IBrowser*> Create(int size) = 0;
        virtual void SetNetworkAccessManager(INetworkAccessManagerFactory *NetworkAccessManagerFactory) = 0;
        virtual INetworkAccessManagerFactory * GetNetworkAccessManager() = 0;
    signals:
        void OnBrowserCreated();
    public slots:

    };
}

#endif // IBROWSERFACTORY_H
