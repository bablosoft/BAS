#include "httpclientfactory.h"
#include "httpclient.h"
#include "curlhttpclient.h"

#include "postpreparestrategyfactory.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    HttpClientFactory::HttpClientFactory(QObject *parent) :
        IHttpClientFactory(parent)
    {
        PostPrepareStrategyFactoryObject = new PostPrepareStrategyFactory(this);
    }

    IHttpClient * HttpClientFactory::GetHttpClient()
    {
        IHttpClient* res = new CurlHttpClient();
        res->SetPostPrepareStrategyFactory(PostPrepareStrategyFactoryObject);
        return res;
    }

}
