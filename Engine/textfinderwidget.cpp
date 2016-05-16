#include "textfinderwidget.h"
#include "ui_textfinderwidget.h"
#include "every_cpp.h"

TextFinderWidget::TextFinderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextFinderWidget)
{
    ui->setupUi(this);
}

TextFinderWidget::~TextFinderWidget()
{
    delete ui;
}

void TextFinderWidget::Show()
{
    ui->lineEdit->setFocus();
    show();
}

void TextFinderWidget::on_pushButton_3_clicked()
{
    this->hide();
}

void TextFinderWidget::on_lineEdit_textChanged(const QString &arg1)
{
    emit TermChanged(arg1);
}

void TextFinderWidget::on_pushButton_clicked()
{
    emit FindNext(true);
}

void TextFinderWidget::on_pushButton_2_clicked()
{
    emit FindNext(false);
}
