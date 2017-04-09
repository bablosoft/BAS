#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include "engine_global.h"

#include "ipreprocessor.h"
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT Preprocessor : public IPreprocessor
    {
        Q_OBJECT
        bool IsInsideComment(const QString& str,int start);

        struct GotoLabelData
        {
          bool IsGotoLabel;
          int Index;
          QString Label;
        };
        GotoLabelData ParseSetGotoLabel(const QString& str,int start);
        QString Encrypt(const QString& Script,int ParanoicLevel);
        IEncryptor* Encryptor;
        QString Key;
        int EncryptIterator;
        bool IsRecord;
    public:
        explicit Preprocessor(QObject *parent = 0);
        virtual void SetEncryptor(IEncryptor* Encryptor);
        virtual void SetKey(const QString& Key);

        void SetIsRecord(bool IsRecord);
        bool GetIsRecord();

        void GenerateKey();
        virtual QString Preprocess(const QString& Script,int ParanoicLevel);

        virtual QString Decrypt(const QString& Script);
        virtual QString DecryptNotSafe(const QString& Script);

    signals:

    public slots:

    };
}

#endif // PREPROCESSOR_H
