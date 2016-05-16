#include "loglocationchooser.h"
#include "ui_loglocationchooser.h"
#include <QFileDialog>
#include "every_cpp.h"

LogLocationChooser::LogLocationChooser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogLocationChooser)
{
    ui->setupUi(this);
}

void LogLocationChooser::SetLogLocation(const QString& Location)
{
    this->ui->lineEdit->setText(Location);
}

QString LogLocationChooser::GetLogLocation()
{
    return this->ui->lineEdit->text();
}

LogLocationChooser::~LogLocationChooser()
{
    delete ui;
}

void LogLocationChooser::on_pushButton_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"",0);
    if(directory.length()>0)
    {
        ui->lineEdit->setText(directory);
    }
}

void LogLocationChooser::on_buttonBox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::RestoreDefaults) == qobject_cast<QPushButton *>(button))
        this->ui->lineEdit->setText("../../logs");
}
