#include "databasegroupwidget.h"
#include "ui_databasegroupwidget.h"
#include "databaseadmindeletegroup.h"
#include "databaseadmineditgroup.h"

DatabaseGroupWidget::DatabaseGroupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseGroupWidget)
{
    ui->setupUi(this);
    IsSelected = false;
    UpdateIsSelected();

}

DatabaseGroupWidget::~DatabaseGroupWidget()
{
    delete ui;
}

void DatabaseGroupWidget::SetName(const QString& Name)
{
    ui->NameLabel->setText(Name);
}
void DatabaseGroupWidget::SetDescription(const QString& Description)
{
    ui->DescriptionLabel->setText(Description);
}

QString DatabaseGroupWidget::GetName()
{
    return ui->NameLabel->text();
}
QString DatabaseGroupWidget::GetDescription()
{
    return ui->DescriptionLabel->text();
}

void DatabaseGroupWidget::SetId(QString Id)
{
    this->Id = Id;
    ui->EditButton->setVisible(Id!="-1" && Id!="-2");
    ui->DeleteButton->setVisible(Id!="-1");
    ui->CopyButton->setVisible(Id!="-1");

}

void DatabaseGroupWidget::SetFilter(const QString& Filter)
{
    this->Filter = Filter;
    this->setVisible(!IsFiltered());
}

bool DatabaseGroupWidget::IsFiltered()
{
    if(Filter.isEmpty())
        return false;

    QRegExp Regexp;
    Regexp.setPatternSyntax(QRegExp::Wildcard);
    Regexp.setPattern("*" + Filter + "*");
    Regexp.setCaseSensitivity(Qt::CaseInsensitive);
    return !(Regexp.exactMatch(GetName()) || Regexp.exactMatch(GetDescription()));

}


void DatabaseGroupWidget::on_EditButton_clicked()
{
    DatabaseAdminEditGroup g;
    g.SetName(ui->NameLabel->text());
    g.SetDescription(ui->DescriptionLabel->text());
    if(g.exec())
    {
        emit Edit(Id,g.GetName(),g.GetDescription());
        SetName(g.GetName());
        SetDescription(g.GetDescription());
    }


}

void DatabaseGroupWidget::on_CopyButton_clicked()
{
    DatabaseAdminEditGroup g;
    g.SetName(ui->NameLabel->text());
    g.SetDescription(ui->DescriptionLabel->text());
    if(g.exec())
    {
        emit Copy(Id,g.GetName(),g.GetDescription());
    }

}

void DatabaseGroupWidget::on_DeleteButton_clicked()
{
    DatabaseAdminDeleteGroup g;
    g.SetGroupList(ui->NameLabel->text());
    if(Id == "-2")
    {
        g.Disable(1);
        g.Disable(2);
    }
    if(g.exec())
    {
        switch(g.GetTaskType())
        {
            case 1: emit DeleteWithData(Id); break;
            case 2: emit DeleteWithoutData(Id); break;
            case 3: emit ClearData(Id); break;

        }

    }
}

QString DatabaseGroupWidget::GetId()
{
    return Id;
}


void DatabaseGroupWidget::SetSelected(bool IsSelected)
{
    this->IsSelected = IsSelected;
    UpdateIsSelected();
}

bool DatabaseGroupWidget::GetSelected()
{
    if(IsFiltered())
        return false;
    return this->IsSelected;
}

void DatabaseGroupWidget::UpdateIsSelected()
{
    if(IsSelected)
    {
        if(ColorSelected.isEmpty())
        {
            ColorSelected = QApplication::palette().color(QPalette::Base).name();
        }
        this->setStyleSheet(QString("QWidget{background-color:%1}").arg(ColorSelected));
    }else
    {
        if(ColorNotSelected.isEmpty())
        {
            ColorNotSelected = QApplication::palette().color(QPalette::Window).name();
        }
        this->setStyleSheet(QString("QWidget{background-color:%1}").arg(ColorNotSelected));
    }
}

void DatabaseGroupWidget::mouseReleaseEvent ( QMouseEvent * event )
{
    IsSelected = !IsSelected;
    emit Selected(Id,IsSelected);
    UpdateIsSelected();
}


