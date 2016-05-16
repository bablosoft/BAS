#ifndef SCRIPTWORKERFACTORY_H
#define SCRIPTWORKERFACTORY_H
#include "engine_global.h"
#include "iworkerfactory.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ScriptWorkerFactory : public IWorkerFactory
    {
        Q_OBJECT
    public:
        explicit ScriptWorkerFactory(QObject *parent = 0);
        virtual IWorker *CreateWorker();
    signals:

    public slots:

    };
}

#endif // SCRIPTWORKERFACTORY_H
