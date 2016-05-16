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

#ifndef MAILATTACHMENT_H
#define MAILATTACHMENT_H

#include "mailglobal.h"

#include <QStringList>
#include <QHash>
#include <QByteArray>
#include <QMetaType>
#include <QSharedDataPointer>
#include <QIODevice>

class QxtMailAttachmentPrivate;
class Q_MAIL_EXPORT QxtMailAttachment
{
public:
    QxtMailAttachment();
    QxtMailAttachment(const QxtMailAttachment& other);
    QxtMailAttachment(const QByteArray& content, const QString& contentType = QStringLiteral("application/octet-stream"));
    QxtMailAttachment(QIODevice* content, const QString& contentType = QStringLiteral("application/octet-stream"));
    QxtMailAttachment& operator=(const QxtMailAttachment& other);
    ~QxtMailAttachment();
    static QxtMailAttachment fromFile(const QString& filename);

    QIODevice* content() const;
    void setContent(const QByteArray& content);
    void setContent(QIODevice* content);

    bool deleteContent() const;
    void setDeleteContent(bool enable);

    QString contentType() const;
    void setContentType(const QString& contentType);

    QHash<QString, QString> extraHeaders() const;
    QString extraHeader(const QString&) const;
    bool hasExtraHeader(const QString&) const;
    void setExtraHeader(const QString& key, const QString& value);
    void setExtraHeaders(const QHash<QString, QString>&);
    void removeExtraHeader(const QString& key);

    QByteArray mimeData();
    const QByteArray& rawData() const;
    bool isText() const;

private:
    QSharedDataPointer<QxtMailAttachmentPrivate> qxt_d;
};
Q_DECLARE_TYPEINFO(QxtMailAttachment, Q_MOVABLE_TYPE);

#endif // MAILATTACHMENT_H
