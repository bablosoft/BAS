#ifndef IPOP3CLIENTFACTORY_H
#define IPOP3CLIENTFACTORY_H
#include "engine_global.h"

#include "ipop3client.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IPop3ClientFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit IPop3ClientFactory(QObject *parent = 0);
        virtual IPop3Client * GetPop3Client() = 0;
    signals:

    public slots:

    };
}

#endif // IPOP3CLIENTFACTORY_H
