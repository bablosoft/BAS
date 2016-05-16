#include "userresourcewrapper.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    UserResourceWrapper::UserResourceWrapper(QObject *parent) :
        IResourceWidget(parent)
    {
        Widget = new UserResourceWidget();
        this->setParent(Widget);
        DependendVisibilityParentVisible = true;
        IsVisibleAccordingToTrigger = true;
        IsAdvancedVisible = true;

        connect(Widget,SIGNAL(ValidationStateChanged()),this,SIGNAL(ValidationStateChanged()));
    }

    void UserResourceWrapper::SetDatabaseState(IDatabaseState *DatabaseState)
    {
        Widget->SetDatabaseState(DatabaseState);
    }

    void UserResourceWrapper::SetTableId(int TableId)
    {
        Widget->SetTableId(TableId);
    }

    int UserResourceWrapper::GetTableId()
    {
        return Widget->GetTableId();
    }


    bool UserResourceWrapper::GetIsAdvancedVisible()
    {
        return IsAdvancedVisible;
    }

    void UserResourceWrapper::SetIndex(int index)
    {

    }

    void UserResourceWrapper::SetLanguage(const QString& Language)
    {
        Widget->SetLanguage(Language);
    }

    void UserResourceWrapper::SetLanguageModel(ILanguageModel *Model)
    {

    }
    ILanguageModel * UserResourceWrapper::GetLanguageModel()
    {
        return 0;
    }


    void UserResourceWrapper::SetStringBuilder(IStringBuilder * val)
    {
        Widget->SetStringBuilder(val);
    }

    IStringBuilder * UserResourceWrapper::GetStringBuilder()
    {
        return Widget->GetStringBuilder();
    }

    UserResourceWrapper::~UserResourceWrapper()
    {

    }


    void UserResourceWrapper::SetVariableName(const QString& text)
    {
        Widget->SetVariableName(text);
    }

    QString UserResourceWrapper::GetVariableName()
    {
        return Widget->GetVariableName();
    }

    MultiLanguageString UserResourceWrapper::GetDescription()
    {
        return Widget->GetDescription();
    }

    void UserResourceWrapper::SetDescription(const MultiLanguageString& text)
    {
        Widget->SetDescription(text);
    }

    void UserResourceWrapper::SetTypeId(const QString& type)
    {
        Widget->SetTypeId(type);
    }

    QWidget* UserResourceWrapper::GetTemplateCurrentWidget(bool IsUser)
    {
        return Widget->GetTemplateCurrentWidget(IsUser);
    }

    QWidget* UserResourceWrapper::GetTemplateWidgetByType(bool IsUser,const QString& type)
    {
        return Widget->GetTemplateWidgetByType(IsUser,type);
    }

    QString UserResourceWrapper::GetTypeId()
    {
        return Widget->GetTypeId();
    }

    QWidget* UserResourceWrapper::GetMainWidget()
    {
        return Widget;
    }

    void UserResourceWrapper::SetVisibleToUser(bool visible)
    {
        IsVisible = visible;
        Widget->SetVisibleToUser(visible);
    }

    void UserResourceWrapper::SetEnabledToUser(bool enabled)
    {
        Widget->SetEnabledToUser(enabled);
    }

    void UserResourceWrapper::SetAvailableNames(const QString& text)
    {
        Widget->SetAvailableNames(text);
    }

    bool UserResourceWrapper::GetVisibleToUser()
    {
        return Widget->GetVisibleToUser();
    }

    bool UserResourceWrapper::GetEnabledToUser()
    {
        return Widget->GetEnabledToUser();
    }

    QString UserResourceWrapper::GetAvailableNames()
    {
        return Widget->GetAvailableNames();
    }

    MultiLanguageString UserResourceWrapper::GetSectionName()
    {
        return Widget->GetSectionName();
    }

    void UserResourceWrapper::SetSectionName(const MultiLanguageString& SectionName)
    {
        Widget->SetSectionName(SectionName);
    }

    QString UserResourceWrapper::GetVisibilityConditionVariable()
    {
        return Widget->GetVisibilityConditionVariable();
    }

    void UserResourceWrapper::SetVisibilityConditionVariable(const QString& VisibilityConditionVariable)
    {
        Widget->SetVisibilityConditionVariable(VisibilityConditionVariable);
    }

    QString UserResourceWrapper::GetVisibilityConditionValue()
    {
        return Widget->GetVisibilityConditionValue();
    }

    void UserResourceWrapper::SetVisibilityConditionValue(const QString& VisibilityConditionValue)
    {
        Widget->SetVisibilityConditionValue(VisibilityConditionValue);
    }

    void UserResourceWrapper::VisibilityTriggerChanged(const QString& Value)
    {
        QStringList list = GetVisibilityConditionValue().split(QRegExp("[\\|\\;\\,]"));
        bool res = false;
        foreach(QString item, list)
        {
            if(Value.contains(item))
            {
                res = true;
                break;
            }
        }
        IsVisibleAccordingToTrigger = res;
        emit RequiresValidationStateChanged(IsVisible && IsVisibleAccordingToTrigger && DependendVisibilityParentVisible);

        if(res)
        {
            Widget->SetVisibleToUser(IsVisible && DependendVisibilityParentVisible && IsAdvancedVisible);
            emit VisibilityChanged(IsVisible && DependendVisibilityParentVisible && IsAdvancedVisible);
        }else
        {
            Widget->SetVisibleToUser(false);
            emit VisibilityChanged(false);
        }


    }

    void UserResourceWrapper::VisibilityParentChanged(bool Visible)
    {
        DependendVisibilityParentVisible = Visible;
        emit RequiresValidationStateChanged(IsVisible && IsVisibleAccordingToTrigger && DependendVisibilityParentVisible);
        if(Visible)
        {
            Widget->SetVisibleToUser(IsVisible && IsVisibleAccordingToTrigger && IsAdvancedVisible);
            emit VisibilityChanged(IsVisible && IsVisibleAccordingToTrigger && IsAdvancedVisible);
        }else
        {
            Widget->SetVisibleToUser(false);
            emit VisibilityChanged(false);
        }


    }

    void UserResourceWrapper::VisibilityAdvancedChanged(bool Visible)
    {
        if(GetIsAdvanced())
        {
            IsAdvancedVisible = Visible;
            if(Visible)
            {
                Widget->SetVisibleToUser(IsVisible && IsVisibleAccordingToTrigger && DependendVisibilityParentVisible);
                emit VisibilityChanged(IsVisible && IsVisibleAccordingToTrigger && DependendVisibilityParentVisible);
            }else
            {
                Widget->SetVisibleToUser(false);
                emit VisibilityChanged(false);
            }
        }
        Widget->SetVisibleAdvanced(Visible);



    }

    bool UserResourceWrapper::IsValid()
    {
        return Widget->IsValid();
    }

    bool UserResourceWrapper::GetIsAdvanced()
    {
        return Widget->GetIsAdvanced();
    }

    void UserResourceWrapper::SetIsAdvanced(bool IsAdvanced)
    {
        Widget->SetIsAdvanced(IsAdvanced);
    }

    bool UserResourceWrapper::GetRequiresValidation()
    {
        return IsVisible && IsVisibleAccordingToTrigger && DependendVisibilityParentVisible && Widget->GetEnabledToUser();
    }

    void UserResourceWrapper::SetVisibleAdvanced(bool Visible)
    {
        Widget->SetVisibleToUser(Visible);
    }

}
