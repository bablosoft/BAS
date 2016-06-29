#ifndef IENGINERESOURCES_H
#define IENGINERESOURCES_H
#include "engine_global.h"

#include <QObject>
#include <QScriptValue>
#include "iresourcehandler.h"
#include "iengineresource.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IEngineResources : public QObject
    {
        Q_OBJECT
    public:
        explicit IEngineResources(QObject *parent = 0);
        virtual void Add(const QString& Name, IEngineResource * Res) = 0;
        virtual QString GetInfo(const QString& Name, const QString& Key) = 0;
        virtual void Create(const QString& name, int successes, int fails, int simultaneous, int interval, bool greedy, bool dont_give_up) = 0;
        virtual IResourceHandler* GetHandler(const QString & name, const QSet<QString>& refuse) = 0;
        virtual QList<QScriptValue> GetAllData(const QString & name) = 0;
        virtual QList<QScriptValue> GetRandomSubarrayData(const QString& name, int size) = 0;
        virtual QScriptValue GetAtIndex(const QString& name, int index) = 0;
        virtual void SetAtIndex(const QString& name, int index, const QString& val) = 0;
        virtual int GetTotalLength(const QString& name) = 0;

        virtual void Reload(const QString & name) = 0;
        virtual void Remove(const QString & name) = 0;
        virtual void Insert(const QString & name, const QString & value, bool onlywrite) = 0;
        virtual void Sync(const QString & name) = 0;
    signals:

    public slots:

    };
}

#endif // IENGINERESOURCES_H
