#include "resourcemodelrandomstring.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    ResourceModelRandomString::ResourceModelRandomString(QObject *parent) :
        ResourceModelAbstract(parent)
    {
    }

    QString ResourceModelRandomString::GetTypeId()
    {
        return QString("RandomString");
    }

    QString ResourceModelRandomString::GetValue()
    {
        return Value;
    }

    void ResourceModelRandomString::SetValue(const QString& val)
    {
        this->Value = val;
    }

}
