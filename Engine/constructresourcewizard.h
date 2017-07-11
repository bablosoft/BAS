#ifndef CONSTRUCTRESOURCEWIZARD_H
#define CONSTRUCTRESOURCEWIZARD_H
#include "engine_global.h"
#include "iconstructresource.h"


namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT ConstructResourceWizard : public IConstructResource
    {
        Q_OBJECT
        IStringBuilder * StringBuilder;
        QStringList Groups;
        QHash<QString,QString> VariablesAndValues;

    public:
        explicit ConstructResourceWizard(QObject *parent = 0);
    public slots:
        virtual int ConstructResource(IResourceWidget* ResourceWidget);
        virtual void SetStringBuilder(IStringBuilder * StringBuilder);
        virtual void SetGroups(const QStringList& Groups);
        virtual void SetSelectsVariablesAndValues(const QHash<QString,QString>& VariablesAndValues);


    };
}




#endif // CONSTRUCTRESOURCEWIZARD_H
