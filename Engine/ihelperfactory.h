#ifndef IHELPERFACTORY_H
#define IHELPERFACTORY_H

#include "engine_global.h"

#include <QObject>
#include "ihelper.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IHelperFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit IHelperFactory(QObject *parent = 0);
        virtual IHelper * GetHelper() = 0;
    signals:

    public slots:

    };
}
#endif // IHELPERFACTORY_H
