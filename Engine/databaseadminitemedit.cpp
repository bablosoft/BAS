#include "databaseadminitemedit.h"
#include "ui_databaseadminitemedit.h"

#include <QSpinBox>
#include <QCheckBox>
#include <QDateTimeEdit>
#include <QLineEdit>

DatabaseAdminItemEdit::DatabaseAdminItemEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseAdminItemEdit)
{
    ui->setupUi(this);
}


void DatabaseAdminItemEdit::SetColumns(QList<DatabaseColumn> Columns)
{
    this->Columns = Columns;
    foreach(DatabaseColumn Column, Columns)
    {
        QLabel *Label = new QLabel(this);
        Label->setText(Column.Description);
        QWidget *DataItem;
        switch(Column.Type)
        {
            case DatabaseColumn::String: {QLineEdit* e = new QLineEdit(this);e->setMaxLength(2147483647); DataItem = e;} break;
            case DatabaseColumn::Int: {QSpinBox * w = new QSpinBox(this);w->setMinimum(-1000000);w->setMaximum(1000000);DataItem = w;} break;
            case DatabaseColumn::Bool: DataItem = new QCheckBox(this); break;
            case DatabaseColumn::Date: DataItem = new QDateTimeEdit(this); break;

        }
        Widgets[Column.Id] = DataItem;
        ui->MainLayout->addRow(Label,DataItem);
    }
}

void DatabaseAdminItemEdit::HideGroupBox()
{
    ui->comboBox->setVisible(false);
}

void DatabaseAdminItemEdit::SetGroupList(QStringList Groups)
{
    ui->comboBox->addItems(Groups);
}

void DatabaseAdminItemEdit::SetSelectedGroup(int index)
{
    ui->comboBox->setCurrentIndex(index);
}

int DatabaseAdminItemEdit::GetSelectedIndex()
{
    return ui->comboBox->currentIndex();
}

DatabaseItem DatabaseAdminItemEdit::GetDatabaseItem()
{
    DatabaseItem res;
    int index = 0;
    foreach (DatabaseColumn Column, Columns)
    {
        QVariant val;
        QWidget*DataItem = Widgets[Column.Id];
        switch(Column.Type)
        {
            case DatabaseColumn::String: val = qobject_cast<QLineEdit*>(DataItem)->text(); break;
            case DatabaseColumn::Int: val = qobject_cast<QSpinBox*>(DataItem)->value(); break;
            case DatabaseColumn::Bool: val = qobject_cast<QCheckBox*>(DataItem)->isChecked(); break;
            case DatabaseColumn::Date: val = qobject_cast<QDateTimeEdit*>(DataItem)->dateTime(); break;

        }
        res.Data[Column.Id] = val;
        index++;
    }
    return res;
}

void DatabaseAdminItemEdit::SetDatabaseItem(DatabaseItem Item)
{
    foreach (DatabaseColumn Column, Columns)
    {
        QVariant val;
        bool found = false;
        QHashIterator<int,QVariant> i(Item.Data);
        while (i.hasNext())
        {
            i.next();
            if(i.key() == Column.Id)
            {
                val =  i.value();
                found = true;
                break;
            }
        }
        if(found)
        {
            QWidget*DataItem = Widgets[Column.Id];
            switch(Column.Type)
            {
                case DatabaseColumn::String: qobject_cast<QLineEdit*>(DataItem)->setText(val.toString()); break;
                case DatabaseColumn::Int: qobject_cast<QSpinBox*>(DataItem)->setValue(val.toInt()); break;
                case DatabaseColumn::Bool: qobject_cast<QCheckBox*>(DataItem)->setChecked(val.toBool()); break;
                case DatabaseColumn::Date: qobject_cast<QDateTimeEdit*>(DataItem)->setDateTime(val.toDateTime()); break;

            }
        }


    }
}

DatabaseAdminItemEdit::~DatabaseAdminItemEdit()
{
    delete ui;
}
