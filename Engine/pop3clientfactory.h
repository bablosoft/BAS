#ifndef POP3CLIENTFACTORY_H
#define POP3CLIENTFACTORY_H
#include "engine_global.h"

#include "ipop3clientfactory.h"
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT Pop3ClientFactory : public IPop3ClientFactory
    {
        Q_OBJECT
    public:
        explicit Pop3ClientFactory(QObject *parent = 0);
        virtual IPop3Client * GetPop3Client();
    signals:

    public slots:

    };
}
#endif // POP3CLIENTFACTORY_H
