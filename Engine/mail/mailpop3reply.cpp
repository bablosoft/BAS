
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


#include "mailpop3reply.h"
#include "mailpop3reply_p.h"
#include "mailpop3statreply.h"
#include "mailpop3listreply.h"
#include "mailpop3retrreply.h"
#include "mailpop3_p.h"
#include <QTextStream>
#ifndef QT_NO_OPENSSL
#    include <QSslSocket>
#endif

class QxtPop3AuthReplyImpl: public QxtPop3ReplyImpl
{
public:
    QxtPop3AuthReplyImpl(QxtPop3ReplyPrivate *reply);
    QByteArray dialog(QByteArray received);
    enum State {
        StartState,
        STLSSent,
        TLSOK,
        UserSent,
        PassSent,
    };
    void setPop(QxtPop3Private* pop_);

private:
    QxtPop3Private* pop;
    bool startTLSdisabled;
    State state;

};

QxtPop3AuthReplyImpl::QxtPop3AuthReplyImpl(QxtPop3ReplyPrivate *reply) : QxtPop3ReplyImpl(reply), state(StartState)
{
}

void QxtPop3AuthReplyImpl::setPop(QxtPop3Private* pop_)
{
    pop = pop_;
    startTLSdisabled = pop->disableStartTLS;
}

QByteArray QxtPop3AuthReplyImpl::dialog(QByteArray received)
{
    QByteArray ret = "";
    switch (state)
    {
    case StartState:
#ifndef QT_NO_OPENSSL
        if (!startTLSdisabled)
        {
            ret = buildCmd("STLS", "");
            state = STLSSent;
            break;
        }
    case TLSOK:   // fallthrough
#endif
        ret = buildCmd("USER", pop->username);
        state = UserSent;
        break;
#ifndef QT_NO_OPENSSL
    case STLSSent:
        if (isAnswerOK(received))
        {
            pop->socket->startClientEncryption();
            state = TLSOK;
        }
        else
        {
            qWarning("startTLS doesn't seem to be supported");
            m_reply->status = QxtPop3Reply::Error;
            m_reply->finish(QxtPop3Reply::Failed);
            pop->socket->disconnectFromHost();
        }
        break;
#endif
    case UserSent:
        if (isAnswerOK(received))
        {
            ret = buildCmd("PASS", pop->password);
            state = PassSent;
        }else
        {
            pop->authenticationFailure(received);
        }
        break;
    case PassSent:
        if (isAnswerOK(received))
        {
            // authenticated
            m_reply->status = QxtPop3Reply::Completed;
            m_reply->finish(QxtPop3Reply::OK);
            pop->authenticated();
        }else
        {
            pop->authenticationFailure(received);
        }
        break;
    default:
        break;
    }
    return ret;
}

class QxtPop3QuitReplyImpl: public QxtPop3ReplyImpl
{
public:
    QxtPop3QuitReplyImpl(QxtPop3ReplyPrivate *reply);
    QByteArray dialog(QByteArray received);
    enum State {
        StartState,
        QuitSent
    };
private:
    State state;
};

QxtPop3QuitReplyImpl::QxtPop3QuitReplyImpl(QxtPop3ReplyPrivate *reply) : QxtPop3ReplyImpl(reply), state(StartState)
{
}

QByteArray QxtPop3QuitReplyImpl::dialog(QByteArray received)
{
    Q_UNUSED(received)
    QByteArray ret = "";
    switch (state)
    {
    case StartState:
        ret = buildCmd("QUIT", "");
        state = QuitSent;
        break;
    case QuitSent:
        m_reply->status = QxtPop3Reply::Completed;
        m_reply->finish(QxtPop3Reply::OK);
        break;
    default:
        break;
    }
    return ret;
}

class QxtPop3StatReplyImpl: public QxtPop3ReplyImpl
{
public:
    QxtPop3StatReplyImpl(QxtPop3ReplyPrivate *reply);
    QByteArray dialog(QByteArray received);
    enum State {
        StartState,
        StatSent
    };
    int count() const {return m_count;}
    int size() const {return m_size;}

private:
    State state;
    int m_count;
    int m_size;
};

QxtPop3StatReplyImpl::QxtPop3StatReplyImpl(QxtPop3ReplyPrivate *reply): QxtPop3ReplyImpl(reply), state(StartState), m_count(-1), m_size(-1)
{
}

QByteArray QxtPop3StatReplyImpl::dialog(QByteArray received)
{
    QByteArray ret = "";
    switch (state)
    {
    case StartState:
        ret = buildCmd("STAT", "");
        state = StatSent;
        break;
    case StatSent:
        if (isAnswerOK(received))
        {
            QTextStream input(received);
            QString ok;
            input >> ok >> m_count >> m_size;
            m_reply->status = QxtPop3Reply::Completed;
            m_reply->finish(QxtPop3Reply::OK);
        } else {
            m_reply->status = QxtPop3Reply::Error;
            m_reply->errString = QString::fromLatin1(received);
            m_reply->finish(QxtPop3Reply::Failed);
        }
        break;
    default:
        break;
    }
    return ret;
}



class QxtPop3ListReplyImpl: public QxtPop3ReplyImpl
{
public:
    QxtPop3ListReplyImpl(QxtPop3ReplyPrivate *reply);
    QByteArray dialog(QByteArray received);
    enum State {
        StartState,
        ListSent,
        OKReceived
    };

    const QList<QxtPop3Reply::MessageInfo>& list() const {return m_list;}

private:
    State state;
    QList<QxtPop3Reply::MessageInfo> m_list;
};

QxtPop3ListReplyImpl::QxtPop3ListReplyImpl(QxtPop3ReplyPrivate *reply): QxtPop3ReplyImpl(reply), state(StartState)
{
}

QByteArray QxtPop3ListReplyImpl::dialog(QByteArray received)
{
    QByteArray ret = "";
    switch (state)
    {
    case StartState:
        ret = buildCmd("LIST", "");
        state = ListSent;
        break;
    case ListSent:
        if (isAnswerOK(received))
        {
            state = OKReceived;
        } else {
            m_reply->status = QxtPop3Reply::Error;
            m_reply->errString = QString::fromLatin1(received);
            m_reply->finish(QxtPop3Reply::Failed);
        }
        break;
    case OKReceived:
        {
            QStringList words = QString::fromLatin1(received).split(QStringLiteral(" "));
            if (words[0] == QLatin1String("."))
            {
                m_reply->status = QxtPop3Reply::Completed;
                m_reply->finish(QxtPop3Reply::OK);
            }
            else
            {
                QxtPop3Reply::MessageInfo info;
                info.id = words[0].toInt();
                info.size = words[1].toInt();
                m_list.append(info);
            }
        }
        break;
    default:
        break;
    }
    return ret;
}


class QxtPop3RetrReplyImpl: public QxtPop3ReplyImpl
{
public:
    QxtPop3RetrReplyImpl(QxtPop3ReplyPrivate *reply);
    QByteArray dialog(QByteArray received);
    enum State {
        StartState,
        ListSent,
        RetrSent,
        OKReceived
    };

    QxtMailMessage* message() {return m_msg;}
    void setWhich(int which) {m_which = which;}

private:
    State state;
    QByteArray m_message;
    QxtMailMessage* m_msg;
    int m_which;
    int m_length;
};

QxtPop3RetrReplyImpl::QxtPop3RetrReplyImpl(QxtPop3ReplyPrivate *reply): QxtPop3ReplyImpl(reply), state(StartState), m_msg(0), m_which(-1), m_length(0)
{
}

QByteArray QxtPop3RetrReplyImpl::dialog(QByteArray received)
{
    QByteArray ret = "";
    switch (state)
    {
    case StartState:
        ret = buildCmd("LIST", QByteArray().number(m_which));
        state = ListSent;
        break;
    case ListSent:
        if (isAnswerOK(received))
        {
            m_length = received.split(' ').at(2).toInt();
            ret = buildCmd("RETR", QByteArray().number(m_which));
            state = RetrSent;
        } else {
            m_reply->status = QxtPop3Reply::Error;
            m_reply->errString = QString::fromLatin1(received);
            m_reply->finish(QxtPop3Reply::Failed);
        }
        break;
    case RetrSent:
        if (isAnswerOK(received))
        {
            state = OKReceived;
        } else {
            m_reply->status = QxtPop3Reply::Error;
            m_reply->errString = QString::fromLatin1(received);
            m_reply->finish(QxtPop3Reply::Failed);
        }
        break;
    case OKReceived:
        {
            if ((received.length() > 0) && (received[0] == '.'))
            {
                if (received.length() == 1)
                {
                    // Termination line. The whole message is received by now.
                    m_msg = new QxtMailMessage(m_message);
                    m_reply->status = QxtPop3Reply::Completed;
                    m_reply->finish(QxtPop3Reply::OK);
                }
                else // remove first dot
                {
                    received = received.mid(1);
                }
            }
            m_message += received + "\r\n";
            int p = (100*m_message.length())/m_length;
            m_reply->progress(p);
        }
        break;
    default:
        break;
    }
    return ret;
}

class QxtPop3ResetReplyImpl: public QxtPop3ReplyImpl
{
public:
    QxtPop3ResetReplyImpl(QxtPop3ReplyPrivate *reply);
    QByteArray dialog(QByteArray received);
    enum State {
        StartState,
        RsetSent
    };

private:
    State state;
};

QxtPop3ResetReplyImpl::QxtPop3ResetReplyImpl(QxtPop3ReplyPrivate *reply): QxtPop3ReplyImpl(reply), state(StartState)
{
    // empty ctor
}



QByteArray QxtPop3ResetReplyImpl::dialog(QByteArray received)
{
    QByteArray ret = "";
    switch (state)
    {
    case StartState:
        ret = buildCmd("RSET", "");
        state = RsetSent;
        break;
    case RsetSent:
        if (isAnswerOK(received))
        {
            m_reply->status = QxtPop3Reply::Completed;
            m_reply->finish(QxtPop3Reply::OK);
        } else {
            m_reply->status = QxtPop3Reply::Error;
            m_reply->errString = QString::fromLatin1(received);
            m_reply->finish(QxtPop3Reply::Failed);
        }
        break;
    default:
        break;
    }
    return ret;
}

class QxtPop3DeleReplyImpl: public QxtPop3ReplyImpl
{
public:
    QxtPop3DeleReplyImpl(QxtPop3ReplyPrivate *reply);
    QByteArray dialog(QByteArray received);
    enum State {
        StartState,
        DeleSent
    };

    void setWhich(int which) {m_which = which;}

private:
    State state;
    int m_which;
};

QxtPop3DeleReplyImpl::QxtPop3DeleReplyImpl(QxtPop3ReplyPrivate *reply): QxtPop3ReplyImpl(reply), state(StartState), m_which(-1)
{
    // empty ctor
}



QByteArray QxtPop3DeleReplyImpl::dialog(QByteArray received)
{
    QByteArray ret = "";
    switch (state)
    {
    case StartState:
        ret = buildCmd("DELE", QByteArray().number(m_which));
        state = DeleSent;
        break;
    case DeleSent:
        if (isAnswerOK(received))
        {
            m_reply->status = QxtPop3Reply::Completed;
            m_reply->finish(QxtPop3Reply::OK);
        } else {
            m_reply->status = QxtPop3Reply::Error;
            m_reply->errString = QString::fromLatin1(received);
            m_reply->finish(QxtPop3Reply::Failed);
        }
        break;
    default:
        break;
    }
    return ret;
}

/*!
  \class QxtPop3Reply
  \inmodule QxtNetwork
  \brief The QxtPop3Reply class encapsulates the reply to an asynchronous POP3 command.

  This isn't a class that is to be instanciated or subclassed by client code. You get
  pointers to QxtPop3Reply (or subclasses thereof) objects via QxtPop3 methods implementing
  the POP3 commands, and you can use them to:

  \list

  \o Monitor the execution of the command via the finished() and progress() signals,

  \o Query its status() and error() methods,

  \o Get the results of the command, if any, via specific methods of subclasses.

  \endlist

  The QxtPop3Reply object is managed by the QxtPop3 object, and is deleted with it.
  If the QxtPop3 object is long-lived, you can do some cleaning-up with its QxtPop3::clearReplies()
  method, for example after closing a connection to the server.

  \sa QxtPop3
 */

/*!
  \enum QxtPop3Reply::Status
  Status of the reply.

  \value Pending The reply is queued and waits to be run.
  \value Running The repy is currently being run.
  \value Completed The reply has completed, the result, if any, is available.
  \value Timedout The reply timed out.
  \value Error An error occured.
  */

/*!
  \enum QxtPop3Reply::ReturnCode
  Return codes for the finished() signal, indicating how the reply finished.

  \value OK Success, the result, if any, is available.
  \value Timeout The reply timed out.
  \value Failed The reply failed.
  \value Aborted The reply was cancelled.
  */

/*!
  \enum QxtPop3Reply::Type
  Type of POP3 command, as returned by type().

  \value Auth AUTH POP3 command.
  \value Quit QUIT POP3 command.
  \value Stat STAT POP3 command.
  \value List LIST POP3 command.
  \value Reset RSET POP3 command.
  \value Dele DELE POP3 command.
  \value Retr RETR POP3 command.
  \value Top TOP POP3 command.
  */

QxtPop3Reply::QxtPop3Reply(int timeout, QObject* parent)
    : QObject(parent), d_ptr(new QxtPop3ReplyPrivate)
{
    d_ptr->q_ptr = this;
    d_ptr->timeout = timeout;
    d_ptr->status = QxtPop3Reply::Pending;
}

/*!
  Destructs the QxtPop3Reply.
  */
QxtPop3Reply::~QxtPop3Reply()
{
}


/*!
  Return the current status of the reply.
  */
QxtPop3Reply::Status QxtPop3Reply::status() const
{
    return d_func()->status;
}

/*!
  If an error occured, returns a string description of it.

  \sa status()
  */
QString QxtPop3Reply::error() const
{
    return d_func()->errString;
}

/*!
  Returns the type of the reply.
  */
QxtPop3Reply::Type QxtPop3Reply::type() const
{
    return d_func()->type;
}

/*!
  Cancels the reply.
  */
void QxtPop3Reply::cancel()
{
    d_func()->status = Error;
    d_func()->errString = QStringLiteral("Canceled.");
    emit finished(Aborted);
}

/*!
  \fn QxtPop3Reply::finished(int code)

  Emitted when the reply terminates. The return \a code indicates how the reply finished.

  \sa QxtPop3Reply::ReturnCode
  */


/*!
  \fn QxtPop3Reply::progress(int percent)

  Emitted to indicate the progress of the reply. \a percent is a number between \c 0 and \c 100, indicating the progress value as a percentage.
  */

void QxtPop3Reply::setup(Type type)
{
    d_func()->type = type;
    switch (type)
    {
    case Auth:
        d_func()->impl = new QxtPop3AuthReplyImpl(d_func());
        break;
    case Quit:
        d_func()->impl = new QxtPop3QuitReplyImpl(d_func());
        break;
    case Stat:
        d_func()->impl = new QxtPop3StatReplyImpl(d_func());
        break;
    case List:
        d_func()->impl = new QxtPop3ListReplyImpl(d_func());
        break;
    case Reset:
        d_func()->impl = new QxtPop3ResetReplyImpl(d_func());
        break;
    case Dele:
        d_func()->impl = new QxtPop3DeleReplyImpl(d_func());
        break;
    case Retr:
        d_func()->impl = new QxtPop3RetrReplyImpl(d_func());
        break;
//    case Top:
//        d_func()->impl = new QxtPop3TopReplyImpl(d_func());
//        break;
    default:
        qWarning("QxtPop3Reply::setup: unhandled type %d", type);
        break;
    }
}

QxtPop3ReplyImpl* QxtPop3Reply::impl()
{
    return d_func()->impl;
}

const QxtPop3ReplyImpl* QxtPop3Reply::impl() const
{
    return d_func()->impl;
}

QByteArray QxtPop3Reply::dialog(QByteArray received)
{
    if (!d_func()->impl)
    {
        qWarning("QxtPop3Reply::dialog: No implementation !");
        return QByteArray();
    }
    return d_func()->impl->dialog(received);
}

QxtPop3ReplyPrivate::QxtPop3ReplyPrivate() : QObject(0), impl(0)
{
}

void QxtPop3ReplyPrivate::run()
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(timedOut()));
    status = QxtPop3Reply::Running;
    timer.start(timeout);
}

void QxtPop3ReplyPrivate::timedOut()
{
    status = QxtPop3Reply::Timedout;
    finish(QxtPop3Reply::Timeout);
}

/*!
  \class QxtPop3StatReply
  \inmodule QxtNetwork
  \brief The QxtPop3StatReply class implements the reply to a STAT command.

  Results of the command are given by the count() and size() methods, once the command has completed.
 */
QxtPop3StatReply::QxtPop3StatReply(int timeout, QObject* parent): QxtPop3Reply(timeout, parent)
{
    setup(Stat);
}

/*!
  Returns the message count in the mailbox on the server.
  */
int QxtPop3StatReply::count() const
{
    return dynamic_cast<const QxtPop3StatReplyImpl*>(impl())->count();
}

/*!
  Returns the total size (in bytes) in the mailbox on the server.
  */
int QxtPop3StatReply::size() const
{
    return dynamic_cast<const QxtPop3StatReplyImpl*>(impl())->size();
}

QxtPop3QuitReply::QxtPop3QuitReply(int timeout, QObject* parent): QxtPop3Reply(timeout, parent)
{
    setup(Quit);
}

QxtPop3AuthReply::QxtPop3AuthReply(QxtPop3Private* pop, int timeout, QObject* parent): QxtPop3Reply(timeout, parent)
{
    setup(Auth);
    dynamic_cast<QxtPop3AuthReplyImpl*>(impl())->setPop(pop);
}

/*!
  \class QxtPop3ListReply
  \inmodule QxtNetwork
  \brief The QxtPop3ListReply class implements the reply to a LIST command.

  Results of the command are given by the list() method, once the command has completed.
 */

QxtPop3ListReply::QxtPop3ListReply(int timeout, QObject* parent): QxtPop3Reply(timeout, parent)
{
    setup(List);
}

/*!
  Returns the list of messages on the server. The reference is valid until deletion of the QxtPop3 object which ran the command.
  */
const QList<QxtPop3Reply::MessageInfo>& QxtPop3ListReply::list() const
{
    return dynamic_cast<const QxtPop3ListReplyImpl*>(impl())->list();
}

/*!
  \class QxtPop3RetrReply
  \inmodule QxtNetwork
  \brief The QxtPop3RetrReply class implements the reply to a RETR command.

  Results of the command are given by the message() method, once the command has completed.
 */

QxtPop3RetrReply::QxtPop3RetrReply(int which, int timeout, QObject* parent): QxtPop3Reply(timeout, parent)
{
    setup(Retr);
    dynamic_cast<QxtPop3RetrReplyImpl*>(impl())->setWhich(which);
}

/*!
  Returns a pointer to the message retrieved from the server, once the command has completed.
  The caller owns the message and is responsible for deleting it after use.
  */

QxtMailMessage* QxtPop3RetrReply::message()
{
    return dynamic_cast<QxtPop3RetrReplyImpl*>(impl())->message();
}

QxtPop3ResetReply::QxtPop3ResetReply(int timeout, QObject* parent): QxtPop3Reply(timeout, parent)
{
    setup(Reset);
}

QxtPop3DeleReply::QxtPop3DeleReply(int which, int timeout, QObject* parent): QxtPop3Reply(timeout, parent)
{
    setup(Dele);
    dynamic_cast<QxtPop3DeleReplyImpl*>(impl())->setWhich(which);
}
