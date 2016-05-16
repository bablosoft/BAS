#ifndef IPOSTPREPARESTRATEGYFACTORY_H
#define IPOSTPREPARESTRATEGYFACTORY_H
#include "engine_global.h"
#include <QObject>
#include "ipostpreparestrategy.h"

namespace BrowserAutomationStudioFramework
{
    class IPostPrepareStrategy;
    class ENGINESHARED_EXPORT IPostPrepareStrategyFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit IPostPrepareStrategyFactory(QObject *parent = 0);
        virtual IPostPrepareStrategy* Create(const QString& type) = 0;
    signals:

    public slots:

    };
}

#endif // IPOSTPREPARESTRATEGYFACTORY_H
