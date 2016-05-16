#ifndef PERIODICALHTTPREQUEST_H
#define PERIODICALHTTPREQUEST_H
#include "engine_global.h"
#include <QObject>
#include <QTimer>

#include "ihttpclientfactory.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT PeriodicalHttpRequest : public QObject
    {
        Q_OBJECT
        IHttpClientFactory *HttpClientFactory;
        IHttpClient * HttpClient;
        QString Url;
        QString LastResponse;
        bool StartedMonitor;
        QTimer Timer;
        public:
            explicit PeriodicalHttpRequest(QObject *parent = 0);

        signals:

        public slots:
            void SetHttpClientFactory(IHttpClientFactory * HttpClientFactory);
            void Start(const QString& Url);
            QString GetLastResponce();
        private slots:
            void StartIteration();
            void DoneIteration();
    };
}

#endif // PERIODICALHTTPREQUEST_H
