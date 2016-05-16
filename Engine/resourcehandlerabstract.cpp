#include "resourcehandlerabstract.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    ResourceHandlerAbstract::ResourceHandlerAbstract(QObject *parent) :
        IResourceHandler(parent)
    {
    }
    ResourceHandlerAbstract::~ResourceHandlerAbstract()
    {

    }

    void ResourceHandlerAbstract::success()
    {
        emit SuccessSignal();
    }

    void ResourceHandlerAbstract::fail()
    {
        emit FailSignal();
    }

    void ResourceHandlerAbstract::die()
    {
        emit DieSignal();
    }
    
    void ResourceHandlerAbstract::purge()
    {
        emit PurgeSignal();    
    }
    
    void ResourceHandlerAbstract::update(const QStringList& data)
    {
        emit UpdateSignal(data);
    }

    IResourceHandler::HandlerStatus ResourceHandlerAbstract::GetHandlerStatus()
    {
        return Status;
    }

    void ResourceHandlerAbstract::SetHandlerStatus(HandlerStatus status)
    {
        Status = status;
    }

}
