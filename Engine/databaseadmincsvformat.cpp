#include "databaseadmincsvformat.h"
#include "ui_databaseadmincsvformat.h"
#include <QDir>
#include <QFileDialog>
#include <QDebug>


DatabaseAdminCsvFormat::DatabaseAdminCsvFormat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseAdminCsvFormat)
{
    ui->setupUi(this);
    connect(ui->DragSectionCombo,SIGNAL(ChangedDragSection()),this,SLOT(ChangedDragSection()));
    IsExport = true;
    ui->LabelValidation->setVisible(false);
    IsCsv = true;
}


QString DatabaseAdminCsvFormat::GetExtension()
{
    return (IsCsv)?".csv":".xls";
}

void DatabaseAdminCsvFormat::SetXls()
{
    IsCsv = false;
    setWindowTitle("Xls");
}

QString DatabaseAdminCsvFormat::GetFileName()
{
    return ui->FileName->text();
}

void DatabaseAdminCsvFormat::SetIsExport(bool IsExport)
{
    this->IsExport = IsExport;
    if(IsExport)
    {
        QString randomString;
        {
           QString possibleCharacters("abcdefghijklmnopqrstuvwxyz");
           int randomStringLength = 10;

           for(int i=0; i<randomStringLength; ++i)
           {
               int index = qrand() % possibleCharacters.length();
               QChar nextChar = possibleCharacters.at(index);
               randomString.append(nextChar);
           }
        }



        ui->FileName->setText(QDir::cleanPath(QDir::currentPath() + QDir::separator() + randomString + GetExtension()));
    }
}




void DatabaseAdminCsvFormat::ChangedDragSection()
{
    QStringList res;

    foreach(int i, ui->DragSectionCombo->SelectedItems())
    {
        res.append(Columns[i].Name);
    }
    ui->FormatResult->setText(res.join(":"));
}

void DatabaseAdminCsvFormat::SetDatabaseColumns(QList<DatabaseColumn> Columns)
{
    this->Columns = Columns;
    QStringList List;
    QList<int> Items;

    int index = 0;
    foreach(DatabaseColumn Column, Columns)
    {
        List.append(Column.Description);
        Items.append(index);
        index++;
    }

    ui->DragSectionCombo->SetData(List,Items);
    ChangedDragSection();
}

QList<int> DatabaseAdminCsvFormat::GetColumnIds()
{
    QList<int> res;
    foreach(int i, ui->DragSectionCombo->SelectedItems())
    {
        res.append(Columns[i].Id);
    }
    return res;
}

DatabaseAdminCsvFormat::~DatabaseAdminCsvFormat()
{
    delete ui;
}

void DatabaseAdminCsvFormat::on_OpenFileButton_clicked()
{
    QString fileName;
    if(IsExport)
        fileName = QFileDialog::getSaveFileName(this, tr("Save"), "", tr("Csv Files (*.csv);;All Files (*.*)"));
    else
        fileName = QFileDialog::getOpenFileName(this, tr("Save"), "", tr("All Files (*.*);;Csv Files (*.csv)"));
    if(fileName.length()>0)
    {
        ui->FileName->setText(fileName);
    }
}

void DatabaseAdminCsvFormat::on_Ok_clicked()
{
    if (IsExport || QFile::exists(GetFileName()))
    {
        accept();
    } else
    {
        ui->LabelValidation->setVisible(true);
    }
}

void DatabaseAdminCsvFormat::on_Cancel_clicked()
{
    reject();
}

