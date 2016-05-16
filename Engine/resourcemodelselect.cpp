#include "resourcemodelselect.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    ResourceModelSelect::ResourceModelSelect(QObject *parent) :
        ResourceModelAbstract(parent)
    {
        Type = Combo;
    }

    QStringList ResourceModelSelect::GetValues()
    {
        return Values;
    }
    void ResourceModelSelect::SetValues(const QStringList& val)
    {
        Values = val;
    }
    QList<int> ResourceModelSelect::GetSelected()
    {
        return Selected;
    }
    void ResourceModelSelect::SetSelected(const QList<int>& val)
    {
        Selected = val;
    }
    QString ResourceModelSelect::GetTypeId()
    {
        return QString("Select");
    }
    ResourceModelSelect::SelectType ResourceModelSelect::GetSelectType()
    {
        return Type;
    }
    void ResourceModelSelect::SetSelectType(SelectType val)
    {
        Type = val;
    }

}
