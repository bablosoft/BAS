#include "designresourcewidget.h"
#include "ui_designresourcewidget.h"
#include <QSpinBox>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QScrollArea>
#include <QRadioButton>
#include <QCheckBox>
#include <QComboBox>
#include "classcomboboxfillpictures.h"
#include "multiselect.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    DesignResourceWidget::DesignResourceWidget(QWidget *parent) :
        QGroupBox(parent),
        ui(new Ui::DesignResourceWidget)
    {
        ui->setupUi(this);
        ComboBoxData<<"FixedString"<<"FixedInteger"<<"RandomString"<<"RandomInteger"<<"Select"<<"LinesFromFile"<<"LinesFromUrl"<<"FilesFromDirectory"<<"Database";
        DescriptionTextBox = new MultiLanguageTextBox(this);
        SectionTextBox = new MultiLanguageTextBox(this);
        DescriptionTextBox->setMaximumWidth(175);
        DescriptionTextBox->setMinimumWidth(175);
        SectionTextBox->setMaximumWidth(175);
        SectionTextBox->setMinimumWidth(175);
        ui->descriptionLayout->addWidget(DescriptionTextBox);
        ui->sectionNameLayout->addWidget(SectionTextBox);
        connect(ui->comboBox, SIGNAL(activated(int)), ui->ChooserWidget, SLOT(setCurrentIndex(int)));
        connect(ui->comboBox, SIGNAL(activated(int)), ui->MoreChooserWidget, SLOT(setCurrentIndex(int)));
        connect(DescriptionTextBox, SIGNAL(textChanged(QString)), this, SLOT(DescriptionChanged(QString)));


        QSpinBox * EditMinumum = findChild<QSpinBox *>("EditMinimum");
        QSpinBox * EditMaximum = findChild<QSpinBox *>("EditMaximum");

        QSpinBox * EditMinimum_2 = findChild<QSpinBox *>("EditMinimum_2");
        QSpinBox * EditMaximum_2 = findChild<QSpinBox *>("EditMaximum_2");

        QPlainTextEdit * SelectValuesEdit = findChild<QPlainTextEdit *>("SelectValuesEdit");
        QComboBox * SelectTypeCombo = findChild<QComboBox *>("SelectTypeCombo");

        connect(ui->MoreChooserWidget, SIGNAL(TableIdChanged(int)),ui->ChooserWidget, SLOT(SetTableId(int)));

        connect(EditMinumum, SIGNAL(valueChanged(int)), this, SLOT(SetMinimum(int)));
        connect(EditMaximum, SIGNAL(valueChanged(int)), this, SLOT(SetMaximum(int)));

        connect(EditMinimum_2, SIGNAL(valueChanged(int)), this, SLOT(SetMinimum_2(int)));
        connect(EditMaximum_2, SIGNAL(valueChanged(int)), this, SLOT(SetMaximum_2(int)));

        connect(SelectValuesEdit, SIGNAL(textChanged()), this, SLOT(UpdateSelect()));
        connect(SelectTypeCombo, SIGNAL(activated(QString)), this, SLOT(UpdateSelect()));
        UpdateSelect();

        SetMinimum(EditMinumum->value());
        SetMaximum(EditMaximum->value());

        SetMinimum_2(EditMinimum_2->value());
        SetMaximum_2(EditMaximum_2->value());

        connect(this,SIGNAL(toggled(bool)),this,SLOT(deleteLater()));
        ui->horizontalLayout_3->setAlignment(Qt::AlignRight);
        ui->gridLayout->setAlignment(Qt::AlignRight);
        HideMore();

        ClassComboBoxFillPictures Icons;
        Icons.AddIconsToCombobox(ui->comboBox);

        ui->ChooserWidget->SetShowValidation(false);

    }



    void DesignResourceWidget::SetLanguageModel(ILanguageModel *Model)
    {
        LanguageModel = Model;
        DescriptionTextBox->SetLanguageModel(Model);
        SectionTextBox->SetLanguageModel(Model);
    }
    ILanguageModel * DesignResourceWidget::GetLanguageModel()
    {
        return LanguageModel;
    }

    void DesignResourceWidget::UpdateSelect()
    {
        QPlainTextEdit * SelectValuesEdit = findChild<QPlainTextEdit *>("SelectValuesEdit");
        QComboBox * SelectTypeCombo = findChild<QComboBox *>("SelectTypeCombo");
        QStringList list = SelectValuesEdit->toPlainText().split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
        QWidget* SelectWidget = findChild<QWidget *>("SelectWidget");
        MultiSelect *multi = SelectWidget->findChild<MultiSelect *>();
        if(!multi)
        {
            MultiSelect * Select = new MultiSelect(SelectWidget);
            SelectWidget->layout()->addWidget(Select);
            multi = Select;
        }
        multi->Update(SelectTypeCombo->currentText(),list, QList<int>());



    }

    void DesignResourceWidget::SetMaximum_2(int val)
    {
        QSpinBox * RandomIntegerMinumumValue = findChild<QSpinBox *>("RIMinimumValue");
        QSpinBox * RandomIntegerMaximumValue = findChild<QSpinBox *>("RIMaximumValue");
        RandomIntegerMinumumValue->setMaximum(val);
        RandomIntegerMaximumValue->setMaximum(val);
    }

    void DesignResourceWidget::SetMinimum_2(int val)
    {
        QSpinBox * RandomIntegerMinumumValue = findChild<QSpinBox *>("RIMinimumValue");
        QSpinBox * RandomIntegerMaximumValue = findChild<QSpinBox *>("RIMaximumValue");
        RandomIntegerMinumumValue->setMinimum(val);
        RandomIntegerMaximumValue->setMinimum(val);
    }

    void DesignResourceWidget::SetMinimum(int val)
    {
        findChild<QSpinBox *>("FixedIntegerValue")->setMinimum(val);
    }

    void DesignResourceWidget::SetMaximum(int val)
    {
        findChild<QSpinBox *>("FixedIntegerValue")->setMaximum(val);
    }

    void DesignResourceWidget::DescriptionChanged(const QString& str)
    {
        if(str.length()>30)
        {
            this->setTitle(str.left(30) + QString("..."));
        }else
        {
            this->setTitle(str);
        }

    }

    QString DesignResourceWidget::GetVariableName()
    {
        return ui->lineEdit->text();
    }

    MultiLanguageString DesignResourceWidget::GetDescription()
    {
        return DescriptionTextBox->GetText();
    }

    DesignResourceWidget::~DesignResourceWidget()
    {
        delete ui;
    }

    void DesignResourceWidget::SetVariableName(const QString& text)
    {
        ui->lineEdit->setText(text);
    }

    void DesignResourceWidget::SetDescription(const MultiLanguageString& text)
    {
        DescriptionTextBox->SetText(text);
        DescriptionChanged(DescriptionTextBox->GetCurrentText());
    }

    void DesignResourceWidget::SetVisibleToUser(bool visible)
    {
        ui->checkBox->setChecked(visible);
    }

    void DesignResourceWidget::SetEnabledToUser(bool enabled)
    {
        ui->checkBox_2->setChecked(enabled);
    }

    void DesignResourceWidget::SetAvailableNames(const QString& text)
    {
        bool FixedString = text.contains("FixedString");
        bool FixedInteger = text.contains("FixedInteger");
        bool RandomInteger = text.contains("RandomInteger");
        bool RandomString = text.contains("RandomString");
        bool Directory = text.contains("FilesFromDirectory");
        bool File = text.contains("LinesFromFile");
        bool Select = text.contains("Select");
        bool Url = text.contains("LinesFromUrl");
        bool Database = text.contains("Database");

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
        ui->checkBox_FixedString->setChecked(FixedString);
        ui->checkBox_FixedInteger->setChecked(FixedInteger);
        ui->checkBox_RandomInteger->setChecked(RandomInteger);
        ui->checkBox_RandomString->setChecked(RandomString);
        ui->checkBox_Directory->setChecked(Directory);
        ui->checkBox_File->setChecked(File);
        ui->checkBox_Select->setChecked(Select);
        ui->checkBox_Url->setChecked(Url);
        ui->checkBox_Database->setChecked(Database);

    }

    bool DesignResourceWidget::GetVisibleToUser()
    {
        return ui->checkBox->isChecked();
    }

    bool DesignResourceWidget::GetEnabledToUser()
    {
        return ui->checkBox_2->isChecked();
    }


    MultiLanguageString DesignResourceWidget::GetSectionName()
    {
        return SectionTextBox->GetText();
    }

    void DesignResourceWidget::SetSectionName(const MultiLanguageString& SectionName)
    {
        SectionTextBox->SetText(SectionName);
    }

    bool DesignResourceWidget::GetIsAdvanced()
    {
        return ui->CheckBoxIsAdvanced->isChecked();
    }

    void DesignResourceWidget::SetIsAdvanced(bool IsAdvanced)
    {
        ui->CheckBoxIsAdvanced->setChecked(IsAdvanced);
    }

    QString DesignResourceWidget::GetVisibilityConditionVariable()
    {
        return ui->lineEdit_VisibilityVariable->text();
    }

    void DesignResourceWidget::SetVisibilityConditionVariable(const QString& VisibilityConditionVariable)
    {
        ui->lineEdit_VisibilityVariable->setText(VisibilityConditionVariable);

    }

    QString DesignResourceWidget::GetVisibilityConditionValue()
    {
        return ui->lineEdit_VisibilityContains->text();
    }

    void DesignResourceWidget::SetVisibilityConditionValue(const QString& VisibilityConditionValue)
    {
        ui->lineEdit_VisibilityContains->setText(VisibilityConditionValue);

    }


    QString DesignResourceWidget::GetAvailableNames()
    {
        QString res;
        bool FixedString = ui->checkBox_FixedString->isChecked();
        bool FixedInteger = ui->checkBox_FixedInteger->isChecked();

        bool RandomInteger = ui->checkBox_RandomInteger->isChecked();
        bool RandomString = ui->checkBox_RandomString->isChecked();

        bool Directory = ui->checkBox_Directory->isChecked();
        bool File = ui->checkBox_File->isChecked();

        bool Select = ui->checkBox_Select->isChecked();
        bool Url = ui->checkBox_Url->isChecked();
        bool Database = ui->checkBox_Database->isChecked();



        if(FixedString && FixedInteger && RandomInteger && RandomString && Directory && File && Select && Url && Database)
        {
            return QString("FixedString,FixedInteger,RandomInteger,RandomString,FilesFromDirectory,LinesFromFile,Select,LinesFromUrl,Database");
        }else
        {
            if(FixedString)
            {
                if(!res.isEmpty())
                    res += ",";
                res += "FixedString";
            }
            if(FixedInteger)
            {
                if(!res.isEmpty())
                    res += ",";

                res += "FixedInteger";
            }
            if(RandomInteger)
            {
                if(!res.isEmpty())
                    res += ",";

                res += "RandomInteger";
            }
            if(RandomString)
            {
                if(!res.isEmpty())
                    res += ",";

                res += "RandomString";
            }
            if(Directory)
            {
                if(!res.isEmpty())
                    res += ",";

                res += "FilesFromDirectory";
            }
            if(File)
            {
                if(!res.isEmpty())
                    res += ",";

                res += "LinesFromFile";
            }
            if(Select)
            {
                if(!res.isEmpty())
                    res += ",";

                res += "Select";
            }
            if(Url)
            {
                if(!res.isEmpty())
                    res += ",";

                res += "LinesFromUrl";
            }
            if(Database)
            {
                if(!res.isEmpty())
                    res += ",";
                res += "Database";
            }
        }
        if(!res.contains(ComboBoxData.at(ui->comboBox->currentIndex())))
        {
            if(!res.isEmpty())
                res += ",";
            res += ComboBoxData.at(ui->comboBox->currentIndex());
        }

        return res;
    }

    void DesignResourceWidget::SetTypeId(const QString& type)
    {
        int index = ComboBoxData.indexOf(type);
        if(index >=0)
            ui->comboBox->setCurrentIndex(index);
        ui->ChooserWidget->setCurrentIndex(ui->comboBox->currentIndex());
    }

    QString DesignResourceWidget::GetTypeId()
    {
        return ComboBoxData.at(ui->comboBox->currentIndex());
    }

    QWidget* DesignResourceWidget::GetTemplateWidgetByType(bool IsUser,const QString& type)
    {
        int size = ui->comboBox->count(), index = -1;

        for(int i = 0;i<size;i++)
        {
            if(ComboBoxData.at(i) == type)
                index = i;
        }

        if(index<0)
            return 0;
        if(IsUser)
            return ui->ChooserWidget->GetTemplateWidgetByIndex(index);

        return ui->MoreChooserWidget->GetTemplateWidgetByIndex(index);
    }

    QWidget* DesignResourceWidget::GetTemplateCurrentWidget(bool IsUser)
    {
        if(IsUser)
            return ui->ChooserWidget->GetTemplateWidgetByIndex(ui->comboBox->currentIndex());

        return ui->MoreChooserWidget->GetTemplateWidgetByIndex(ui->comboBox->currentIndex());
    }

    void DesignResourceWidget::on_ButtonMore_clicked()
    {
        if(MoreState)
        {
            HideMore();
        }else
        {
            ShowMore();
        }
        ui->MoreChooserWidget->setCurrentIndex(ui->comboBox->currentIndex());
    }
    void DesignResourceWidget::Visibility(bool visibility)
    {
        ui->MoreChooserWidget->setVisible(visibility);
        ui->checkBox_2->setVisible(visibility);
        ui->checkBox_RandomInteger->setVisible(visibility);
        SectionTextBox->setVisible(visibility);
        ui->checkBox_RandomString->setVisible(visibility);
        ui->checkBox_Directory->setVisible(visibility);
        ui->checkBox_File->setVisible(visibility);
        ui->checkBox_Select->setVisible(visibility);
        ui->checkBox_Url->setVisible(visibility);
        ui->checkBox_Database->setVisible(visibility);
        ui->checkBox->setVisible(visibility);
        ui->label_4->setVisible(visibility);
        ui->label_5->setVisible(visibility);
        ui->checkBox_FixedInteger->setVisible(visibility);
        ui->label_8->setVisible(visibility);
        ui->label_7->setVisible(visibility);
        ui->lineEdit_VisibilityVariable->setVisible(visibility);
        ui->lineEdit_VisibilityContains->setVisible(visibility);
        ui->label_6->setVisible(visibility);
        ui->CheckBoxIsAdvanced->setVisible(visibility);
        /*if(visibility)
        {
            ui->horizontalSpacer_2->changeSize(40,20, QSizePolicy::Expanding, QSizePolicy::Expanding);
            ui->horizontalSpacer_3->changeSize(40,20, QSizePolicy::Expanding, QSizePolicy::Expanding);
            ui->horizontalSpacer_4->changeSize(40,20, QSizePolicy::Expanding, QSizePolicy::Expanding);
        }else
        {
            ui->horizontalSpacer_2->changeSize(0,0, QSizePolicy::Fixed, QSizePolicy::Fixed);
            ui->horizontalSpacer_3->changeSize(0,0, QSizePolicy::Fixed, QSizePolicy::Fixed);
            ui->horizontalSpacer_4->changeSize(0,0, QSizePolicy::Fixed, QSizePolicy::Fixed);
        }*/
        ui->checkBox_FixedString->setVisible(visibility);
    }
    void DesignResourceWidget::ShowMore()
    {
        ui->ButtonMore->setText(tr("Hide"));
        Visibility(true);
        MoreState = true;
    }
    void DesignResourceWidget::HideMore()
    {
        ui->ButtonMore->setText(tr("Show more"));
        Visibility(false);
        MoreState = false;
    }

    IStringBuilder * DesignResourceWidget::GetStringBuilder()
    {
        return ui->ChooserWidget->GetStringBuilder();
    }

    void DesignResourceWidget::SetStringBuilder(IStringBuilder * val)
    {
        ui->ChooserWidget->SetStringBuilder(val);
    }

    void DesignResourceWidget::SetDatabaseState(IDatabaseState *DatabaseState)
    {
        ui->ChooserWidget->SetDatabaseState(DatabaseState);
        ui->MoreChooserWidget->SetDatabaseState(DatabaseState);
    }

    int DesignResourceWidget::FindMyIndex()
    {
        int res = 0;
        while(res < parentWidget()->layout()->count())
        {
            QLayoutItem* item = parentWidget()->layout()->itemAt(res);
            if(item)
            {
                QWidget* widget = item->widget();
                if(widget == this)
                {
                    return res;
                }
            }
            res++;
        }
        return -1;
    }

    void DesignResourceWidget::on_ButtonUp_clicked()
    {


        emit Up(FindMyIndex());
    }

    void DesignResourceWidget::on_ButtonDown_clicked()
    {
        emit Down(FindMyIndex());
    }

    void DesignResourceWidget::changeEvent(QEvent *e)
    {
        QGroupBox::changeEvent(e);
        switch (e->type()) {
        case QEvent::LanguageChange:
        {
            int index = ui->comboBox->currentIndex();
            ui->retranslateUi(this);
            ui->comboBox->setCurrentIndex(index);
            DescriptionChanged(DescriptionTextBox->GetCurrentText());
            break;
        }
        default:
            break;
        }
    }


}






