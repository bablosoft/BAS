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

#ifndef MAILPOP3_H
#define MAILPOP3_H

#include "mailglobal.h"
#include "mailmessage.h"
#include "mailpop3reply.h"
#include "mailpop3statreply.h"
#include "mailpop3listreply.h"
#include "mailpop3retrreply.h"

#include <QObject>
#include <QHostAddress>
#include <QString>
#include <QHash>
#include <QList>
#include <QPair>
#include <QSslError>
#include <QScopedPointer>

class QTcpSocket;
#ifndef QT_NO_OPENSSL
class QSslSocket;
#endif

class QxtPop3Private;
class Q_MAIL_EXPORT QxtPop3 : public QObject
{
    Q_OBJECT
public:
    explicit QxtPop3(QObject* parent = 0);
    ~QxtPop3();

    QByteArray username() const;
    void setUsername(const QByteArray& name);

    QByteArray password() const;
    void setPassword(const QByteArray& password);

    QTcpSocket* socket() const;
    void connectToHost(const QString& hostName, quint16 port = 110);
    void connectToHost(const QHostAddress& address, quint16 port = 110);
    void disconnectFromHost();

    bool startTlsDisabled() const;
    void setStartTlsDisabled(bool disable);

#ifndef QT_NO_OPENSSL
    QSslSocket* sslSocket() const;
    void connectToSecureHost(const QString& hostName, quint16 port = 995);
    void connectToSecureHost(const QHostAddress& address, quint16 port = 995);
#endif

    bool isConnected() const;

    QxtPop3StatReply* stat(int timeout=3000);
    QxtPop3ListReply* messageList(int timeout=100000);
    QxtPop3RetrReply* retrieveMessage(int which, int timeout=300000);
//    QxtPop3Reply* retrieveAll(QList<QxtMailMessage>& list, int timeout=300000);
    QxtPop3Reply* deleteMessage(int which, int timeout=100000);
//    QxtPop3Reply* deleteAll(int timeout=100000);
    QxtPop3Reply* reset(int timeout=10000);
//    QxtPop3TopReply* top(int which, int lines, int timeout=100000);
    QxtPop3Reply* quit(int timeout=3000);

    void clearReplies();


Q_SIGNALS:
    void connected();
    void connectionFailed( const QByteArray & msg );
    void encrypted();
    void encryptionFailed( const QByteArray & msg );
    void authenticated();
    void authenticationFailed( const QByteArray & msg );

    void disconnected();

private:
    Q_DECLARE_PRIVATE(QxtPop3)
    Q_DISABLE_COPY(QxtPop3)
    QScopedPointer<QxtPop3Private> d_ptr;
private slots:
    void error(QAbstractSocket::SocketError);
    void sslErrors(QList<QSslError>);
};

#endif // MAILPOP3_H
