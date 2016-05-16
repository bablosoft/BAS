#include "pop3client.h"
#include <QNetworkProxy>
#include <QTcpSocket>
#include <QSslSocket>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    Pop3Client::Pop3Client(QObject *parent) :
        IPop3Client(parent)
    {
        Status = true;
        Pop = new QxtPop3(this);
        NumberOfMessages = -1;
        connect(Pop,SIGNAL(authenticated()),this,SLOT(connected()));
        connect(Pop,SIGNAL(connectionFailed(QByteArray)),this,SLOT(connectionFailed(QByteArray)));
        connect(Pop,SIGNAL(authenticationFailed(QByteArray)),this,SLOT(connectionFailed(QByteArray)));
        connect(Pop,SIGNAL(encryptionFailed(QByteArray)),this,SLOT(connectionFailed(QByteArray)));
    }

    void Pop3Client::Reset()
    {
        Pop->disconnect();
        Pop->deleteLater();
        Pop = new QxtPop3(this);
        connect(Pop,SIGNAL(authenticated()),this,SLOT(connected()));
        connect(Pop,SIGNAL(connectionFailed(QByteArray)),this,SLOT(connectionFailed(QByteArray)));
        connect(Pop,SIGNAL(authenticationFailed(QByteArray)),this,SLOT(connectionFailed(QByteArray)));
        connect(Pop,SIGNAL(encryptionFailed(QByteArray)),this,SLOT(connectionFailed(QByteArray)));
    }

    void Pop3Client::Connect()
    {
        Pop->setUsername(UserName.toUtf8());
        Pop->setPassword(Password.toUtf8());

        if(!ProxyServer.isEmpty() && ProxyPort>0)
        {
            QNetworkProxy proxy;
            if(IsHttp)
            {
                proxy.setType(QNetworkProxy::HttpProxy);
            }else
            {
                proxy.setType(QNetworkProxy::Socks5Proxy);
            }

            proxy.setHostName(ProxyServer);
            proxy.setPort(ProxyPort);

            proxy.setUser(ProxyLogin);
            proxy.setPassword(ProxyPassword);

            Pop->socket()->setProxy(proxy);
            //Pop->sslSocket()->setProxy(proxy);
        }

        bool useSSL = Encryption == IPop3Client::SSL;
        if (Encryption == IPop3Client::StatTls)
        {
            Pop->setStartTlsDisabled(false);
        }
        else
        {
            Pop->setStartTlsDisabled(true);
        }

        if(useSSL)
        {
            Pop->connectToSecureHost(Host, Port);
        }
        else
        {
            Pop->connectToHost(Host, Port);
        }
    }

    void Pop3Client::connected()
    {
        if(Action == "PullNumberOfMessages")
        {
            PullNumberOfMessages();
        }else if(Action == "PullMessage")
        {
            PullMessage(MessageNumber);
        }
        Action = QString();
    }

    QString Pop3Client::GetLastOperation()
    {
        return LastOperation;
    }

    void Pop3Client::connectionFailed(QByteArray error)
    {
        Status = false;
        LastError = QString::fromUtf8(error);
        emit Result();
    }

    void Pop3Client::SetHost(const QString &Host)
    {
        this->Host = Host;
    }
    void Pop3Client::SetPort(int Port)
    {
        this->Port = Port;
    }
    void Pop3Client::SetUserName(const QString &UserName)
    {
        this->UserName = UserName;
    }
    void Pop3Client::SetPassword(const QString &Password)
    {
        this->Password = Password;
    }
    void Pop3Client::SetEncryption(IPop3Client::EncryptionType Encryption)
    {
        this->Encryption = Encryption;
    }
    void Pop3Client::SetEncryptionString(const QString& EncryptionString)
    {
        if(EncryptionString.toLower() == "ssl")
        {
            SetEncryption(IPop3Client::SSL);
        }else if(EncryptionString.toLower() == "stattls")
        {
            SetEncryption(IPop3Client::StatTls);
        }else
            SetEncryption(IPop3Client::None);
    }
    void Pop3Client::SetProxy(const QString &ProxyServer, int ProxyPort, bool IsHttp, QString ProxyLogin, QString ProxyPassword)
    {
        this->ProxyServer = ProxyServer;
        this->ProxyPort = ProxyPort;
        this->IsHttp = IsHttp;
        this->ProxyLogin = ProxyLogin;
        this->ProxyPassword = ProxyPassword;
    }
    int Pop3Client::GetNumberOfMessages()
    {
        return NumberOfMessages;
    }
    void Pop3Client::PullNumberOfMessages()
    {
        Status = false;
        LastOperation = "PullNumberOfMessages";
        if(!Pop->isConnected())
        {
            Action = LastOperation;
            Connect();
            return;
        }
        QxtPop3Reply* Reply = Pop->stat();
        connect(Reply,SIGNAL(finished(int)),this,SLOT(HandleStat(int)));
    }

    void Pop3Client::HandleStat(int code)
    {
        QxtPop3StatReply* reply = dynamic_cast<QxtPop3StatReply *>(sender());

        switch (code)
        {
            case QxtPop3Reply::OK:
            {
                Status = true;
                NumberOfMessages = reply->count();
            }
            break;
            case QxtPop3Reply::Aborted:
                Status = false;
                LastError = "POP3 Client STAT: Aborted."  + reply->error();
                break;
            case QxtPop3Reply::Timeout:
                Status = false;
                LastError = "POP3 Client STAT: time out. " +reply->error();
                break;
            default:
                Status = false;
                LastError = "POP3 Client STAT: " + reply->error();
                break;
        }
        reply->deleteLater();
        emit Result();
    }

    void Pop3Client::HandleRetr(int code)
    {
        QxtPop3RetrReply* reply = dynamic_cast<QxtPop3RetrReply *>(sender());
        switch (code)
        {
            case QxtPop3Reply::OK:
            {
                Status = true;

                Message.Body = reply->message()->body();
                Message.Sender = reply->message()->extraHeader("from");
                Message.Subject = reply->message()->extraHeader("subject");
            }
            break;
        case QxtPop3Reply::Aborted:
            Status = false;
            LastError = "POP3 Client RETR: Aborted."  + reply->error();
            break;
        case QxtPop3Reply::Timeout:
            Status = false;
            LastError = "POP3 Client RETR: time out. " + reply->error();
            break;
        default:
            Status = false;
            LastError = "POP3 Client RETR: "  + reply->error();
            break;
        }
        reply->deleteLater();
        emit Result();
    }

    IPop3Client::MailMessage Pop3Client::GetMessage()
    {
        return Message;
    }

    QString Pop3Client::GetMessageBody()
    {
        return Message.Body;
    }

    QString Pop3Client::GetMessageSubject()
    {
        return Message.Subject;
    }

    QString Pop3Client::GetMessageSender()
    {
        return Message.Sender;
    }

    void Pop3Client::PullMessage(int index)
    {
        Status = false;
        LastOperation = "PullMessage";
        if(!Pop->isConnected())
        {
            Action = LastOperation;
            MessageNumber = index;
            Connect();
            return;
        }
        QxtPop3Reply* reply = Pop->retrieveMessage(index);
        connect(reply, SIGNAL(finished(int)), this, SLOT(HandleRetr(int)));
    }

    bool Pop3Client::GetStatus()
    {
        return Status;
    }

    QString Pop3Client::GetLastError()
    {
        return LastError;
    }
}
