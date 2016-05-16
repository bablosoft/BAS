#ifndef POP3CLIENT_H
#define POP3CLIENT_H
#include "engine_global.h"

#include "ipop3client.h"
#include "mail/mailpop3.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT Pop3Client : public IPop3Client
    {
        Q_OBJECT
        /* Config */
        QString Host;
        int Port;
        QString UserName;
        QString Password;

        IPop3Client::EncryptionType Encryption;
        QString ProxyServer;
        int ProxyPort;
        bool IsHttp;
        QString ProxyLogin;
        QString ProxyPassword;

        /* Data */
        bool Status;
        int NumberOfMessages;
        QString LastError;
        IPop3Client::MailMessage Message;

        /* Internal State */
        QxtPop3 *Pop;
        QString Action;
        int MessageNumber;
        QString LastOperation;


        void Connect();
    public:

        explicit Pop3Client(QObject *parent = 0);

    public slots:
        virtual void Reset();
        virtual void SetHost(const QString &Host);
        virtual void SetPort(int Port);
        virtual void SetUserName(const QString &UserName);
        virtual void SetPassword(const QString &Password);
        virtual void SetEncryption(IPop3Client::EncryptionType Encryption);
        virtual void SetEncryptionString(const QString& EncryptionString);
        virtual void SetProxy(const QString &ProxyServer, int ProxyPort, bool IsHttp = true, QString ProxyLogin = QString(), QString ProxyPassword= QString());
        virtual int GetNumberOfMessages();
        virtual void PullNumberOfMessages();
        virtual IPop3Client::MailMessage GetMessage();
        virtual QString GetMessageBody();
        virtual QString GetMessageSubject();
        virtual QString GetMessageSender();

        virtual void PullMessage(int index);
        virtual bool GetStatus();
        virtual QString GetLastError();
        virtual QString GetLastOperation();
    signals:

    private slots:

        void connected();

        void connectionFailed(QByteArray error);
        void HandleStat(int code);
        void HandleRetr(int code);
    };
}

#endif // POP3CLIENT_H
