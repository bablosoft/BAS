#include "databasestatedialog.h"
#include "ui_databasestatedialog.h"
#include "databaseschemaeditor.h"
#include <QMessageBox>
#include <QClipboard>
#include <QDir>
#include <QCompleter>


DatabaseStateDialog::DatabaseStateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseStateDialog)
{
    ui->setupUi(this);
    ui->DatabaseIdNotValid->setVisible(false);
    ui->DatabaseLocation->setEnabled(false);
    ui->RestartProcess->setVisible(false);
    ui->groupBox_2->setVisible(false);
    on_ConnectionType_currentIndexChanged(-1);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->ConnectionLogin->setVisible(false);
    ui->ConnectionPassword->setVisible(false);

}

void DatabaseStateDialog::SetIsRemote(bool IsRemote)
{
    if(IsRemote)
    {
        ui->ConnectionType->setCurrentIndex(1);
    }else
    {
        ui->ConnectionType->setCurrentIndex(0);
    }

}
bool DatabaseStateDialog::GetIsRemote()
{
    return ui->ConnectionType->currentIndex() == 1;
}

void DatabaseStateDialog::SetConnectionServer(const QString& ConnectionServer)
{
    ui->ConnectionServer->setText(ConnectionServer);
}
QString DatabaseStateDialog::GetConnectionServer()
{
    return ui->ConnectionServer->text();
}

void DatabaseStateDialog::SetConnectionPort(const QString& ConnectionPort)
{
    ui->ConnectionPort->setText(ConnectionPort);
}
QString DatabaseStateDialog::GetConnectionPort()
{
    return ui->ConnectionPort->text();
}

void DatabaseStateDialog::SetConnectionLogin(const QString& ConnectionLogin)
{
    ui->ConnectionLogin->setText(ConnectionLogin);
}
QString DatabaseStateDialog::GetConnectionLogin()
{
    return ui->ConnectionLogin->text();
}

void DatabaseStateDialog::SetConnectionPassword(const QString& ConnectionPassword)
{
    ui->ConnectionPassword->setText(ConnectionPassword);
}
QString DatabaseStateDialog::GetConnectionPassword()
{

    return ui->ConnectionPassword->text();

}


bool DatabaseStateDialog::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui->DatabaseId)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            ui->DatabaseId->completer()->complete();
        }
    }
    return QDialog::eventFilter(target, event);
}
void DatabaseStateDialog::SetDatabaseBaseLocation(const QString& DatabaseBaseLocation)
{

    QDir recoredDir(DatabaseBaseLocation);
    QStringList List = recoredDir.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs, QDir::DirsFirst);


    QCompleter *completer = new QCompleter(List, ui->DatabaseId);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);

    ui->DatabaseId->setCompleter(completer);
    completer->complete();

    ui->DatabaseId->installEventFilter(this);

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

void DatabaseStateDialog::on_ConnectionType_currentIndexChanged(int index)
{
    if(ui->ConnectionType->currentIndex() == 0)
    {
        ui->groupBox_4->setVisible(true);
        ui->groupBox_5->setVisible(true);
        ui->groupBox_7->setVisible(false);
    }else
    {
        ui->groupBox_4->setVisible(false);
        ui->groupBox_5->setVisible(false);
        ui->groupBox_7->setVisible(true);
    }
    if(index>=0)
        SetIsDirty(true);

}

void DatabaseStateDialog::on_ConnectionServer_textEdited(const QString &arg1)
{
    SetIsDirty(true);
}

void DatabaseStateDialog::on_ConnectionPort_textEdited(const QString &arg1)
{
    SetIsDirty(true);
}

void DatabaseStateDialog::on_ConnectionLogin_textEdited(const QString &arg1)
{
    SetIsDirty(true);
}

void DatabaseStateDialog::on_ConnectionPassword_textEdited(const QString &arg1)
{
    SetIsDirty(true);
}
