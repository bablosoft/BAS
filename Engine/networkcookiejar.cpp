#include "networkcookiejar.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    NetworkCookieJar::NetworkCookieJar(QObject *parent) : QNetworkCookieJar(parent)
    {
    }

    QList<QNetworkCookie> NetworkCookieJar::AllCookies()
    {
        return QNetworkCookieJar::allCookies();
    }
}
