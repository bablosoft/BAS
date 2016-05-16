#ifndef IIMAPCLIENT_H
#define IIMAPCLIENT_H

#include <QObject>
#include <QString>
#include <QStringList>
#include "engine_global.h"


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IImapClient : public QObject
    {
        Q_OBJECT
    public:
        enum EncryptionType{SSL, None};
        explicit IImapClient(QObject *parent = 0);
    public slots:
        virtual void SetHost(const QString &Host) = 0;
        virtual void SetHostPort(int Port) = 0;
        virtual void SetUserName(const QString &UserName) = 0;
        virtual void SetPassword(const QString &Password) = 0;
        virtual void SetEncryption(EncryptionType Encryption) = 0;
        virtual void SetEncryptionString(const QString& EncryptionString) = 0;
        virtual void SetInboxFolder(const QString& Inbox) = 0;
        virtual void SetProxy(const QString &ProxyServer, int ProxyPort, bool IsHttp = true, QString ProxyLogin = QString(), QString ProxyPassword= QString()) = 0;

        virtual void PullNumberOfMessages() = 0;
        virtual int GetNumberOfMessages() = 0;

        virtual void SearchMessages(const QString& Sender,const QString& Subject,const QString& Body) = 0;
        virtual void SearchCustomMessages(const QString& SearchTerm) = 0;
        virtual QStringList GetSearchResult() = 0;

        virtual void PullMessage(const QString& uid) = 0;
        virtual QString GetLastMessage() = 0;


        virtual bool GetStatus() = 0;
        virtual QString GetLastError() = 0;
        virtual QString GenerateUrl() = 0;


        virtual void CustomQuery(const QString& Url, const QString& query, const QString& filter) = 0;
        virtual QString CustomQueryResult() = 0;
        virtual QString CustomQueryLog() = 0;

    signals:
        void Result();
    public slots:
    };
}
#endif // IIMAPCLIENT_H
