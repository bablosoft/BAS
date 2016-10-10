#ifndef CURLHTTPCLIENT_H
#define CURLHTTPCLIENT_H
#include "ihttpclient.h"

#include <QList>
#include "networkcookiejar.h"
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QStringList>
#include <QFile>
#include <QFileInfo>
#include <QImage>
#include <QBuffer>
#include <QThread>

#include "curlexecutor.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT CurlHttpClient : public IHttpClient
    {
        Q_OBJECT
        QThread *Thread;
        bool was_error;
        QString last_error;
        QString page_content;
        QString location;
        int status;
        QByteArray page_data;
        bool disconnected;
        QString LastUrl;
        QHash<QString,QString> Headers;
        QList<QPair<QByteArray, QByteArray> > ReturnHeaders;
        IPostPrepareStrategyFactory* PostPrepareStrategyFactory;
        NetworkCookieJar Cookies;
        QString ProxyString;
        QString ProxyAuthString;
        QPair<bool, ContentData> ParsePostArgument(const QString& str, const QString& encoding);
        QObject *request_holder;
        CurlExecutor* Curl;
        void GetInternal(const QString &url,const QString &filename, const GetOptions & Options);
        QThread *GetThread();
    public:
        explicit CurlHttpClient(QObject *parent = 0);
        ~CurlHttpClient();
    public slots:
        virtual void Stop();
        virtual void Get(const QString &url, const GetOptions & Options = GetOptions());
        virtual void Download(const QString &url, const QString &file);

        virtual void Post(const QString &url, const QHash<QString,QString> & params, const PostOptions & Options = PostOptions());
        virtual void Post(const QString &url, const QHash<QString,ContentData> & params, const PostOptions & Options = PostOptions());
        virtual bool WasError();
        virtual QString GetErrorString();
        virtual QString GetContent();
        virtual QByteArray GetPageData();
        virtual QString GetBase64();
        virtual int GetStatus();
        virtual QString GetLastUrl();
        virtual void Connect(QObject *object, const char * slot);
        virtual void Disconnect();
        virtual QString GetHeader(const QString& header);
        virtual void AddHeader(const QString& name,const QString& value);
        virtual void CleanHeader();
        virtual void SetProxy(const QString& server, int Port, bool IsHttp, const QString& name, const QString& password);
        virtual QString GetCookiesForUrl(const QString& url);
        virtual void SetPostPrepareStrategyFactory(IPostPrepareStrategyFactory* PostPrepareStrategyFactory);
        virtual QString SaveCookies();
        virtual void RestoreCookies(const QString& cookies);
    signals:

    private slots:
        void FinishedSlot();


    };
}

#endif // CURLHTTPCLIENT_H
