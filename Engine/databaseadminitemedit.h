#ifndef DATABASEADMINITEMEDIT_H
#define DATABASEADMINITEMEDIT_H

#include <QDialog>
#include "DatabaseConnectorHelperClass.h"


namespace Ui {
class DatabaseAdminItemEdit;
}
using namespace BrowserAutomationStudioFramework;
class DatabaseAdminItemEdit : public QDialog
{
    Q_OBJECT
    QHash<int,QWidget *> Widgets;
    QList<DatabaseColumn> Columns;

public:
    explicit DatabaseAdminItemEdit(QWidget *parent = 0);
    ~DatabaseAdminItemEdit();
    void SetColumns(QList<DatabaseColumn> Columns);
    void SetGroupList(QStringList Groups);
    void SetSelectedGroup(int index);
    int GetSelectedIndex();
    void HideGroupBox();
    DatabaseItem GetDatabaseItem();
    void SetDatabaseItem(DatabaseItem Item);
private:
    Ui::DatabaseAdminItemEdit *ui;
};

#endif // DATABASEADMINITEMEDIT_H
