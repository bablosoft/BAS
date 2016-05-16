#ifndef POSTPREPARESTRATEGYFACTORY_H
#define POSTPREPARESTRATEGYFACTORY_H
#include "engine_global.h"
#include "ipostpreparestrategyfactory.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT PostPrepareStrategyFactory : public IPostPrepareStrategyFactory
    {
        Q_OBJECT
    public:
        explicit PostPrepareStrategyFactory(QObject *parent = 0);
        virtual IPostPrepareStrategy* Create(const QString& type);
    signals:

    public slots:

    };
}

#endif // POSTPREPARESTRATEGYFACTORY_H
