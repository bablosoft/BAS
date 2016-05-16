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

#ifndef MAILPOP3_P_H
#define MAILPOP3_P_H

#include "mailpop3.h"
#include <QQueue>

class QxtPop3Private : public QObject
{
    Q_OBJECT
public:
    QxtPop3Private();

    Q_DECLARE_PUBLIC(QxtPop3)
    QxtPop3 *q_ptr;

    enum Pop3State
    {
        Disconnected,
        StartState,
        Busy,
        Ready
    };

    bool useSecure, disableStartTLS;
    Pop3State state;// rather then an int use the enum.  makes sure invalid states are entered at compile time, and makes debugging easier
    QByteArray buffer, username, password;
    QQueue<QxtPop3Reply*> pending;
    QxtPop3Reply* current;

#ifndef QT_NO_OPENSSL
    QSslSocket* socket;
#else
    QTcpSocket* socket;
#endif

public slots:
    void socketError(QAbstractSocket::SocketError err);
    void authenticationFailure(QByteArray);
    void disconnected();
    void socketRead();
    void dequeue();
    void terminate(int code);
    void encrypted();
    void authenticated();
};

#endif // MAILPOP3_P_H
