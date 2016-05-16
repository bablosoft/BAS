
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
 * \class QxtMailMessage
 * \inmodule QxtNetwork
 * \brief The QxtMailMessage class encapsulates an e-mail according to RFC 2822 and related specifications
 * TODO: {implicitshared}
 */


#include "mailmessage.h"
#include "mailutility_p.h"
#include <QTextCodec>
#include <QUuid>
#include <QDir>
#include <QtDebug>
#include <QRegExp>

//#define QXT_MAIL_MESSAGE_DEBUG 1

#define MUST_QP(x) (x < char(32) || x > char(126) || x == '=' || x == '?')

struct QxtMailMessagePrivate : public QSharedData
{
    QxtMailMessagePrivate() {}
    QxtMailMessagePrivate(const QxtMailMessagePrivate& other)
            : QSharedData(other), rcptTo(other.rcptTo), rcptCc(other.rcptCc), rcptBcc(other.rcptBcc),
            subject(other.subject), body(other.body), sender(other.sender),
            extraHeaders(other.extraHeaders), attachments(other.attachments),
            wordWrapLimit(78), preserveStartSpaces(false) {}
    QStringList rcptTo, rcptCc, rcptBcc;
    QString subject, body, sender;
    QHash<QString, QString> extraHeaders;
    QHash<QString, QxtMailAttachment> attachments;
    mutable QByteArray boundary;
    int wordWrapLimit;
    bool preserveStartSpaces;
};

class QxtRfc2822Parser
{
public:
    QxtMailMessagePrivate* parse(const QByteArray& buffer);
private:
    enum State {
        Headers,
        Body
    };
    State state;
    QString currentHeaderKey;
    QStringList currentHeaderValue;
    void parseHeader(const QByteArray& line, QHash<QString, QString>& headers);
    void parseBody(QxtMailMessagePrivate* msg);
    void parseEntity(const QByteArray& buffer, QHash<QString,QString>& headers, QString& body);
    QxtMailAttachment* parseAttachment(const QHash<QString,QString>& headers, const QString& body, QString& filename);
    QString unfoldValue(QStringList& folded);
    QString decode(const QString& charset, const QString& encoding, const QString& encoded);
};

QxtMailMessage::QxtMailMessage()
{
    qxt_d = new QxtMailMessagePrivate;
}

QxtMailMessage::QxtMailMessage(const QxtMailMessage& other) : qxt_d(other.qxt_d)
{
    // trivial copy constructor
}

QxtMailMessage::QxtMailMessage(const QString& sender, const QString& recipient)
{
    qxt_d = new QxtMailMessagePrivate;
    setSender(sender);
    addRecipient(recipient);
}

/*!
  Constructs a new QxtMailMessage object from a \a buffer that conforms to RFC 2822 and the MIME related RFCs.
  */
QxtMailMessage::QxtMailMessage(const QByteArray& buffer)
{
    QxtRfc2822Parser parser;
    qxt_d = parser.parse(buffer);
}

QxtMailMessage::~QxtMailMessage()
{
    // trivial destructor
}

QxtMailMessage& QxtMailMessage::operator=(const QxtMailMessage & other)
{
    qxt_d = other.qxt_d;
    return *this;
}

QString QxtMailMessage::sender() const
{
    return qxt_d->sender;
}

void QxtMailMessage::setSender(const QString& a)
{
    qxt_d->sender = a;
}

QString QxtMailMessage::subject() const
{
    return qxt_d->subject;
}

void QxtMailMessage::setSubject(const QString& a)
{
    qxt_d->subject = a;
}

QString QxtMailMessage::body() const
{
    return qxt_d->body;
}

void QxtMailMessage::setBody(const QString& a)
{
    qxt_d->body = a;
}

QStringList QxtMailMessage::recipients(QxtMailMessage::RecipientType type) const
{
    if (type == Bcc)
        return qxt_d->rcptBcc;
    if (type == Cc)
        return qxt_d->rcptCc;
    return qxt_d->rcptTo;
}

void QxtMailMessage::addRecipient(const QString& a, QxtMailMessage::RecipientType type)
{
    if (type == Bcc)
        qxt_d->rcptBcc.append(a);
    else if (type == Cc)
        qxt_d->rcptCc.append(a);
    else
        qxt_d->rcptTo.append(a);
}

void QxtMailMessage::removeRecipient(const QString& a)
{
    qxt_d->rcptTo.removeAll(a);
    qxt_d->rcptCc.removeAll(a);
    qxt_d->rcptBcc.removeAll(a);
}

QHash<QString, QString> QxtMailMessage::extraHeaders() const
{
    return qxt_d->extraHeaders;
}

QString QxtMailMessage::extraHeader(const QString& key) const
{
    return qxt_d->extraHeaders[key.toLower()];
}

bool QxtMailMessage::hasExtraHeader(const QString& key) const
{
    return qxt_d->extraHeaders.contains(key.toLower());
}

void QxtMailMessage::setExtraHeader(const QString& key, const QString& value)
{
    qxt_d->extraHeaders[key.toLower()] = value;
}

void QxtMailMessage::setExtraHeaders(const QHash<QString, QString>& a)
{
    QHash<QString, QString>& headers = qxt_d->extraHeaders;
    headers.clear();
    foreach(const QString& key, a.keys())
    {
        headers[key.toLower()] = a[key];
    }
}

void QxtMailMessage::removeExtraHeader(const QString& key)
{
    qxt_d->extraHeaders.remove(key.toLower());
}

QHash<QString, QxtMailAttachment> QxtMailMessage::attachments() const
{
    return qxt_d->attachments;
}

QxtMailAttachment QxtMailMessage::attachment(const QString& filename) const
{
    return qxt_d->attachments[filename];
}

void QxtMailMessage::addAttachment(const QString& filename, const QxtMailAttachment& attach)
{
    if (qxt_d->attachments.contains(filename))
    {
        qWarning() << "QxtMailMessage::addAttachment: " << filename << " already in use";
        int i = 1;
        while (qxt_d->attachments.contains(filename + QLatin1Char('.') + QString::number(i)))
        {
            i++;
        }
        qxt_d->attachments[filename+QLatin1Char('.')+QString::number(i)] = attach;
    }
    else
    {
        qxt_d->attachments[filename] = attach;
    }
}

void QxtMailMessage::removeAttachment(const QString& filename)
{
    qxt_d->attachments.remove(filename);
}

/*!
 * \brief Rewrites default 78 word wrap line length limit with new \a limit
 */
void QxtMailMessage::setWordWrapLimit(int limit)
{
    qxt_d->wordWrapLimit = limit;
}

/*!
 * \brief Forces wrapped line to have the same indent as original.
 *
 * Ex: If your very long line starts with 4 sp. then wrapped part
 *     will start with 4 sp too when this feature enabled
 */
void QxtMailMessage::setWordWrapPreserveStartSpaces(bool state)
{
    qxt_d->preserveStartSpaces = state;
}

QByteArray qxt_fold_mime_header(const QString& key, const QString& value, QTextCodec* latin1, const QByteArray& prefix)
{
    QByteArray rv = "";
    QByteArray line = key.toLatin1() + ": ";
    if (!prefix.isEmpty()) line += prefix;
    if (!value.contains(QStringLiteral("=?")) && latin1->canEncode(value))
    {
        bool firstWord = true;
        foreach(const QByteArray& word, value.toLatin1().split(' '))
        {
            if (line.size() > 78)
            {
                rv = rv + line + "\r\n";
                line.clear();
            }
            if (firstWord)
                line += word;
            else
                line += " " + word;
            firstWord = false;
        }
    }
    else
    {
        // The text cannot be losslessly encoded as Latin-1. Therefore, we
        // must use quoted-printable or base64 encoding. This is a quick
        // heuristic based on the first 100 characters to see which
        // encoding to use.
        QByteArray utf8 = value.toUtf8();
        int ct = utf8.length();
        int nonAscii = 0;
        for (int i = 0; i < ct && i < 100; i++)
        {
            if (MUST_QP(utf8[i])) nonAscii++;
        }
        if (nonAscii > 20)
        {
            // more than 20%-ish non-ASCII characters: use base64
            QByteArray base64 = utf8.toBase64();
            ct = base64.length();
            line += "=?utf-8?b?";
            for (int i = 0; i < ct; i += 4)
            {
                if (line.length() > 72)
                {
                    rv += line + "?=\r\n";
                    line = " =?utf-8?b?";
                }
                line = line + base64.mid(i, 4);
            }
        }
        else
        {
            // otherwise use Q-encoding
            line += "=?utf-8?q?";
            for (int i = 0; i < ct; i++)
            {
                if (line.length() > 73)
                {
                    rv += line + "?=\r\n";
                    line = " =?utf-8?q?";
                }
                if (MUST_QP(utf8[i]) || utf8[i] == ' ')
                {
                    line += "=" + utf8.mid(i, 1).toHex().toUpper();
                }
                else
                {
                    line += utf8[i];
                }
            }
        }
        line += "?="; // end encoded-word atom
    }
    return rv + line + "\r\n";
}

QByteArray QxtMailMessage::rfc2822() const
{
    // Use quoted-printable if requested
    bool useQuotedPrintable = (extraHeader(QStringLiteral("Content-Transfer-Encoding")).toLower() == QLatin1String("quoted-printable"));
    // Use base64 if requested
    bool useBase64 = (extraHeader(QStringLiteral("Content-Transfer-Encoding")).toLower() == QLatin1String("base64"));
    // Check to see if plain text is ASCII-clean; assume it isn't if QP or base64 was requested
    QTextCodec* latin1 = QTextCodec::codecForName("latin1");
    bool bodyIsAscii = latin1->canEncode(body()) && !useQuotedPrintable && !useBase64;

    QHash<QString, QxtMailAttachment> attach = attachments();
    QByteArray rv;

    if (!sender().isEmpty() && !hasExtraHeader(QStringLiteral("From")))
    {
        rv += qxt_fold_mime_header(QStringLiteral("From"), sender(), latin1);
    }

    if (!qxt_d->rcptTo.isEmpty())
    {
        rv += qxt_fold_mime_header(QStringLiteral("To"), qxt_d->rcptTo.join(QStringLiteral(", ")), latin1);
    }

    if (!qxt_d->rcptCc.isEmpty())
    {
        rv += qxt_fold_mime_header(QStringLiteral("Cc"), qxt_d->rcptCc.join(QStringLiteral(", ")), latin1);
    }

    if (!subject().isEmpty())
    {
        rv += qxt_fold_mime_header(QStringLiteral("Subject"), subject(), latin1);
    }

    if (!bodyIsAscii)
    {
        if (!hasExtraHeader(QStringLiteral("MIME-Version")) && !attach.count())
            rv += "MIME-Version: 1.0\r\n";

        // If no transfer encoding has been requested, guess.
        // Heuristic: If >20% of the first 100 characters aren't
        // 7-bit clean, use base64, otherwise use Q-P.
        if(!bodyIsAscii && !useQuotedPrintable && !useBase64)
        {
            QString b = body();
            int nonAscii = 0;
            int ct = b.length();
            for (int i = 0; i < ct && i < 100; i++)
            {
                if (MUST_QP(b[i])) nonAscii++;
            }
            useQuotedPrintable = !(nonAscii > 20);
            useBase64 = !useQuotedPrintable;
        }
    }

    if (attach.count())
    {
        if (qxt_d->boundary.isEmpty())
            qxt_d->boundary = QUuid::createUuid().toString().toLatin1().replace("{", "").replace("}", "");
        if (!hasExtraHeader(QStringLiteral("MIME-Version")))
            rv += "MIME-Version: 1.0\r\n";
        if (!hasExtraHeader(QStringLiteral("Content-Type")))
            rv += "Content-Type: multipart/mixed; boundary=" + qxt_d->boundary + "\r\n";
    }
    else if (!bodyIsAscii && !hasExtraHeader(QStringLiteral("Content-Transfer-Encoding")))
    {
        if (!useQuotedPrintable)
        {
            // base64
            rv += "Content-Transfer-Encoding: base64\r\n";
        }
        else
        {
            // quoted-printable
            rv += "Content-Transfer-Encoding: quoted-printable\r\n";
        }
    }

    foreach(const QString& r, qxt_d->extraHeaders.keys())
    {
        if ((r.toLower() == QLatin1String("content-type") || r.toLower() == QLatin1String("content-transfer-encoding")) && attach.count())
        {
            // Since we're in multipart mode, we'll be outputting this later
            continue;
        }
        rv += qxt_fold_mime_header(r, extraHeader(r), latin1);
    }

    rv += "\r\n";

    if (attach.count())
    {
        // we're going to have attachments, so output the lead-in for the message body
        rv += "This is a message with multiple parts in MIME format.\r\n";
        rv += "--" + qxt_d->boundary + "\r\nContent-Type: ";
        if (hasExtraHeader(QStringLiteral("Content-Type")))
            rv += extraHeader(QStringLiteral("Content-Type")).toLatin1() + "\r\n";
        else
            rv += "text/plain; charset=UTF-8\r\n";
        if (hasExtraHeader(QStringLiteral("Content-Transfer-Encoding")))
        {
            rv += "Content-Transfer-Encoding: " + extraHeader(QStringLiteral("Content-Transfer-Encoding")).toLatin1() + "\r\n";
        }
        else if (!bodyIsAscii)
        {
            if (!useQuotedPrintable)
            {
                // base64
                rv += "Content-Transfer-Encoding: base64\r\n";
            }
            else
            {
                // quoted-printable
                rv += "Content-Transfer-Encoding: quoted-printable\r\n";
            }
        }
        rv += "\r\n";
    }

    if (bodyIsAscii)
    {
        QByteArray b = latin1->fromUnicode(body());
        int len = b.length();
        QByteArray line;
        QByteArray word;
        QByteArray spaces;
        QByteArray startSpaces;
        for (int i = 0; i <= len; i++)
        {
            char ignoredChar = 0;
            if (i != len) {
                ignoredChar = b[i] == '\n'? '\r' : b[i] == '\r'? '\n' : 0;
            }
            if (!(ignoredChar || (i == len) || (b[i] == ' ') || (b[i] == '\t'))) {
                // the char is part of word
                if (word.isEmpty()) { // start of new word / end of spaces
                    if (line.isEmpty()) {
                        startSpaces = spaces;
                    }
                }
                word += b[i];
                continue;
            }

            // space char, so end of word or continuous spaces
            if (!word.isEmpty()) { // start of new space area / end of word
                if (line.length() + spaces.length() +
                                        word.length() > qxt_d->wordWrapLimit) {
                    // have to wrap word to next line
                    if(line[0] == '.')
                        rv += ".";
                    rv += line + "\r\n";
                    if (qxt_d->preserveStartSpaces) {
                        line = startSpaces + word;
                    } else {
                        line = word;
                    }
                } else { // no wrap required
                    line += spaces + word;
                }
                word.clear();
                spaces.clear();
            }

            if (ignoredChar || i == len) { // new line or eof
                // trailing `spaces` are ignored here
                if(line[0] == '.')
                    rv += ".";
                rv += line + "\r\n";
                line.clear();
                startSpaces.clear();
                spaces.clear();
            } else {
                spaces += b[i];
            }
        }
    }
    else if (useQuotedPrintable)
    {
        QByteArray b = body().toUtf8();
        int ct = b.length();
        QByteArray line;
        for (int i = 0; i < ct; i++)
        {
            if(b[i] == '\n' || b[i] == '\r')
            {
                if(line[0] == '.')
                    rv += ".";
                rv += line + "\r\n";
                line = "";
                if ((b[i+1] == '\n' || b[i+1] == '\r') && b[i] != b[i+1])
                {
                    // If we're looking at a CRLF pair, skip the second half
                    i++;
                }
            }
            else if (line.length() > 74)
            {
                rv += line + "=\r\n";
                line = "";
            }
            if (MUST_QP(b[i]))
            {
                line += "=" + b.mid(i, 1).toHex().toUpper();
            }
            else
            {
                line += b[i];
            }
        }
        if(!line.isEmpty()) {
            if(line[0] == '.')
                rv += ".";
            rv += line + "\r\n";
        }
    }
    else /* base64 */
    {
        QByteArray b = body().toUtf8().toBase64();
        int ct = b.length();
        for (int i = 0; i < ct; i += 78)
        {
            rv += b.mid(i, 78) + "\r\n";
        }
    }

    if (attach.count())
    {
        foreach(const QString& filename, attach.keys())
        {
            rv += "--" + qxt_d->boundary + "\r\n";
            rv += qxt_fold_mime_header(QStringLiteral("Content-Disposition"), QDir(filename).dirName(), latin1, "attachment; filename=");
            rv += attach[filename].mimeData();
        }
        rv += "--" + qxt_d->boundary + "--\r\n";
    }

    return rv;
}

/*!
  Constructs a new QxtMailMessage object from a \a buffer that conforms to RFC 2822 and the MIME related RFCs.
  */
QxtMailMessage QxtMailMessage::fromRfc2822(const QByteArray& buffer)
{
    QxtMailMessage rv;
    QxtRfc2822Parser parser;
    rv.qxt_d = parser.parse(buffer);
    return rv;
}

QxtMailMessagePrivate* QxtRfc2822Parser::parse(const QByteArray& buffer)
{
    QxtMailMessagePrivate* rv = new QxtMailMessagePrivate();
    parseEntity(buffer, rv->extraHeaders, rv->body);
    parseBody(rv);
    return rv;
}

void QxtRfc2822Parser::parseEntity(const QByteArray& buffer, QHash<QString,QString>& headers, QString& body)
{
    int pos = 0;
    int crlfPos = 0;
    QByteArray line;
    currentHeaderKey = QString();
    currentHeaderValue.clear();
    state = Headers;
    while (true)
    {
        crlfPos = buffer.indexOf("\r\n", pos);
        if (crlfPos == -1)
        {
            break;
        }
        if (state == Headers && crlfPos == pos)  // double CRLF reached: end of headers section
        {
            state = Body;
            parseHeader("", headers); // to store the header currently being parsed (last one)
            pos += 2;
            continue;
        }
        line = buffer.mid(pos, crlfPos - pos);
        pos = crlfPos + 2;
        switch(state)
        {
        case Headers:
            parseHeader(line, headers);
            break;
        case Body:
            body.append(QString::fromUtf8(line + "\r\n"));
            break;
        default:
            break;
        }
    }
}

void QxtRfc2822Parser::parseHeader(const QByteArray& line, QHash<QString, QString>& headers )
{
    QRegExp spRe(QStringLiteral("^[ \\t]"));
    QRegExp hdrRe(QStringLiteral("^([!-9;-~]+):[ \\t](.*)$"));
    QString lineStr = QString::fromLatin1(line);
    if (spRe.indexIn(lineStr) == 0) // continuation line
    {
        currentHeaderValue.append(lineStr);
    }
    else
    {
        // starting a new header field. Store the current one before
        if (!currentHeaderKey.isEmpty())
        {
            QString value = unfoldValue(currentHeaderValue);
            headers[currentHeaderKey.toLower()] = value;
            currentHeaderKey = QString();
            currentHeaderValue.clear();
        }
        if (hdrRe.exactMatch(lineStr))
        {
            QString key = hdrRe.cap(1),value = hdrRe.cap(2);
            key = key.trimmed();
            value = value.trimmed();
            currentHeaderKey = key;
            currentHeaderValue.append(value);
        } // else: empty or malformed header line. Ignore.
    }
}

// extract the attachments from a multipart body
// proceed only one level deep
// future plans may involve nested parts and dealing with inline parts too
void QxtRfc2822Parser::parseBody(QxtMailMessagePrivate* msg)
{
    QString& body = msg->body;
    if (!msg->extraHeaders.contains(QStringLiteral("content-type"))) return;
    QString contentType = msg->extraHeaders[QStringLiteral("content-type")];


    if (!contentType.indexOf(QStringLiteral("multipart"), 0, Qt::CaseInsensitive) == 0)
    {
        if(msg->extraHeaders[QStringLiteral("content-transfer-encoding")].toLower().indexOf("base64")>=0)
        {
            QString correct_body = decode("UTF-8","b",msg->body);
            msg->body = correct_body;
        }

        return;
    }
    // extract the boundary delimiter
    QRegExp boundaryRe(QStringLiteral("boundary=\"?([^\"]*)\"?(?=;|$)"));
    if (boundaryRe.indexIn(contentType) == -1)
    {
        qDebug("Boundary regexp didn't match for %s", contentType.toLatin1().data());
        return;
    }
    QString boundary = boundaryRe.cap(1);
//    qDebug("Boundary=%s", boundary.toLatin1().data());
    QRegExp bndRe(QStringLiteral("(^|\\r?\\n)--%1(--)?[ \\t]*\\r?\\n").arg(QRegExp::escape(boundary)));   // find boundary delimiters in the body
//    qDebug("search for %s", bndRe.pattern().toLatin1().data());
    if (!bndRe.isValid())
    {
        qDebug("regexp %s not valid ! %s", bndRe.pattern().toLatin1().data(), bndRe.errorString().toLatin1().data());
    }
#ifdef QXT_MAIL_MESSAGE_DEBUG
    bool last = false;
#endif
    // keep track of the position of two consecutive boundary delimiters:
    // begin* is the position of the delimiter first character,
    // end* is the position of the first character of the part following it.
    int beginFirst = 0;
    int endFirst = 0;
    int beginSecond = 0;
    int endSecond = 0;
    while(bndRe.indexIn(body, endSecond) != -1)
    {
        beginSecond = bndRe.pos() + bndRe.cap(1).length(); // add length of preceding line break, if any
        endSecond = bndRe.pos() + bndRe.matchedLength();
#ifdef QXT_MAIL_MESSAGE_DEBUG
#if QT_VERSION >= 0x040600
        if (bndRe.captureCount() == 2 && bndRe.cap(2) == "--") last = true;
#else
        if (bndRe.numCaptures() == 2 && bndRe.cap(2) == "--") last = true;
#endif
#endif

//        qDebug("found%s boundary delimiter at position %d.", last?" last":"", beginSecond);
//        qDebug("%d captures", bndRe.numCaptures());
//        foreach(QString capture, bndRe.capturedTexts())
//        {
//            qDebug("->%s<-", capture.toLatin1().data());
//        }
//        qDebug("beginFirst = %d\nendFirst = %d\nbeginSecond = %d\nendSecond = %d", beginFirst, endFirst, beginSecond, endSecond);
        if (endFirst != 0)
        {
            // handle part here:
            QByteArray part = body.mid(endFirst, beginSecond - endFirst).toLocal8Bit();

            QHash<QString,QString> partHeaders;
            QString partBody;
            parseEntity(part, partHeaders, partBody);

//            qDebug("Part headers:");
//            foreach (QString key, partHeaders.keys())
//            {
//                qDebug("%s: %s", key.toLatin1().data(), partHeaders[key].toLatin1().data());
//            }
//            qDebug("Part body:\n%s", partBody.toLatin1().data());
            if (partHeaders.contains(QStringLiteral("content-disposition")) && partHeaders[QStringLiteral("content-disposition")].indexOf(QStringLiteral("attachment;")) == 0)
            {
//                qDebug("Attachment!");
                QString filename;
                QxtMailAttachment* attachment = parseAttachment(partHeaders, partBody, filename);
                if (attachment)
                {
                    msg->attachments.insert(filename, *attachment);
                    delete attachment;
                }
                // strip part from body
                body.replace(beginFirst, beginSecond - beginFirst, QStringLiteral(""));
                beginSecond = beginFirst;
                endSecond = endFirst;
            }else if (partHeaders["content-transfer-encoding"].toLower().indexOf("base64")>=0)
            {
                QString correct_body = decode("UTF-8","b",partBody);
                body.replace(beginFirst, beginSecond - beginFirst,correct_body);
                beginFirst = 0;
                endFirst = 0;
                beginSecond = 0;
                endSecond = 0;
            }
        }
        beginFirst = beginSecond;
        endFirst = endSecond;
    }
}

QString QxtRfc2822Parser::unfoldValue(QStringList& folded)
{
    QString unfolded;
    QRegExp encRe(QStringLiteral("=\\?([^? \\t]+)\\?([qQbB])\\?([^? \\t]+)\\?=")); // search for an encoded word
    QStringList::iterator i;
    for (i = folded.begin(); i != folded.end(); ++i)
    {
        int offset = 0;
        while (encRe.indexIn(*i, offset) != -1)
        {
            QString decoded = decode(encRe.cap(1), encRe.cap(2).toLower(), encRe.cap(3));
            i->replace(encRe.pos(), encRe.matchedLength(), decoded);  // replace encoded word with decoded one
            QString real = i->trimmed();
            i->clear();
            i->append(real);
            offset = encRe.pos() + decoded.length(); // set offset after the inserted decoded word
        }
    }
    unfolded = folded.join(QString());
    return unfolded;
}

QString QxtRfc2822Parser::decode(const QString& charset, const QString& encoding, const QString& encoded)
{
    QString rv;
    QByteArray buf;
    if (encoding == QLatin1String("q"))
    {
        QByteArray src = encoded.toLatin1();
        int len = src.length();
        for (int i = 0; i < len; i++)
        {
            if (src[i] == '_')
            {
                buf += 0x20;
            }
            else if (src[i] == '=')
            {
                if (i+2 < len)
                {
                    buf += QByteArray::fromHex(src.mid(i+1,2));
                    i += 2;
                }
            }
            else
            {
                buf += src[i];
            }
        }
    }
    else if (encoding == QLatin1String("b"))
    {
        buf = QByteArray::fromBase64(encoded.toLatin1());
    }
    QTextCodec *codec = QTextCodec::codecForName(charset.toLatin1());
    if (codec)
    {
        rv = codec->toUnicode(buf);
    }
    return rv;
}

QxtMailAttachment* QxtRfc2822Parser::parseAttachment(const QHash<QString,QString>& headers, const QString& body, QString& filename)
{
    static int count = 1;
    QByteArray content;
    QRegExp filenameRe(QStringLiteral(";\\s+filename=\"?([^\"]*)\"?(?=;|$)"));
    if (filenameRe.indexIn(headers[QStringLiteral("content-disposition")]) != -1)
    {
        filename = filenameRe.cap(1);
    }
    else
    {
        filename = QStringLiteral("attachment%1").arg(count);
    }
//    qDebug("Attachment %s", filename.toLocal8Bit().data());

    QString ct;
    if (headers.contains(QStringLiteral("content-type")))
    {
        ct = headers[QStringLiteral("content-type")];
    }
    else
    {
        ct = QStringLiteral("application/octet-stream");
    }

    QString cte;
    if (headers.contains(QStringLiteral("content-transfer-encoding")))
    {
        cte = headers[QStringLiteral("content-transfer-encoding")].toLower();
//        qDebug("Content-Transfer-Encoding: %s", cte.toLatin1().data());
    }
    if ( cte == QLatin1String("base64"))
    {
        content = QByteArray::fromBase64(body.toLatin1());
    }
    else if (cte == QStringLiteral("quoted-printable"))
    {
        QByteArray src = body.toLatin1();
        int len = src.length();
        QTextStream dest(&content);
        for (int i = 0; i < len; i++)
        {
            if (src.mid(i,2) == "\r\n")
            {
                dest << endl;
                i++;
            }
            else if (src[i] == '=')
            {
                if (i+2 < len)
                {
                    if (src.mid(i+1,2) == "\r\n") // soft line break; skip
                    {
                        i +=2;
                    }
                    else
                    {
                        dest << QByteArray::fromHex(src.mid(i+1,2));
                        i += 2;
                    }
                }
            }
            else
            {
                dest << src[i];
            }
        }
    }
    else // assume 7bit or 8bit
    {
        content = body.toLocal8Bit();
        if (isTextMedia(ct))
        {
            content.replace("\r\n","\n");
        }
    }
    QxtMailAttachment* rv = new QxtMailAttachment(content, ct);
    rv->setExtraHeaders(headers);
    return rv;
}


// gives only a hint, based on content-type value.
// takes value of Content-Type header field as parameter
// return true if the content-type corresponds to textual data (text/*, application/xml...)
// and false if unsure, so don't interpret a 'false' response as 'it's binary data...
bool isTextMedia(const QString& contentType)
{
    // extract media type/sub-type part (e.g. text/plain, image/png...)
    QRegExp mtRe(QStringLiteral("^([^;/]*)/([^;/]*)(?=;|$)"));
    if (mtRe.indexIn(contentType) == -1)
    {
        qWarning("failed to parse %s for type/subtype", contentType.toLatin1().data());
        return false;
    }
    QString type = mtRe.cap(1).toLower();
    QString subtype = mtRe.cap(2).toLower();
    if (type == QLatin1String("text")) return true;
    if (type == QLatin1String("application") &&
        (subtype == QLatin1String("x-csh") ||
         subtype == QLatin1String("x-desktop") ||
         subtype == QLatin1String("x-m4") ||
         subtype == QLatin1String("x-perl") ||
         subtype == QLatin1String("x-php") ||
         subtype == QLatin1String("x-ruby") ||
         subtype == QLatin1String("x-troff-man") ||
         subtype == QLatin1String("xsd") ||
         subtype == QLatin1String("xml-dtd") ||
         subtype == QLatin1String("xml-external-parsed-entity") ||
         subtype == QLatin1String("xslt+xml") ||
         subtype == QLatin1String("xhtml+xml") ||
         subtype == QLatin1String("pgp-keys") ||
         subtype == QLatin1String("pgp-signature") ||
         subtype == QLatin1String("javascript") ||
         subtype == QLatin1String("ecmascript") ||
         subtype == QLatin1String("docbook+xml") ||
         subtype == QLatin1String("xml") ||
         subtype == QLatin1String("html") ||
         subtype == QLatin1String("x-shellscript"))) return true;
    if (type == QLatin1String("image") && subtype == QLatin1String("svg+xml")) return true;
    return false;
}
