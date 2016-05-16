#ifndef RESOURCEHANDLERS_H
#define RESOURCEHANDLERS_H
#include "engine_global.h"

#include "iresourcehandlers.h"
#include "iresourcehandler.h"
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ResourceHandlers : public IResourceHandlers
    {
        Q_OBJECT
        QList<IResourceHandler *> Data;
        void Disconnect(IResourceHandler *handler);
        void Connect(IResourceHandler *handler);
    public:
        explicit ResourceHandlers(QObject *parent = 0);

    public slots:

        virtual void AddHandler(IResourceHandler *handler);
        virtual void Die();
        virtual void Success();
        virtual void Fail();
    private slots:
        void Used();
    };
}

#endif // RESOURCEHANDLERS_H
