#ifndef DESIGNRESOURCEWIDGET_H
#define DESIGNRESOURCEWIDGET_H
#include "engine_global.h"
#include "multilanguagetextbox.h"

#include <QGroupBox>
#include "istringbuilder.h"
#include "idatabasestate.h"
namespace Ui {
class DesignResourceWidget;
}
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT DesignResourceWidget : public QGroupBox
    {
        Q_OBJECT
        bool MoreState;
        ILanguageModel *LanguageModel;
        QStringList ComboBoxData;
        QString OldName;
        bool TooltipUserFocus;
        bool ShowTooltip;
        bool TooltipUserFocus2;
        bool ShowTooltip2;
        bool TooltipUserFocus3;
        bool ShowTooltip3;
        bool eventFilter(QObject *obj, QEvent *event);

    public:
        MultiLanguageTextBox *DescriptionTextBox;
        MultiLanguageTextBox *SectionTextBox;
        IStringBuilder * GetStringBuilder();
        void SetStringBuilder(IStringBuilder * val);
        void SetDatabaseState(IDatabaseState *DatabaseState);

        explicit DesignResourceWidget(QWidget *parent = 0);
        ~DesignResourceWidget();
        void SetVariableName(const QString& text);
        void SetDescription(const MultiLanguageString& text);
        void SetTypeId(const QString& type);
        QString GetVariableName();
        MultiLanguageString GetDescription();
        QString GetTypeId();
        MultiLanguageString GetSectionName();
        void SetSectionName(const MultiLanguageString& SectionName);

        QString GetVisibilityConditionVariable();
        void SetVisibilityConditionVariable(const QString& VisibilityConditionVariable);
        QString GetVisibilityConditionValue();
        void SetVisibilityConditionValue(const QString& VisibilityConditionValue);
        void SetLanguageModel(ILanguageModel *Model);
        ILanguageModel * GetLanguageModel();

        bool GetIsAdvanced();
        void SetIsAdvanced(bool IsAdvanced);

        void SetVisibleToUser(bool visible);
        void SetEnabledToUser(bool enabled);
        void SetAvailableNames(const QString& text);

        bool GetVisibleToUser();
        bool GetEnabledToUser();
        QString GetAvailableNames();

        QWidget* GetTemplateCurrentWidget(bool IsUser);
        QWidget* GetTemplateWidgetByType(bool IsUser, const QString& type);


    signals:
        void Up(int index);
        void Down(int index);
        void VariableNameChanged(QString name);
        void WillBeDeleted();

    private slots:
        void SetMinimum(int);
        void SetMinimum_2(int);
        void SetMaximum_2(int);
        void SetMaximum(int);
        void UpdateSelect();
        void DescriptionChanged(const QString& str);

        void on_ButtonMore_clicked();
        void ShowMore();
        void HideMore();

        void Visibility(bool visibility);

        void SetSectionName(const QString& SectionName);

        void GoingToDelete();

        void on_lineEdit_textChanged(const QString &arg1);

    private:
        Ui::DesignResourceWidget *ui;
        int FindMyIndex();
        void changeEvent(QEvent *e);
    };
}
#endif // DESIGNRESOURCEWIDGET_H

