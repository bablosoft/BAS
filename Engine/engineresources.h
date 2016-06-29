#ifndef ENGINERESOURCES_H
#define ENGINERESOURCES_H
#include "engine_global.h"

#include <QHash>
#include "iengineresource.h"
#include "iengineresources.h"
#include "iresourcecontroller.h"
#include "iresources.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT EngineResources : public IEngineResources
    {
        Q_OBJECT
        QHash<QString,IEngineResource *> Data;
        IResourceController* EngineResourcesController;
        IResources* Resources;

    public:
        explicit EngineResources(QObject *parent = 0);


        void Clear();

    signals:

    public slots:
        virtual QString GetInfo(const QString& Name, const QString& Key);
        virtual void Add(const QString& Name, IEngineResource * Res);
        virtual void Create(const QString& name, int successes, int fails, int simultaneous, int interval, bool greedy, bool dont_give_up);
        virtual IResourceHandler* GetHandler(const QString & name,const QSet<QString>& refuse);
        virtual QList<QScriptValue> GetAllData(const QString & name);
        virtual QList<QScriptValue> GetRandomSubarrayData(const QString& name, int size);
        virtual QScriptValue GetAtIndex(const QString& name, int index);
        virtual void SetAtIndex(const QString& name, int index, const QString& val);

        virtual int GetTotalLength(const QString& name);
        virtual void Reload(const QString & name);
        virtual void Remove(const QString & name);
        virtual void Insert(const QString & name, const QString & value, bool onlywrite);
        virtual void Sync(const QString & name);
        void SetEngineResourcesController(IResourceController* EngineResourcesController);
        void SetResources(IResources* Resources);

    };
}

#endif // ENGINERESOURCES_H
