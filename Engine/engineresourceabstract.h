#ifndef ENGINERESOURCEABSTRACT_H
#define ENGINERESOURCEABSTRACT_H
#include "engine_global.h"

#include "iengineresource.h"

#include <QObject>
#include <QHash>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT EngineResourceAbstract : public IEngineResource
    {
        Q_OBJECT
        QHash<QString,QString> InfoHash;
    public:
        explicit EngineResourceAbstract(QObject *parent = 0);
        virtual void SetInfo(const QString& key, const QString& value);
    signals:

    public slots:
        virtual QString GetInfo(const QString& key);
        virtual IResourceHandler* GetHandler(const QSet<QString>& refuse) = 0;

        virtual QList<QScriptValue> GetAllData() = 0;
        virtual QList<QScriptValue> GetRandomSubarrayData(int size) = 0;
        virtual QScriptValue GetAtIndex(int index) = 0;
        virtual void SetAtIndex(int index, const QString& val) = 0;
        virtual int GetTotalLength() = 0;

        virtual void Success() = 0;
        virtual void Fail() = 0;
        virtual void Die() = 0;
        virtual void Reload() = 0;
        virtual void Insert(const QString& value, bool onlywrite) = 0;
        virtual void Sync() = 0;
    };
}

#endif // ENGINERESOURCEABSTRACT_H
