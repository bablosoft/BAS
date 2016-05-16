#ifndef IWAITERFACTORY_H
#define IWAITERFACTORY_H
#include "engine_global.h"

#include <QObject>
#include "iwaiter.h"

namespace BrowserAutomationStudioFramework
{
    class IWaiter;
    class ENGINESHARED_EXPORT IWaiterFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit IWaiterFactory(QObject *parent = 0);
        virtual IWaiter * CreateWaiter() = 0;
    signals:

    public slots:

    };
}
#endif // IWAITERFACTORY_H
