#ifndef IHTTPCLIENT_H
#define IHTTPCLIENT_H
#include "engine_global.h"

#include <QObject>
#include <QHash>
#include <QMap>
#include <QVariantMap>
#include <QDateTime>
#include "ipostpreparestrategyfactory.h"

namespace BrowserAutomationStudioFramework
{
    struct ContentData
    {
        QString DataString;
        QByteArray DataRaw;
        QString ContentType;
        QString FileName;
    };

    struct ENGINESHARED_EXPORT GetOptions
    {
        QString Method;
        GetOptions();
    };

    struct ENGINESHARED_EXPORT PostOptions
    {
        QString PrepareStrategy;
        QString Method;
        QString ContentTypeEncoding;
        PostOptions();
    };
    class IPostPrepareStrategyFactory;
    class ENGINESHARED_EXPORT IHttpClient : public QObject
    {
        Q_OBJECT
        public:


            explicit IHttpClient(QObject *parent = 0);
            virtual void Get(const QString &url, const GetOptions & Options = GetOptions()) = 0;
            virtual void Download(const QString &url, const QString &file) = 0;
            virtual void Post(const QString &url, const QHash<QString,QString> & params, const PostOptions & Options = PostOptions()) = 0;
            virtual void Post(const QString &url, const QHash<QString,ContentData> & params, const PostOptions & Options = PostOptions()) = 0;
            virtual bool WasError() = 0;
            virtual QString GetErrorString() = 0;
            virtual QString GetContent() = 0;
            virtual QByteArray GetPageData() = 0;
            virtual QString GetBase64() = 0;
            virtual int GetStatus() = 0;
            virtual QString GetLastUrl() = 0;
            virtual void Connect(QObject *object, const char * slot) = 0;
            virtual void Disconnect() = 0;
            virtual void Stop() = 0;

            virtual QString GetHeader(const QString& header) = 0;
            virtual void AddHeader(const QString& name,const QString& value) = 0;
            virtual void CleanHeader() = 0;
            virtual void SetProxy(const QString& server, int Port, bool IsHttp, const QString& name, const QString& password) = 0;
            virtual QString GetCookiesForUrl(const QString& url) = 0;
            virtual void SetPostPrepareStrategyFactory(IPostPrepareStrategyFactory* PostPrepareStrategyFactory) = 0;
            virtual QString SaveCookies() = 0;
            virtual void RestoreCookies(const QString& cookies) = 0;

            QVariantMap SerializeTime(const QDateTime& time);
            QDateTime DeserializeTime(const QJsonObject& object);

        signals:
            void Finished();
            void DownloadProgress(qint64 BytesReceived, qint64 BytesTotal);
        public slots:

    };

}

#endif // IHTTPCLIENT_H
