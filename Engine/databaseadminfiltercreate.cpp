#include "databaseadminfiltercreate.h"
#include "ui_databaseadminfiltercreate.h"
#include <QSpinBox>
#include <QDateTimeEdit>
#include <QLineEdit>

DatabaseAdminFilterCreate::DatabaseAdminFilterCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseAdminFilterCreate)
{
    ui->setupUi(this);
    Widget = 0;
}

void DatabaseAdminFilterCreate::SetColumns(QList<DatabaseColumn> Columns)
{
    this->Columns = Columns;
    ui->ComboColumn->clear();
    foreach(DatabaseColumn Column,Columns)
    {
        ui->ComboColumn->addItem(Column.Description,Column.Id);
    }
}

DatabaseAdminFilterCreate::~DatabaseAdminFilterCreate()
{
    delete ui;
}

void DatabaseAdminFilterCreate::on_ComboColumn_currentIndexChanged(int index)
{
    ui->ComboType->clear();
    DatabaseColumn Column = Columns[index];
    switch(Column.Type)
    {
        case DatabaseColumn::String:
        {
            ui->ComboType->addItem(tr("Not Empty"));
            ui->ComboType->addItem(tr("Empty"));
            ui->ComboType->addItem(tr("Contains"));
        }break;
        case DatabaseColumn::Int:
        {
            ui->ComboType->addItem(tr("Is Equal ="));
            ui->ComboType->addItem(tr("Not Equal <>"));
            ui->ComboType->addItem(tr("Greater Than >"));
            ui->ComboType->addItem(tr("Less Than <"));
            ui->ComboType->addItem(tr("Greater Or Equal >="));
            ui->ComboType->addItem(tr("Less Or Equal <="));
        }break;
        case DatabaseColumn::Date:
        {
            ui->ComboType->addItem(tr("Earlier Than"));
            ui->ComboType->addItem(tr("Later Than"));
            ui->ComboType->addItem(tr("Same Year As In"));
            ui->ComboType->addItem(tr("Same Month As In"));
            ui->ComboType->addItem(tr("Same Day As In"));
            ui->ComboType->addItem(tr("Same Hour As In"));
        }break;
        case DatabaseColumn::Bool:
        {
            ui->ComboType->addItem(tr("Is True"));
            ui->ComboType->addItem(tr("Is False"));
        }break;
    }
}

void DatabaseAdminFilterCreate::on_ComboType_currentIndexChanged(int index)
{
    if(Widget)
    {
        delete Widget;
        Widget = 0;
    }
    DatabaseColumn Column = Columns[ui->ComboColumn->currentIndex()];
    switch(Column.Type)
    {
        case DatabaseColumn::String:
        {
            if(index == 2)
            {
                Widget = new QLineEdit();
            }
        }break;
        case DatabaseColumn::Int:
        {
            QSpinBox * w= new QSpinBox();
            w->setMinimum(-1000000);
            w->setMaximum(1000000);
            Widget = w;
        }break;
        case DatabaseColumn::Date:
        {
            Widget = new QDateTimeEdit(QDateTime::currentDateTime());

        }break;
        case DatabaseColumn::Bool:
        {

        }break;
    }
    if(Widget)
    {
        Widget->setParent(ui->DataWidget);
        ui->DataLayout->addWidget(Widget);
    }
    ui->LabelData->setVisible(Widget);

}

DatabaseFilter DatabaseAdminFilterCreate::GetFilter()
{
    DatabaseColumn Column = Columns[ui->ComboColumn->currentIndex()];
    DatabaseFilter res;
    res.ColumnId = Column.Id;
    int TypeIndex = ui->ComboType->currentIndex();
    switch(Column.Type)
    {
        case DatabaseColumn::String:
        {
            switch(TypeIndex)
            {
                case 0: res.Type = DatabaseFilter::StringNotEmpty;return res;
                case 1: res.Type = DatabaseFilter::StringEmpty;return res;
                case 2: res.Type = DatabaseFilter::StringContains; res.Data = qobject_cast<QLineEdit *>(Widget)->text(); return res;
            }
        }break;
        case DatabaseColumn::Int:
        {
            res.Data = qobject_cast<QSpinBox *>(Widget)->value();
            switch(TypeIndex)
            {
                case 0: res.Type = DatabaseFilter::IntEquals;return res;
                case 1: res.Type = DatabaseFilter::IntNotEquals;return res;
                case 2: res.Type = DatabaseFilter::IntGreater;return res;
                case 3: res.Type = DatabaseFilter::IntLessThan;return res;
                case 4: res.Type = DatabaseFilter::IntGreaterOrEqual;return res;
                case 5: res.Type = DatabaseFilter::IntLessThanOrEqual;return res;

            }
        }break;
        case DatabaseColumn::Date:
        {
            res.Data = qobject_cast<QDateTimeEdit *>(Widget)->dateTime();

            switch(TypeIndex)
            {
                case 0: res.Type = DatabaseFilter::DateIsLessThan;return res;
                case 1: res.Type = DatabaseFilter::DateGreaterThan;return res;
                case 2: res.Type = DatabaseFilter::DateIsSameYear;return res;
                case 3: res.Type = DatabaseFilter::DateIsSameMonth;return res;
                case 4: res.Type = DatabaseFilter::DateIsSameMonth;return res;
                case 5: res.Type = DatabaseFilter::DateIsSameHour;return res;
            }
        }break;
        case DatabaseColumn::Bool:
        {
        switch(TypeIndex)
        {
            case 0: res.Type = DatabaseFilter::BoolIsTrue;return res;
            case 1: res.Type = DatabaseFilter::BoolIsFalse;return res;
        }
        }break;
    }
}

QString DatabaseAdminFilterCreate::GetFilterText()
{
    DatabaseColumn Column = Columns[ui->ComboColumn->currentIndex()];
    QString res;
    int TypeIndex = ui->ComboType->currentIndex();
    switch(Column.Type)
    {
        case DatabaseColumn::String:
        {
            switch(TypeIndex)
            {
                case 0: res = QString(tr("%1 Is Not Empty")).arg(Column.Description);return res;
                case 1: res = QString(tr("%1 Is Empty")).arg(Column.Description);return res;
                case 2: res = QString(tr("%1 Contains %2")).arg(Column.Description).arg(qobject_cast<QLineEdit *>(Widget)->text()); return res;
            }
        }break;
        case DatabaseColumn::Int:
        {
            int Number = qobject_cast<QSpinBox *>(Widget)->value();
            switch(TypeIndex)
            {
                case 0: res = QString(tr("%1 = %2")).arg(Column.Description).arg(QString::number(Number));return res;
                case 1: res = QString(tr("%1 <> %2")).arg(Column.Description).arg(QString::number(Number));return res;
                case 2: res = QString(tr("%1 > %2")).arg(Column.Description).arg(QString::number(Number));return res;
                case 3: res = QString(tr("%1 < %2")).arg(Column.Description).arg(QString::number(Number));return res;
                case 4: res = QString(tr("%1 >= %2")).arg(Column.Description).arg(QString::number(Number));return res;
                case 5: res = QString(tr("%1 <= %2")).arg(Column.Description).arg(QString::number(Number));return res;

            }
        }break;
        case DatabaseColumn::Date:
        {
            QDateTime DateTime = qobject_cast<QDateTimeEdit *>(Widget)->dateTime();


            switch(TypeIndex)
            {
                case 0: res = QString(tr("%1 Earlier Than %2")).arg(Column.Description).arg(DateTime.toString("dd.MM.yyyy hh:mm"));return res;
                case 1: res = QString(tr("%1 Later Than %2")).arg(Column.Description).arg(DateTime.toString("dd.MM.yyyy hh:mm"));return res;
                case 2: res = QString(tr("%1 Same Year As %2")).arg(Column.Description).arg(DateTime.toString("yyyy"));return res;
                case 3: res = QString(tr("%1 Same Month As %2")).arg(Column.Description).arg(DateTime.toString("MM.yyyy"));return res;
                case 4: res = QString(tr("%1 Same Day As %2")).arg(Column.Description).arg(DateTime.toString("dd.MM.yyyy"));return res;
                case 5: res = QString(tr("%1 Same Hour As %2")).arg(Column.Description).arg(DateTime.toString("dd.MM.yyyy hh"));return res;
            }
        }break;
        case DatabaseColumn::Bool:
        {
            switch(TypeIndex)
            {
            case 0: res = QString(tr("%1 Is True")).arg(Column.Description);return res;
            case 1: res = QString(tr("%1 Is False")).arg(Column.Description);return res;
            }
        }break;
    }
}
