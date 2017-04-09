#ifndef DATABASESCHEMAEDITORCOLUMNDIALOG_H
#define DATABASESCHEMAEDITORCOLUMNDIALOG_H

#include <QDialog>

namespace Ui {
class DatabaseSchemaEditorColumnDialog;
}

class DatabaseSchemaEditorColumnDialog : public QDialog
{
    Q_OBJECT
    bool IsSuccess = false;
public:
    explicit DatabaseSchemaEditorColumnDialog(QWidget *parent = 0);
    ~DatabaseSchemaEditorColumnDialog();
    bool GetIsSuccess();
    QString GetName();
    QString GetDescriptionEn();
    QString GetDescriptionRu();
    QString GetType();

    void SetName(const QString& Name);
    void SetDescriptionEn(const QString& DescriptionEn);
    void SetDescriptionRu(const QString& DescriptionRu);
    void SetType(const QString& Type);
private slots:
    void on_pushButtonOk_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::DatabaseSchemaEditorColumnDialog *ui;
};

#endif // DATABASESCHEMAEDITORCOLUMNDIALOG_H
