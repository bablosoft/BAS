#ifndef IENCRYPTOR_H
#define IENCRYPTOR_H

#include <QObject>

#include "engine_global.h"


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IEncryptor : public QObject
    {
        Q_OBJECT
    public:
        explicit IEncryptor(QObject *parent = 0);
        virtual QByteArray Encrypt(const QByteArray & Data,const QString & Key) = 0;
        virtual QByteArray Decrypt(const QByteArray & Data,const QString & Key) = 0;
        virtual QByteArray DecryptNotSafe(const QByteArray & Data,const QString & Key) = 0;

    signals:

    public slots:

    };
}

#endif // IENCRYPTOR_H
