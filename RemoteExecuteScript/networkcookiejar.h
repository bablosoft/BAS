#ifndef NETWORKCOOKIEJAR_H
#define NETWORKCOOKIEJAR_H

#include <QNetworkCookieJar>
#include <QNetworkCookie>


class NetworkCookieJar : public QNetworkCookieJar
{
    Q_OBJECT
public:
    explicit NetworkCookieJar(QObject *parent = 0);
    QList<QNetworkCookie> AllCookies();
signals:

public slots:

};


#endif // NETWORKCOOKIEJAR_H
