#include "resourcedesignwidgetfactory.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    ResourceDesignWidgetFactory::ResourceDesignWidgetFactory(QObject *parent) :
        IResourceWidgetFactory(parent)
    {
    }

    IResourceWidget * ResourceDesignWidgetFactory::CreateObject()
    {
        DesignResourceWrapper *res = new DesignResourceWrapper();
        res->SetStringBuilder(GetStringBuilder());
        res->SetDatabaseState(DatabaseState);
        return res;
    }

    IStringBuilder * ResourceDesignWidgetFactory::GetStringBuilder()
    {
        return StringBulder;
    }

    void ResourceDesignWidgetFactory::SetStringBuilder(IStringBuilder * val)
    {
        StringBulder = val;
    }

    void ResourceDesignWidgetFactory::SetDatabaseState(IDatabaseState *DatabaseState)
    {
        this->DatabaseState = DatabaseState;
    }
}
