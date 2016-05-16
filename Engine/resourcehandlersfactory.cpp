#include "resourcehandlersfactory.h"
#include "resourcehandlers.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    ResourceHandlersFactory::ResourceHandlersFactory(QObject *parent) :
        IResourceHandlersFactory(parent)
    {
    }
    IResourceHandlers * ResourceHandlersFactory::CreateResourceHandlers()
    {
        return new ResourceHandlers();
    }
}
