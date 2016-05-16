#ifndef COPYRESOURCECONTROLLER_H
#define COPYRESOURCECONTROLLER_H
#include "engine_global.h"

#include "iresourcecontroller.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT CopyResourceController : public IResourceController
    {
        Q_OBJECT
        IResources * ResourcesExternal;
        IResources * DefaultsExternal;
        IResourceModel* CopyModelToActual(const QString& Type, IResourceModel* ModelTo, IResourceModel* ModelFrom, IResourceModel* ModelDefault, QObject* parent);
        bool IsDefaultChanged(const QString& Type,IResourceModel* ModelFrom, IResourceModel* ModelDefault);

    public:
        explicit CopyResourceController(QObject *parent = 0);

    signals:

    public slots:
        void SetResources(IResources * ResourcesExternal);
        void SetDefaults(IResources * DefaultsExternal);
        virtual void FromViewToModel(IResources * resources, bool Clear = true);
        virtual void FromModelToView(IResources * resources, bool Clear = true);
    };
}

#endif // COPYRESOURCECONTROLLER_H
