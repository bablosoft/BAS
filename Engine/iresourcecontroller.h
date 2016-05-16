#ifndef IRESOURCECONTROLLER_H
#define IRESOURCECONTROLLER_H
#include "engine_global.h"

#include <QObject>
#include <QList>
#include "iresourcemodel.h"
#include "iresources.h"
namespace BrowserAutomationStudioFramework
{
    class IResources;
    class ENGINESHARED_EXPORT IResourceController : public QObject
    {
        Q_OBJECT
    public:
        explicit IResourceController(QObject *parent = 0);

    signals:

    public slots:
        virtual void FromViewToModel(IResources * resources, bool Clear = true) = 0;
        virtual void FromModelToView(IResources * resources, bool Clear = true) = 0;
    };
}

#endif // IRESOURCECONTROLLER_H
