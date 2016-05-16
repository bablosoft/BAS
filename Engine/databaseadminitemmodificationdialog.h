#ifndef DATABASEADMINITEMMODIFICATIONDIALOG_H
#define DATABASEADMINITEMMODIFICATIONDIALOG_H

#include <QDialog>

namespace Ui {
class DatabaseAdminItemModificationDialog;
}

class DatabaseAdminItemModificationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseAdminItemModificationDialog(QWidget *parent = 0);
    ~DatabaseAdminItemModificationDialog();
    void SetNumberRows(int RowsNumber);
    void SetQuestion(const QString& Question);
private:
    Ui::DatabaseAdminItemModificationDialog *ui;
};

#endif // DATABASEADMINITEMMODIFICATIONDIALOG_H
