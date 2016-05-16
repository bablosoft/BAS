/****************************************************************************
** Copyright (c) 2006 - 2011, the LibQxt project <http://libqxt.org>
** See the Qxt AUTHORS file for a list of authors and copyright holders.
** Copyright (c) 2013 Debao Zhang <hello@debao.me>
**
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of the LibQxt project nor the
**       names of its contributors may be used to endorse or promote products
**       derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
** DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*****************************************************************************/

#ifndef MAILSMTP_H
#define MAILSMTP_H

#include "mailglobal.h"
#include "mailmessage.h"
#include <QScopedPointer>
#include <QObject>
#include <QHostAddress>
#include <QString>

class QTcpSocket;
#ifndef QT_NO_OPENSSL
class QSslSocket;
#endif

class QxtSmtpPrivate;
class Q_MAIL_EXPORT QxtSmtp : public QObject
{
    Q_OBJECT
public:
    enum SmtpError
    {
        NoError,
        NoRecipients,
        CommandUnrecognized = 500,
        SyntaxError,
        CommandNotImplemented,
        BadSequence,
        ParameterNotImplemented,
        MailboxUnavailable = 550,
        UserNotLocal,
        MessageTooLarge,
        InvalidMailboxName,
        TransactionFailed
    };

    enum AuthType
    {
        AuthPlain,
        AuthLogin,
        AuthCramMD5
    };

    QxtSmtp(QObject* parent = 0);
    ~QxtSmtp();

    QByteArray username() const;
    void setUsername(const QByteArray& name);

    QByteArray password() const;
    void setPassword(const QByteArray& password);

    int send(const QxtMailMessage& message);
    int pendingMessages() const;

    QTcpSocket* socket() const;
    void connectToHost(const QString& hostName, quint16 port = 25);
    void connectToHost(const QHostAddress& address, quint16 port = 25);
    void disconnectFromHost();

    bool startTlsDisabled() const;
    void setStartTlsDisabled(bool disable);

#ifndef QT_NO_OPENSSL
    QSslSocket* sslSocket() const;
    void connectToSecureHost(const QString& hostName, quint16 port = 465);
    void connectToSecureHost(const QHostAddress& address, quint16 port = 465);
#endif

    bool hasExtension(const QString& extension);
    QString extensionData(const QString& extension);

    bool isAuthMethodEnabled(AuthType type) const;
    void setAuthMethodEnabled(AuthType type, bool enable);

Q_SIGNALS:
    void connected();
    void connectionFailed();
    void connectionFailed( const QByteArray & msg );
    void encrypted();
    void encryptionFailed();
    void encryptionFailed( const QByteArray & msg );
    void authenticated();
    void authenticationFailed();
    void authenticationFailed( const QByteArray & msg );

    void senderRejected(int mailID, const QString& address );
    void senderRejected(int mailID, const QString& address, const QByteArray & msg );
    void recipientRejected(int mailID, const QString& address );
    void recipientRejected(int mailID, const QString& address, const QByteArray & msg );
    void mailFailed(int mailID, int errorCode);
    void mailFailed(int mailID, int errorCode, const QByteArray & msg);
    void mailSent(int mailID);

    void finished();
    void disconnected();

private:
    Q_DECLARE_PRIVATE(QxtSmtp)
    QScopedPointer<QxtSmtpPrivate> d_ptr;
};

#endif // MAILSMTP_H
