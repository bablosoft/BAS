#include "databaseconnectiondialog.h"
#include <QCloseEvent>
#include "ui_databaseconnectiondialog.h"

DatabaseConnectionDialog::DatabaseConnectionDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseConnectionDialog)
{
    ui->setupUi(this);
    connect(ui->ShowLog,SIGNAL(clicked(bool)),this,SIGNAL(ShowLog()));
    connect(ui->RunAnyway,SIGNAL(clicked(bool)),this,SIGNAL(RunWithoutDatabase()));
    connect(ui->Close,SIGNAL(clicked(bool)),this,SIGNAL(Close()));
}

DatabaseConnectionDialog::~DatabaseConnectionDialog()
{
    delete ui;
}

void DatabaseConnectionDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
    emit Close();
}


void DatabaseConnectionDialog::SetLabel(const QString& Label)
{
    ui->Info->setText(Label);
}

