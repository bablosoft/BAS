#ifndef BASSCHEMEHANDLER_H
#define BASSCHEMEHANDLER_H

#include <QObject>
#include <QWebEngineUrlSchemeHandler>


class BasSchemeHandler : public QWebEngineUrlSchemeHandler
{
    Q_OBJECT
public:
    explicit BasSchemeHandler(QObject *parent = 0);
public:

    void requestStarted(QWebEngineUrlRequestJob *request);
};

#endif // BASSCHEMEHANDLER_H
