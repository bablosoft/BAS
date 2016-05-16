
/****************************************************************************
** Copyright (c) 2006 - 2011, the LibQxt project.
** See the Qxt AUTHORS file for a list of authors and copyright holders.
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
** <http://libqxt.org>  <foundation@libqxt.org>
*****************************************************************************/


/*!
 * \class QxtSmtp
 * \inmodule QxtNetwork
 * \brief The QxtSmtp class implements the SMTP protocol for sending email
 */

#include "mailsmtp.h"
#include "mailsmtp_p.h"
#include "mailhmac.h"
#include <QStringList>
#include <QTcpSocket>
#include <QNetworkInterface>
#ifndef QT_NO_OPENSSL
#    include <QSslSocket>
#endif

QxtSmtpPrivate::QxtSmtpPrivate(QxtSmtp *q)
    : QObject(0), q_ptr(q)
    , allowedAuthTypes(QxtSmtp::AuthPlain | QxtSmtp::AuthLogin | QxtSmtp::AuthCramMD5)
{
    // empty ctor
}

QxtSmtp::QxtSmtp(QObject* parent)
    : QObject(parent), d_ptr(new QxtSmtpPrivate(this))
{
    d_ptr->state = QxtSmtpPrivate::Disconnected;
    d_ptr->nextID = 0;
#ifndef QT_NO_OPENSSL
    d_ptr->socket = new QSslSocket(this);
    QObject::connect(socket(), SIGNAL(encrypted()), this, SIGNAL(encrypted()));
    //QObject::connect(socket(), SIGNAL(encrypted()), &qxt_d(), SLOT(ehlo()));
#else
    d_func()->socket = new QTcpSocket(this);
#endif
    QObject::connect(socket(), SIGNAL(connected()), this, SIGNAL(connected()));
    QObject::connect(socket(), SIGNAL(disconnected()), this, SIGNAL(disconnected()));
    QObject::connect(socket(), SIGNAL(error(QAbstractSocket::SocketError)), d_func(), SLOT(socketError(QAbstractSocket::SocketError)));
    QObject::connect(this, SIGNAL(authenticated()), d_func(), SLOT(sendNext()));
    QObject::connect(socket(), SIGNAL(readyRead()), d_func(), SLOT(socketRead()));
}

/*!
 * Destroy the object.
 */
QxtSmtp::~QxtSmtp()
{

}

QByteArray QxtSmtp::username() const
{
    return d_func()->username;
}

void QxtSmtp::setUsername(const QByteArray& username)
{
    d_func()->username = username;
}

QByteArray QxtSmtp::password() const
{
    return d_func()->password;
}

void QxtSmtp::setPassword(const QByteArray& password)
{
    d_func()->password = password;
}

int QxtSmtp::send(const QxtMailMessage& message)
{
    int messageID = ++d_func()->nextID;
    d_func()->pending.append(qMakePair(messageID, message));
    if (d_func()->state == QxtSmtpPrivate::Waiting)
        d_func()->sendNext();
    return messageID;
}

int QxtSmtp::pendingMessages() const
{
    return d_func()->pending.count();
}

QTcpSocket* QxtSmtp::socket() const
{
    return d_func()->socket;
}

void QxtSmtp::connectToHost(const QString& hostName, quint16 port)
{
    d_func()->useSecure = false;
    d_func()->state = QxtSmtpPrivate::StartState;
    socket()->connectToHost(hostName, port);
}

void QxtSmtp::connectToHost(const QHostAddress& address, quint16 port)
{
    connectToHost(address.toString(), port);
}

void QxtSmtp::disconnectFromHost()
{
    socket()->disconnectFromHost();
}

bool QxtSmtp::startTlsDisabled() const
{
    return d_func()->disableStartTLS;
}

void QxtSmtp::setStartTlsDisabled(bool disable)
{
    d_func()->disableStartTLS = disable;
}

#ifndef QT_NO_OPENSSL
QSslSocket* QxtSmtp::sslSocket() const
{
    return d_func()->socket;
}

void QxtSmtp::connectToSecureHost(const QString& hostName, quint16 port)
{
    d_func()->useSecure = true;
    d_func()->state = QxtSmtpPrivate::StartState;
    sslSocket()->connectToHostEncrypted(hostName, port);
}

void QxtSmtp::connectToSecureHost(const QHostAddress& address, quint16 port)
{
    connectToSecureHost(address.toString(), port);
}
#endif

bool QxtSmtp::hasExtension(const QString& extension)
{
    return d_func()->extensions.contains(extension);
}

QString QxtSmtp::extensionData(const QString& extension)
{
    return d_func()->extensions[extension];
}

bool QxtSmtp::isAuthMethodEnabled(AuthType type) const
{
    return d_func()->allowedAuthTypes & type;
}

void QxtSmtp::setAuthMethodEnabled(AuthType type, bool enable)
{
    if(enable)
        d_func()->allowedAuthTypes |= type;
    else
        d_func()->allowedAuthTypes &= ~type;
}

void QxtSmtpPrivate::socketError(QAbstractSocket::SocketError err)
{
    if (err == QAbstractSocket::SslHandshakeFailedError)
    {
        emit q_func()->encryptionFailed();
        emit q_func()->encryptionFailed( socket->errorString().toLatin1() );
    }
    else if (state == StartState)
    {
        emit q_func()->connectionFailed();
        emit q_func()->connectionFailed( socket->errorString().toLatin1() );
    }
}

void QxtSmtpPrivate::socketRead()
{
    buffer += socket->readAll();
    while (true)
    {
        int pos = buffer.indexOf("\r\n");
        if (pos < 0) return;
        QByteArray line = buffer.left(pos);
        buffer = buffer.mid(pos + 2);
        QByteArray code = line.left(3);
        switch (state)
        {
        case StartState:
            if (code[0] != '2')
            {
                state = Disconnected;
                emit q_func()->connectionFailed();
                emit q_func()->connectionFailed(line);
                socket->disconnectFromHost();
            }
            else
            {
                ehlo();
            }
            break;
        case HeloSent:
        case EhloSent:
        case EhloGreetReceived:
            parseEhlo(code, (line[3] != ' '), QString::fromLatin1(line.mid(4)));
            break;
#ifndef QT_NO_OPENSSL
        case StartTLSSent:
            if (code == "220")
            {
                socket->startClientEncryption();
                ehlo();
            }
            else
            {
                authenticate();
            }
            break;
#endif
        case AuthRequestSent:
        case AuthUsernameSent:
            if (authType == QxtSmtp::AuthPlain) authPlain();
            else if (authType == QxtSmtp::AuthLogin) authLogin();
            else authCramMD5(line.mid(4));
            break;
        case AuthSent:
            if (code[0] == '2')
            {
                state = Authenticated;
                emit q_func()->authenticated();
            }
            else
            {
                state = Disconnected;
                emit q_func()->authenticationFailed();
                emit q_func()->authenticationFailed( line );
                socket->disconnectFromHost();
            }
            break;
        case MailToSent:
        case RcptAckPending:
            if (code[0] != '2') {
                emit q_func()->mailFailed( pending.first().first, code.toInt() );
                emit q_func()->mailFailed(pending.first().first, code.toInt(), line);
				// pending.removeFirst();
				// DO NOT remove it, the body sent state needs this message to assigned the next mail failed message that will 
				// the sendNext 
				// a reset will be sent to clear things out
                sendNext();
                state = BodySent;
            }
            else
                sendNextRcpt(code, line);
            break;
        case SendingBody:
            sendBody(code, line);
            break;
        case BodySent:
			if ( pending.count() )
			{
				// if you removeFirst in RcpActpending/MailToSent on an error, and the queue is now empty, 
				// you will get into this state and then crash because no check is done.  CHeck added but shouldnt
				// be necessary since I commented out the removeFirst
				if (code[0] != '2')
				{
                    emit q_func()->mailFailed(pending.first().first, code.toInt() );
                    emit q_func()->mailFailed(pending.first().first, code.toInt(), line);
				}
				else
                    emit q_func()->mailSent(pending.first().first);
	            pending.removeFirst();
			}
            sendNext();
            break;
        case Resetting:
            if (code[0] != '2') {
                emit q_func()->connectionFailed();
                emit q_func()->connectionFailed( line );
            }
            else {
                state = Waiting;
                sendNext();
            }
            break;
        default:
            // Do nothing.
            break;
        }
    }
}

void QxtSmtpPrivate::ehlo()
{
    QByteArray address = "127.0.0.1";
    foreach(const QHostAddress& addr, QNetworkInterface::allAddresses())
    {
        if (addr == QHostAddress::LocalHost || addr == QHostAddress::LocalHostIPv6)
            continue;
        address = addr.toString().toLatin1();
        break;
    }
    socket->write("ehlo " + address + "\r\n");
    extensions.clear();
    state = EhloSent;
}

void QxtSmtpPrivate::parseEhlo(const QByteArray& code, bool cont, const QString& line)
{
    if (code != "250")
    {
        // error!
        if (state != HeloSent)
        {
            // maybe let's try HELO
            socket->write("helo\r\n");
            state = HeloSent;
        }
        else
        {
            // nope
            socket->write("QUIT\r\n");
            socket->flush();
            socket->disconnectFromHost();
        }
        return;
    }
    else if (state != EhloGreetReceived)
    {
        if (!cont)
        {
            // greeting only, no extensions
            state = EhloDone;
        }
        else
        {
            // greeting followed by extensions
            state = EhloGreetReceived;
            return;
        }
    }
    else
    {
        extensions[line.section(' ', 0, 0).toUpper()] = line.section(' ', 1);
        if (!cont)
            state = EhloDone;
    }
    if (state != EhloDone) return;
    if (extensions.contains(QStringLiteral("STARTTLS")) && !disableStartTLS)
    {
        startTLS();
    }
    else
    {
        authenticate();
    }
}

void QxtSmtpPrivate::startTLS()
{
#ifndef QT_NO_OPENSSL
    socket->write("starttls\r\n");
    state = StartTLSSent;
#else
    authenticate();
#endif
}

void QxtSmtpPrivate::authenticate()
{
    if (!extensions.contains(QStringLiteral("AUTH")) || username.isEmpty() || password.isEmpty())
    {
        state = Authenticated;
        emit q_func()->authenticated();
    }
    else
    {
        QStringList auth = extensions[QStringLiteral("AUTH")].toUpper().split(' ', QString::SkipEmptyParts);
        if (auth.contains(QStringLiteral("CRAM-MD5")) && (allowedAuthTypes & QxtSmtp::AuthCramMD5))
        {
            authCramMD5();
        }
        else if (auth.contains(QStringLiteral("PLAIN")) && (allowedAuthTypes & QxtSmtp::AuthPlain))
        {
            authPlain();
        }
        else if (auth.contains(QStringLiteral("LOGIN")) && (allowedAuthTypes & QxtSmtp::AuthLogin))
        {
            authLogin();
        }
        else
        {
            state = Authenticated;
            emit q_func()->authenticated();
        }
    }
}

void QxtSmtpPrivate::authCramMD5(const QByteArray& challenge)
{
    if (state != AuthRequestSent)
    {
        socket->write("auth cram-md5\r\n");
        authType = QxtSmtp::AuthCramMD5;
        state = AuthRequestSent;
    }
    else
    {
        QxtHmac hmac(QCryptographicHash::Md5);
        hmac.setKey(password);
        hmac.addData(QByteArray::fromBase64(challenge));
        QByteArray response = username + ' ' + hmac.result().toHex();
        socket->write(response.toBase64() + "\r\n");
        state = AuthSent;
    }
}

void QxtSmtpPrivate::authPlain()
{
    if (state != AuthRequestSent)
    {
        socket->write("auth plain\r\n");
        authType = QxtSmtp::AuthPlain;
        state = AuthRequestSent;
    }
    else
    {
        QByteArray auth;
        auth += '\0';
        auth += username;
        auth += '\0';
        auth += password;
        socket->write(auth.toBase64() + "\r\n");
        state = AuthSent;
    }
}

void QxtSmtpPrivate::authLogin()
{
    if (state != AuthRequestSent && state != AuthUsernameSent)
    {
        socket->write("auth login\r\n");
        authType = QxtSmtp::AuthLogin;
        state = AuthRequestSent;
    }
    else if (state == AuthRequestSent)
    {
        socket->write(username.toBase64() + "\r\n");
        state = AuthUsernameSent;
    }
    else
    {
        socket->write(password.toBase64() + "\r\n");
        state = AuthSent;
    }
}

static QByteArray qxt_extract_address(const QString& address)
{
    int parenDepth = 0;
    int addrStart = -1;
    bool inQuote = false;
    int ct = address.length();

    for (int i = 0; i < ct; i++)
    {
        QChar ch = address[i];
        if (inQuote)
        {
            if (ch == '"')
                inQuote = false;
        }
        else if (addrStart != -1)
        {
            if (ch == '>')
                return address.mid(addrStart, (i - addrStart)).toLatin1();
        }
        else if (ch == '(')
        {
            parenDepth++;
        }
        else if (ch == ')')
        {
            parenDepth--;
            if (parenDepth < 0) parenDepth = 0;
        }
        else if (ch == '"')
        {
            if (parenDepth == 0)
                inQuote = true;
        }
        else if (ch == '<')
        {
            if (!inQuote && parenDepth == 0)
                addrStart = i + 1;
        }
    }
    return address.toLatin1();
}

void QxtSmtpPrivate::sendNext()
{
    if (state == Disconnected)
    {
        // leave the mail in the queue if not ready to send
        return;
    }

    if (pending.isEmpty())
    {
        // if there are no additional mails to send, finish up
        state = Waiting;
        emit q_func()->finished();
        return;
    }

    if(state != Waiting) {
        state = Resetting;
        socket->write("rset\r\n");
        return;
    }
    const QxtMailMessage& msg = pending.first().second;
    rcptNumber = rcptAck = mailAck = 0;
    recipients = msg.recipients(QxtMailMessage::To) +
                 msg.recipients(QxtMailMessage::Cc) +
                 msg.recipients(QxtMailMessage::Bcc);
    if (recipients.count() == 0)
    {
        // can't send an e-mail with no recipients
        emit q_func()->mailFailed(pending.first().first, QxtSmtp::NoRecipients );
        emit q_func()->mailFailed(pending.first().first, QxtSmtp::NoRecipients, QByteArray( "e-mail has no recipients" ) );
        pending.removeFirst();
        sendNext();
        return;
    }
    // We explicitly use lowercase keywords because for some reason gmail
    // interprets any string starting with an uppercase R as a request
    // to renegotiate the SSL connection.
    socket->write("mail from:<" + qxt_extract_address(msg.sender()) + ">\r\n");
    if (extensions.contains(QStringLiteral("PIPELINING")))  // almost all do nowadays
    {
        foreach(const QString& rcpt, recipients)
        {
            socket->write("rcpt to:<" + qxt_extract_address(rcpt) + ">\r\n");
        }
        state = RcptAckPending;
    }
    else
    {
        state = MailToSent;
    }
}

void QxtSmtpPrivate::sendNextRcpt(const QByteArray& code, const QByteArray&line)
{
    int messageID = pending.first().first;
    const QxtMailMessage& msg = pending.first().second;

    if (code[0] != '2')
    {
        // on failure, emit a warning signal
        if (!mailAck)
        {
            emit q_func()->senderRejected(messageID, msg.sender());
            emit q_func()->senderRejected(messageID, msg.sender(), line );
        }
        else
        {
            emit q_func()->recipientRejected(messageID, msg.sender());
            emit q_func()->recipientRejected(messageID, msg.sender(), line);
        }
    }
    else if (!mailAck)
    {
        mailAck = true;
    }
    else
    {
        rcptAck++;
    }

    if (rcptNumber == recipients.count())
    {
        // all recipients have been sent
        if (rcptAck == 0)
        {
            // no recipients were considered valid
            emit q_func()->mailFailed(messageID, code.toInt() );
            emit q_func()->mailFailed(messageID, code.toInt(), line);
            pending.removeFirst();
            sendNext();
        }
        else
        {
            // at least one recipient was acknowledged, send mail body
            socket->write("data\r\n");
            state = SendingBody;
        }
    }
    else if (state != RcptAckPending)
    {
        // send the next recipient unless we're only waiting on acks
        socket->write("rcpt to:<" + qxt_extract_address(recipients[rcptNumber]) + ">\r\n");
        rcptNumber++;
    }
    else
    {
        // If we're only waiting on acks, just count them
        rcptNumber++;
    }
}

void QxtSmtpPrivate::sendBody(const QByteArray& code, const QByteArray & line)
{
    int messageID = pending.first().first;
    const QxtMailMessage& msg = pending.first().second;

    if (code[0] != '3')
    {
        emit q_func()->mailFailed(messageID, code.toInt() );
        emit q_func()->mailFailed(messageID, code.toInt(), line);
        pending.removeFirst();
        sendNext();
        return;
    }

    socket->write(msg.rfc2822());
    socket->write(".\r\n");
    state = BodySent;
}
