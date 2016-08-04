#include "designresourcewrapper.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    DesignResourceWrapper::DesignResourceWrapper(QObject *parent) :
        IResourceWidget(parent)
    {
        Widget = new DesignResourceWidget();
        connect(Widget,SIGNAL(Up(int)),this,SIGNAL(Up(int)));
        connect(Widget,SIGNAL(Down(int)),this,SIGNAL(Down(int)));
        connect(Widget,SIGNAL(VariableNameChanged(QString)),this,SIGNAL(VariableNameChanged(QString)));
        connect(Widget,SIGNAL(WillBeDeleted()),this,SIGNAL(ResourceDestroyed()));
        this->setParent(Widget);
    }

    void DesignResourceWrapper::SetTableId(int TableId)
    {

    }

    int DesignResourceWrapper::GetTableId()
    {
        return -1;
    }

    void DesignResourceWrapper::SetLanguageModel(ILanguageModel *Model)
    {
        Widget->SetLanguageModel(Model);
    }

    ILanguageModel * DesignResourceWrapper::GetLanguageModel()
    {
        return Widget->GetLanguageModel();
    }

    void DesignResourceWrapper::SetLanguage(const QString& Language)
    {

    }

    IStringBuilder * DesignResourceWrapper::GetStringBuilder()
    {
        return Widget->GetStringBuilder();
    }

    void DesignResourceWrapper::SetStringBuilder(IStringBuilder * val)
    {
        Widget->SetStringBuilder(val);
    }

    void DesignResourceWrapper::SetDatabaseState(IDatabaseState *DatabaseState)
    {
        Widget->SetDatabaseState(DatabaseState);
    }

    DesignResourceWrapper::~DesignResourceWrapper()
    {

    }


    void DesignResourceWrapper::SetVariableName(const QString& text)
    {
        Widget->SetVariableName(text);
    }

    QString DesignResourceWrapper::GetVariableName()
    {
        return Widget->GetVariableName();
    }

    MultiLanguageString DesignResourceWrapper::GetDescription()
    {
        return Widget->GetDescription();
    }

    void DesignResourceWrapper::SetDescription(const MultiLanguageString& text)
    {
        Widget->SetDescription(text);
    }

    void DesignResourceWrapper::SetTypeId(const QString& type)
    {
        Widget->SetTypeId(type);
    }

    QWidget* DesignResourceWrapper::GetTemplateCurrentWidget(bool IsUser)
    {
        return Widget->GetTemplateCurrentWidget(IsUser);
    }

    QWidget* DesignResourceWrapper::GetTemplateWidgetByType(bool IsUser,const QString& type)
    {
        return Widget->GetTemplateWidgetByType(IsUser,type);
    }

    QString DesignResourceWrapper::GetTypeId()
    {
        return Widget->GetTypeId();
    }

    QWidget* DesignResourceWrapper::GetMainWidget()
    {
        return Widget;
    }

    void DesignResourceWrapper::SetVisibleToUser(bool visible)
    {
        Widget->SetVisibleToUser(visible);
    }

    void DesignResourceWrapper::SetEnabledToUser(bool enabled)
    {
        Widget->SetEnabledToUser(enabled);
    }

    void DesignResourceWrapper::SetAvailableNames(const QString& text)
    {
        Widget->SetAvailableNames(text);
    }

    bool DesignResourceWrapper::GetVisibleToUser()
    {
        return Widget->GetVisibleToUser();
    }

    bool DesignResourceWrapper::GetEnabledToUser()
    {
        return Widget->GetEnabledToUser();
    }

    QString DesignResourceWrapper::GetAvailableNames()
    {
        return Widget->GetAvailableNames();
    }

    MultiLanguageString DesignResourceWrapper::GetSectionName()
    {
        return Widget->GetSectionName();
    }

    void DesignResourceWrapper::SetSectionName(const MultiLanguageString& SectionName)
    {
        Widget->SetSectionName(SectionName);
    }

    QString DesignResourceWrapper::GetVisibilityConditionVariable()
    {
        return Widget->GetVisibilityConditionVariable();
    }

    void DesignResourceWrapper::SetVisibilityConditionVariable(const QString& VisibilityConditionVariable)
    {
        Widget->SetVisibilityConditionVariable(VisibilityConditionVariable);
    }

    QString DesignResourceWrapper::GetVisibilityConditionValue()
    {
        return Widget->GetVisibilityConditionValue();
    }

    void DesignResourceWrapper::SetVisibilityConditionValue(const QString& VisibilityConditionValue)
    {
        Widget->SetVisibilityConditionValue(VisibilityConditionValue);
    }

    void DesignResourceWrapper::VisibilityTriggerChanged(const QString& Value)
    {

    }

    void DesignResourceWrapper::VisibilityParentChanged(bool Visible)
    {


    }
    bool DesignResourceWrapper::IsValid()
    {
        return true;
    }

    bool DesignResourceWrapper::GetIsAdvanced()
    {
        return Widget->GetIsAdvanced();
    }
    void DesignResourceWrapper::SetIsAdvanced(bool IsAdvanced)
    {
        Widget->SetIsAdvanced(IsAdvanced);
    }

    bool DesignResourceWrapper::GetIsAdvancedVisible()
    {
        return true;
    }

    void DesignResourceWrapper::VisibilityAdvancedChanged(bool Visible)
    {

    }

    bool DesignResourceWrapper::GetRequiresValidation()
    {
        return false;
    }

    void DesignResourceWrapper::SetVisibleAdvanced(bool Visible)
    {

    }

}
