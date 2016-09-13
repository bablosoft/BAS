#ifndef POSTTOANTIGATE_H
#define POSTTOANTIGATE_H
#include "engine_global.h"

#include <QObject>
#include "ihttpclient.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT PostToAntigate : public QObject
    {
        Q_OBJECT
        IHttpClient * HttpClient;
        QString id;
        QString Server;
    public:
        explicit PostToAntigate(QObject *parent = 0);
        void SetServer(const QString& Server);
        void Post(const QString& id, const QString& key, const QString& base64, const QMap<QString,QString>& Properties, const QString& soft, bool DisableImageConvert);
    signals:
        void PostedToAntigate(const QString& antigate_id, const QString& id, bool res);
    public slots:
        void SetHttpClient(IHttpClient * HttpClient);
        IHttpClient * GetHttpClient();
    private slots:
        void submitRequestFinished();
    };
}

#endif // POSTTOANTIGATE_H
