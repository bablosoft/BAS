#include "downloadingwidget.h"
#include "ui_downloadingwidget.h"

DownloadingWidget::DownloadingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadingWidget)
{
    ui->setupUi(this);
    ui->LabelError->setVisible(false);
}

DownloadingWidget::~DownloadingWidget()
{
    delete ui;
}


void DownloadingWidget::SetProgress(int Progress)
{
    ui->progressBar->setValue(Progress);
}

void DownloadingWidget::SetError(const QString& Error)
{
    ui->LabelError->setVisible(true);
    ui->progressBar->setVisible(false);
    ui->LabelError->setText(Error);
    ui->label->setVisible(false);
    ui->SkipButton->setText("Close");
    show();

}

void DownloadingWidget::on_SkipButton_clicked()
{
    emit Cancel();
}
