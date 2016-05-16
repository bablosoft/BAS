#ifndef USERRESOURCEWRAPPER_H
#define USERRESOURCEWRAPPER_H
#include "engine_global.h"

#include "userresourcewidget.h"
#include "iresourcewidget.h"
#include "istringbuilder.h"
#include "idatabasestate.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT UserResourceWrapper : public IResourceWidget
    {
        Q_OBJECT
        UserResourceWidget *Widget;
        bool IsVisible;
        bool IsAdvancedVisible;
        bool IsVisibleAccordingToTrigger;
        bool DependendVisibilityParentVisible;
    public:
        void SetStringBuilder(IStringBuilder * val);
        IStringBuilder * GetStringBuilder();
        explicit UserResourceWrapper(QObject *parent = 0);
        ~UserResourceWrapper();
        void SetDatabaseState(IDatabaseState *DatabaseState);
        virtual void SetTableId(int TableId);
        virtual int GetTableId();


        virtual void SetVariableName(const QString& text);
        virtual void SetDescription(const MultiLanguageString& text);
        virtual void SetTypeId(const QString& type);
        virtual QString GetVariableName();
        virtual MultiLanguageString GetDescription();
        virtual void SetLanguageModel(ILanguageModel *Model);
        virtual ILanguageModel * GetLanguageModel();
        virtual void SetLanguage(const QString& Language);

        virtual void SetVisibleToUser(bool visible);
        virtual void SetEnabledToUser(bool enabled);
        virtual void SetAvailableNames(const QString& text);
        virtual bool GetVisibleToUser();
        virtual bool GetEnabledToUser();
        virtual QString GetAvailableNames();

        virtual bool GetIsAdvanced();
        virtual void SetIsAdvanced(bool IsAdvanced);

        virtual MultiLanguageString GetSectionName();
        virtual void SetSectionName(const MultiLanguageString& SectionName);
        virtual QString GetVisibilityConditionVariable();
        virtual void SetVisibilityConditionVariable(const QString& VisibilityConditionVariable);
        virtual QString GetVisibilityConditionValue();
        virtual void SetVisibilityConditionValue(const QString& VisibilityConditionValue);

        virtual QWidget* GetTemplateCurrentWidget(bool IsUser);
        virtual QWidget* GetTemplateWidgetByType(bool IsUser, const QString& type);
        virtual QString GetTypeId();
        virtual QWidget* GetMainWidget();
        virtual void SetIndex(int index);
        virtual bool IsValid();
        virtual bool GetIsAdvancedVisible();
        virtual bool GetRequiresValidation();

    signals:

    public slots:
        virtual void VisibilityTriggerChanged(const QString& Value);
        virtual void VisibilityParentChanged(bool Visible);
        virtual void VisibilityAdvancedChanged(bool Visible);
        virtual void SetVisibleAdvanced(bool Visible);
    };
}

#endif // USERRESOURCEWRAPPER_H
