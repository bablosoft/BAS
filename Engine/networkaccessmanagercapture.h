#ifndef NETWORKACCESSMANAGERCAPTURE_H
#define NETWORKACCESSMANAGERCAPTURE_H
#include "engine_global.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "networkaccessmanager.h"

namespace BrowserAutomationStudioFramework
{
    class NetworkAccessManager;
    class ENGINESHARED_EXPORT NetworkAccessManagerCapture : public QNetworkAccessManager
    {
        Q_OBJECT
        NetworkAccessManager * _NetworkAccessManager;
        QHash<QString,QString> Headers;
    public:
        void AddHeader(const QString& name,const QString& value);
        void CleanHeader();
        explicit NetworkAccessManagerCapture(QObject *parent = 0);
        void SetNetworkAccessManager(NetworkAccessManager * _NetworkAccessManager);
    protected:
        QNetworkReply *createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData);
    signals:
        void ReadData(QNetworkReply*);
        void UrlLoad(const QString& url, int status);
    private slots:
        void ReadDataSlot();
        void UrlLoadSlot();

    };
}

#endif // NETWORKACCESSMANAGERCAPTURE_H
