#ifndef IENGINERESOURCE_H
#define IENGINERESOURCE_H
#include "engine_global.h"

#include <QObject>
#include <QScriptValue>
#include "iresourcehandler.h"

namespace BrowserAutomationStudioFramework
{
    class IResourceHandler;
    class ENGINESHARED_EXPORT IEngineResource : public QObject
    {
        Q_OBJECT
        virtual void SetInfo(const QString& key, const QString& value) = 0;
    public:
        explicit IEngineResource(QObject *parent = 0);

    signals:

    public slots:
        virtual QString GetInfo(const QString& key) = 0;
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

#endif // IENGINERESOURCE_H
