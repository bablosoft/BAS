#include "networkcookiejar.h"


    NetworkCookieJar::NetworkCookieJar(QObject *parent) : QNetworkCookieJar(parent)
    {
    }

    QList<QNetworkCookie> NetworkCookieJar::AllCookies()
    {
        return QNetworkCookieJar::allCookies();
    }

