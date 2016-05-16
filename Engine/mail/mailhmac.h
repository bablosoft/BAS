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

#ifndef MAILHMAC_H
#define MAILHMAC_H

#include "mailglobal.h"
#include <QScopedPointer>
#include <QCryptographicHash>

class QxtHmacPrivate;
class Q_MAIL_EXPORT QxtHmac
{
public:
    typedef QCryptographicHash::Algorithm Algorithm;

    QxtHmac(QCryptographicHash::Algorithm algorithm);
    ~QxtHmac();

    void setKey(QByteArray key);
    void reset();

    void addData(const char* data, int length);
    void addData(const QByteArray& data);

    QByteArray innerHash() const;
    QByteArray result();
    bool verify(const QByteArray& otherInner);

    static QByteArray hash(const QByteArray& key, const QByteArray& data, Algorithm algorithm);
    static bool verify(const QByteArray& key, const QByteArray& hmac, const QByteArray& inner, Algorithm algorithm);

private:
    Q_DECLARE_PRIVATE(QxtHmac)
    QScopedPointer<QxtHmacPrivate> d_ptr;
};

#endif //MAILHMAC_H
