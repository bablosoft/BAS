#include "resources.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    Resources::Resources(QObject *parent) :
        IResources(parent)
    {

    }
    bool Resources::NeedToFillByUser()
    {
        foreach(IResourceModel *m,ModelList)
        {
            if(m->GetVisibleByUser())
            {
                return true;
            }
        }
        return false;

    }

    QList<IResourceModel * > * Resources::GetModelList()
    {
        return &ModelList;
    }
    void Resources::FromViewToModel(IResourceController *controller)
    {
        controller->FromViewToModel(this);
    }
    void Resources::FromModelToView(IResourceController *controller)
    {
        controller->FromModelToView(this);
    }
}
