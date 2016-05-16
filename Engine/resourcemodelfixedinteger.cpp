#include "resourcemodelfixedinteger.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    ResourceModelFixedInteger::ResourceModelFixedInteger(QObject *parent) :
        ResourceModelAbstract(parent),MinValue(-99999999),MaxValue(99999999)
    {
    }
    ResourceModelFixedInteger::~ResourceModelFixedInteger()
    {

    }

    int ResourceModelFixedInteger::GetValue()
    {
        return Value;
    }

    void ResourceModelFixedInteger::SetValue(int Value)
    {
        this->Value = Value;
    }

    int ResourceModelFixedInteger::GetMaxValue()
    {
        return MaxValue;
    }

    void ResourceModelFixedInteger::SetMaxValue(int MaxValue)
    {
        this->MaxValue = MaxValue;
    }

    int ResourceModelFixedInteger::GetMinValue()
    {
        return MinValue;
    }

    void ResourceModelFixedInteger::SetMinValue(int MinValue)
    {
        this->MinValue = MinValue;
    }

    QString ResourceModelFixedInteger::GetTypeId()
    {
        return QString("FixedInteger");
    }
}
