#include "databaseadmintable.h"
#include "ui_databaseadmintable.h"
#include <QDebug>
#include <QStyleFactory>
#include <QModelIndex>
#include <QInputDialog>
#include <QLabel>
#include <QScrollBar>
#include <QPushButton>
#include <QMessageBox>
#include <QFutureWatcher>
#include <QFuture>
#include <QMenu>
#include <QtConcurrent/QtConcurrent>
#include "databaseadminitemedit.h"
#include "databaseadminitemmodificationdialog.h"
#include "databaseadminmovetogroup.h"
#include "databaseadminrowtoolbox.h"


DatabaseAdminTable::DatabaseAdminTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseAdminTable)
{
    ui->setupUi(this);
    connect(ui->FilterWidget,SIGNAL(FiltersChanged()),this, SLOT(FilterChanged()));
    InitTable();
    ReloadPageNumber();
    ReactRowSelectionChange = true;
    IsInverseSelection = false;
    SortId = -1;
    ui->AddItem->setVisible(false);
    ui->DeletSelected->setVisible(false);
    ui->SelectAll->setVisible(false);
    ui->SelectNone->setVisible(false);
    ui->MoveSelectedGroup->setVisible(false);
    ui->CopySelectedGroup->setVisible(false);
    ui->DeleteSelectedFromGroups->setVisible(false);


}

void DatabaseAdminTable::FilterChanged()
{
    Filters = ui->FilterWidget->GetFilters();
    Reload();
}

void DatabaseAdminTable::SetDatabaseConnector(IDatabaseConnector *DatabaseConnector)
{
    this->DatabaseConnector = DatabaseConnector;

}

void DatabaseAdminTable::ReloadPageNumber()
{
    IsInverseSelection = false;
    SelectedRows.clear();
    PageNumber = 1;
    SortId = -1;

}

void DatabaseAdminTable::SetTableId(int TableId)
{
    IsInverseSelection = false;
    SelectedRows.clear();
    this->TableId = TableId;

    Filters.IsNull = true;
    Filters.FilterList.clear();
    ui->FilterWidget->Clear();
}

void DatabaseAdminTable::SetGroups(QList<DatabaseGroup> Groups)
{
    this->Groups = Groups;
}
void DatabaseAdminTable::SetAllGroups(QList<DatabaseGroupWidget *>* AllGroups)
{
    this->AllGroups = AllGroups;
}



void DatabaseAdminTable::InitTable()
{
    ui->DataTable->verticalHeader()->setVisible(false);
    ui->DataTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->DataTable->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->DataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->DataTable->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(HeaderClicked(int)));

    ui->DataTable->setStyle(QStyleFactory::create("fusion"));
    QPalette palette;


    palette.setColor(QPalette::Window, QColor( 240 , 240 , 240 ));
    palette.setColor(QPalette::WindowText, QColor( 0 , 0 , 0 ));
    palette.setColor(QPalette::Base, QColor( 255 , 255 , 255 ));
    palette.setColor(QPalette::AlternateBase, QColor( 250 , 250 , 250 ));
    palette.setColor(QPalette::ToolTipBase, QColor( 255 , 255 , 220 ));
    palette.setColor(QPalette::ToolTipText, QColor( 0 , 0 , 0 ));
    palette.setColor(QPalette::Text, QColor( 0 , 0 , 0 ));
    palette.setColor(QPalette::Button, QColor( 240 , 240 , 240 ));
    palette.setColor(QPalette::ButtonText, QColor( 0 , 0 , 0 ));
    palette.setColor(QPalette::BrightText, QColor( 255 , 255 , 255 ));

    palette.setColor(QPalette::Highlight, QColor( 222 , 226 , 252 ));
    palette.setColor(QPalette::HighlightedText, QColor( 0 , 0 , 0 ));


    ui->DataTable->setPalette(palette);
    this->setPalette(palette);


}


void DatabaseAdminTable::Reload()
{
    ui->FilterWidget->SetColumns(DatabaseConnector->GetColumns(TableId));

    ReactRowSelectionChange = false;

    CurrentPageIds.clear();
    DatabaseSelector Selector = GetDatabaseSelector();
    int vsize = ui->PageSize->currentText().toInt();

    //QTime t = QTime::currentTime();
    {
        emit Deactivate();
        if(!DatabaseConnector->IsConnected())
        {
            QEventLoop loop;
            connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
            loop.exec();
        }
        QFutureWatcher<int > watcher;
        QFuture<int > future;
        QEventLoop loop;
        connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));


        future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::Count,Selector);
        watcher.setFuture(future);
        loop.exec();
        TotalRows = future.result();
    }
    //qDebug()<<t.msecsTo(QTime::currentTime());
    //TotalRows = DatabaseConnector->Count(Selector);
    //TotalRows = 100000;
    TotalPages = TotalRows/vsize + 1;
    if(TotalRows%vsize == 0 && TotalRows>0)
        TotalPages--;

    QList<DatabaseColumn> columns = DatabaseConnector->GetColumns(TableId);
    if(PageNumber*vsize > TotalRows)
    {
        vsize -= PageNumber*vsize - TotalRows;
    }
    int hsize = columns.length();
    int CurrentVSize = ui->DataTable->rowCount();
    if(vsize>=CurrentVSize)
    {
        ui->DataTable->setRowCount(vsize);
    }else
    {
        for(int i = vsize;i<CurrentVSize;i++)
            ui->DataTable->setRowHidden(i, true);
    }

    for(int i = 0;i<vsize;i++)
        ui->DataTable->setRowHidden(i, false);

    ui->DataTable->setColumnCount(hsize+1);

    //ui->DataToolbar->setRowCount(vsize);
    //qDebug()<<vsize;


    for(int i = 0;i<vsize;i++)
    {
        for(int j = 1;j<hsize+1;j++)
        {
            if(!ui->DataTable->item(i,j))
            {
                ui->DataTable->setItem(i,j,new QTableWidgetItem());
            }else
            {
                ui->DataTable->item(i,j)->setText("");
            }
        }
    }

    for(int i = 0;i<vsize;i++)
    {
        //qDebug()<<ui->DataTable->cellWidget(i,0);
        if(!ui->DataTable->cellWidget(i,0))
        {
            //qDebug()<<"Create";
            DatabaseAdminRowToolbox *w = new DatabaseAdminRowToolbox();
            connect(w,SIGNAL(Edit(QString)),this,SLOT(SingleItemEdit(QString)));
            connect(w,SIGNAL(Delete(QString)),this,SLOT(SingleItemDelete(QString)));
            ui->DataTable->setCellWidget(i,0,w);
        }
    }


    for(int j = 1;j<hsize+1;j++)
    {
        if(!ui->DataTable->horizontalHeaderItem(j))
        {
            QTableWidgetItem* item = new QTableWidgetItem();
            ui->DataTable->setHorizontalHeaderItem(j,item);
        }


        ui->DataTable->horizontalHeaderItem(j)->setIcon(QIcon());
    }
    if(SortId>=0)
    {
        QIcon Icon;
        if(SortOrder == Asc)
        {
            Icon = QIcon(":/engine/images/sortasc.png");
        }else
        {
            Icon = QIcon(":/engine/images/sortdesc.png");
        }
        ui->DataTable->horizontalHeaderItem(1+SortId)->setIcon(Icon);
    }




    QStringList Headers;
    Headers.append("");
    foreach(DatabaseColumn column,columns)
    {
        Headers<<column.Description;
    }
    ui->DataTable->setHorizontalHeaderLabels(Headers);
    ui->DataTable->horizontalHeader()->resizeSection(0,42);
    ui->PageNumberLabel->setText(QString::number(PageNumber));




    ui->TotalSizeNumber->setText(QString::number(TotalRows));
    QList<DatabaseItem> Items;
    {
        //emit Deactivate();
        if(!DatabaseConnector->IsConnected())
        {
            QEventLoop loop;
            connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
            loop.exec();
        }
        QFutureWatcher<QList<DatabaseItem> > watcher;
        QFuture<QList<DatabaseItem> > future;
        QEventLoop loop;
        connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));
        connect(&watcher, SIGNAL(finished()), this, SIGNAL(Activate()));


        future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::Select,Selector);
        watcher.setFuture(future);
        loop.exec();
        Items = future.result();
    }
    //QList<DatabaseItem> Items = DatabaseConnector->Select(Selector);
    CurrentItems = Items;
    int y=0;

    ui->DataTable->clearSelection();
    if(IsInverseSelection)
        ui->DataTable->selectAll();
    //ui->DataToolbar->clearSelection();
    foreach(DatabaseItem Item, Items)
    {
        //qDebug()<<"z1";
        int x = 1;

        foreach(DatabaseColumn column, columns)
        {
            foreach(int ColumnId, Item.Data.keys())
            {

                if(ColumnId == column.Id)
                {
                    ui->DataTable->item(y,x)->setText(Item.Data[ColumnId].toString());

                    break;
                }
            }
            x++;
        }


        CurrentPageIds.append(Item.Id);
        //qDebug()<<"z21";
        if(SelectedRows.contains(Item.Id))
        {
            ui->DataTable->selectRow(y);

        }

        DatabaseAdminRowToolbox *w = (DatabaseAdminRowToolbox *)(ui->DataTable->cellWidget(y,0));

        w->SetId(Item.Id);


        y++;



    }
    ReactRowSelectionChange = true;

    GetSelectedNumber();
}

void DatabaseAdminTable::HeaderClicked(int index)
{
    //qDebug()<<index;
    if(index == 0)
        return;
    index --;

    if(SortId == index)
    {
        if(SortOrder == Asc)
        {
            SortOrder = Desc;
        }else if(SortOrder == Desc)
        {
            SortId = -1;
        }
    }else
    {
        SortId = index;
        SortOrder = Asc;
    }


    Reload();
}

DatabaseAdminTable::~DatabaseAdminTable()
{
    delete ui;
}

void DatabaseAdminTable::on_PageSize_currentIndexChanged(int index)
{
    ReloadPageNumber();
    Reload();
}

DatabaseSelector DatabaseAdminTable::GetDatabaseSelector()
{
    DatabaseSelector res;
    res.Filter.IsNull = true;
    res.Sort.IsNull = true;

    res.Page.IsNull = false;
    res.Page.PageNumber = PageNumber;
    res.Page.PageSize = ui->PageSize->currentText().toInt();


    DatabaseGroups GroupIds;
    GroupIds.IsNull = false;
    foreach(DatabaseGroup Group, Groups)
    {
        //if(Group.Id>=0)
        //{
            GroupIds.GroupIdList.append(Group.Id);
        //}
    }
    res.TableId = TableId;
    res.Groups = GroupIds;

    DatabaseSort Sort;
    Sort.IsNull = true;
    if(SortId>=0)
    {
        QList<DatabaseColumn> Columns = DatabaseConnector->GetColumns(TableId);
        if(SortId < Columns.length())
        {
            Sort.IsNull = false;
            Sort.OrderIsAsc = SortOrder == Asc;
            Sort.ColumnId = Columns.at(SortId).Id;
        }
    }
    res.Sort = Sort;
    res.Filter = Filters;
    return res;
}


void DatabaseAdminTable::on_AddItem_clicked()
{
    DatabaseAdminItemEdit d;
    QStringList GroupsListNames;
    QList<QString> GroupsListIds;
    GroupsListIds.append("-1");
    GroupsListNames.append(tr("None"));

    int index = -1;
    int i = 1;
    foreach(DatabaseGroupWidget* Group, *AllGroups)
    {
        if(Group->GetId()!="-1" && Group->GetId()!="-2")
        {
            GroupsListNames.append(Group->GetName());
            GroupsListIds.append(Group->GetId());
            if(index == -1)
            {
                foreach(DatabaseGroup g, Groups)
                {

                    if(Group->GetId() == g.Id)
                    {
                        index = i;
                        break;
                    }
                }
            }
            i++;
        }


    }
    d.SetGroupList(GroupsListNames);

    if(index>=0)
        d.SetSelectedGroup(index);

    QList<DatabaseColumn> columns = DatabaseConnector->GetColumns(TableId);

    d.SetColumns(columns);





    if(d.exec())
    {
        DatabaseGroups GroupIds;
        GroupIds.IsNull = false;
        QString GroupId = GroupsListIds[d.GetSelectedIndex()];
        if(GroupId != "-1" && GroupId != "-2")
            GroupIds.GroupIdList.append(GroupId);
        if(!DatabaseConnector->IsConnected())
        {
            QEventLoop loop;
            connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
            loop.exec();
        }

        DatabaseConnector->Insert(GroupIds,d.GetDatabaseItem(),TableId);
        Reload();
    }
}

void DatabaseAdminTable::on_NextPageButton_clicked()
{

    if(PageNumber<TotalPages)
    {
        PageNumber ++;
        Reload();
    }
}

void DatabaseAdminTable::on_PreviousPageButton_clicked()
{
    if(PageNumber > 1)
    {
        PageNumber --;
        Reload();
    }
}

void DatabaseAdminTable::on_FirstPageButton_clicked()
{
    if(PageNumber > 1)
    {
        PageNumber = 1;
        Reload();
    }
}

void DatabaseAdminTable::on_LastPageButton_clicked()
{

    if(PageNumber!=TotalPages)
    {
        PageNumber = TotalPages;
        Reload();
    }
}

void DatabaseAdminTable::on_DataTable_itemSelectionChanged()
{
    if(!ReactRowSelectionChange)
        return;


    if(!IsInverseSelection)
    {
        foreach(QVariant id, CurrentPageIds)
            SelectedRows.remove(id.toString());
    }else
    {
        foreach(QVariant id, CurrentPageIds)
            SelectedRows.insert(id.toString());
    }

    QList<QModelIndex> Indexes = ui->DataTable->selectionModel()->selection().indexes();
    //ui->DataToolbar->clearSelection();
    foreach(QModelIndex Index,Indexes)
    {
        if(Index.row()>=CurrentPageIds.length()||Index.row()<0)
            continue;
        if(!IsInverseSelection)
        {
            SelectedRows.insert(CurrentPageIds[Index.row()].toString());
        }else
        {

            SelectedRows.remove(CurrentPageIds[Index.row()].toString());
        }
        //ui->DataToolbar->selectRow(Index.row());
    }
    GetSelectedNumber();
}



void DatabaseAdminTable::on_SelectNone_clicked()
{
    ReactRowSelectionChange = false;
    ui->DataTable->clearSelection();
    //ui->DataToolbar->clearSelection();
    ReactRowSelectionChange = true;
    IsInverseSelection = false;
    SelectedRows.clear();
    GetSelectedNumber();
}

void DatabaseAdminTable::on_SelectAll_clicked()
{
    ReactRowSelectionChange = false;
    ui->DataTable->clearSelection();
    //ui->DataToolbar->clearSelection();
    ui->DataTable->selectAll();
    /*for(int i = 0;i<ui->DataToolbar->rowCount();i++)
    {
        ui->DataToolbar->selectRow(i);
    }*/
    ReactRowSelectionChange = true;
    IsInverseSelection = true;
    SelectedRows.clear();
    GetSelectedNumber();
}

int DatabaseAdminTable::GetSelectedNumber()
{
    int Number = 0;
    int NumberShow;
    if(!IsInverseSelection)
    {
        if(SelectedRows.size() == 0)
        {
            Number = TotalRows;
            NumberShow = 0;
        }else
        {
            Number = SelectedRows.size();
            NumberShow = Number;
        }
    }else
    {
        Number = TotalRows - SelectedRows.size();
        NumberShow = Number;
    }
    ui->TotalSelectedItems->setText(QString::number(NumberShow));
    return Number;
}

DatabaseMassSelector DatabaseAdminTable::PrepareSelector()
{
    DatabaseItems Items;
    Items.IsNull = false;
    Items.IsInverseSelection = IsInverseSelection;
    Items.SelectedRows = SelectedRows;
    if(!IsInverseSelection && SelectedRows.size() == 0)
    {
        Items.IsInverseSelection = true;
    }
    DatabaseGroups GroupIds;
    GroupIds.IsNull = false;
    foreach(DatabaseGroup Group, Groups)
    {
        GroupIds.GroupIdList.append(Group.Id);
    }

    DatabaseSort Sort;
    Sort.IsNull = true;
    if(SortId>=0)
    {
        QList<DatabaseColumn> Columns = DatabaseConnector->GetColumns(TableId);
        if(SortId < Columns.length())
        {
            Sort.IsNull = false;
            Sort.OrderIsAsc = SortOrder == Asc;
            Sort.ColumnId = Columns.at(SortId).Id;
        }
    }

    DatabaseMassSelector Selector;
    Selector.Filters = Filters;
    Selector.TableId = TableId;
    Selector.Items = Items;
    Selector.Groups = GroupIds;
    Selector.Sort = Sort;



    return Selector;
}

void DatabaseAdminTable::on_DeletSelected_clicked()
{
    DatabaseAdminItemModificationDialog d;
    d.SetQuestion(tr("Delete Rows") + "?");
    int Number = GetSelectedNumber();
    d.SetNumberRows(Number);
    if(d.exec())
    {



        {
            emit Deactivate();
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
            //connect(&watcher, SIGNAL(finished()), this, SIGNAL(Activate()));



            future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::Delete,PrepareSelector());
            watcher.setFuture(future);
            loop.exec();
        }

        //DatabaseConnector->Delete(Items,GroupIds,Filters,TableId);
        SelectedRows.clear();
        IsInverseSelection = false;
        Reload();

    }
}

void DatabaseAdminTable::MoveSelected(bool MoveOrCopy)
{
    DatabaseAdminMoveToGroup d;
    int Number = GetSelectedNumber();
    d.SetNumberRows(Number);
    QStringList GroupsListNames;
    QList<QString> GroupsListIds;
    foreach(DatabaseGroupWidget* Group, *AllGroups)
    {
        if(Group->GetId()!="-1" && Group->GetId()!="-2")
        {
            GroupsListNames.append(Group->GetName());
            GroupsListIds.append(Group->GetId());
        }
    }
    if(GroupsListNames.isEmpty())
    {
        QMessageBox::information(0, "", tr("Please Create Group First"));
        return;
    }
    d.SetGroups(GroupsListNames);
    if(d.exec())
    {




        {
            emit Deactivate();
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
            //connect(&watcher, SIGNAL(finished()), this, SIGNAL(Activate()));


            if(MoveOrCopy)
                future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::MoveToGroup,PrepareSelector(),GroupsListIds[d.GetSelectedGroupIndex()]);
            else
                future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::CopyToGroup,PrepareSelector(),GroupsListIds[d.GetSelectedGroupIndex()]);

            watcher.setFuture(future);
            loop.exec();
        }
        //DatabaseConnector->MoveToGroup(PrepareSelector(),GroupsListIds[d.GetSelectedGroupIndex()],MoveOrCopy);
        SelectedRows.clear();
        IsInverseSelection = false;
        Reload();

    }
}

void DatabaseAdminTable::on_MoveSelectedGroup_clicked()
{
    MoveSelected(true);
}

void DatabaseAdminTable::on_CopySelectedGroup_clicked()
{
    MoveSelected(false);
}

void DatabaseAdminTable::on_DeleteSelectedFromGroups_clicked()
{
    DatabaseAdminItemModificationDialog d;
    d.SetQuestion(tr("Remove From Gorups") + "?");
    int Number = GetSelectedNumber();
    d.SetNumberRows(Number);
    if(d.exec())
    {





        {
            emit Deactivate();
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
            //connect(&watcher, SIGNAL(finished()), this, SIGNAL(Activate()));



            future = QtConcurrent::run(DatabaseConnector, &IDatabaseConnector::DeleteFromAllGroups,PrepareSelector());
            watcher.setFuture(future);
            loop.exec();
        }
        //DatabaseConnector->DeleteFromAllGroups(PrepareSelector());
        SelectedRows.clear();
        IsInverseSelection = false;
        Reload();

    }
}

void DatabaseAdminTable::on_ReloadButton_clicked()
{
    Reload();
}

void DatabaseAdminTable::on_PageNumberLabel_clicked()
{
    bool ok;

    int val = QInputDialog::getInt(this, tr("Get Page Number"),tr("Page Number:"),PageNumber,1,TotalPages,1,&ok);
    if (ok)
    {
        PageNumber = val;
        Reload();
    }
}

void DatabaseAdminTable::SingleItemEdit(QString Index)
{
    DatabaseAdminItemEdit d;

    d.HideGroupBox();
    QList<DatabaseColumn> columns = DatabaseConnector->GetColumns(TableId);

    d.SetColumns(columns);

    bool found = false;
    DatabaseItem Item;
    foreach(DatabaseItem i, CurrentItems)
    {
        if(i.Id == Index)
        {
            Item = i;
            found = true;
            break;
        }
    }

    if(!found)
        return;

    d.SetDatabaseItem(Item);
    if(d.exec())
    {
        DatabaseItem ItemNew = d.GetDatabaseItem();
        ItemNew.IsNull = false;
        ItemNew.Id = Item.Id;
        if(!DatabaseConnector->IsConnected())
        {
            QEventLoop loop;
            connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
            loop.exec();
        }

        DatabaseConnector->Update(ItemNew,TableId);
        Reload();
    }
}
void DatabaseAdminTable::SingleItemDelete(QString Index)
{
    DatabaseAdminItemModificationDialog d;
    d.SetQuestion(tr("Delete Row") + "?");
    d.SetNumberRows(1);
    if(d.exec())
    {
        DatabaseItems Items;
        Items.IsNull = false;
        Items.IsInverseSelection = false;
        QSet<QString> sr = QSet<QString>()<<Index;
        Items.SelectedRows = sr;


        DatabaseGroups GroupIds;
        GroupIds.IsNull = false;
        foreach(DatabaseGroup Group, Groups)
        {
            GroupIds.GroupIdList.append(Group.Id);
        }

        DatabaseMassSelector Selector;
        Selector.Filters = Filters;
        Selector.TableId = TableId;
        Selector.Items = Items;
        Selector.Groups = GroupIds;
        if(!DatabaseConnector->IsConnected())
        {
            QEventLoop loop;
            connect(DatabaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
            loop.exec();
        }

        DatabaseConnector->Delete(Selector);
        SelectedRows.remove(Index);
        Reload();

    }
}


void DatabaseAdminTable::on_MenuButton2_clicked()
{
    QMenu myMenu;
    myMenu.addAction(ui->AddItem->icon(),ui->AddItem->text(),ui->AddItem, SLOT(click()));
    myMenu.addAction(ui->DeletSelected->icon(),ui->DeletSelected->text(),ui->DeletSelected, SLOT(click()));
    myMenu.addAction(ui->SelectAll->icon(),ui->SelectAll->text(),ui->SelectAll, SLOT(click()));
    myMenu.addAction(ui->SelectNone->icon(),ui->SelectNone->text(),ui->SelectNone, SLOT(click()));
    myMenu.addAction(ui->MoveSelectedGroup->icon(),ui->MoveSelectedGroup->text(),ui->MoveSelectedGroup, SLOT(click()));
    myMenu.addAction(ui->CopySelectedGroup->icon(),ui->CopySelectedGroup->text(),ui->CopySelectedGroup, SLOT(click()));
    myMenu.addAction(ui->DeleteSelectedFromGroups->icon(),ui->DeleteSelectedFromGroups->text(),ui->DeleteSelectedFromGroups, SLOT(click()));


    myMenu.exec(QCursor::pos());
}
