#include "constructresourcewizard.h"
#include "resourcewizard.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    ConstructResourceWizard::ConstructResourceWizard(QObject *parent) : IConstructResource(parent)
    {
        StringBuilder = 0;
    }

    int ConstructResourceWizard::ConstructResource(IResourceWidget* ResourceWidget)
    {
        ResourceWizard Wizard;
        Wizard.SetResourceWidget(ResourceWidget);
        Wizard.SetGroups(Groups);
        Wizard.SetStringBuilder(StringBuilder);
        Wizard.SetSelectsVariablesAndValues(VariablesAndValues);

        return Wizard.exec();
    }
    void ConstructResourceWizard::SetStringBuilder(IStringBuilder * StringBuilder)
    {
        this->StringBuilder = StringBuilder;
    }
    void ConstructResourceWizard::SetGroups(const QStringList& Groups)
    {
        this->Groups = Groups;
    }
    void ConstructResourceWizard::SetSelectsVariablesAndValues(const QHash<QString,QString>& VariablesAndValues)
    {
        this->VariablesAndValues = VariablesAndValues;
    }
}
