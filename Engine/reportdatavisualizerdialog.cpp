#include "reportdatavisualizerdialog.h"
#include "ui_reportdatavisualizerdialog.h"
#include <QPushButton>
#include <QClipboard>
#include <QIcon>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    ReportDataVisualizerDialog::ReportDataVisualizerDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ReportDataVisualizerDialog)
    {
        ui->setupUi(this);

        QPushButton *ReloadKey = new QPushButton(tr(" Reload"));
        ReloadKey->setIcon(QIcon(":/engine/images/reload.png"));
        connect(ReloadKey,SIGNAL(clicked()),this,SIGNAL(Reload()));
        ui->buttonBox->addButton(ReloadKey,QDialogButtonBox::HelpRole);

        QPushButton *CopyKey = new QPushButton(tr(" Copy To Clipboard"));
        CopyKey->setIcon(QIcon(":/engine/images/clipboard.png"));
        connect(CopyKey,SIGNAL(clicked()),this,SLOT(Copy()));
        ui->buttonBox->addButton(CopyKey,QDialogButtonBox::HelpRole);
    }

    void ReportDataVisualizerDialog::SetData(const QString& Data)
    {
        ui->textBrowser->setPlainText(Data);
    }

    void ReportDataVisualizerDialog::SetHtml(const QString& Html)
    {
        ui->textBrowser->setHtml(Html);
    }

    void ReportDataVisualizerDialog::Copy()
    {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(ui->textBrowser->toPlainText());
    }

    ReportDataVisualizerDialog::~ReportDataVisualizerDialog()
    {
        delete ui;
    }

    void ReportDataVisualizerDialog::changeEvent(QEvent *e)
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

}
