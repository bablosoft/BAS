
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
 * \class QxtMailAttachment
 * \inmodule QxtNetwork
 * \brief The QxtMailAttachment class represents an attachement to a QxtMailMessage
 */




#include "mailattachment.h"
#include "mailutility_p.h"
#include <QTextCodec>
#include <QBuffer>
#include <QPointer>
#include <QFile>
#include <QtDebug>

class QxtMailAttachmentPrivate : public QSharedData
{
public:
    QHash<QString, QString> extraHeaders;
    QString contentType;
    // those two members are mutable because they may change in the const rawData() method of QxtMailAttachment,
    // while caching the raw data for the attachment if needed.
    mutable QPointer<QIODevice> content;
    mutable bool deleteContent;

    QxtMailAttachmentPrivate()
    {
        content = 0;
        deleteContent = false;
        contentType = QStringLiteral("text/plain");
    }

    ~QxtMailAttachmentPrivate()
    {
        if (deleteContent && content)
            content->deleteLater();
        deleteContent = false;
        content = 0;
    }
};

QxtMailAttachment::QxtMailAttachment()
{
    qxt_d = new QxtMailAttachmentPrivate;
}

QxtMailAttachment::QxtMailAttachment(const QxtMailAttachment& other) : qxt_d(other.qxt_d)
{
    // trivial copy constructor
}

QxtMailAttachment::QxtMailAttachment(const QByteArray& content, const QString& contentType)
{
    qxt_d = new QxtMailAttachmentPrivate;
    setContentType(contentType);
    setContent(content);
}

QxtMailAttachment::QxtMailAttachment(QIODevice* content, const QString& contentType)
{
    qxt_d = new QxtMailAttachmentPrivate;
    setContentType(contentType);
    setContent(content);
}

QxtMailAttachment& QxtMailAttachment::operator=(const QxtMailAttachment & other)
{
    qxt_d = other.qxt_d;
    return *this;
}

QxtMailAttachment::~QxtMailAttachment()
{
    // trivial destructor
}

QIODevice* QxtMailAttachment::content() const
{
    return qxt_d->content;
}

void QxtMailAttachment::setContent(const QByteArray& content)
{
    if (qxt_d->deleteContent && qxt_d->content)
        qxt_d->content->deleteLater();
    qxt_d->content = new QBuffer;
    setDeleteContent(true);
    static_cast<QBuffer*>(qxt_d->content.data())->setData(content);
}

void QxtMailAttachment::setContent(QIODevice* content)
{
    if (qxt_d->deleteContent && qxt_d->content)
        qxt_d->content->deleteLater();
    qxt_d->content = content;
}

bool QxtMailAttachment::deleteContent() const
{
    return qxt_d->deleteContent;
}

void QxtMailAttachment::setDeleteContent(bool enable)
{
    qxt_d->deleteContent = enable;
}

QString QxtMailAttachment::contentType() const
{
    return qxt_d->contentType;
}

void QxtMailAttachment::setContentType(const QString& contentType)
{
    qxt_d->contentType = contentType;
}

QHash<QString, QString> QxtMailAttachment::extraHeaders() const
{
    return qxt_d->extraHeaders;
}

QString QxtMailAttachment::extraHeader(const QString& key) const
{
    return qxt_d->extraHeaders[key.toLower()];
}

bool QxtMailAttachment::hasExtraHeader(const QString& key) const
{
    return qxt_d->extraHeaders.contains(key.toLower());
}

void QxtMailAttachment::setExtraHeader(const QString& key, const QString& value)
{
    qxt_d->extraHeaders[key.toLower()] = value;
}

void QxtMailAttachment::setExtraHeaders(const QHash<QString, QString>& a)
{
    QHash<QString, QString>& headers = qxt_d->extraHeaders;
    headers.clear();
    foreach(const QString& key, a.keys())
    {
        headers[key.toLower()] = a[key];
    }
}

void QxtMailAttachment::removeExtraHeader(const QString& key)
{
    qxt_d->extraHeaders.remove(key.toLower());
}

QByteArray QxtMailAttachment::mimeData()
{
    QTextCodec* latin1 = QTextCodec::codecForName("latin1");
    QByteArray rv = "Content-Type: " + qxt_d->contentType.toLatin1() + "\r\nContent-Transfer-Encoding: base64\r\n";
    foreach(const QString& r, qxt_d->extraHeaders.keys())
    {
        rv += qxt_fold_mime_header(r, extraHeader(r), latin1);
    }
    rv += "\r\n";

    const QByteArray& d = rawData();
    for (int pos = 0; pos < d.length(); pos += 57)
    {
        rv += d.mid(pos, 57).toBase64() + "\r\n";
    }
    return rv;
}

const QByteArray& QxtMailAttachment::rawData() const
{
    if (qxt_d->content == 0)
    {
        qWarning("QxtMailAttachment::rawData(): Content not set!");
        static QByteArray defaultRv;
        return defaultRv;
    }
    if (qobject_cast<QBuffer *>(qxt_d->content.data()) == 0)
    {
        // content isn't hold in a buffer but in another kind of QIODevice
        // (probably a QFile...). Read the data and cache it into a buffer
        static QByteArray empty;
        QIODevice* c = content();
        if (!c->isOpen() && !c->open(QIODevice::ReadOnly))
        {
            qWarning() << "QxtMailAttachment::rawData(): Cannot open content for reading";
            return empty;
        }
        QBuffer* cache = new QBuffer();
        cache->open(QIODevice::WriteOnly);
        char buf[1024];
        while (!c->atEnd())
        {
            cache->write(buf, c->read(buf, 1024));
        }
        if (qxt_d->deleteContent && qxt_d->content)
        qxt_d->content->deleteLater();
        qxt_d->content = cache;
        qxt_d->deleteContent = true;
    }
    return qobject_cast<QBuffer *>(qxt_d->content.data())->data();
}


// gives only a hint, based on content-type value.
// return true if the content-type corresponds to textual data (text/*, application/xml...)
// and false if unsure, so don't interpret a 'false' response as 'it's binary data...
bool QxtMailAttachment::isText() const
{
    return isTextMedia(contentType());
}

QxtMailAttachment QxtMailAttachment::fromFile(const QString& filename)
{
    QxtMailAttachment rv(new QFile(filename));
    rv.setDeleteContent(true);
    return rv;
}
