#include "designchooserresourcewidget.h"
#include "ui_designchooserresourcewidget.h"

#include "every_cpp.h"

DesignChooserResourceWidget::DesignChooserResourceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DesignChooserResourceWidget)
{
    ui->setupUi(this);
    DatabaseDrag = new DragSection(ui->page_9);
    DatabaseDrag->setObjectName("DatabaseColumns");
    ui->DatabaseDragLayout->addWidget(DatabaseDrag);
    setCurrentIndex(0);
}

void DesignChooserResourceWidget::SetDatabaseState(IDatabaseState *DatabaseState)
{
    this->DatabaseState = DatabaseState;

    GroupsChanged();
    connect(ui->TableCombobox,SIGNAL(activated(int)),this,SLOT(TableIdChanged()));
    TableIdChanged();
}

void DesignChooserResourceWidget::TableIdChanged()
{
    emit TableIdChanged(ui->TableCombobox->currentData().toInt());
}

void DesignChooserResourceWidget::GroupsChanged()
{
    ui->TableCombobox->clear();
    foreach(DatabaseTable Table, DatabaseState->GetDatabaseTables())
    {
        ui->TableCombobox->addItem(Table.Description, Table.Id);
    }
}


DesignChooserResourceWidget::~DesignChooserResourceWidget()
{
    delete ui;
}



void DesignChooserResourceWidget::setCurrentIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    int size = ui->stackedWidget->count();
    for(int i = 0;i<size;i++)
        ui->stackedWidget->widget(i)->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);


    QWidget* Widget = ui->stackedWidget->widget(index);
    Widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    Widget->adjustSize();
    ui->stackedWidget->adjustSize();
}



QWidget* DesignChooserResourceWidget::GetTemplateWidgetByIndex(int index)
{
    return ui->stackedWidget->widget(index);
}

void DesignChooserResourceWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DesignChooserResourceWidget::on_TableCombobox_currentIndexChanged(int index)
{
    QStringList Columns;
    ColumnsData = DatabaseState->GetColumns(ui->TableCombobox->currentData().toInt());
    foreach(DatabaseColumn Column, ColumnsData)
    {
        Columns.append(Column.Description);
    }
    DatabaseDrag->SetData(Columns, QList<int>());

}

QList<int> DesignChooserResourceWidget::GetDatabaseColumnsIds()
{
    QList<int> res;
    foreach(int index, DatabaseDrag->SelectedItems())
    {
        if(index>=0 && index<ColumnsData.length())
            res.append(ColumnsData[index].Id);
    }
    return res;
}

void DesignChooserResourceWidget::SetDatabaseColumnsIds(const QList<int>& ColumnIds)
{
    DatabaseDrag->Clear();
    QList<int> Selected;
    QStringList Columns;

    int index = 0;
    foreach(DatabaseColumn Column, ColumnsData)
    {
        Columns.append(Column.Description);
        if(ColumnIds.contains(Column.Id))
            Selected.append(index);
        index ++;
    }
    DatabaseDrag->SetData(Columns, Selected);

}
