#include "ihttpclient.h"
#include "every_cpp.h"
namespace BrowserAutomationStudioFramework
{
    IHttpClient::IHttpClient(QObject *parent) :
        QObject(parent)
    {
    }

    PostOptions::PostOptions()
    {
        PrepareStrategy = "multipart";
    }

}
