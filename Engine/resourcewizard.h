#ifndef RESOURCEWIZARD_H
#define RESOURCEWIZARD_H

#include <QWizard>
#include "iresourcewidget.h"
#include "istringbuilder.h"

using namespace BrowserAutomationStudioFramework;

namespace Ui {
class ResourceWizard;
}

class ResourceWizard : public QWizard
{
    Q_OBJECT
    QString NamePrev;
    IResourceWidget *ResourceWidget;
    QString Type;
    int CurrentPageId;

    IStringBuilder * StringBuilder;
    QStringList Groups;
    QHash<QString,QString> VariablesAndValues;
    bool IsAdditionalTab;
    bool IsAdditionalIf;
    bool eventFilter(QObject *target, QEvent *event);
    bool TooltipUserFocus;
    bool ShowTooltip;
    bool TooltipUserFocus2;
    bool ShowTooltip2;
    bool TooltipUserFocus3;
    bool ShowTooltip3;
    bool TooltipUserFocus4;
    bool ShowTooltip4;

public:
    explicit ResourceWizard(QWidget *parent = 0);
    ~ResourceWizard();
    void SetResourceWidget(IResourceWidget *ResourceWidget);

    void SetStringBuilder(IStringBuilder * StringBuilder);
    void SetGroups(const QStringList& Groups);
    void SetSelectsVariablesAndValues(const QHash<QString,QString>& VariablesAndValues);


private slots:
    void PageChanged(int PageId);
    void on_Name_textEdited(const QString &arg1);

    void on_FixedString_toggled(bool checked);

    void on_FixedInteger_toggled(bool checked);

    void on_RandomString_toggled(bool checked);

    void on_RandomInteger_toggled(bool checked);

    void on_Select_toggled(bool checked);

    void on_LinesFromFile_toggled(bool checked);

    void on_LinesFromUrl_toggled(bool checked);

    void on_FilesFromDirectory_toggled(bool checked);

    void on_Database_toggled(bool checked);
    void HideAllTypesLabels();

    void SetRandomStringEdit(const QString& text);
    void SetSectionName(const QString& SectionName);


    void UpdateSelect();


    void on_StartStringBuilder_clicked();

    void on_SelectType_currentIndexChanged(int index);

    void on_SelectLines_textChanged();

    void on_Finish_clicked();

    void askReject();


    void on_ToTab_clicked();

    void on_VisibleIf_clicked();

private:
    Ui::ResourceWizard *ui;
};

#endif // RESOURCEWIZARD_H
