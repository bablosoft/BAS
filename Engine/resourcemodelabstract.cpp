#include "resourcemodelabstract.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    ResourceModelAbstract::ResourceModelAbstract(QObject *parent) :
        IResourceModel(parent), Types(QString("All")), Enabled(true), Visible(true), IsAdvanced(false)
    {
    }

    MultiLanguageString ResourceModelAbstract::GetSectionName()
    {
        return SectionName;
    }

    void ResourceModelAbstract::SetSectionName(const MultiLanguageString& SectionName)
    {
        this->SectionName = SectionName;
    }

    QString ResourceModelAbstract::GetVisibilityConditionVariable()
    {
        return VisibilityConditionVariable;
    }

    void ResourceModelAbstract::SetVisibilityConditionVariable(const QString& VisibilityConditionVariable)
    {
        this->VisibilityConditionVariable = VisibilityConditionVariable;
    }

    QString ResourceModelAbstract::GetVisibilityConditionValue()
    {
        return VisibilityConditionValue;
    }
    void ResourceModelAbstract::SetVisibilityConditionValue(const QString& VisibilityConditionValue)
    {
        this->VisibilityConditionValue = VisibilityConditionValue;
    }

    QString ResourceModelAbstract::GetName()
    {
        return Name;
    }

    void ResourceModelAbstract::SetName(const QString& Name)
    {
        this->Name = Name;
    }

    MultiLanguageString ResourceModelAbstract::GetDescription()
    {
        return Description;
    }

    void ResourceModelAbstract::SetDescription(const MultiLanguageString& Description)
    {
        this->Description = Description;
    }

    bool ResourceModelAbstract::GetVisibleByUser()
    {
        return Visible;
    }

    void ResourceModelAbstract::SetVisibleByUser(bool visible)
    {
        Visible = visible;
    }

    bool ResourceModelAbstract::GetEnabledByUser()
    {
        return Enabled;
    }

    void ResourceModelAbstract::SetEnabledByUser(bool enabled)
    {
        Enabled = enabled  ;
    }

    QString ResourceModelAbstract::GetAllowedTypes()
    {
        return Types;
    }

    void ResourceModelAbstract::SetAllowedTypes(const QString& Types)
    {
        this->Types = Types;
    }

    QList<IResourceModel*> ResourceModelAbstract::GetDefaults()
    {
        return Defaults;
    }

    void ResourceModelAbstract::SetDefaults(QList<IResourceModel*>& Defaults)
    {
        this->Defaults = Defaults;
    }

    bool ResourceModelAbstract::GetIsAdvanced()
    {
        return IsAdvanced;
    }

    void ResourceModelAbstract::SetIsAdvanced(bool IsAdvanced)
    {
        this->IsAdvanced = IsAdvanced;
    }

}
