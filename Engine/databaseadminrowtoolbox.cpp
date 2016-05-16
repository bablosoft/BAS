#include "databaseadminrowtoolbox.h"
#include "ui_databaseadminrowtoolbox.h"
#include <QDebug>
DatabaseAdminRowToolbox::DatabaseAdminRowToolbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseAdminRowToolbox)
{
    ui->setupUi(this);
}

void DatabaseAdminRowToolbox::SetId(QString Id)
{
    this->Id = Id;
}


DatabaseAdminRowToolbox::~DatabaseAdminRowToolbox()
{
    delete ui;
}



void DatabaseAdminRowToolbox::on_EditButton_clicked()
{
    emit Edit(Id);
}

void DatabaseAdminRowToolbox::on_DeleteButton_clicked()
{
    emit Delete(Id);
}
