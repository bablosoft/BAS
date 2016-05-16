#include "outputwidgetconfigurator.h"
#include "ui_outputwidgetconfigurator.h"
#include "multilanguagetextbox.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    OutputWidgetConfigurator::OutputWidgetConfigurator(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::OutputWidgetConfigurator)
    {
        ui->setupUi(this);
        TextBox = new MultiLanguageTextBox(this);
        ui->textPlace->addWidget(TextBox);
        connect(TextBox,SIGNAL(textChanged(QString)),this,SIGNAL(TitleChanged(QString)));
    }

    void OutputWidgetConfigurator::SetTitle(const MultiLanguageString& Title)
    {
        TextBox->SetText(Title);
    }
    MultiLanguageString OutputWidgetConfigurator::GetTitle()
    {
        return TextBox->GetText();
    }
    QString OutputWidgetConfigurator::GetTitleText()
    {
        return TextBox->GetCurrentText();
    }
    bool OutputWidgetConfigurator::GetVisibility()
    {
        return ui->checkBox->isChecked();
    }
    void OutputWidgetConfigurator::SetVisibility(bool Visibility)
    {
        ui->checkBox->setChecked(Visibility);
    }

    OutputWidgetConfigurator::~OutputWidgetConfigurator()
    {
        delete ui;
    }

    void OutputWidgetConfigurator::SetLanguageModel(ILanguageModel *LanguageModel)
    {
        this->LanguageModel = LanguageModel;
        TextBox->SetLanguageModel(LanguageModel);
    }

    void OutputWidgetConfigurator::changeEvent(QEvent *e)
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
