#include "databaseadmineditgroup.h"
#include "ui_databaseadmineditgroup.h"

DatabaseAdminEditGroup::DatabaseAdminEditGroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseAdminEditGroup)
{
    ui->setupUi(this);
}

void DatabaseAdminEditGroup::SetName(const QString& Name)
{
    ui->lineEdit->setText(Name);
}
void DatabaseAdminEditGroup::SetDescription(const QString& Description)
{
    ui->plainTextEdit->setPlainText(Description);
}
QString DatabaseAdminEditGroup::GetName()
{
    return ui->lineEdit->text();
}
QString DatabaseAdminEditGroup::GetDescription()
{
    return ui->plainTextEdit->toPlainText();
}

DatabaseAdminEditGroup::~DatabaseAdminEditGroup()
{
    delete ui;
}
