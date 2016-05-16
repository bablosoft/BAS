#include "resourceuserwidgetfactory.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    ResourceUserWidgetFactory::ResourceUserWidgetFactory(QObject *parent) :
        IResourceWidgetFactory(parent)
    {
    }

    IResourceWidget * ResourceUserWidgetFactory::CreateObject()
    {
        UserResourceWrapper* res = new UserResourceWrapper();
        res->SetStringBuilder(StringBulder);
        res->SetDatabaseState(DatabaseState);
        return res;
    }

    void ResourceUserWidgetFactory::SetStringBuilder(IStringBuilder * val)
    {
        StringBulder = val;
    }

    IStringBuilder * ResourceUserWidgetFactory::GetStringBuilder()
    {
        return StringBulder;

    }
    void ResourceUserWidgetFactory::SetDatabaseState(IDatabaseState *DatabaseState)
    {
        this->DatabaseState = DatabaseState;
    }
}
