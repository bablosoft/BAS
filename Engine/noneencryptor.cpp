#include "noneencryptor.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    NoneEncryptor::NoneEncryptor(QObject *parent) :
        IEncryptor(parent)
    {
    }

    QByteArray NoneEncryptor::Encrypt(const QByteArray & Data,const QString & Key)
    {
        return Data;
    }
    QByteArray NoneEncryptor::Decrypt(const QByteArray & Data,const QString & Key)
    {
        return Data;
    }
    QByteArray NoneEncryptor::DecryptNotSafe(const QByteArray & Data,const QString & Key)
    {
        return Data;
    }
}
