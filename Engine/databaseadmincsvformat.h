#ifndef DATABASEADMINCSVFORMAT_H
#define DATABASEADMINCSVFORMAT_H

#include <QDialog>
#include <QCloseEvent>
#include "DatabaseConnectorHelperClass.h"
using namespace BrowserAutomationStudioFramework;

namespace Ui {
class DatabaseAdminCsvFormat;
}

class DatabaseAdminCsvFormat : public QDialog
{
    Q_OBJECT
    QList<DatabaseColumn> Columns;
    bool IsExport;
    bool IsCsv;
    QString GetExtension();
public:
    explicit DatabaseAdminCsvFormat(QWidget *parent = 0);
    void SetXls();
    ~DatabaseAdminCsvFormat();
    void SetDatabaseColumns(QList<DatabaseColumn> Columns);
    QList<int> GetColumnIds();
    void SetIsExport(bool IsExport);
    QString GetFileName();
private:
    Ui::DatabaseAdminCsvFormat *ui;
private slots:
    void ChangedDragSection();
    void on_OpenFileButton_clicked();
    void on_Ok_clicked();
    void on_Cancel_clicked();
};

#endif // DATABASEADMINCSVFORMAT_H
