#ifndef IRESOURCEHANDLERSFACTORY_H
#define IRESOURCEHANDLERSFACTORY_H
#include "engine_global.h"

#include <QObject>
#include "iresourcehandlers.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IResourceHandlersFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit IResourceHandlersFactory(QObject *parent = 0);
        virtual IResourceHandlers * CreateResourceHandlers() = 0;
    signals:

    public slots:

    };
}

#endif // IRESOURCEHANDLERSFACTORY_H
