#include "downloadingwidget.h"
#include "ui_downloadingwidget.h"

DownloadingWidget::DownloadingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadingWidget)
{
    ui->setupUi(this);
}

DownloadingWidget::~DownloadingWidget()
{
    delete ui;
}

void DownloadingWidget::on_SkipButton_clicked()
{
    emit Skip();
}

void DownloadingWidget::SetProgress(int Progress)
{
    ui->progressBar->setValue(Progress);
}

void DownloadingWidget::HideSkip()
{
    ui->SkipButton->setVisible(false);
}
