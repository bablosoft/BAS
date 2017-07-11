#include "compilewindow.h"
#include "ui_compilewindow.h"
#include <QTimer>
#include "every_cpp.h"

CompileWindow::CompileWindow(Compiler *compiler,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompileWindow)
{
    ui->setupUi(this);
    this->compiler = compiler;
    if(!compiler->GetName().isEmpty())
        ui->lineEdit->setText(compiler->GetName());
    if(!compiler->GetVersion().isEmpty())
    {
        QStringList list = compiler->GetVersion().split(".");
        if(list.length() == 3)
        {
            ui->spinBox->setValue(list.at(0).toInt());
            ui->spinBox_2->setValue(list.at(1).toInt());
            ui->spinBox_3->setValue(list.at(2).toInt());
        }
    }

    connect(this,SIGNAL(accepted()),this,SLOT(Accepted()));
    GuiUpdate();
}

void CompileWindow::GuiUpdate()
{
    bool Visible = ui->PrivateScriptEnterPassForUser->isChecked();
    ui->UserName->setVisible(Visible);
    ui->Password->setVisible(Visible);
    ui->label_7->setVisible(Visible);
    ui->label_8->setVisible(Visible);
    if(ui->NoProtection->isChecked())
    {
        ui->HideBrowsers->setEnabled(false);
        ui->HideBrowsers->setChecked(false);
        ui->HideBrowsers->setStyleSheet("*{color:gray}");
    }else
    {
        ui->HideBrowsers->setEnabled(true);
        ui->HideBrowsers->setStyleSheet("*{color:white}");
    }
    QTimer::singleShot(0,this,SLOT(Resize()));

}

void CompileWindow::Resize()
{
    resize(width(),1);
}

void CompileWindow::Accepted()
{
    compiler->SetUsername(ui->UserName->text());
    compiler->SetPassword(ui->Password->text());
    if(ui->NoProtection->isChecked())
    {
        compiler->SetType(Compiler::NoProtection);
    }else if(ui->PrivateScriptEnterPassForUser->isChecked())
    {
        compiler->SetType(Compiler::PrivateScriptEnterPassForUser);
    }else if(ui->PrivateScriptUserEnterPass->isChecked())
    {
        compiler->SetType(Compiler::PrivateScriptUserEnterPass);
    }
    compiler->SetName(ui->lineEdit->text());
    compiler->SetHideBrowsers(ui->HideBrowsers->isChecked());
    compiler->SetVersion(QString::number(ui->spinBox->value()) + "." + QString::number(ui->spinBox_2->value()) + "."+ QString::number(ui->spinBox_3->value()));
    compiler->SetOs("Windows");
}

CompileWindow::~CompileWindow()
{
    delete ui;
}

void CompileWindow::on_NoProtection_clicked()
{
    GuiUpdate();
}

void CompileWindow::on_PrivateScriptUserEnterPass_clicked()
{
    GuiUpdate();
}

void CompileWindow::on_PrivateScriptEnterPassForUser_clicked()
{
    GuiUpdate();
}
