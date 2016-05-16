#include "networkaccessmanagerfactory.h"
#include "networkaccessmanager.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    NetworkAccessManagerFactory::NetworkAccessManagerFactory(QObject *parent) :
        INetworkAccessManagerFactory(parent)
    {
    }

    INetworkAccessManager* NetworkAccessManagerFactory::CreateNetworkAccessManager()
    {
        return new NetworkAccessManager();
    }
}
