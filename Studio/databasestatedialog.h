#ifndef DATABASESTATEDIALOG_H
#define DATABASESTATEDIALOG_H

#include <QDialog>

namespace Ui {
class DatabaseStateDialog;
}

class DatabaseStateDialog : public QDialog
{
    Q_OBJECT
    bool HasDatabase = false;
    bool IsSuccess = false;
    bool IsDirty = false;
    bool NeedRestart = false;
    bool IsValid = true;
    QString Schema;
    QString DatabaseBaseLocation;
public:
    explicit DatabaseStateDialog(QWidget *parent = 0);
    ~DatabaseStateDialog();
    void SetHasDabase(bool HasDatabase);
    void SetIsDirty(bool IsDirty);
    bool GetIsDirty();
    bool GetNeedRestart();
    void SetSchema(const QString& Schema);
    QString GetSchema();
    void SetDatabaseId(const QString& DatabaseId);
    QString GetDatabaseId();
    bool GetIsSuccess();
    void SetDatabaseBaseLocation(const QString& DatabaseBaseLocation);


private slots:
    void on_CancelButton_clicked();

    void on_SaveButton_clicked();

    void on_EditDatabaseSchema_clicked();

    void on_DeleteDatabase_clicked();

    void on_RestartProcess_clicked();

    void on_DataManager_clicked();

    void on_DatabaseId_textEdited(const QString &arg1);
    void CheckValid();
    void UpdateDatabaseLocation();

    void on_CopyDatabaseLocation_clicked();

private:
    Ui::DatabaseStateDialog *ui;
signals:
    void EditDatabase();
};

#endif // DATABASESTATEDIALOG_H
