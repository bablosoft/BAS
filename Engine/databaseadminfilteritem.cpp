#include "databaseadminfilteritem.h"
#include "ui_databaseadminfilteritem.h"

DatabaseAdminFilterItem::DatabaseAdminFilterItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseAdminFilterItem)
{
    ui->setupUi(this);
}

void DatabaseAdminFilterItem::SetText(const QString& Text)
{
    ui->LabelText->setText(Text);
}

DatabaseAdminFilterItem::~DatabaseAdminFilterItem()
{
    delete ui;
}

void DatabaseAdminFilterItem::on_pushButton_clicked()
{
    emit NeedDelete();
}
