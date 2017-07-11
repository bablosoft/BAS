#ifndef ICONSTRUCTRESOURCE_H
#define ICONSTRUCTRESOURCE_H
#include "engine_global.h"
#include "iresourcewidget.h"
#include "istringbuilder.h"
#include <QObject>
#include <QHash>

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT IConstructResource : public QObject
    {
    Q_OBJECT
    public:
        explicit IConstructResource(QObject *parent = 0);

    public slots:
        virtual int ConstructResource(IResourceWidget* ResourceWidget) = 0;
        virtual void SetStringBuilder(IStringBuilder * StringBuilder) = 0;
        virtual void SetGroups(const QStringList& Groups) = 0;
        virtual void SetSelectsVariablesAndValues(const QHash<QString,QString>& VariablesAndValues) = 0;

    };
}


#endif // ICONSTRUCTRESOURCE_H
