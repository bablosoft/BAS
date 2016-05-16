#include "vocabularytest.h"
#include "ui_vocabularytest.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    VocabularyTest::VocabularyTest(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::VocabularyTest)
    {
        ui->setupUi(this);
        connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SIGNAL(Changed(QString)));
        QList<QPushButton *> buttons = ui->scrollArea->findChildren<QPushButton *>();
        foreach(QPushButton *button,buttons)
        {
            button->disconnect();
            connect(button,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
        }
    }

    void VocabularyTest::SetStringBuilder(IStringBuilder *StringBuilder)
    {
        this->StringBuilder = StringBuilder;
    }

    void VocabularyTest::SetText(const QString& str)
    {
        ui->lineEdit->setText(str);
    }

    VocabularyTest::~VocabularyTest()
    {
        delete ui;
    }
    void VocabularyTest::on_pushButton_clicked()
    {
        QString text = ui->lineEdit->text();
        int cursor = ui->lineEdit->cursorPosition();
        QString injection = qobject_cast<QPushButton *>(sender())->text();
        if(!injection.startsWith("{"))
            injection = QString("<") + injection + QString(">");
        text = text.mid(0,cursor) + injection + text.mid(cursor);

        ui->lineEdit->setText(text);
        ui->lineEdit->setCursorPosition(cursor + injection.length());

        ui->lineEdit->setFocus();
    }
    void VocabularyTest::on_TestButton_clicked()
    {
        ui->plainTextEdit->clear();
        QString text;
        QString mask = ui->lineEdit->text();
        for(int i = 0;i<40;i++)
        {
            text.append(StringBuilder->Expand(mask));
            text.append("\r\n");
        }
        ui->plainTextEdit->setPlainText(text);
    }

    void VocabularyTest::changeEvent(QEvent *e)
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




