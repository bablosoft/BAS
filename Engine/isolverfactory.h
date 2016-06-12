#ifndef ISOLVERFACTORY_H
#define ISOLVERFACTORY_H
#include "engine_global.h"

#include <QObject>
#include "isolver.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ISolverFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit ISolverFactory(QObject *parent = 0);
        virtual ISolver* GetSolver(const QString& name) = 0;
    signals:
        void UsedSolver(const QString& Name);
        void FailedSolver(const QString& Name);
    public slots:

    };
}

#endif // ISOLVERFACTORY_H
