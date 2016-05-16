#include "resourcehandlers.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    ResourceHandlers::ResourceHandlers(QObject *parent) :
        IResourceHandlers(parent)
    {
    }

    void ResourceHandlers::Disconnect(IResourceHandler *handler)
    {
        disconnect(handler,SIGNAL(DieSignal()),this,SLOT(Used()));
        disconnect(handler,SIGNAL(SuccessSignal()),this,SLOT(Used()));
        disconnect(handler,SIGNAL(FailSignal()),this,SLOT(Used()));
    }
    void ResourceHandlers::Connect(IResourceHandler *handler)
    {
        connect(handler,SIGNAL(DieSignal()),this,SLOT(Used()));
        connect(handler,SIGNAL(SuccessSignal()),this,SLOT(Used()));
        connect(handler,SIGNAL(FailSignal()),this,SLOT(Used()));
    }


    void ResourceHandlers::AddHandler(IResourceHandler *handler)
    {
        Data.append(handler);
        Connect(handler);
    }

    void ResourceHandlers::Die()
    {
        foreach(IResourceHandler * handler,Data)
        {
            Disconnect(handler);
            handler->die();
            handler->deleteLater();
        }
        Data.clear();
    }
    void ResourceHandlers::Success()
    {
        foreach(IResourceHandler * handler,Data)
        {
            Disconnect(handler);
            handler->success();
            handler->deleteLater();
        }
        Data.clear();
    }
    void ResourceHandlers::Fail()
    {
        foreach(IResourceHandler * handler,Data)
        {
            Disconnect(handler);
            handler->fail();
            handler->deleteLater();
        }
        Data.clear();
    }

    void ResourceHandlers::Used()
    {
        IResourceHandler * handler = qobject_cast<IResourceHandler *>(sender());
        Disconnect(handler);
        Data.removeOne(handler);
        handler->deleteLater();
    }
}
