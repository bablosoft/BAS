#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H
#include "engine_global.h"

#include "ihttpclient.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QList>


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT HttpClient : public IHttpClient
    {
    Q_OBJECT
        QNetworkAccessManager *network_manager;
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
        QObject *request_holder;
    public:
        explicit HttpClient(QObject *parent = 0);
        virtual void Get(const QString &url, const GetOptions & Options = GetOptions());
        virtual void Download(const QString &url, const QString &file);

        virtual void Post(const QString &url, const QHash<QString,QString> & params, const PostOptions & Options = PostOptions());
        virtual void Post(const QString &url, const QHash<QString,ContentData> & params, const PostOptions & Options = PostOptions());
        virtual QByteArray GetPageData();
        virtual void Connect(QObject *object, const char * slot);
        virtual void Disconnect();
        virtual void Stop();


    signals:

    public slots:
        virtual bool WasError();
        virtual QString GetErrorString();
        virtual QString GetContent();
        virtual QString GetBase64();
        virtual int GetStatus();
        virtual QString GetHeader(const QString& header);
        virtual QString GetLastUrl();
        virtual void AddHeader(const QString& name,const QString& value);
        virtual void CleanHeader();
        virtual void SetProxy(const QString& server, int Port, bool IsHttp, const QString& name, const QString& password);
        virtual QString GetCookiesForUrl(const QString& url);
        virtual void SetPostPrepareStrategyFactory(IPostPrepareStrategyFactory* PostPrepareStrategyFactory);
        virtual QString SaveCookies();
        virtual void RestoreCookies(const QString& cookies);

    private slots:
        void sslErrors(QNetworkReply* reply,const QList<QSslError> &errors);
        void FinishedSlot();
        QPair<bool, ContentData> ParsePostArgument(const QString& str);
    };
}

#endif // HTTPCLIENT_H
