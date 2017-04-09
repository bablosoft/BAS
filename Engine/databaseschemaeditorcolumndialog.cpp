#include "databaseschemaeditorcolumndialog.h"
#include "ui_databaseschemaeditorcolumndialog.h"

DatabaseSchemaEditorColumnDialog::DatabaseSchemaEditorColumnDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseSchemaEditorColumnDialog)
{
    ui->setupUi(this);
}

DatabaseSchemaEditorColumnDialog::~DatabaseSchemaEditorColumnDialog()
{
    delete ui;
}

bool DatabaseSchemaEditorColumnDialog::GetIsSuccess()
{
    return IsSuccess;
}


void DatabaseSchemaEditorColumnDialog::on_pushButtonOk_clicked()
{
    IsSuccess = true;
    close();
}

void DatabaseSchemaEditorColumnDialog::on_pushButtonCancel_clicked()
{
    close();
}


QString DatabaseSchemaEditorColumnDialog::GetName()
{
    return ui->ColumnName->text();
}
QString DatabaseSchemaEditorColumnDialog::GetDescriptionEn()
{
    return ui->ColumnDescriptionEn->text();
}
QString DatabaseSchemaEditorColumnDialog::GetDescriptionRu()
{
    return ui->ColumnDescriptionRu->text();
}
QString DatabaseSchemaEditorColumnDialog::GetType()
{
    return ui->ColumnType->currentText();
}

void DatabaseSchemaEditorColumnDialog::SetName(const QString& Name)
{
    ui->ColumnName->setText(Name);
}
void DatabaseSchemaEditorColumnDialog::SetDescriptionEn(const QString& DescriptionEn)
{
    ui->ColumnDescriptionEn->setText(DescriptionEn);
}
void DatabaseSchemaEditorColumnDialog::SetDescriptionRu(const QString& DescriptionRu)
{
    ui->ColumnDescriptionRu->setText(DescriptionRu);
}
void DatabaseSchemaEditorColumnDialog::SetType(const QString& Type)
{
    ui->ColumnType->setCurrentText(Type);
}
