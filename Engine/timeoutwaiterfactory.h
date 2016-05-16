#ifndef TIMEOUTWAITERFACTORY_H
#define TIMEOUTWAITERFACTORY_H
#include "engine_global.h"

#include "iwaiterfactory.h"
#include "timeoutwaiter.h"
#include "multitimer.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT TimeoutWaiterFactory : public IWaiterFactory
    {
        Q_OBJECT
        BrowserAutomationStudioFramework::MultiTimer * _MultiTimer;
    public:
        explicit TimeoutWaiterFactory(QObject *parent = 0);
        void SetMultiWorker(MultiTimer * _MultiTimer);
        virtual IWaiter * CreateWaiter();
    signals:

    public slots:

    };
}

#endif // TIMEOUTWAITERFACTORY_H
