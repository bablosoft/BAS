#include "pop3clientfactory.h"
#include "pop3client.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    Pop3ClientFactory::Pop3ClientFactory(QObject *parent) :
        IPop3ClientFactory(parent)
    {
    }
    IPop3Client * Pop3ClientFactory::GetPop3Client()
    {
        return new Pop3Client();
    }
}
