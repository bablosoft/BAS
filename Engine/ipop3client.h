#ifndef IPOP3CLIENT_H
#define IPOP3CLIENT_H

#include <QObject>

class IPop3Client : public QObject
{
    Q_OBJECT
public:
    struct MailMessage{QString Sender;QString Subject;QString Body;};
    enum EncryptionType{SSL, StatTls, None};
    explicit IPop3Client(QObject *parent = 0);
    virtual void SetHost(const QString &Host) = 0;
    virtual void Reset() = 0;
    virtual void SetPort(int Port) = 0;
    virtual void SetUserName(const QString &UserName) = 0;
    virtual void SetPassword(const QString &Password) = 0;
    virtual void SetEncryption(EncryptionType Encryption) = 0;
    virtual void SetEncryptionString(const QString& EncryptionString) = 0;
    virtual void SetProxy(const QString &ProxyServer, int ProxyPort, bool IsHttp = true, QString ProxyLogin = QString(), QString ProxyPassword= QString()) = 0;
    virtual int GetNumberOfMessages() = 0;
    virtual void PullNumberOfMessages() = 0;
    virtual IPop3Client::MailMessage GetMessage() = 0;
    virtual QString GetMessageBody() = 0;
    virtual QString GetMessageSubject() = 0;
    virtual QString GetMessageSender() = 0;
    virtual void PullMessage(int index) = 0;
    virtual bool GetStatus() = 0;
    virtual QString GetLastError() = 0;
    virtual QString GetLastOperation() = 0;

signals:
    void Result();
public slots:

};

#endif // IPOP3CLIENT_H
