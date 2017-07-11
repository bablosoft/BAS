#include "userresourcewidget.h"
#include "ui_userresourcewidget.h"
#include <QApplication>
#include "classcomboboxfillpictures.h"
#include "every_cpp.h"
namespace BrowserAutomationStudioFramework
{

    UserResourceWidget::UserResourceWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::UserResourceWidget)
    {
        IsAdvanced = false;
        ui->setupUi(this);
        ComboBoxData<<"FixedString"<<"FixedInteger"<<"RandomString"<<"RandomInteger"<<"Select"<<"LinesFromFile"<<"LinesFromUrl"<<"FilesFromDirectory"<<"Database";
        connect(ui->comboBox, SIGNAL(activated(int)), ui->widget, SLOT(setCurrentIndex(int)));

        ClassComboBoxFillPictures Icons;
        Icons.AddIconsToCombobox(ui->comboBox);
        ui->widget->SetShowValidation(true);
        connect(ui->widget,SIGNAL(ValidationStateChanged()),this,SIGNAL(ValidationStateChanged()));

        //ui->Advanced->setVisible(true);
        //ui->widget->layout()->setAlignment(Qt::AlignLeft);
    }

    QList<int> UserResourceWidget::GetColumnIds()
    {
        return ColumnIds;
    }

    void UserResourceWidget::SetColumnIds(const QList<int>& ColumnIds)
    {
        this->ColumnIds = ColumnIds;
    }

    void UserResourceWidget::SetTableId(int TableId)
    {
        ui->widget->SetTableId(TableId);
    }

    int UserResourceWidget::GetTableId()
    {
        return ui->widget->GetTableId();
    }

    bool UserResourceWidget::GetIsAdvanced()
    {
        return IsAdvanced;
    }
    void UserResourceWidget::SetIsAdvanced(bool IsAdvanced)
    {
        this->IsAdvanced = IsAdvanced;
    }

    void UserResourceWidget::SetVisibleAdvanced(bool Visible)
    {
        ui->widget->SetVisibleAdvanced(Visible);
        this->adjustSize();
    }

    bool UserResourceWidget::IsValid()
    {
        return ui->widget->IsValid();
    }

    void UserResourceWidget::SetStringBuilder(IStringBuilder * val)
    {
        ui->widget->SetStringBuilder(val);
    }

    IStringBuilder * UserResourceWidget::GetStringBuilder()
    {
        return ui->widget->GetStringBuilder();
    }

    UserResourceWidget::~UserResourceWidget()
    {
        delete ui;
    }
    QString UserResourceWidget::GetVariableName()
    {
        return VariableName;
    }

    MultiLanguageString UserResourceWidget::GetDescription()
    {
        return Descrition;
    }

    void UserResourceWidget::SetLanguage(const QString& lang)
    {
        Language = lang;
        SetDescription(Descrition);
    }

    void UserResourceWidget::SetVariableName(const QString& text)
    {
        VariableName = text;
    }

    void UserResourceWidget::SetDescription(const MultiLanguageString& text)
    {
        Descrition = text;
        QString str = Descrition.GetTranslation(Language);
        ui->label_2->setText(str);

    }

    void UserResourceWidget::SetVisibleToUser(bool visible)
    {
        this->setVisible(visible);
    }

    void UserResourceWidget::SetEnabledToUser(bool enabled)
    {
        this->setEnabled(enabled);
    }

    int UserResourceWidget::FindComboBoxIndexByName(const QString& name)
    {
        int size = ui->comboBox->count(), index = -1;

        for(int i = 0;i<size;i++)
        {
            if(ComboBoxData.at(i) == name)
                index = i;
        }
        return index;
    }

    void UserResourceWidget::SetDatabaseState(IDatabaseState *DatabaseState)
    {
        ui->widget->SetDatabaseState(DatabaseState);
    }

    void UserResourceWidget::SetAvailableNames(const QString& text)
    {
        ui->NoChoiceLabel->setVisible(false);
        ui->NoChoiceIcon->setVisible(false);
        ui->comboBox->setVisible(true);

        bool FixedString = text.contains("FixedString");
        bool FixedInteger = text.contains("FixedInteger");
        bool RandomInteger = text.contains("RandomInteger");
        bool RandomString = text.contains("RandomString");
        bool Directory = text.contains("FilesFromDirectory");
        bool File = text.contains("LinesFromFile");
        bool Select = text.contains("Select");
        bool Url = text.contains("LinesFromUrl");
        bool Database = text.contains("Database");
        int position = -1;

        if(text == QString("All"))
        {
            FixedString = true;
            FixedInteger = true;
            RandomInteger = true;
            RandomString = true;
            Directory = true;
            File = true;
            Select = true;
            Url = true;
            Database = true;
        }
        if(!FixedString)
        {

            int index = FindComboBoxIndexByName("FixedString");
            if(index>=0)
            {
                ui->widget->RemoveWidgetAtIndex(index);
                ui->comboBox->removeItem(index);
                ComboBoxData.removeAt(index);
            }
        }else
        {
            position = 0;
        }

        if(!FixedInteger)
        {

            int index = FindComboBoxIndexByName("FixedInteger");
            if(index>=0)
            {
                ui->widget->RemoveWidgetAtIndex(index);
                ui->comboBox->removeItem(index);
                ComboBoxData.removeAt(index);
            }
        }else
        {
            position = 1;
        }

        if(!RandomInteger)
        {

            int index = FindComboBoxIndexByName("RandomInteger");
            if(index>=0)
            {
                ui->widget->RemoveWidgetAtIndex(index);
                ui->comboBox->removeItem(index);
                ComboBoxData.removeAt(index);
            }
        }else
        {
            position = 3;
        }

        if(!RandomString)
        {

            int index = FindComboBoxIndexByName("RandomString");
            if(index>=0)
            {
                ui->widget->RemoveWidgetAtIndex(index);
                ui->comboBox->removeItem(index);
                ComboBoxData.removeAt(index);
            }
        }else
        {
            position = 2;
        }
        if(!Directory)
        {

            int index = FindComboBoxIndexByName("FilesFromDirectory");
            if(index>=0)
            {
                ui->widget->RemoveWidgetAtIndex(index);
                ui->comboBox->removeItem(index);
                ComboBoxData.removeAt(index);
            }
        }else
        {
            position = 7;
        }

        if(!File)
        {

            int index = FindComboBoxIndexByName("LinesFromFile");
            if(index>=0)
            {
                ui->widget->RemoveWidgetAtIndex(index);
                ui->comboBox->removeItem(index);
                ComboBoxData.removeAt(index);
            }
        }
        else
        {
            position = 5;
        }
        if(!Url)
        {

            int index = FindComboBoxIndexByName("LinesFromUrl");
            if(index>=0)
            {
                ui->widget->RemoveWidgetAtIndex(index);
                ui->comboBox->removeItem(index);
                ComboBoxData.removeAt(index);
            }
        }else
        {
            position = 6;
        }
        if(!Select)
        {

            int index = FindComboBoxIndexByName("Select");
            if(index>=0)
            {
                ui->widget->RemoveWidgetAtIndex(index);
                ui->comboBox->removeItem(index);
                ComboBoxData.removeAt(index);
            }
        }
        else
        {
            position = 4;
        }

        if(!Database)
        {

            int index = FindComboBoxIndexByName("Database");
            if(index>=0)
            {
                ui->widget->RemoveWidgetAtIndex(index);
                ui->comboBox->removeItem(index);
                ComboBoxData.removeAt(index);
            }
        }
        else
        {
            position = 8;
        }

        if(ui->comboBox->count() == 1)
        {
            ClassComboBoxFillPictures Icons;
            QIcon icon = Icons.GetIconFor(position);
            int w = icon.availableSizes().at(0).width();
            int h = icon.availableSizes().at(0).height();
            ui->NoChoiceIcon->setPixmap(icon.pixmap(QSize(w,h)));
            ui->NoChoiceLabel->setVisible(false);
            ui->NoChoiceIcon->setVisible(false);
            ui->NoChoiceLabel->setText(ui->comboBox->currentText());
            //ui->label->setVisible(false);

            ui->comboBox->setVisible(false);
        }



    }

    bool UserResourceWidget::GetVisibleToUser()
    {
        return this->isVisibleTo(this->parentWidget());
    }

    bool UserResourceWidget::GetEnabledToUser()
    {
        return this->isEnabled();
    }

    QString UserResourceWidget::GetAvailableNames()
    {
        int size = ui->comboBox->count();
        QString res;
        for(int i = 0;i<size;i++)
        {
            if(!res.isEmpty())
            {
                res += ",";
            }
            res += ComboBoxData.at(i);
        }


        return res;
    }

    void UserResourceWidget::SetTypeId(const QString& type)
    {
        int index = FindComboBoxIndexByName(type);
        if(index>=0)
        {
            ui->comboBox->setCurrentIndex(index);
            ui->widget->setCurrentIndex(index);
        }
    }

    QString UserResourceWidget::GetTypeId()
    {
        return ComboBoxData.at(ui->comboBox->currentIndex());
    }

    QWidget* UserResourceWidget::GetTemplateWidgetByType(bool IsUser,const QString& type)
    {
        int index = FindComboBoxIndexByName(type);

        if(index<0)
            return 0;
        if(IsUser)
            return ui->widget->GetTemplateWidgetByIndex(index);

        return 0;
    }

    QWidget* UserResourceWidget::GetTemplateCurrentWidget(bool IsUser)
    {
        if(IsUser)
            return ui->widget->GetTemplateWidgetByIndex(ui->comboBox->currentIndex());

        return 0;
    }


    MultiLanguageString UserResourceWidget::GetSectionName()
    {
        return SectionName;
    }

    void UserResourceWidget::SetSectionName(const MultiLanguageString& SectionName)
    {
        this->SectionName = SectionName;
    }

    QString UserResourceWidget::GetVisibilityConditionVariable()
    {
        return VisibilityConditionVariable;
    }

    void UserResourceWidget::SetVisibilityConditionVariable(const QString& VisibilityConditionVariable)
    {
        this->VisibilityConditionVariable = VisibilityConditionVariable;
    }

    QString UserResourceWidget::GetVisibilityConditionValue()
    {
        return VisibilityConditionValue;
    }

    void UserResourceWidget::SetVisibilityConditionValue(const QString& VisibilityConditionValue)
    {
        this->VisibilityConditionValue = VisibilityConditionValue;
    }

    void UserResourceWidget::changeEvent(QEvent *e)
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

}
