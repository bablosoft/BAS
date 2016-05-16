#ifndef IPREPROCESSOR_H
#define IPREPROCESSOR_H
#include "engine_global.h"

#include <QObject>
#include "iencryptor.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IPreprocessor : public QObject
    {
        Q_OBJECT
    public:
        explicit IPreprocessor(QObject *parent = 0);
        virtual void SetEncryptor(IEncryptor* Encryptor) = 0;
        virtual void SetKey(const QString& Key) = 0;

        virtual QString Preprocess(const QString& Script,int ParanoicLevel) = 0;
        virtual QString Decrypt(const QString& Script) = 0;
        virtual QString DecryptNotSafe(const QString& Script) = 0;
    signals:

    public slots:

    };
}

#endif // IPREPROCESSOR_H
