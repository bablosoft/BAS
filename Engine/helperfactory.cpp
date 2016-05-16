#include "helperfactory.h"
#include "helper.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    HelperFactory::HelperFactory(QObject *parent) :
        IHelperFactory(parent)
    {
    }

    IHelper * HelperFactory::GetHelper()
    {
        return new Helper();
    }
}
