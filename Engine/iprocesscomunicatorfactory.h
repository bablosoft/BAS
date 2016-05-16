#ifndef IPROCESSCOMUNICATORFACTORY_H
#define IPROCESSCOMUNICATORFACTORY_H
#include "engine_global.h"

#include <QObject>
#include "iprocesscomunicator.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IProcessComunicatorFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit IProcessComunicatorFactory(QObject *parent = 0);
        virtual IProcessComunicator * CreateProcessComunicator() = 0;
    signals:

    public slots:

    };
}

#endif // IPROCESSCOMUNICATORFACTORY_H
