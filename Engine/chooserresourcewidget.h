#ifndef CHOOSERRESOURCEWIDGET_H
#define CHOOSERRESOURCEWIDGET_H
#include "engine_global.h"

#include <QWidget>
#include "istringbuilder.h"
#include "qxtcheckcombobox.h"
#include "idatabasestate.h"

namespace Ui {
class ChooserResourceWidget;
}

using namespace BrowserAutomationStudioFramework;

class ENGINESHARED_EXPORT ChooserResourceWidget : public QWidget
{
    Q_OBJECT
    IStringBuilder *StringBuilder;
    bool ShowValidation;
    bool LastValidateResult;
    QList<QWidget *> Widgets;
    QxtCheckComboBox * MultiWidget;
    bool DatabaseIndexesChangedInAction;
    IDatabaseState * DatabaseState;
    int LastTableId;
    bool LastVisibleAdvanced;
signals:
    void ValidationStateChanged();
public:
    IStringBuilder * GetStringBuilder();
    void SetStringBuilder(IStringBuilder * val);
    void SetDatabaseState(IDatabaseState * DatabaseState);

    explicit ChooserResourceWidget(QWidget *parent = 0);
    ~ChooserResourceWidget();
    QWidget* GetTemplateWidgetByIndex(int index);
    void RemoveWidgetAtIndex(int index);
    void SetShowValidation(bool ShowValidation);
    bool IsValid();
    int GetTableId();
public slots:
    void setCurrentIndex(int index);
    void SetVisibleAdvanced(bool Visible);
    void SetTableId(int TableId);

private:

    Ui::ChooserResourceWidget *ui;
    void changeEvent(QEvent *e);
private slots:
    void Validate();

    void on_ButtonFileSelect_clicked();
    void on_ButtonDirectorySelect_clicked();

    void on_RandomStringEdit_clicked();
    void SetRandomStringEdit(const QString& val);
    void on_DirectoryReload_toggled(bool checked);
    void on_FileReload_toggled(bool checked);
    void on_UrlReload_toggled(bool checked);
    void on_FileRenew_toggled(bool checked);
    void on_UrlRenew_toggled(bool checked);
    void on_DirectoryRenew_toggled(bool checked);
    void on_DatabaseReload_toggled(bool checked);
    void on_DatabaseRenew_toggled(bool checked);
    void DatabaseIndexesChanged(QList<int> Previous,QList<int> Now);
    void GroupsChanged();
};

#endif // CHOOSERRESOURCEWIDGET_H
