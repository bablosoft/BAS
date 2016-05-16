#ifndef DATABASEADMINFILTERCREATE_H
#define DATABASEADMINFILTERCREATE_H

#include <QDialog>
#include "DatabaseConnectorHelperClass.h"
namespace Ui {
class DatabaseAdminFilterCreate;
}
using namespace BrowserAutomationStudioFramework;

class DatabaseAdminFilterCreate : public QDialog
{
    Q_OBJECT
    QList<DatabaseColumn> Columns;
    QWidget *Widget;
public:
    explicit DatabaseAdminFilterCreate(QWidget *parent = 0);
    ~DatabaseAdminFilterCreate();
    void SetColumns(QList<DatabaseColumn> Columns);
    DatabaseFilter GetFilter();
    QString GetFilterText();
private slots:
    void on_ComboColumn_currentIndexChanged(int index);

    void on_ComboType_currentIndexChanged(int index);

private:
    Ui::DatabaseAdminFilterCreate *ui;
};

#endif // DATABASEADMINFILTERCREATE_H
