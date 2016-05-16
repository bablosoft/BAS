#include "checkforupdateswidget.h"
#include "ui_checkforupdateswidget.h"

CheckForUpdatesWidget::CheckForUpdatesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckForUpdatesWidget)
{
    ui->setupUi(this);
}

CheckForUpdatesWidget::~CheckForUpdatesWidget()
{
    delete ui;
}

void CheckForUpdatesWidget::on_SkipButton_clicked()
{
    emit Skip();
}
