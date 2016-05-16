#include "resourcemodelrandominteger.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    ResourceModelRandomInteger::ResourceModelRandomInteger(QObject *parent) :
        ResourceModelAbstract(parent)
    {
    }

    int ResourceModelRandomInteger::GetMaxUserValue()
    {
        return MaxUserValue;
    }

    void ResourceModelRandomInteger::SetMaxUserValue(int MaxUserValue)
    {
        this->MaxUserValue = MaxUserValue;
    }

    int ResourceModelRandomInteger::GetMinUserValue()
    {
        return MinUserValue;
    }

    void ResourceModelRandomInteger::SetMinUserValue(int MinUserValue)
    {
        this->MinUserValue = MinUserValue;
    }


    int ResourceModelRandomInteger::GetMaxDesignValue()
    {
        return MaxDesignValue;
    }

    void ResourceModelRandomInteger::SetMaxDesignValue(int MaxDesignValue)
    {
        this->MaxDesignValue = MaxDesignValue;
    }

    int ResourceModelRandomInteger::GetMinDesignValue()
    {
        return MinDesignValue;
    }

    void ResourceModelRandomInteger::SetMinDesignValue(int MinDesignValue)
    {
        this->MinDesignValue = MinDesignValue;
    }

    QString ResourceModelRandomInteger::GetTypeId()
    {
        return QString("RandomInteger");
    }
}
