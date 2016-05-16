#include "languagechooserdevelopmentwidget.h"
#include "ui_languagechooserdevelopmentwidget.h"
#include <QMessageBox>
#include <QPushButton>
#include "flowlayout.h"
#include "every_cpp.h"

LanguageChooserDevelopmentWidget::LanguageChooserDevelopmentWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LanguageChooserDevelopmentWidget)
{
    ui->setupUi(this);
    ui->supportedLanguages->setLayout(new FlowLayout(ui->supportedLanguages));
    ui->switchTo->setLayout(new FlowLayout(ui->switchTo));
    connect(this,SIGNAL(accepted()),this,SLOT(AcceptedSlot()));
    correcting = false;
}

void LanguageChooserDevelopmentWidget::AcceptedSlot()
{
    QList<int> SelectedIndexes;
    int index = 0;
    foreach(QCheckBox* c, CheckBoxes)
    {
        if(c->isChecked())
        {
           SelectedIndexes.append(index);
        }
        index++;
    }
    LanguageModel->SetScriptAvailableLanguages(SelectedIndexes);
}

void LanguageChooserDevelopmentWidget::SetLanguageModel(ILanguageModel *LanguageModel)
{
    this->LanguageModel = LanguageModel;

    int index = 0;
    QList<int> AvailableLanguages = LanguageModel->GetScriptAvailableLanguages();
    foreach(QString lang, LanguageModel->GetEngineAvailableLanguages())
    {
        QCheckBox*check = new QCheckBox(this);
        connect(check,SIGNAL(toggled(bool)),this,SLOT(CheckBoxClicked()));
        check->setText(lang);
        check->setIcon(QIcon(QString(":/engine/images/flags/%1.png").arg(lang)));

        if(AvailableLanguages.contains(index))
            check->setChecked(true);
        ui->supportedLanguages->layout()->addWidget(check);
        QPushButton *button = new QPushButton(this);
        if(AvailableLanguages.contains(index))
            connect(button,SIGNAL(clicked()),this,SLOT(ButtonClicked()));
        else
            button->setEnabled(false);
        button->setText(lang);
        ui->switchTo->layout()->addWidget(button);
        CheckBoxes.append(check);
        index++;
    }


}

void LanguageChooserDevelopmentWidget::ButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    LanguageModel->ChangeDefaultLanguage(button->text());
}

void LanguageChooserDevelopmentWidget::CheckBoxClicked()
{
    if(correcting)
        return;

    foreach(QCheckBox* c, CheckBoxes)
    {
        if(c->isChecked())
            return;
    }

    QCheckBox * check = qobject_cast<QCheckBox*>(sender());
    if(!check->isChecked())
    {
        correcting = true;
        check->setChecked(true);
        correcting = false;
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("At least one language should be present"));
        msgBox.setText(tr("At least one language should be present"));
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowIcon(QIcon(":/engine/images/language.png"));
        msgBox.setInformativeText("");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

    }

}

void LanguageChooserDevelopmentWidget::changeEvent(QEvent *e)
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


LanguageChooserDevelopmentWidget::~LanguageChooserDevelopmentWidget()
{
    delete ui;
}
