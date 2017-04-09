#include "databaseadmin.h"
#include "ui_databaseadmin.h"
#include <QDebug>
#include "databaseadmineditgroup.h"
#include "databaseadmindeletegroup.h"
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>
#include <QDesktopServices>
#include <QInputDialog>
#include <QDesktopWidget>
#include <QMenuBar>

#include "databaseadmincsvformat.h"
#include "every_cpp.h"
#ifdef Q_OS_WIN
    #include <windows.h>
#endif



namespace BrowserAutomationStudioFramework
{
    DatabaseAdmin::DatabaseAdmin(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::DatabaseAdmin)
    {
        ui->setupUi(this);

        ui->DatabaseTables->SetAllGroups(&GroupWidgets);
        DeactivateLabel = 0;
        connect(ui->DatabaseTables,SIGNAL(Activate()),this,SLOT(Activate()));
        connect(ui->DatabaseTables,SIGNAL(Deactivate()),this,SLOT(Deactivate()));
        IsDeactivated = false;
        ui->ClearDatabaseFilter->setVisible(false);

        ui->AddGroup->setVisible(false);
        ui->DeleteSelectedGroups->setVisible(false);
        ui->SelectAllGroups->setVisible(false);
        ui->SelectNoGroups->setVisible(false);

        QMenuBar *Menu = new QMenuBar(this);

        QMenu *FileMenu = Menu->addMenu(tr("File"));
        FileMenu->addAction(ui->RefreshButton->icon(),tr("Refresh"),ui->RefreshButton,SLOT(click()));
        FileMenu->addAction(ui->DeleteAllButton->icon(),tr("Delete All Data"),ui->DeleteAllButton,SLOT(click()));

        QMenu *ConvertMenu = Menu->addMenu(tr("Convert"));
        ConvertMenu->addAction(QIcon(":/engine/images/csv.png"),ui->ImportCsv->text(),ui->ImportCsv,SLOT(click()));
        ConvertMenu->addAction(QIcon(":/engine/images/csv.png"),ui->ExportCsv->text(),ui->ExportCsv,SLOT(click()));
        ConvertMenu->addAction(QIcon(":/engine/images/sql.png"),ui->Backup->text(),ui->Backup,SLOT(click()));
        ConvertMenu->addAction(QIcon(":/engine/images/sql.png"),ui->Restore->text(),ui->Restore,SLOT(click()));
        ConvertMenu->addAction(QIcon(":/engine/images/xls.png"),ui->ExportXls->text(),ui->ExportXls,SLOT(click()));

        ui->groupBox->setVisible(false);
        ui->groupBox_2->setVisible(false);

        this->layout()->setMenuBar(Menu);

    }

    void DatabaseAdmin::Deactivate()
    {
        IsDeactivated = true;
        if(!DeactivateLabel)
        {
            DeactivateWidget = new QWidget(this);

            DeactivateWidget->setStyleSheet("QWidget{background-color:white; border:1px solid gray;}");

            DeactivateLabel = new QLabel(DeactivateWidget);
            Movie = new QMovie(":/engine/images/loading.gif");
            Movie->setParent(DeactivateLabel);
            DeactivateLabel->setMovie(Movie);

            DeactivateWidget->resize(400,100);

        }

        Movie->start();
        DeactivateLabel->show();
        DeactivateWidget->show();

        DeactivateWidget->move(this->width()/2 - DeactivateWidget->width()/2, this->height()/2- DeactivateWidget->height()/2);
        DeactivateLabel->move(DeactivateWidget->width()/2 - DeactivateLabel->width()/2, DeactivateWidget->height()/2 - DeactivateLabel->height()/2);
        this->setEnabled(false);
    }
    void DatabaseAdmin::Activate()
    {
        IsDeactivated = false;
        if(DeactivateLabel)
        {
            Movie->stop();
            DeactivateLabel->setVisible(false);
            DeactivateWidget->setVisible(false);
        }

        this->setEnabled(true);
    }



    DatabaseAdmin::~DatabaseAdmin()
    {
        delete ui;
    }


    void DatabaseAdmin::SetGroupsToTable()
    {
        QList<DatabaseGroup> SelectedGroups;

        foreach(DatabaseGroupWidget * Group,GetSelectedGroups(Raw))
        {
            DatabaseGroup dc;
            dc.Id = Group->GetId();
            dc.Name = Group->GetName();
            dc.Description = Group->GetDescription();
            dc.IsNull = false;
            SelectedGroups<<dc;
        }
        ui->DatabaseTables->SetGroups(SelectedGroups);
    }

    void DatabaseAdmin::RefreshData()
    {
        if(ui->Tables->currentIndex()<0)
            return;
        int TableId = ui->Tables->currentData().toInt();

        foreach(DatabaseGroupWidget* GroupWidget,GroupWidgets)
        {
            delete GroupWidget;
        }
        GroupWidgets.clear();

        if(!DatabaseConnector->IsConnected())
        {
            QEventLoop loop;
            connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
            loop.exec();
        }
        QList<DatabaseGroup> Groups = DatabaseConnector->GetGroups(TableId);
        foreach(DatabaseGroup Group,Groups)
        {
            InsertGroupInsideInterface(Group,-1);
        }
        if(GroupWidgets.length()>0)
            GroupWidgets.last()->SetSelected(true);


        SetGroupsToTable();
        ui->DatabaseTables->SetTableId(TableId);
        ui->DatabaseTables->ReloadPageNumber();
        ui->DatabaseTables->Reload();


    }

    void DatabaseAdmin::InsertGroupInsideInterface(DatabaseGroup Group, int index)
    {
        DatabaseGroupWidget *GroupWidget = new DatabaseGroupWidget(ui->GroupsWidgetContent);
        GroupWidgets.insert(index,GroupWidget);
        connect(GroupWidget,SIGNAL(DeleteWithData(QString)),this,SLOT(DeleteWithData(QString)));
        connect(GroupWidget,SIGNAL(DeleteWithoutData(QString)),this,SLOT(DeleteWithoutData(QString)));
        connect(GroupWidget,SIGNAL(ClearData(QString)),this,SLOT(ClearData(QString)));
        connect(GroupWidget,SIGNAL(Copy(QString,QString,QString)),this,SLOT(CopyGroup(QString,QString,QString)));
        connect(GroupWidget,SIGNAL(Selected(QString,bool)),this,SLOT(SelectedGroup(QString,bool)));

        connect(GroupWidget,SIGNAL(Edit(QString,QString,QString)),this,SLOT(EditGroup(QString,QString,QString)));


        GroupWidget->SetName(Group.Name);
        GroupWidget->SetDescription(Group.Description);
        GroupWidget->SetId(Group.Id);
        ui->GroupsLayout->insertWidget(index,GroupWidget);
    }

    QList<DatabaseGroupWidget *> DatabaseAdmin::GetSelectedGroups(SelectTarget Target)
    {
        QList<DatabaseGroupWidget *> res;
        bool First = true;
        foreach(DatabaseGroupWidget* Group, GroupWidgets)
        {
            if(Group->GetSelected() && (Group->GetId()>=0||Target == Raw))
            {
                res.append(Group);
                First = false;
            }
        }
        if(First)
        {
            foreach(DatabaseGroupWidget* Group, GroupWidgets)
            {
                if((Group->GetId()>=0||Target == Raw))
                {
                    res.append(Group);
                    First = false;
                }
            }
        }
        return res;
    }

    int DatabaseAdmin::GetGroupArrayIndexByDatabaseId(QString Id)
    {
        int Index = -1;
        int i = 0;
        foreach(DatabaseGroupWidget* GroupWidget,GroupWidgets)
        {
            if(GroupWidget->GetId() == Id)
            {
                Index = i;

            }
            i++;
        }


        return Index;
    }

    void DatabaseAdmin::SelectedGroup(QString GroupId, bool IsSelected)
    {
        if(QApplication::keyboardModifiers() & Qt::ShiftModifier || QApplication::keyboardModifiers() & Qt::ControlModifier)
        {
            if(GroupId == "-1" && IsSelected)
            {
                foreach(DatabaseGroupWidget* Group, GroupWidgets)
                {
                    if(Group->GetId() != "-1")
                        Group->SetSelected(false);
                }
            }
            if(GroupId != "-1" && IsSelected)
            {
                foreach(DatabaseGroupWidget* Group, GroupWidgets)
                {
                    if(Group->GetId() == "-1")
                        Group->SetSelected(false);
                }
            }
        }else
        {
            foreach(DatabaseGroupWidget* Group, GroupWidgets)
            {
                if(Group->GetId() != GroupId)
                    Group->SetSelected(false);
            }
        }

        SetGroupsToTable();
        ui->DatabaseTables->ReloadPageNumber();
        ui->DatabaseTables->Reload();
    }

    void DatabaseAdmin::EditGroup(QString Id,QString Name,QString Description)
    {
        DatabaseGroup g;
        g.Id = Id;
        g.IsNull = false;
        g.Name = Name;
        g.Description = Description;
        int TableId = ui->Tables->currentData().toInt();
        if(!DatabaseConnector->IsConnected())
        {
            QEventLoop loop;
            connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
            loop.exec();
        }
        DatabaseConnector->UpdateGroup(g,TableId);

    }

    void DatabaseAdmin::DeleteWithData(QString Id)
    {
        int Index = GetGroupArrayIndexByDatabaseId(Id);
        if(Index>=0 && Id!="-2")
        {

            delete GroupWidgets[Index];
            GroupWidgets.removeAt(Index);
        }
        DatabaseGroups groups;
        groups.GroupIdList.append(Id);
        groups.IsNull = false;
        int TableId = ui->Tables->currentData().toInt();

        {
            Deactivate();
            if(!DatabaseConnector->IsConnected())
            {
                QEventLoop loop;
                connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
                loop.exec();
            }
            QFutureWatcher<void> watcher;
            QFuture<void> future;
            QEventLoop loop;
            connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));
            connect(&watcher, SIGNAL(finished()), this, SLOT(Activate()));


            future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::DeleteGroupWithData,groups,TableId);
            watcher.setFuture(future);
            loop.exec();
        }
        //DatabaseConnector->DeleteGroupWithData(groups,TableId);
        SetGroupsToTable();
        ui->DatabaseTables->ReloadPageNumber();
        ui->DatabaseTables->Reload();
    }

    void DatabaseAdmin::DeleteWithoutData(QString Id)
    {
        int Index = GetGroupArrayIndexByDatabaseId(Id);
        if(Index>=0 && Id!="-2")
        {
            delete GroupWidgets[Index];
            GroupWidgets.removeAt(Index);
        }
        DatabaseGroups groups;
        groups.GroupIdList.append(Id);
        groups.IsNull = false;
        int TableId = ui->Tables->currentData().toInt();
        {
            Deactivate();
            if(!DatabaseConnector->IsConnected())
            {
                QEventLoop loop;
                connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
                loop.exec();
            }
            QFutureWatcher<void> watcher;
            QFuture<void> future;
            QEventLoop loop;
            connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));
            connect(&watcher, SIGNAL(finished()), this, SLOT(Activate()));


            future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::DeleteGroupNoData,groups,TableId);
            watcher.setFuture(future);
            loop.exec();
        }
        //DatabaseConnector->DeleteGroupNoData(groups,TableId);
        SetGroupsToTable();
        ui->DatabaseTables->ReloadPageNumber();
        ui->DatabaseTables->Reload();
    }

    void DatabaseAdmin::ClearData(QString Id)
    {
        DatabaseGroups groups;
        groups.GroupIdList.append(Id);
        groups.IsNull = false;
        int TableId = ui->Tables->currentData().toInt();

        {
            Deactivate();
            if(!DatabaseConnector->IsConnected())
            {
                QEventLoop loop;
                connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
                loop.exec();
            }
            QFutureWatcher<void> watcher;
            QFuture<void> future;
            QEventLoop loop;
            connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));
            connect(&watcher, SIGNAL(finished()), this, SLOT(Activate()));


            future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::ClearGroup,groups,TableId);
            watcher.setFuture(future);
            loop.exec();
        }
        if(!DatabaseConnector->IsConnected())
        {
            QEventLoop loop;
            connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
            loop.exec();
        }
        DatabaseConnector->ClearGroup(groups,TableId);
        SetGroupsToTable();
        ui->DatabaseTables->ReloadPageNumber();
        ui->DatabaseTables->Reload();
    }



    void DatabaseAdmin::Show()
    {
        if(!IsDeactivated)
        {
            QList<DatabaseTable> Tables = DatabaseConnector->GetTables();
            ui->Tables->clear();

            foreach(DatabaseTable t, Tables)
            {
                ui->Tables->addItem(t.Description,t.Id);
            }

            RefreshData();
            ui->splitter->setSizes(QList<int>()<<300<<this->width()-300);
        }

        QRect screenGeometry = QApplication::desktop()->screenGeometry();
        int x = (screenGeometry.width()-width()) / 2;
        int y = (screenGeometry.height()-height()) / 2;
        if(x<0)
            x = 0;
        if(y<0)
            y = 0;
        move(x, y);
        show();
    }

    void DatabaseAdmin::SetDatabaseConnector(IDatabaseConnector *DatabaseConnector)
    {
        this->DatabaseConnector = DatabaseConnector;

        ui->DatabaseTables->SetDatabaseConnector(DatabaseConnector);
    }

    void DatabaseAdmin::on_RefreshButton_clicked()
    {
        RefreshData();
    }
    void DatabaseAdmin::on_Tables_activated(int index)
    {
        RefreshData();
    }

    void DatabaseAdmin::on_AddGroup_clicked()
    {

        DatabaseAdminEditGroup d;
        if(d.exec())
        {
            DatabaseGroup Group;
            Group.IsNull = false;
            Group.Name = d.GetName();
            Group.Description = d.GetDescription();
            if(ui->Tables->currentIndex()<0)
                return;
            int TableId = ui->Tables->currentData().toInt();
            if(!DatabaseConnector->IsConnected())
            {
                QEventLoop loop;
                connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
                loop.exec();
            }
            Group.Id = DatabaseConnector->InsertGroup(Group,TableId);
            InsertGroupInsideInterface(Group,2);
        }

    }

    void DatabaseAdmin::CopyGroup(QString GroupId,QString Name,QString Description)
    {
        DatabaseGroup Group;
        Group.IsNull = false;
        Group.Name = Name;
        Group.Description = Description;
        if(ui->Tables->currentIndex()<0)
            return;
        int TableId = ui->Tables->currentData().toInt();

        {
            Deactivate();
            if(!DatabaseConnector->IsConnected())
            {
                QEventLoop loop;
                connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
                loop.exec();
            }
            QFutureWatcher<QString> watcher;
            QFuture<QString> future;
            QEventLoop loop;
            connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));
            connect(&watcher, SIGNAL(finished()), this, SLOT(Activate()));


            future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::CopyGroup,Group,TableId,GroupId);
            watcher.setFuture(future);
            loop.exec();
            Group.Id = future.result();
        }
        //Group.Id = DatabaseConnector->CopyGroup(Group,TableId,GroupId);
        InsertGroupInsideInterface(Group,2);
    }

    void DatabaseAdmin::on_SelectAllGroups_clicked()
    {
        foreach(DatabaseGroupWidget* Group, GroupWidgets)
        {
            if(!Group->IsFiltered())
                Group->SetSelected(Group->GetId()!="-1");
        }
        SetGroupsToTable();
        ui->DatabaseTables->ReloadPageNumber();
        ui->DatabaseTables->Reload();
    }

    void DatabaseAdmin::on_SelectNoGroups_clicked()
    {
        foreach(DatabaseGroupWidget* Group, GroupWidgets)
        {
            Group->SetSelected(false);
        }
        SetGroupsToTable();
        ui->DatabaseTables->ReloadPageNumber();
        ui->DatabaseTables->Reload();
    }

    void DatabaseAdmin::on_DeleteSelectedGroups_clicked()
    {
        int TableId = ui->Tables->currentData().toInt();
        DatabaseAdminDeleteGroup d;
        QString Groups;
        bool First = true;
        QList<DatabaseGroupWidget*> SelectedGroups = GetSelectedGroups(Delete);
        DatabaseGroups g;
        g.IsNull = false;

        foreach(DatabaseGroupWidget* Group, SelectedGroups)
        {
            if(Group->GetId()!="-1" && Group->GetId()!="-2")
            {
                if(!First)
                    Groups += ", ";
                Groups.append(Group->GetName());
                g.GroupIdList.append(Group->GetId());
                First = false;
            }
        }
        d.SetGroupList(Groups);
        if(d.exec())
        {
            foreach(DatabaseGroupWidget* Group, SelectedGroups)
            {
                switch(d.GetTaskType())
                {
                    case 1: {
                            int Index = GetGroupArrayIndexByDatabaseId(Group->GetId());
                            if(Index>=0 && Group->GetId() != "-2" && Group->GetId() != "-1")
                            {
                                delete GroupWidgets[Index];
                                GroupWidgets.removeAt(Index);
                            }

                        } break;
                    case 2: {
                            int Index = GetGroupArrayIndexByDatabaseId(Group->GetId());
                            if(Index>=0 && Group->GetId() != "-2" && Group->GetId() != "-1")
                            {
                                delete GroupWidgets[Index];
                                GroupWidgets.removeAt(Index);
                            }

                        } break;
                    case 3: {} break;
                }
            }
            switch(d.GetTaskType())
            {
                case 1:
                    {
                        Deactivate();
                        if(!DatabaseConnector->IsConnected())
                        {
                            QEventLoop loop;
                            connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
                            loop.exec();
                        }
                        QFutureWatcher<void> watcher;
                        QFuture<void> future;
                        QEventLoop loop;
                        connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));
                        connect(&watcher, SIGNAL(finished()), this, SLOT(Activate()));


                        future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::DeleteGroupWithData,g,TableId);
                        watcher.setFuture(future);
                        loop.exec();
                    }

                    //DatabaseConnector->DeleteGroupWithData(g,TableId);
                break;
                case 2:
                    {
                        Deactivate();
                        if(!DatabaseConnector->IsConnected())
                        {
                            QEventLoop loop;
                            connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
                            loop.exec();
                        }
                        QFutureWatcher<void> watcher;
                        QFuture<void> future;
                        QEventLoop loop;
                        connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));
                        connect(&watcher, SIGNAL(finished()), this, SLOT(Activate()));


                        future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::DeleteGroupNoData,g,TableId);
                        watcher.setFuture(future);
                        loop.exec();
                    }
                    //DatabaseConnector->DeleteGroupNoData(g,TableId);
                break;
                case 3:
                    {
                        Deactivate();
                        if(!DatabaseConnector->IsConnected())
                        {
                            QEventLoop loop;
                            connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
                            loop.exec();
                        }

                        QFutureWatcher<void> watcher;
                        QFuture<void> future;
                        QEventLoop loop;
                        connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));
                        connect(&watcher, SIGNAL(finished()), this, SLOT(Activate()));


                        future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::ClearGroup,g,TableId);
                        watcher.setFuture(future);
                        loop.exec();
                    }

                    //DatabaseConnector->ClearGroup(g,TableId);
                break;
            }

        }
        SetGroupsToTable();
        ui->DatabaseTables->ReloadPageNumber();
        ui->DatabaseTables->Reload();
    }

    void DatabaseAdmin::on_EditGroupFilter_textChanged(const QString &arg1)
    {
        foreach(DatabaseGroupWidget *Group, GroupWidgets)
        {
            Group->SetFilter(arg1);
        }
        ui->ClearDatabaseFilter->setVisible(!arg1.isEmpty());

    }

    void DatabaseAdmin::on_ClearDatabaseFilter_clicked()
    {
        ui->EditGroupFilter->clear();
    }
    void DatabaseAdmin::on_DeleteAllButton_clicked()
    {

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Delete All?"), tr("Are you sure, that you want to delete all data?"), QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            {
                Deactivate();
                if(!DatabaseConnector->IsConnected())
                {
                    QEventLoop loop;
                    connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
                    loop.exec();
                }
                QFutureWatcher<void> watcher;
                QFuture<void> future;
                QEventLoop loop;
                connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));
                connect(&watcher, SIGNAL(finished()), this, SLOT(Activate()));


                future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::DeleteAll);
                watcher.setFuture(future);
                loop.exec();
            }

            //DatabaseConnector->DeleteAll();
            RefreshData();
        }

    }

    void DatabaseAdmin::on_ImportCsv_clicked()
    {
        DatabaseAdminCsvFormat d;
        if(ui->Tables->currentIndex()<0)
            return;
        int TableId = ui->Tables->currentData().toInt();
        QList<DatabaseColumn> Columns = DatabaseConnector->GetColumns(TableId);
        d.SetDatabaseColumns(Columns);
        d.SetIsExport(false);
        if(d.exec())
        {
            if(!DatabaseConnector->IsConnected())
            {
                QEventLoop loop;
                connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
                loop.exec();
            }
            DatabaseGroup Group;
            Group.IsNull = false;
            Group.Name = tr("Csv");
            Group.Description = tr("Imported at ") + QString(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"));
            Group.Id = DatabaseConnector->InsertGroup(Group,TableId);
            InsertGroupInsideInterface(Group,2);

           {
                Deactivate();
                if(!DatabaseConnector->IsConnected())
                {
                    QEventLoop loop;
                    connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
                    loop.exec();
                }
                QFutureWatcher<void> watcher;
                QFuture<void> future;
                QEventLoop loop;
                connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));
                //connect(&watcher, SIGNAL(finished()), this, SLOT(Activate()));


                future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::ImportCsv,d.GetFileName(),d.GetColumnIds(),Group.Id, TableId);
                watcher.setFuture(future);
                loop.exec();
            }

            foreach(DatabaseGroupWidget* group, GroupWidgets)
            {
                bool IsSelected = group->GetId() == Group.Id;
                group->SetSelected(IsSelected);
            }
            SetGroupsToTable();
            ui->DatabaseTables->ReloadPageNumber();
            ui->DatabaseTables->Reload();

            //DatabaseConnector->ImportCsv(d.GetFileName(),d.GetColumnIds());
        }

    }


    void DatabaseAdmin::on_ExportCsv_clicked()
    {

        DatabaseAdminCsvFormat d;
        if(ui->Tables->currentIndex()<0)
            return;
        int TableId = ui->Tables->currentData().toInt();
        QList<DatabaseColumn> Columns = DatabaseConnector->GetColumns(TableId);
        d.SetDatabaseColumns(Columns);
        d.SetIsExport(true);
        if(d.exec())
        {


            {
                Deactivate();
                if(!DatabaseConnector->IsConnected())
                {
                    QEventLoop loop;
                    connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
                    loop.exec();
                }
                QFutureWatcher<void> watcher;
                QFuture<void> future;
                QEventLoop loop;
                connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));
                connect(&watcher, SIGNAL(finished()), this, SLOT(Activate()));


                future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::ExportCsv,d.GetFileName(),d.GetColumnIds(),ui->DatabaseTables->PrepareSelector());
                watcher.setFuture(future);
                loop.exec();
            }

            //DatabaseConnector->ExportCsv(d.GetFileName(),d.GetColumnIds(),ui->DatabaseTables->PrepareSelector());
            if(DatabaseConnector->WasError())
            {
                 QMessageBox::information(0, "Database Error", DatabaseConnector->GetError());
            }else
            {
                QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(d.GetFileName()).absoluteFilePath()));

            }
        }

    }


    void DatabaseAdmin::on_ExportXls_clicked()
    {
        DatabaseAdminCsvFormat d;
        d.SetXls();
        if(ui->Tables->currentIndex()<0)
            return;
        int TableId = ui->Tables->currentData().toInt();
        QList<DatabaseColumn> Columns = DatabaseConnector->GetColumns(TableId);
        d.SetDatabaseColumns(Columns);
        d.SetIsExport(true);
        if(d.exec())
        {


            {
                Deactivate();
                if(!DatabaseConnector->IsConnected())
                {
                    QEventLoop loop;
                    connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
                    loop.exec();
                }
                QFutureWatcher<void> watcher;
                QFuture<void> future;
                QEventLoop loop;
                connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));
                connect(&watcher, SIGNAL(finished()), this, SLOT(Activate()));


                future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::ExportExcel,d.GetFileName()+".xml",d.GetColumnIds(),ui->DatabaseTables->PrepareSelector());
                watcher.setFuture(future);
                loop.exec();
            }

            //DatabaseConnector->ExportCsv(d.GetFileName(),d.GetColumnIds(),ui->DatabaseTables->PrepareSelector());
            if(DatabaseConnector->WasError())
            {
                QMessageBox::information(0, "Database Error", DatabaseConnector->GetError());
            }else
            {
                #ifdef Q_OS_WIN
                    QString str1 = QString("excel.exe");
                    LPCWSTR s1 = (LPCWSTR)(str1.utf16());
                    QString str2 = QString(d.GetFileName()+".xml");
                    LPCWSTR s2 = (LPCWSTR)(str2.utf16());

                    ShellExecute(NULL,NULL,s1,s2,NULL,SW_RESTORE);
                #endif
            }
        }
    }

    void DatabaseAdmin::on_Backup_clicked()
    {
        {
             Deactivate();
             if(!DatabaseConnector->IsConnected())
             {
                 QEventLoop loop;
                 connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
                 loop.exec();
             }

             QEventLoop loop;
             connect(DatabaseConnector, SIGNAL(BackupOrRestoreFinished()), &loop, SLOT(quit()));
             DatabaseConnector->Backup();

             loop.exec();
             Activate();

             if(DatabaseConnector->WasError())
             {
                 QMessageBox::information(0, "Database Error", DatabaseConnector->GetError());
             }
         }
    }

    void DatabaseAdmin::on_Restore_clicked()
    {
        QStringList all = DatabaseConnector->ShowBackupList();
        if(all.isEmpty())
        {
            QMessageBox::information(0, tr("Database Error"), tr("No Backup Made"));
            return;
        }
        bool ok;
        QString item = QInputDialog::getItem(this, tr("Choose Backup To Restore"),
                                             tr("Restore:"), all, 0, false, &ok);
        if (!ok)
            return;

        {
            Deactivate();
            if(!DatabaseConnector->IsConnected())
            {
                QEventLoop loop;
                connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
                loop.exec();
            }

            {
                QFutureWatcher<void> watcher;
                QFuture<void> future;
                QEventLoop loop;
                connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));


                future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::DeleteAll);
                watcher.setFuture(future);
                loop.exec();
            }

             QEventLoop loop;
             connect(DatabaseConnector, SIGNAL(BackupOrRestoreFinished()), &loop, SLOT(quit()));
             DatabaseConnector->Restore(item);

             loop.exec();
             RefreshData();
             //Activate();

             if(DatabaseConnector->WasError())
             {
                 QMessageBox::information(0, tr("Database Error"), DatabaseConnector->GetError());
             }
         }
    }

}




void BrowserAutomationStudioFramework::DatabaseAdmin::on_MenuButton_clicked()
{
    QMenu myMenu;
    myMenu.addAction(ui->AddGroup->icon(),ui->AddGroup->text(),ui->AddGroup, SLOT(click()));
    myMenu.addAction(ui->DeleteSelectedGroups->icon(),ui->DeleteSelectedGroups->text(),ui->DeleteSelectedGroups, SLOT(click()));
    myMenu.addAction(ui->SelectAllGroups->icon(),ui->SelectAllGroups->text(),ui->SelectAllGroups, SLOT(click()));
    myMenu.addAction(ui->SelectNoGroups->icon(),ui->SelectNoGroups->text(),ui->SelectNoGroups, SLOT(click()));

    myMenu.exec(QCursor::pos());
}

