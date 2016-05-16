#ifndef HELPERFACTORY_H
#define HELPERFACTORY_H

#include "engine_global.h"

#include <QObject>
#include "ihelperfactory.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT HelperFactory : public IHelperFactory
    {
        Q_OBJECT
    public:
        explicit HelperFactory(QObject *parent = 0);
        virtual IHelper * GetHelper();
    signals:

    public slots:

    };
}

#endif // HELPERFACTORY_H
