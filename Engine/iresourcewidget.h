#ifndef IRESOURCEWIDGET_H
#define IRESOURCEWIDGET_H
#include "engine_global.h"
#include "multilanguagestring.h"
#include <QObject>
#include "ilanguagemodel.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IResourceWidget : public QObject
    {
        Q_OBJECT
    public:
        explicit IResourceWidget(QObject *parent = 0);
        virtual void SetTableId(int TableId) = 0;
        virtual int GetTableId() = 0;
        virtual void SetVariableName(const QString& text) = 0;
        virtual void SetDescription(const MultiLanguageString& text) = 0;
        virtual void SetTypeId(const QString& type) = 0;
        virtual void SetLanguageModel(ILanguageModel *Model) = 0;
        virtual QString GetVariableName() = 0;
        virtual MultiLanguageString GetDescription() = 0;
        virtual QString GetTypeId() = 0;

        virtual void SetVisibleToUser(bool visible) = 0;
        virtual void SetEnabledToUser(bool enabled) = 0;
        virtual void SetAvailableNames(const QString& text) = 0;

        virtual bool GetVisibleToUser() = 0;
        virtual bool GetEnabledToUser() = 0;
        virtual QString GetAvailableNames() = 0;

        virtual bool GetIsAdvanced() = 0;
        virtual void SetIsAdvanced(bool IsAdvanced) = 0;

        virtual MultiLanguageString GetSectionName() = 0;
        virtual void SetSectionName(const MultiLanguageString& SectionName) = 0;
        virtual QString GetVisibilityConditionVariable() = 0;
        virtual void SetVisibilityConditionVariable(const QString& VisibilityConditionVariable) = 0;
        virtual QString GetVisibilityConditionValue() = 0;
        virtual void SetVisibilityConditionValue(const QString& VisibilityConditionValue) = 0;

        virtual QWidget* GetTemplateCurrentWidget(bool IsUser) = 0;
        virtual QWidget* GetTemplateWidgetByType(bool IsUser,const QString& type) = 0;
        virtual QWidget* GetMainWidget() = 0;

        virtual ILanguageModel * GetLanguageModel() = 0;
        virtual void SetLanguage(const QString& Language) = 0;

        virtual bool IsValid() = 0;
        virtual bool GetRequiresValidation() = 0;

        virtual bool GetIsAdvancedVisible() = 0;

        virtual void SetVisibleAdvanced(bool Visible) = 0;

    signals:
        void Up(int index);
        void Down(int index);
        void VariableNameChanged(QString name);
        void ResourceDestroyed();
        void VisibilityChanged(bool Visible);
        void ValidationStateChanged();
        void RequiresValidationStateChanged(bool Visible);
    public slots:
        virtual void VisibilityTriggerChanged(const QString& Value) = 0;
        virtual void VisibilityParentChanged(bool Visible) = 0;
        virtual void VisibilityAdvancedChanged(bool Visible) = 0;
    };
}

#endif // IRESOURCEWIDGET_H
