#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();
    view = new QWebEngineView(this);
    setCentralWidget(view);
    QSettings Settings("shop_settings.ini",QSettings::IniFormat,this);
    Server = Settings.value("Server","https://bablosoft.com/").toString();
    view->setUrl(QUrl(Server + "shopview"));
    ui->home->setParent(view);
    ui->home->raise();
    ui->home->setStyleSheet("QPushButton {   border: none; }");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_home_clicked()
{
    view->setUrl(QUrl(Server + "shopview"));
}
