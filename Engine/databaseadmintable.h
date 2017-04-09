#ifndef DATABASEADMINTABLE_H
#define DATABASEADMINTABLE_H

#include <QWidget>
#include <QSet>
#include "databasegroupwidget.h"

#include "idatabaseconnector.h"
namespace Ui {
class DatabaseAdminTable;
}
using namespace BrowserAutomationStudioFramework;
class DatabaseAdminTable : public QWidget
{
    Q_OBJECT
    void InitTable();
    IDatabaseConnector *DatabaseConnector;
    int TableId;
    int PageNumber;
    int TotalRows;
    int TotalPages;
    QList<DatabaseItem> CurrentItems;
    QList<DatabaseGroup> Groups;
    QList<DatabaseGroupWidget *>* AllGroups;
    DatabaseFilters Filters;
    bool IsInverseSelection;
    QSet<QString> SelectedRows;
    QList<QVariant> CurrentPageIds;
    DatabaseSelector GetDatabaseSelector();
    bool ReactRowSelectionChange;
    int GetSelectedNumber();
    void MoveSelected(bool MoveOrCopy);
    int SortId;
    enum {Asc,Desc}SortOrder;
public:
    explicit DatabaseAdminTable(QWidget *parent = 0);
    ~DatabaseAdminTable();

    void Reload();
    void ReloadPageNumber();
    void SetDatabaseConnector(IDatabaseConnector *DatabaseConnector);
    void SetTableId(int TableId);
    void SetGroups(QList<DatabaseGroup> Groups);
    void SetAllGroups(QList<DatabaseGroupWidget *>* AllGroups);
    DatabaseMassSelector PrepareSelector();
private:
    Ui::DatabaseAdminTable *ui;

signals:
    void Activate();
    void Deactivate();

private slots:
    void HeaderClicked(int index);
    void on_PageSize_currentIndexChanged(int index);
    void on_AddItem_clicked();
    void on_NextPageButton_clicked();
    void on_PreviousPageButton_clicked();
    void on_FirstPageButton_clicked();
    void on_LastPageButton_clicked();
    void on_DataTable_itemSelectionChanged();
    void on_SelectNone_clicked();
    void on_SelectAll_clicked();
    void on_DeletSelected_clicked();
    void on_MoveSelectedGroup_clicked();
    void on_CopySelectedGroup_clicked();
    void on_DeleteSelectedFromGroups_clicked();
    void on_ReloadButton_clicked();
    void on_PageNumberLabel_clicked();

    void SingleItemEdit(QString Index);
    void SingleItemDelete(QString Index);
    void FilterChanged();
    void on_MenuButton2_clicked();
};

#endif // DATABASEADMINTABLE_H
