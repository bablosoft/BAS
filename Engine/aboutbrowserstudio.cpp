#include "aboutbrowserstudio.h"
#include "ui_aboutbrowserstudio.h"

#include "every_cpp.h"


AboutBrowserStudio::AboutBrowserStudio(const QString& Version,const QString& ServerName,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutBrowserStudio)
{
    ui->setupUi(this);
    ui->LabelWebkit->setText(QString("<b>") + "51.0.2704.103" + QString("</b>"));
    ui->LabelVersion->setText(QString("<b>") + Version + QString("</b>"));
    ui->LabelDescription->setText(QString(tr("<html><head/><body><p><span style=\" font-size:10pt;\">Browser Automation Studio - a comprehensive solution for creating complex network software. </span>Visit <a href=\"%1\"><span style=\" text-decoration: underline; color:#0000ff;\">%1</span></a> to see more details</p></body></html>")).arg(ServerName));
    this->setFixedSize(327,270);

}

void AboutBrowserStudio::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

AboutBrowserStudio::~AboutBrowserStudio()
{
    delete ui;
}
