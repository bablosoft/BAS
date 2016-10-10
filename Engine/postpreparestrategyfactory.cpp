#include "postpreparestrategyfactory.h"
#include "postpreparestrategymultipart.h"
#include "postpreparestrategyurlencode.h"
#include "postpreparestrategyjsonencode.h"
#include "postpreparestrategycustomencode.h"
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
        }else if (type == "urlencode")
        {
            res = new PostPrepareStrategyUrlEncode();
        }else if (type == "json")
        {
            res = new PostPrepareStrategyJsonEncode();
        }else
        {
            PostPrepareStrategyCustomEncode *r = new PostPrepareStrategyCustomEncode();
            r->SetContentType(type);
            res = r;
        }
        return res;

    }
}
