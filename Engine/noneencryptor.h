#ifndef NONEENCRYPTOR_H
#define NONEENCRYPTOR_H
#include <QObject>

#include "engine_global.h"
#include "iencryptor.h"


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT NoneEncryptor : public IEncryptor
    {
        Q_OBJECT
    public:
        explicit NoneEncryptor(QObject *parent = 0);
        virtual QByteArray Encrypt(const QByteArray & Data,const QString & Key);
        virtual QByteArray Decrypt(const QByteArray & Data,const QString & Key);
        virtual QByteArray DecryptNotSafe(const QByteArray & Data,const QString & Key);
    signals:

    public slots:

    };
}

#endif // NONEENCRYPTOR_H
