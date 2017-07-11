#ifndef USERRESOURCEWIDGET_H
#define USERRESOURCEWIDGET_H
#include "engine_global.h"

#include <QGroupBox>
#include "istringbuilder.h"
#include "multilanguagestring.h"
#include "idatabasestate.h"

namespace Ui {
class UserResourceWidget;
}

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT UserResourceWidget : public QWidget
    {
        Q_OBJECT
        QStringList ComboBoxData;
        QString VariableName,VisibilityConditionVariable,VisibilityConditionValue, Language;
        MultiLanguageString Descrition,SectionName;
        bool IsAdvanced;
        QList<int> ColumnIds;

    signals:
        void ValidationStateChanged();
    public:
        explicit UserResourceWidget(QWidget *parent = 0);
        ~UserResourceWidget();
        void SetStringBuilder(IStringBuilder * val);
        void SetDatabaseState(IDatabaseState *DatabaseState);

        IStringBuilder * GetStringBuilder();
        void SetVariableName(const QString& text);
        void SetLanguage(const QString& lang);
        void SetDescription(const MultiLanguageString& text);
        void SetTypeId(const QString& type);
        QString GetVariableName();
        MultiLanguageString GetDescription();
        QString GetTypeId();

        void SetVisibleToUser(bool visible);
        void SetEnabledToUser(bool enabled);
        void SetAvailableNames(const QString& text);

        bool GetVisibleToUser();
        bool GetEnabledToUser();
        QString GetAvailableNames();

        bool GetIsAdvanced();
        void SetIsAdvanced(bool IsAdvanced);

        MultiLanguageString GetSectionName();
        void SetSectionName(const MultiLanguageString& SectionName);
        QString GetVisibilityConditionVariable();
        void SetVisibilityConditionVariable(const QString& VisibilityConditionVariable);
        QString GetVisibilityConditionValue();
        void SetVisibilityConditionValue(const QString& VisibilityConditionValue);

        QWidget* GetTemplateCurrentWidget(bool IsUser);
        QWidget* GetTemplateWidgetByType(bool IsUser, const QString& type);

        bool IsValid();
        void SetTableId(int TableId);
        int GetTableId();
        QList<int> GetColumnIds();
        void SetColumnIds(const QList<int>& ColumnIds);
    public slots:
        void SetVisibleAdvanced(bool Visible);

    private:
        Ui::UserResourceWidget *ui;
        int FindComboBoxIndexByName(const QString& name);
        void changeEvent(QEvent *e);
    };
}

#endif // USERRESOURCEWIDGET_H
