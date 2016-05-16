#ifndef DESIGNRESOURCEWRAPPER_H
#define DESIGNRESOURCEWRAPPER_H
#include "engine_global.h"

#include "designresourcewidget.h"
#include "iresourcewidget.h"
#include "istringbuilder.h"
#include "idatabasestate.h"
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT DesignResourceWrapper : public IResourceWidget
    {
        Q_OBJECT
        DesignResourceWidget *Widget;

    public:
        IStringBuilder * GetStringBuilder();
        void SetStringBuilder(IStringBuilder * val);
        void SetDatabaseState(IDatabaseState *DatabaseState);
        explicit DesignResourceWrapper(QObject *parent = 0);
        ~DesignResourceWrapper();
        virtual void SetVariableName(const QString& text);
        virtual void SetDescription(const MultiLanguageString& text);
        virtual void SetTypeId(const QString& type);
        virtual QString GetVariableName();
        virtual MultiLanguageString GetDescription();
        virtual void SetTableId(int TableId);
        virtual int GetTableId();


        virtual void SetVisibleToUser(bool visible);
        virtual void SetEnabledToUser(bool enabled);
        virtual void SetAvailableNames(const QString& text);
        virtual bool GetVisibleToUser();
        virtual bool GetEnabledToUser();
        virtual void SetLanguageModel(ILanguageModel *Model);
        virtual ILanguageModel * GetLanguageModel();
        virtual void SetLanguage(const QString& Language);

        virtual bool GetIsAdvanced();
        virtual void SetIsAdvanced(bool IsAdvanced);

        virtual QString GetAvailableNames();

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

        virtual void VisibilityTriggerChanged(const QString& Value);
        virtual void VisibilityParentChanged(bool Visible);
        virtual bool GetRequiresValidation();
        virtual bool IsValid();
        virtual bool GetIsAdvancedVisible();
        virtual void VisibilityAdvancedChanged(bool Visible);
        virtual void SetVisibleAdvanced(bool Visible);

    signals:

    public slots:

    };
}

#endif // DESIGNRESOURCEWRAPPER_H

