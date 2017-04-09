#include "databaseschemaeditordialog.h"
#include <QMenu>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include "ui_databaseschemaeditordialog.h"
#include "databaseschemaeditorcolumndialog.h"

DatabaseSchemaEditorDialog::DatabaseSchemaEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseSchemaEditorDialog)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 4);
    ui->splitter->setStretchFactor(1, 10);
    ui->widget_3->hide();

    ui->listWidget->setVisible(false);
    ui->label_4->setVisible(false);

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ShowContextMenu(QPoint)));
    ui->listWidget_2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget_2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ShowContextMenu2(QPoint)));
    connect(ui->listWidget_2, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(EditItem2()));

    connect(ui->listWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(TableChanged()));

    Menu = new QMenuBar(this);
    QMenu *FileMenu = Menu->addMenu(tr("File"));
    QAction * RawMode = FileMenu->addAction(tr("Raw mode"));
    QAction * ConstructorMode = FileMenu->addAction(tr("Constructor mode"));
    connect(RawMode,SIGNAL(triggered(bool)),this,SLOT(RawMode()));
    connect(ConstructorMode,SIGNAL(triggered(bool)),this,SLOT(ConstructorMode()));
    this->layout()->setMenuBar(Menu);
    ui->pushButton->setVisible(false);
}

void DatabaseSchemaEditorDialog::RawMode()
{
    if(ui->stackedWidget->currentIndex() == 0)
    {
        ui->plainTextEdit->setPlainText(GetXml());
    }
    ui->stackedWidget->setCurrentIndex(1);
}

void DatabaseSchemaEditorDialog::ConstructorMode()
{
    if(ui->stackedWidget->currentIndex() == 1)
    {
        ParseXml(ui->plainTextEdit->toPlainText());
    }
    ui->stackedWidget->setCurrentIndex(0);

}

QString DatabaseSchemaEditorDialog::GetXml()
{
    QString WriteString;
    QXmlStreamWriter xmlWriter(&WriteString);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartElement("DataBase");
    for(Table &t:_Model.Tables)
    {
        xmlWriter.writeStartElement("Table");
        xmlWriter.writeAttribute("id",QString::number(t.Id));
        xmlWriter.writeAttribute("name",t.Name);
        xmlWriter.writeAttribute("description_en",t.DescriptionEn);
        xmlWriter.writeAttribute("description_ru",t.DescriptionRu);
        for(Column &c:t.Columns)
        {
            xmlWriter.writeStartElement("Column");
            xmlWriter.writeAttribute("id",QString::number(c.Id));
            xmlWriter.writeAttribute("name",c.Name);
            xmlWriter.writeAttribute("description_en",c.DescriptionEn);
            xmlWriter.writeAttribute("description_ru",c.DescriptionRu);
            xmlWriter.writeAttribute("type",c.Type);
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();

    return WriteString;
}

void DatabaseSchemaEditorDialog::ParseXml(const QString& Xml)
{
    _Model.Tables.clear();
    ui->listWidget->clear();
    ui->listWidget_2->clear();

    TableIndex = 1;

    QXmlStreamReader xmlReader(Xml);

    Table t;
    bool first = true;
    while(!xmlReader.atEnd() && !xmlReader.hasError())
    {
        QXmlStreamReader::TokenType token = xmlReader.readNext();

        if(xmlReader.name() == "Table" && token == QXmlStreamReader::StartElement)
        {
            if(!first)
            {
                _Model.Tables.append(t);
                QListWidgetItem *item = new QListWidgetItem(t.Name, ui->listWidget);
                item->setIcon(QIcon(":/engine/images/table.png"));
                item->setSizeHint(QSize(item->sizeHint().width(), 50));
                item->setData(Qt::UserRole,t.Id);
                ui->listWidget->addItem(item);
            }
            t.Id = 0;
            t.DescriptionEn.clear();
            t.DescriptionRu.clear();
            t.Name.clear();
            t.Columns.clear();
            first = false;
            foreach(QXmlStreamAttribute attr, xmlReader.attributes())
            {
                if(attr.name() == "id")
                {
                    t.Id = attr.value().toInt();
                }
                if(attr.name() == "name")
                {
                    t.Name = attr.value().toString();
                }
                if(attr.name() == (QString("description_en")))
                {
                    t.DescriptionEn = attr.value().toString();
                }
                if(attr.name() == (QString("description_ru")))
                {
                    t.DescriptionRu = attr.value().toString();
                }

            }
        }
        if(xmlReader.name() == "Column" && token == QXmlStreamReader::StartElement)
        {
            Column c;
            foreach(QXmlStreamAttribute attr, xmlReader.attributes())
            {
                if(attr.name() == "id")
                {
                    c.Id = attr.value().toInt();
                }
                if(attr.name() == "name")
                {
                    c.Name = attr.value().toString();
                }
                if(attr.name() == (QString("description_en")))
                {
                    c.DescriptionEn = attr.value().toString();
                }
                if(attr.name() == (QString("description_ru")))
                {
                    c.DescriptionRu = attr.value().toString();
                }
                if(attr.name() == "type")
                {
                    c.Type = attr.value().toString();
                }
            }
            t.Columns.append(c);
        }
    }
    if(!xmlReader.hasError())
    {
        _Model.Tables.append(t);
        QListWidgetItem *item = new QListWidgetItem(t.Name, ui->listWidget);
        item->setIcon(QIcon(":/engine/images/table.png"));
        item->setSizeHint(QSize(item->sizeHint().width(), 50));
        item->setData(Qt::UserRole,t.Id);
        ui->listWidget->addItem(item);
    }

    if(_Model.Tables.length()> 0)
        ui->listWidget->setCurrentRow(0);

    TableChanged();
}



void DatabaseSchemaEditorDialog::TableChanged()
{
    ui->listWidget->setVisible(_Model.Tables.length() > 0);
    ui->label_4->setVisible(_Model.Tables.length() > 0);
    ui->pushButton->setVisible(_Model.Tables.length() > 0);
    ui->widget_3->setVisible(_Model.Tables.length() > 0);
    if(ui->listWidget->currentRow() >= 0)
    {
        ui->TableName->setText(_Model.Tables[ui->listWidget->currentRow()].Name);
        ui->TableDescriptionEn->setText(_Model.Tables[ui->listWidget->currentRow()].DescriptionEn);
        ui->TableDescriptionRu->setText(_Model.Tables[ui->listWidget->currentRow()].DescriptionRu);
        CurrentTableId = _Model.Tables[ui->listWidget->currentRow()].Id;
        ui->listWidget_2->clear();

        for(Column &c : _Model.Tables[ui->listWidget->currentRow()].Columns)
        {
            QListWidgetItem *item = new QListWidgetItem(c.Name + QString(" (") + c.Type + QString(")"), ui->listWidget_2);
            item->setIcon(QIcon(":/engine/images/column.png"));
            item->setSizeHint(QSize(item->sizeHint().width(), 50));
            item->setData(Qt::UserRole,c.Id);
            ui->listWidget_2->addItem(item);
        }
    }

}

void DatabaseSchemaEditorDialog::ShowContextMenu(const QPoint &pos)
{
    if(ui->listWidget->currentRow()<0)
        return;
    QPoint globalPos = ui->listWidget->mapToGlobal(pos);
    QMenu myMenu;
    myMenu.addAction(QIcon(":/engine/images/up.png"),QString(tr("Move up ")) + ui->listWidget->currentItem()->data(Qt::DisplayRole).toString(),  this, SLOT(MoveUp()));
    myMenu.addAction(QIcon(":/engine/images/down.png"),QString(tr("Move down ")) + ui->listWidget->currentItem()->data(Qt::DisplayRole).toString(),  this, SLOT(MoveDown()));
    myMenu.addAction(QIcon(":/engine/images/close_gray.png"),QString(tr("Erase ")) + ui->listWidget->currentItem()->data(Qt::DisplayRole).toString(),  this, SLOT(EraseItem()));

    myMenu.exec(globalPos);
}

void DatabaseSchemaEditorDialog::MoveUp()
{
    int row = ui->listWidget->currentRow();
    ui->listWidget->insertItem(row - 1, ui->listWidget->takeItem(row));
    if(row <= ui->listWidget->count() - 1 && row - 1 >= 0)
        _Model.Tables.swap(row,row-1);
    row--;
    if(row < 0)
        row = 0;
    ui->listWidget->setCurrentRow(row);
    TableChanged();
}

void DatabaseSchemaEditorDialog::MoveDown()
{
    int row = ui->listWidget->currentRow();
    ui->listWidget->insertItem(row + 1, ui->listWidget->takeItem(row));
    if(row + 1 <= ui->listWidget->count() - 1 && row >= 0)
        _Model.Tables.swap(row,row+1);
    row++;
    if(row > ui->listWidget->count() - 1)
        row = ui->listWidget->count() - 1;
    ui->listWidget->setCurrentRow(row);
    TableChanged();
}
void DatabaseSchemaEditorDialog::MoveUp2()
{
    int row = ui->listWidget_2->currentRow();
    ui->listWidget_2->insertItem(row - 1, ui->listWidget_2->takeItem(row));
    if(row <= ui->listWidget_2->count() - 1 && row - 1 >= 0)
        _Model.Tables[ui->listWidget->currentRow()].Columns.swap(row,row-1);
    row--;
    if(row < 0)
        row = 0;
    ui->listWidget_2->setCurrentRow(row);
}

void DatabaseSchemaEditorDialog::MoveDown2()
{
    int row = ui->listWidget_2->currentRow();
    ui->listWidget_2->insertItem(row + 1, ui->listWidget_2->takeItem(row));
    if(row + 1<= ui->listWidget_2->count() - 1 && row >= 0)
        _Model.Tables[ui->listWidget->currentRow()].Columns.swap(row,row+1);
    row++;
    if(row > ui->listWidget_2->count() - 1)
        row = ui->listWidget_2->count() - 1;
    ui->listWidget_2->setCurrentRow(row);

}



void DatabaseSchemaEditorDialog::ShowContextMenu2(const QPoint &pos)
{
    if(ui->listWidget_2->currentRow()<0)
        return;
    QPoint globalPos = ui->listWidget_2->mapToGlobal(pos);
    QMenu myMenu;
    myMenu.addAction(QIcon(":/engine/images/up.png"),QString(tr("Move up ")) + ui->listWidget_2->currentItem()->data(Qt::DisplayRole).toString(),  this, SLOT(MoveUp2()));
    myMenu.addAction(QIcon(":/engine/images/down.png"),QString(tr("Move down ")) + ui->listWidget_2->currentItem()->data(Qt::DisplayRole).toString(),  this, SLOT(MoveDown2()));
    myMenu.addAction(QIcon(":/engine/images/edit.png"),QString(tr("Edit ")) + ui->listWidget_2->currentItem()->data(Qt::DisplayRole).toString(),  this, SLOT(EditItem2()));
    myMenu.addAction(QIcon(":/engine/images/close_gray.png"),QString(tr("Erase ")) + ui->listWidget_2->currentItem()->data(Qt::DisplayRole).toString(),  this, SLOT(EraseItem2()));

    myMenu.exec(globalPos);
}

void DatabaseSchemaEditorDialog::EditItem2()
{
    DatabaseSchemaEditorColumnDialog dialog;
    Column &cp = _Model.Tables[ui->listWidget->currentRow()].Columns[ui->listWidget_2->currentRow()];
    dialog.SetDescriptionEn(cp.DescriptionEn);
    dialog.SetDescriptionRu(cp.DescriptionRu);
    dialog.SetType(cp.Type);
    dialog.SetName(cp.Name);
    dialog.exec();
    if(dialog.GetIsSuccess())
    {
        cp.Name = dialog.GetName();
        cp.DescriptionEn = dialog.GetDescriptionEn();
        cp.DescriptionRu = dialog.GetDescriptionRu();
        cp.Type = dialog.GetType();
        ui->listWidget_2->item(ui->listWidget_2->currentRow())->setData(Qt::DisplayRole,cp.Name + QString(" (") + cp.Type + QString(")"));
    }
}

void DatabaseSchemaEditorDialog::EraseItem2()
{
    for (int i = 0; i < ui->listWidget_2->selectedItems().size(); ++i)
    {
        QListWidgetItem *item = ui->listWidget_2->takeItem(ui->listWidget_2->currentRow());
        QMutableListIterator<Column> it(_Model.Tables[ui->listWidget->currentRow()].Columns);
        while (it.hasNext())
        {
            if (it.next().Id == item->data(Qt::UserRole).toInt())
                it.remove();
        }
        delete item;
    }
}

void DatabaseSchemaEditorDialog::EraseItem()
{
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowIcon(QIcon(":/engine/images/Logo.png"));
    msgBox.setText(tr("Are you sure, that you want to delete table?"));
    if(msgBox.exec() != QMessageBox::Ok)
    {
        return;
    }

    for (int i = 0; i < ui->listWidget->selectedItems().size(); ++i)
    {
        QListWidgetItem *item = ui->listWidget->takeItem(ui->listWidget->currentRow());
        QMutableListIterator<Table> it(_Model.Tables);
        while (it.hasNext())
        {
            if (it.next().Id == item->data(Qt::UserRole).toInt())
                it.remove();
        }
        delete item;
    }
    TableChanged();
}

DatabaseSchemaEditorDialog::~DatabaseSchemaEditorDialog()
{
    delete ui;
}

void DatabaseSchemaEditorDialog::on_pushButton_3_clicked()
{
    Table t;
    t.Id = GetMaxTableId();
    t.Name = QString("table") + QString::number(TableIndex++);
    _Model.Tables.append(t);
    QListWidgetItem *item = new QListWidgetItem(t.Name, ui->listWidget);
    item->setIcon(QIcon(":/engine/images/table.png"));
    item->setSizeHint(QSize(item->sizeHint().width(), 50));
    item->setData(Qt::UserRole,t.Id);
    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentRow(_Model.Tables.length() - 1);

}

void DatabaseSchemaEditorDialog::on_pushButton_2_clicked()
{
    this->close();
}

void DatabaseSchemaEditorDialog::on_pushButton_clicked()
{
    if(ui->stackedWidget->currentIndex() == 1)
    {
        ParseXml(ui->plainTextEdit->toPlainText());
    }
    IsAccept = true;
    this->close();
}

bool DatabaseSchemaEditorDialog::GetIsAccept()
{
    return IsAccept;
}


void DatabaseSchemaEditorDialog::on_TableName_textEdited(const QString &arg1)
{
    QMutableListIterator<Table> it(_Model.Tables);
    while (it.hasNext())
    {
        if (it.next().Id == CurrentTableId)
        {
            Table t = it.value();
            t.Name = arg1;
            it.setValue(t);
        }
    }
    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        if(CurrentTableId == ui->listWidget->item(i)->data(Qt::UserRole).toInt())
        {
            ui->listWidget->item(i)->setText(arg1);
        }

    }
}

void DatabaseSchemaEditorDialog::on_TableDescriptionEn_textEdited(const QString &arg1)
{
    QMutableListIterator<Table> it(_Model.Tables);
    while (it.hasNext())
    {
        if (it.next().Id == CurrentTableId)
        {
            Table t = it.value();
            t.DescriptionEn = arg1;
            it.setValue(t);
        }
    }
}

void DatabaseSchemaEditorDialog::on_TableDescriptionRu_textEdited(const QString &arg1)
{
    QMutableListIterator<Table> it(_Model.Tables);
    while (it.hasNext())
    {
        if (it.next().Id == CurrentTableId)
        {
            Table t = it.value();
            t.DescriptionRu = arg1;
            it.setValue(t);
        }
    }
}

void DatabaseSchemaEditorDialog::on_pushButton_AddColumn_clicked()
{
    if(ui->listWidget->currentRow()<0)
        return;
    DatabaseSchemaEditorColumnDialog dialog;
    dialog.exec();
    if(dialog.GetIsSuccess())
    {
        Column c;
        c.Name = dialog.GetName();
        c.DescriptionEn = dialog.GetDescriptionEn();
        c.DescriptionRu = dialog.GetDescriptionRu();
        Table &t = _Model.Tables[ui->listWidget->currentRow()];
        c.Id = GetMaxColumnId();
        c.Type = dialog.GetType();
        t.Columns.append(c);
        QListWidgetItem *item = new QListWidgetItem(c.Name + QString(" (") + c.Type + QString(")"), ui->listWidget_2);
        item->setIcon(QIcon(":/engine/images/column.png"));
        item->setSizeHint(QSize(item->sizeHint().width(), 50));
        item->setData(Qt::UserRole,c.Id);
        ui->listWidget_2->addItem(item);
    }
}

int DatabaseSchemaEditorDialog::GetMaxTableId()
{
    int res = 1;
    for(Table &t:_Model.Tables)
    {
        if(t.Id>=res)
            res = t.Id + 1;
        for(Column &c:t.Columns)
        {
            if(c.Id>=res)
                res = c.Id + 1;
        }
    }
    return res;
}
int DatabaseSchemaEditorDialog::GetMaxColumnId()
{
    int res = 1;
    for(Table &t:_Model.Tables)
    {
        if(t.Id>=res)
            res = t.Id + 1;
        for(Column &c:t.Columns)
        {
            if(c.Id>=res)
                res = c.Id + 1;
        }
    }
    return res;
}
