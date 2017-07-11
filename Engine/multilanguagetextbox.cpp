#include "multilanguagetextbox.h"
#include "ui_multilanguagetextbox.h"
#include <QDebug>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    MultiLanguageTextBox::MultiLanguageTextBox(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::MultiLanguageTextBox)
    {
        ui->setupUi(this);
        connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(SetTranslation(QString)));
        connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(textChangedMultilanguageSlot()));
        connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SIGNAL(textChanged(QString)));
        connect(ui->comboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(ComboTextChanged(QString)));
    }

    QLineEdit * MultiLanguageTextBox::GetEdit()
    {
        return ui->lineEdit;
    }

    void MultiLanguageTextBox::SetTranslation(const QString& text)
    {
        MultilanguageText.SetTranslation(ui->comboBox->currentText(),text);
    }

    void MultiLanguageTextBox::ComboTextChanged(const QString& lang)
    {
        ui->lineEdit->setText(MultilanguageText.GetTranslation(lang));
    }

    void MultiLanguageTextBox::textChangedMultilanguageSlot()
    {
        emit textChangedMultilanguage(MultilanguageText);
    }

    QString MultiLanguageTextBox::GetCurrentText()
    {
        return ui->lineEdit->text();
    }

    MultiLanguageTextBox::~MultiLanguageTextBox()
    {
        delete ui;
    }

    void MultiLanguageTextBox::SetLanguageModel(ILanguageModel * LanguageModel)
    {
        this->LanguageModel = LanguageModel;
        connect(LanguageModel,SIGNAL(ScriptAvailableLanguagesChanged()),this,SLOT(UpdateLanguageModel()));
        connect(LanguageModel,SIGNAL(DefaultLanguageChanged(QString)),this,SLOT(DefaultLanguageChanged(QString)));
        MultilanguageText.Clear();
        UpdateLanguageModel();
        DefaultLanguageChanged(LanguageModel->GetInterfaceLanguage());


    }

    void MultiLanguageTextBox::DefaultLanguageChanged(const QString& lang)
    {
        int index = ui->comboBox->findText(lang);
        if(index<0)
            return;
        ui->comboBox->setCurrentText(lang);

    }

    void MultiLanguageTextBox::UpdateLanguageModel()
    {
        bool SelectedPresent = false;
        QString SelectedText = ui->comboBox->currentText();
        ui->comboBox->clear();
        QList<int> SelectedLang = LanguageModel->GetScriptAvailableLanguages();
        QStringList AllLang = LanguageModel->GetEngineAvailableLanguages();

        foreach(int index, SelectedLang)
        {
            QString lang = AllLang.at(index);
            if(lang == SelectedText)
            {
                SelectedPresent = true;
            }

            ui->comboBox->addItem(lang);
        }

        //ui->comboBox->setVisible(SelectedLang.length()>=2);

        if(SelectedPresent)
        {
            ui->comboBox->setCurrentText(SelectedText);
        }else
        {
            if(ui->comboBox->count() > 0)
                ui->comboBox->setCurrentIndex(0);
        }

    }

    MultiLanguageString MultiLanguageTextBox::GetText()
    {
       return MultilanguageText;
    }

    void MultiLanguageTextBox::SetText(const MultiLanguageString& text)
    {
        MultilanguageText = text;
        ui->lineEdit->setText(MultilanguageText.GetTranslation(ui->comboBox->currentText()));
    }

    void MultiLanguageTextBox::changeEvent(QEvent *e)
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
