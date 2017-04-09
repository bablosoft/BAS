#ifndef DATABASECONNECTIONDIALOG_H
#define DATABASECONNECTIONDIALOG_H

#include <QWidget>

namespace Ui {
class DatabaseConnectionDialog;
}

class DatabaseConnectionDialog : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseConnectionDialog(QWidget *parent = 0);
    ~DatabaseConnectionDialog();
    void SetLabel(const QString& Label);
    void closeEvent(QCloseEvent *event);


private:
    Ui::DatabaseConnectionDialog *ui;
signals:
    void ShowLog();
    void RunWithoutDatabase();
    void Close();
};

#endif // DATABASECONNECTIONDIALOG_H
