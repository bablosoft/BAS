#ifndef IHTTPCLIENTFACTORY_H
#define IHTTPCLIENTFACTORY_H
#include "engine_global.h"

#include <QObject>
#include "ihttpclient.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IHttpClientFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit IHttpClientFactory(QObject *parent = 0);
        virtual IHttpClient * GetHttpClient() = 0;
    signals:

    public slots:

    };
}

#endif // IHTTPCLIENTFACTORY_H
