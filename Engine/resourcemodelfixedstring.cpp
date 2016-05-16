#include "resourcemodelfixedstring.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    ResourceModelFixedString::ResourceModelFixedString(QObject *parent) :
        ResourceModelAbstract(parent)
    {
        NotEmpty = false;
    }

    QString ResourceModelFixedString::GetValue()
    {
        return Value;
    }

    void ResourceModelFixedString::SetValue(const QString& Value)
    {
        this->Value = Value;
    }

    QString ResourceModelFixedString::GetTypeId()
    {
        return QString("FixedString");
    }

    bool ResourceModelFixedString::GetNotEmpty()
    {
        return NotEmpty;
    }
    void ResourceModelFixedString::SetNotEmpty(bool NotEmpty)
    {
        this->NotEmpty = NotEmpty;
    }
}
