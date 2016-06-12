#include "modulemanagerwindow.h"
#include "ui_modulemanagerwindow.h"
#include <QCheckBox>
#include <QLabel>
#include <QDir>
#include <QUrl>
#include <QDebug>
#include <QDesktopServices>
#include "every_cpp.h"

ModuleManagerWindow::ModuleManagerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModuleManagerWindow)
{
    ui->setupUi(this);
    ui->MainWidget->layout()->setAlignment(Qt::AlignTop);
}

void ModuleManagerWindow::Reload()
{
    for(QWidget * w:ui->MainWidget->findChildren<QWidget *>())
        w->deleteLater();

    int index = 0;
    for(IModuleManager::ModuleInfo Info:ModuleManager->GetModuleInfo())
    {
        QCheckBox *CheckBox = new QCheckBox(ui->MainWidget);
        CheckBox->setChecked(Info->IsEnabled);
        CheckBox->setProperty("name",Info->Name);
        connect(CheckBox,SIGNAL(stateChanged(int)),this,SLOT(CheckBoxClicked()));

        QLabel *Label = new QLabel(ui->MainWidget);
        Label->setText(QString("<html><head/><body><a href=\"bas://loadmodule\" style=\" text-decoration: none;\"> <table style=\"margin-bottom:10px\"><tr><td rowspan=\"2\"><img src=\":/engine/images/modules.png\"/></td><td><div>&nbsp;&nbsp;<span style=\" text-decoration: underline; color:white\">%1</span> <span style=\"color:white\"> - %3</span></div></td></tr><tr><td><div>&nbsp;&nbsp;<span style=\"color:gray;\">%2</span></div></td></tr></table></a></body></html>").arg(Info->Name).arg(Info->Description).arg(QString::number(Info->MajorVersion) + QString(".") + QString::number(Info->MinorVersion)));
        Label->setProperty("name",Info->Name);
        connect(Label,SIGNAL(linkActivated(QString)),this,SLOT(LabelClicked()));

        ui->gridLayout->addWidget(Label,index,0,Qt::AlignLeft);
        ui->gridLayout->addWidget(CheckBox,index,1,Qt::AlignRight);
        index++;
    }
}

void ModuleManagerWindow::CheckBoxClicked()
{
    QString ModuleName = sender()->property("name").toString();
    QCheckBox * CheckBox = qobject_cast<QCheckBox *>(sender());
    bool IsChecked = CheckBox->isChecked();
    ModuleManager->SetModuleEnabled(ModuleName,IsChecked);
}

void ModuleManagerWindow::LabelClicked()
{
    QString ModuleName = sender()->property("name").toString();
    QDir ModuleDir = QDir::current();
    ModuleDir.cd("modules");
    ModuleDir.cd(ModuleName);

    qDebug()<<ModuleDir.absolutePath();
    QDesktopServices::openUrl(QUrl::fromLocalFile(ModuleDir.absolutePath()));

}

void ModuleManagerWindow::SetModuleManager(IModuleManager *ModuleManager)
{
    this->ModuleManager = ModuleManager;
}

ModuleManagerWindow::~ModuleManagerWindow()
{
    delete ui;
}

void ModuleManagerWindow::on_Close_clicked()
{
    close();
}

void ModuleManagerWindow::on_Reload_clicked()
{
    Reload();
}

void ModuleManagerWindow::on_DeselectAll_clicked()
{
    for(QCheckBox * w:ui->MainWidget->findChildren<QCheckBox *>())
        w->setChecked(false);
}

void ModuleManagerWindow::on_SelectAll_clicked()
{
    for(QCheckBox * w:ui->MainWidget->findChildren<QCheckBox *>())
        w->setChecked(true);
}
