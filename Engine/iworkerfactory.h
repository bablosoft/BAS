#ifndef IWORKERFACTORY_H
#define IWORKERFACTORY_H
#include "engine_global.h"

#include <QObject>
#include "iworker.h"
namespace BrowserAutomationStudioFramework
{
    class IWorker;
    class ENGINESHARED_EXPORT IWorkerFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit IWorkerFactory(QObject *parent = 0);
        virtual IWorker *CreateWorker() = 0;
    signals:

    public slots:

    };
}

#endif // IWORKERFACTORY_H
