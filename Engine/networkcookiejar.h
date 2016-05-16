#ifndef NETWORKCOOKIEJAR_H
#define NETWORKCOOKIEJAR_H

#include "engine_global.h"
#include <QNetworkCookieJar>
#include <QNetworkCookie>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT NetworkCookieJar : public QNetworkCookieJar
    {
        Q_OBJECT
    public:
        explicit NetworkCookieJar(QObject *parent = 0);
        QList<QNetworkCookie> AllCookies();
    signals:

    public slots:

    };
}

#endif // NETWORKCOOKIEJAR_H
