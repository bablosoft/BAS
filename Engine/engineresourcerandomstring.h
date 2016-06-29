#ifndef ENGINERESOURCERANDOMSTRING_H
#define ENGINERESOURCERANDOMSTRING_H
#include "engine_global.h"

#include "engineresourceabstract.h"
#include "istringbuilder.h"


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT EngineResourceRandomString : public EngineResourceAbstract
    {
        Q_OBJECT
        QString Value;
        IStringBuilder *Builder;
    public:
        explicit EngineResourceRandomString(QObject *parent = 0);

        void SetValue(const QString& Value);


    signals:

    public slots:
        virtual IResourceHandler* GetHandler(const QSet<QString>& refuse);
        virtual void Reload();
        void SetStringBuilder(IStringBuilder *Builder);
        virtual QList<QScriptValue> GetAllData();
        virtual QList<QScriptValue> GetRandomSubarrayData(int size);
        virtual QScriptValue GetAtIndex(int index);
        virtual void SetAtIndex(int index, const QString& val);

        virtual int GetTotalLength();

        virtual void Success();
        virtual void Fail();
        virtual void Die();
        virtual void Insert(const QString& value, bool onlywrite);
        virtual void Sync();
    };
}

#endif // ENGINERESOURCERANDOMSTRING_H
