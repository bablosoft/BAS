#include "databaseadmindeletegroup.h"
#include "ui_databaseadmindeletegroup.h"

DatabaseAdminDeleteGroup::DatabaseAdminDeleteGroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseAdminDeleteGroup)
{
    ui->setupUi(this);
}

void DatabaseAdminDeleteGroup::UpdateChecked()
{
    if(ui->radioButton_2->isVisibleTo(this))
    {
        ui->radioButton_2->setChecked(true);
    }else if(ui->radioButton->isVisibleTo(this))
    {
        ui->radioButton->setChecked(true);
    }else if(ui->radioButton_3->isVisibleTo(this))
    {
        ui->radioButton_3->setChecked(true);
    }
}

void DatabaseAdminDeleteGroup::Disable(int TaskType)
{
    switch(TaskType)
    {
        case 1: ui->radioButton->setVisible(false); UpdateChecked(); break;
        case 2: ui->radioButton_2->setVisible(false); UpdateChecked(); break;
        case 3: ui->radioButton_3->setVisible(false); UpdateChecked(); break;
    }
}

int DatabaseAdminDeleteGroup::GetTaskType()
{
    if(ui->radioButton->isChecked())
        return 1;
    if(ui->radioButton_2->isChecked())
        return 2;
    if(ui->radioButton_3->isChecked())
        return 3;
}

void DatabaseAdminDeleteGroup::SetGroupList(const QString& Groups)
{
    ui->GroupsList->setText(Groups);
}

DatabaseAdminDeleteGroup::~DatabaseAdminDeleteGroup()
{
    delete ui;
}
