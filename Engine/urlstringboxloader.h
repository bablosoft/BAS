#ifndef URLSTRINGBOXLOADER_H
#define URLSTRINGBOXLOADER_H
#include "engine_global.h"
#include "istringboxloader.h"
#include "ihttpclientfactory.h"
#include <QStringList>
#include "resourcemodelurl.h"
#include "iwaiter.h"

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT UrlStringBoxLoader : public IStringBoxLoader
    {
        Q_OBJECT
        QString Url;
        QStringList UrlList;
        int UrlIterator;
        IHttpClient *HttpClient;
        IHttpClientFactory *HttpClientFactory;
        bool IsLoading;
        QString Argument;
        ResourceModelUrl::CaptureMethod Capture;
        IWaiter*Waiter;
        int FailCount;
    public:
        explicit UrlStringBoxLoader(QObject *parent = 0);

        void SetUrl(const QString& Url);
        void SetHttpClientFactory(IHttpClientFactory *HttpClientFactory);

        ResourceModelUrl::CaptureMethod GetCaptureMethod();
        void SetCaptureMethod(ResourceModelUrl::CaptureMethod Capture);

        QString GetCaptureArgument();
        void SetCaptureArgument(QString Argument);

        void SetWaiter(IWaiter*Waiter);
    signals:

    public slots:
        virtual void Load();
    private slots:
        void LoadComplete();
        void OnFail();
        void Reqeust();
    };
}

#endif // URLSTRINGBOXLOADER_H
