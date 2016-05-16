#ifndef IMAPCLIENT_H
#define IMAPCLIENT_H

#include "iimapclient.h"
#include "curlexecutor.h"
#include <QStringList>
#include "engine_global.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ImapClient : public IImapClient
    {
        Q_OBJECT

        QString Host;
        int Port;
        QString Username;
        QString Password;
        EncryptionType Encryption;
        QString InboxFolder;

        QString ProxyServer;
        int ProxyPort;
        bool IsHttp;
        QString ProxyLogin;
        QString ProxyPassword;

        QString Message;
        int MessageNumber;
        QStringList SearchResult;

        bool Status;
        QString LastError;
        CurlExecutor* Curl;

        QString CustomQueryData;
        QString CustomQueryAll;

    public:

        explicit ImapClient(QObject *parent = 0);

    public slots:
        virtual void SetHost(const QString &Host);
        virtual void SetHostPort(int Port);
        virtual void SetUserName(const QString &UserName);
        virtual void SetPassword(const QString &Password);
        virtual void SetEncryption(EncryptionType Encryption);
        virtual void SetEncryptionString(const QString& EncryptionString);
        virtual void SetInboxFolder(const QString& Inbox);
        virtual void SetProxy(const QString &ProxyServer, int ProxyPort, bool IsHttp = true, QString ProxyLogin = QString(), QString ProxyPassword= QString());

        virtual void PullNumberOfMessages();
        virtual int GetNumberOfMessages();

        virtual void SearchMessages(const QString& Sender,const QString& Subject,const QString& Body);
        virtual void SearchCustomMessages(const QString& SearchTerm);
        virtual QStringList GetSearchResult();

        virtual void PullMessage(const QString& uid);
        virtual QString GetLastMessage();


        virtual bool GetStatus();
        virtual QString GetLastError();
        virtual QString GenerateUrl();


        virtual void CustomQuery(const QString& Url, const QString& query, const QString& filter);
        virtual QString CustomQueryResult();
        virtual QString CustomQueryLog();


    private slots:
        void PullNumberOfMessagesDone();
        void SearchMessagesDone();
        void PullMessageDone();
        void SetProxyToCurl();
        void CustomQueryDone();


    };
}

#endif // IMAPCLIENT_H
