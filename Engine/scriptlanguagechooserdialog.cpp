#include "scriptlanguagechooserdialog.h"
#include "ui_scriptlanguagechooserdialog.h"

#include <QList>
#include <QRadioButton>
#include "every_cpp.h"

ScriptLanguageChooserDialog::ScriptLanguageChooserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScriptLanguageChooserDialog)
{
    ui->setupUi(this);
    ui->label_2->setVisible(false);
    CurrentLang = "en";
}
void ScriptLanguageChooserDialog::SetLang(const QString &CurrentLang)
{
    this->CurrentLang = CurrentLang;
}

void ScriptLanguageChooserDialog::ChangesWillTakeEffectAfterRestart()
{
    ui->label_2->setVisible(true);
}

void ScriptLanguageChooserDialog::SetLanguageModel(ILanguageModel *LanguageModel)
{
    this->LanguageModel = LanguageModel;


    QList<int> AvailableLanguages = LanguageModel->GetScriptAvailableLanguages();
    foreach(QString lang, LanguageModel->GetEngineAvailableLanguages())
    {
        QRadioButton*radio = new QRadioButton(this);
        connect(radio,SIGNAL(toggled(bool)),this,SLOT(RadioBoxToggled(bool)));
        radio->setText(lang);
        radio->setIcon(QIcon(QString(":/engine/images/flags/%1.png").arg(lang)));
        radio->setChecked(lang == CurrentLang);
        ui->languageLayout->addWidget(radio);

    }
}

void ScriptLanguageChooserDialog::RadioBoxToggled(bool state)
{
    if(!state)
        return;
    QRadioButton * radio = qobject_cast<QRadioButton*>(sender());
    CurrentLang = radio->text();
}

QString ScriptLanguageChooserDialog::GetLang()
{
    return CurrentLang;
}

ScriptLanguageChooserDialog::~ScriptLanguageChooserDialog()
{
    delete ui;
}

void ScriptLanguageChooserDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

