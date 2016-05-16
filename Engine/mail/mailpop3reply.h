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

#ifndef MAILPOP3REPLY_H
#define MAILPOP3REPLY_H

#include "mailglobal.h"

#include <QObject>
#include <QSharedPointer>

class QxtPop3ReplyPrivate;
class QxtPop3ReplyImpl;
class Q_MAIL_EXPORT QxtPop3Reply: public QObject
{
    Q_OBJECT
    friend class QxtPop3;
    friend class QxtPop3Private;
public:

    enum Status {
        Pending,
        Running,
        Completed,
        Timedout,
        Error
    };

    enum ReturnCode {
        OK,
        Timeout,
        Failed,
        Aborted
    };

    enum Type {
        Auth,
        Quit,
        Stat,
        List,
        Reset,
        Dele,
        Retr,
        Top
    };

    struct MessageInfo
    {
        int id;
        int size;
    };

    Status status() const;
    QString error() const;
    Type type() const;

    virtual void cancel();

    virtual ~QxtPop3Reply();

Q_SIGNALS:
    void finished(int code);
    void progress(int percent);

protected:
    /*!
      \internal
      This class isn't meant to be subclassed by client code. This API only exists for internal purposes.
      */
    QxtPop3Reply(int timeout, QObject* parent = 0);
//    void setError(const QString& s);
//    void setStatus(const Status);
    /*!
      \internal
      This class isn't meant to be subclassed by client code. This API only exists for internal purposes.
      */
    void setup(Type type);
    /*!
      \internal
      This class isn't meant to be subclassed by client code. This API only exists for internal purposes.
      */
    QxtPop3ReplyImpl* impl();
    /*!
      \internal
      This class isn't meant to be subclassed by client code. This API only exists for internal purposes.
      */
    const QxtPop3ReplyImpl* impl() const;

private:
    QByteArray dialog(QByteArray received);
    Q_DECLARE_PRIVATE(QxtPop3Reply)
    QScopedPointer<QxtPop3ReplyPrivate> d_ptr;
    Q_DISABLE_COPY(QxtPop3Reply)
};

#endif // MAILPOP3LISTREPLY_H
