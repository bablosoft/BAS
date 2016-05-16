#include "postpreparestrategyfactory.h"
#include "postpreparestrategymultipart.h"
#include "postpreparestrategyurlencode.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    PostPrepareStrategyFactory::PostPrepareStrategyFactory(QObject *parent) :
        IPostPrepareStrategyFactory(parent)
    {
    }

    IPostPrepareStrategy* PostPrepareStrategyFactory::Create(const QString& type)
    {
        IPostPrepareStrategy* res = 0;
        if(type == "multipart")
        {
            res = new PostPrepareStrategyMultipart();
        }if (type == "urlencode")
        {
            res = new PostPrepareStrategyUrlEncode();
        }
        return res;

    }
}
