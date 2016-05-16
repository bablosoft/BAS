#include "imapclientfactory.h"
#include "imapclient.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    ImapClientFactory::ImapClientFactory(QObject *parent) :
        IImapClientFactory(parent)
    {
    }

    IImapClient * ImapClientFactory::GetImapClient()
    {
        return new ImapClient();
    }
}
