#ifndef HTTPCLIENTFACTORY_H
#define HTTPCLIENTFACTORY_H
#include "engine_global.h"

#include <QObject>
#include "ihttpclientfactory.h"
#include "ipostpreparestrategyfactory.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT HttpClientFactory : public IHttpClientFactory
    {
        Q_OBJECT
        IPostPrepareStrategyFactory *PostPrepareStrategyFactoryObject;
    public:
        explicit HttpClientFactory(QObject *parent = 0);
        virtual IHttpClient * GetHttpClient();
    signals:

    public slots:

    };
}

#endif // HTTPCLIENTFACTORY_H
