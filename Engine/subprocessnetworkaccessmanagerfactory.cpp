#include "subprocessnetworkaccessmanagerfactory.h"
#include "subprocessnetworkaccessmanager.h"
#include "every_cpp.h"
namespace BrowserAutomationStudioFramework
{

    SubprocessNetworkAccessManagerFactory::SubprocessNetworkAccessManagerFactory(QObject *parent) :
        INetworkAccessManagerFactory(parent)
    {
    }

    INetworkAccessManager* SubprocessNetworkAccessManagerFactory::CreateNetworkAccessManager()
    {
        return new SubprocessNetworkAccessManager();
    }

}
