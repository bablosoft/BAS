#include "tabinputdialog.h"
#include "ui_tabinputdialog.h"

TabInputDialog::TabInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TabInputDialog)
{
    ui->setupUi(this);
}

TabInputDialog::~TabInputDialog()
{
    delete ui;
}

QString TabInputDialog::GetTabNameEn()
{
    return ui->TabNameEn->text();
}
QString TabInputDialog::GetTabNameRu()
{
    return ui->TabNameRu->text();
}
void TabInputDialog::SetTabNameEn(const QString& TabNameEn)
{
    ui->TabNameEn->setText(TabNameEn);
}
void TabInputDialog::SetTabNameRu(const QString& TabNameRu)
{
    ui->TabNameRu->setText(TabNameRu);
}
