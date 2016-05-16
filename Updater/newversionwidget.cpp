#include "newversionwidget.h"
#include "ui_newversionwidget.h"

NewVersionWidget::NewVersionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewVersionWidget)
{
    ui->setupUi(this);
}

NewVersionWidget::~NewVersionWidget()
{
    delete ui;
}

void NewVersionWidget::SetVersion(const QString& Version)
{
    ui->VersionLabel->setText(QString("Version %1").arg(Version));
}

void NewVersionWidget::SetChangelog(const QString& Changelog)
{
    QString text;

    if(!Changelog.isEmpty())
        text = QString("<ul><li style='margin-left:-20px'>") + Changelog.split("\r\n").join("</li><li style='margin-left:-20px;margin-top:10px'>") + QString("</li></ul>");
    ui->ChangeLog->setText(text);
}

void NewVersionWidget::on_SkipButton_clicked()
{
    emit Skip();
}

void NewVersionWidget::on_ApplyButton_clicked()
{
    emit Update();
}
