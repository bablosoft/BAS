#ifndef RESOURCES_H
#define RESOURCES_H
#include "engine_global.h"

#include <QObject>
#include "iresourcemodel.h"
#include "iresourcecontroller.h"
#include "iresources.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT Resources : public IResources
    {
        Q_OBJECT
        QList<IResourceModel * > ModelList;
    public:
        explicit Resources(QObject *parent = 0);

    signals:

    public slots:
        virtual QList<IResourceModel * > * GetModelList();
        bool NeedToFillByUser();
        virtual void FromViewToModel(IResourceController *controller);
        virtual void FromModelToView(IResourceController *controller);
    };
}

#endif // RESOURCES_H
