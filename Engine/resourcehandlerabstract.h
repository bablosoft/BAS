#ifndef RESOURCEHANDLERABSTRACT_H
#define RESOURCEHANDLERABSTRACT_H
#include "engine_global.h"

#include "iresourcehandler.h"
#include "iengineresource.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ResourceHandlerAbstract : public IResourceHandler
    {
        Q_OBJECT
        IResourceHandler::HandlerStatus Status;
    public:
        explicit ResourceHandlerAbstract(QObject *parent = 0);
        ~ResourceHandlerAbstract();
    signals:

    public slots:
        virtual QScriptValue get() = 0;
        virtual void success();
        virtual void fail();
        virtual void die();
        virtual void purge();
        virtual void update(const QStringList& data);

        virtual HandlerStatus GetHandlerStatus();


        virtual void SetHandlerStatus(HandlerStatus status);
    };
}

#endif // RESOURCEHANDLERABSTRACT_H
