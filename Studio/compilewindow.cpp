#include "compilewindow.h"
#include "ui_compilewindow.h"
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

    ui->radioButton_2->setVisible(false);
    ui->radioButton_3->setVisible(false);
    connect(this,SIGNAL(accepted()),this,SLOT(Accepted()));

}

void CompileWindow::Accepted()
{
    compiler->SetName(ui->lineEdit->text());
    compiler->SetVersion(QString::number(ui->spinBox->value()) + "." + QString::number(ui->spinBox_2->value()) + "."+ QString::number(ui->spinBox_3->value()));
    if(ui->radioButton->isChecked())
    {
        compiler->SetOs("Windows");
    }else if(ui->radioButton_2->isChecked())
    {
        compiler->SetOs("Linux");
    }else if(ui->radioButton_3->isChecked())
    {
        compiler->SetOs("Mac");
    }
}

CompileWindow::~CompileWindow()
{
    delete ui;
}
