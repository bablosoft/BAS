#ifndef RESOURCEHANDLERSFACTORY_H
#define RESOURCEHANDLERSFACTORY_H
#include "engine_global.h"

#include "iresourcehandlersfactory.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ResourceHandlersFactory : public IResourceHandlersFactory
    {
        Q_OBJECT
    public:
        explicit ResourceHandlersFactory(QObject *parent = 0);
        virtual IResourceHandlers * CreateResourceHandlers();
    signals:

    public slots:

    };
}

#endif // RESOURCEHANDLERSFACTORY_H
