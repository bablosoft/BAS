#ifndef IRESOURCES_H
#define IRESOURCES_H
#include "engine_global.h"

#include <QObject>
#include "iresourcemodel.h"
#include "iresourcecontroller.h"

namespace BrowserAutomationStudioFramework
{
    class IResourceController;
    class ENGINESHARED_EXPORT IResources : public QObject
    {
        Q_OBJECT
    public:
        explicit IResources(QObject *parent = 0);

    signals:

    public slots:
        virtual QList<IResourceModel * > * GetModelList() = 0;
        virtual void FromViewToModel(IResourceController *controller) = 0;
        virtual void FromModelToView(IResourceController *controller) = 0;
    };
}

#endif // IRESOURCES_H
