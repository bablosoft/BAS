#ifndef DATABASEADMINFILTERWIDGET_H
#define DATABASEADMINFILTERWIDGET_H
#include "DatabaseConnectorHelperClass.h"
#include "flowlayout.h"
#include "databaseadminfilteritem.h"
#include <QList>
#include <QWidget>
#include "DatabaseConnectorHelperClass.h"

namespace Ui {
class DatabaseAdminFilterWidget;
}

using namespace BrowserAutomationStudioFramework;

class DatabaseAdminFilterWidget : public QWidget
{
    Q_OBJECT
    QLayout *Layout;
    QHash<DatabaseAdminFilterItem*,DatabaseFilter> Items;
    QList<DatabaseColumn> Columns;
public:
    explicit DatabaseAdminFilterWidget(QWidget *parent = 0);
    ~DatabaseAdminFilterWidget();
    DatabaseFilters GetFilters();
    void SetColumns(QList<DatabaseColumn> Columns);
public slots:
    void Clear();
signals:
    void FiltersChanged();
private slots:
    void on_AddFilter_clicked();
    void DeleteFilter();
    void on_DeleteAllFilters_clicked();

private:
    Ui::DatabaseAdminFilterWidget *ui;
};

#endif // DATABASEADMINFILTERWIDGET_H
