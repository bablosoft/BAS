#include "databaseadminmovetogroup.h"
#include "ui_databaseadminmovetogroup.h"

DatabaseAdminMoveToGroup::DatabaseAdminMoveToGroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseAdminMoveToGroup)
{
    ui->setupUi(this);
}

void DatabaseAdminMoveToGroup::SetNumberRows(int RowsNumber)
{
    ui->RowsNumber->setText(QString::number(RowsNumber));
}
void DatabaseAdminMoveToGroup::SetGroups(QStringList Groups)
{
    ui->comboBox->addItems(Groups);
}

int DatabaseAdminMoveToGroup::GetSelectedGroupIndex()
{
    return ui->comboBox->currentIndex();
}

DatabaseAdminMoveToGroup::~DatabaseAdminMoveToGroup()
{
    delete ui;
}
