#include "databasestatedialog.h"
#include "ui_databasestatedialog.h"
#include "databaseschemaeditor.h"
#include <QMessageBox>
#include <QClipboard>
#include <QDir>


DatabaseStateDialog::DatabaseStateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseStateDialog)
{
    ui->setupUi(this);
    ui->DatabaseIdNotValid->setVisible(false);
    ui->DatabaseLocation->setEnabled(false);
    ui->RestartProcess->setVisible(false);
    ui->groupBox_2->setVisible(false);
}
void DatabaseStateDialog::SetDatabaseBaseLocation(const QString& DatabaseBaseLocation)
{
    this->DatabaseBaseLocation = DatabaseBaseLocation;
    UpdateDatabaseLocation();
}

void DatabaseStateDialog::UpdateDatabaseLocation()
{
    ui->DatabaseLocation->setText(QDir::cleanPath(DatabaseBaseLocation + "/" + ui->DatabaseId->text()));
}

DatabaseStateDialog::~DatabaseStateDialog()
{
    delete ui;
}

void DatabaseStateDialog::SetIsDirty(bool IsDirty)
{
    this->IsDirty = IsDirty;
    if(IsDirty)
    {
        ui->RelevanceRelevant->setText("");
        ui->RelevanceRelevant->setPixmap(QPixmap(":/images/redball.png"));
        ui->RelevanceRelevantLabel->setText(tr("Changes will take effect only after restart"));
        //ui->groupBox_2->setVisible(true);
        ui->RestartProcess->setText(tr("Restart process"));
        ui->RestartProcess->setIcon(QIcon(":/engine/images/reload.png"));
        //ui->RestartProcess->setVisible(true);
        ui->SaveButton->setVisible(true);
    }else
    {
        //ui->groupBox_2->setVisible(false);
        ui->RelevanceRelevant->setText("");
        ui->RelevanceRelevant->setPixmap(QPixmap(":/images/greenball.png"));
        ui->RelevanceRelevantLabel->setText(tr("No need to restart"));
        ui->RestartProcess->setText(tr("Restart process"));
        ui->RestartProcess->setIcon(QIcon(":/engine/images/reload.png"));
        //ui->RestartProcess->setVisible(false);
        ui->SaveButton->setVisible(false);
    }
}

void DatabaseStateDialog::SetDatabaseId(const QString& DatabaseId)
{
    ui->DatabaseId->setText(DatabaseId);
    UpdateDatabaseLocation();
}

QString DatabaseStateDialog::GetDatabaseId()
{
    return ui->DatabaseId->text();
}

bool DatabaseStateDialog::GetIsDirty()
{
    return IsDirty;
}
void DatabaseStateDialog::SetSchema(const QString& Schema)
{
    this->Schema = Schema;
}

QString DatabaseStateDialog::GetSchema()
{
    return Schema;
}

void DatabaseStateDialog::SetHasDabase(bool HasDatabase)
{
    this->HasDatabase = HasDatabase;
    if(HasDatabase)
    {
        ui->WorkNotWorButton->setText("");
        ui->WorkNotWorButton->setPixmap(QPixmap(":/images/greenball.png"));
        ui->WorkNotWorkLabel->setText(tr("Database works"));
        ui->EditDatabaseSchema->setText(tr("Edit database schema"));
        ui->DeleteDatabase->setText(tr("Delete database"));
        ui->DeleteDatabase->setIcon(QIcon(":/engine/images/delete_all.png"));
        ui->DeleteDatabase->setVisible(true);
        ui->groupBox_3->setVisible(true);

    }else
    {
        ui->WorkNotWorButton->setText("");
        ui->WorkNotWorButton->setPixmap(QPixmap(":/images/redball.png"));
        ui->WorkNotWorkLabel->setText(tr("Database does not work"));
        ui->EditDatabaseSchema->setText(tr("Create database"));
        ui->DeleteDatabase->setText(tr("Delete database"));
        ui->DeleteDatabase->setIcon(QIcon(":/engine/images/delete_all.png"));
        ui->DeleteDatabase->setVisible(false);
        ui->groupBox_3->setVisible(false);

    }

}

void DatabaseStateDialog::on_CancelButton_clicked()
{
    close();
}

void DatabaseStateDialog::on_SaveButton_clicked()
{
    if(!IsValid)
        return;

    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.addButton(tr("Restart"),QMessageBox::ResetRole);

    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowIcon(QIcon(":/engine/images/Logo.png"));
    msgBox.setText(tr("Changes will take effect only after restart."));

    int res = msgBox.exec();
    if(res == QMessageBox::Ok)
    {
        IsSuccess = true;
        close();
    }else if(res == QMessageBox::Cancel)
    {

    }else
    {
        NeedRestart = true;
        IsSuccess = true;
        close();
    }
}

bool DatabaseStateDialog::GetIsSuccess()
{
    return IsSuccess;
}

void DatabaseStateDialog::on_EditDatabaseSchema_clicked()
{
    BrowserAutomationStudioFramework::DatabaseSchemaEditor editor;

    QString SchemaNew = editor.GetXml(Schema);
    if(SchemaNew != Schema)
    {
        SetIsDirty(true);
    }

    Schema = SchemaNew;

}

void DatabaseStateDialog::on_DeleteDatabase_clicked()
{
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowIcon(QIcon(":/engine/images/Logo.png"));
    msgBox.setText(tr("Are you sure, that you want to delete database?"));
    if(msgBox.exec() != QMessageBox::Ok)
    {
        return;
    }
    Schema.clear();
    SetIsDirty(true);
}

bool DatabaseStateDialog::GetNeedRestart()
{
    return NeedRestart;
}

void DatabaseStateDialog::on_RestartProcess_clicked()
{
    if(!IsValid)
        return;
    NeedRestart = true;
    IsSuccess = true;
    close();
}

void DatabaseStateDialog::on_DataManager_clicked()
{
    emit EditDatabase();
}

void DatabaseStateDialog::on_DatabaseId_textEdited(const QString &arg1)
{
    SetIsDirty(true);
    CheckValid();
    UpdateDatabaseLocation();
}

void DatabaseStateDialog::CheckValid()
{
    IsValid = !ui->DatabaseId->text().isEmpty();
    ui->DatabaseIdNotValid->setVisible(!IsValid);
}

void DatabaseStateDialog::on_CopyDatabaseLocation_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->DatabaseLocation->text());
}
