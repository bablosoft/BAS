#include "databaseadminitemmodificationdialog.h"
#include "ui_databaseadminitemmodificationdialog.h"

DatabaseAdminItemModificationDialog::DatabaseAdminItemModificationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseAdminItemModificationDialog)
{
    ui->setupUi(this);
}

void DatabaseAdminItemModificationDialog::SetNumberRows(int RowsNumber)
{
    ui->RowsNumber->setText(QString::number(RowsNumber));
}
void DatabaseAdminItemModificationDialog::SetQuestion(const QString& Question)
{
    ui->LabelAsk->setText(Question);
}

DatabaseAdminItemModificationDialog::~DatabaseAdminItemModificationDialog()
{
    delete ui;
}
