#include "subprocesslistwidget.h"
#include "ui_subprocesslistwidget.h"
#include <QLabel>
#include <QXmlStreamReader>
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    SubprocessListWidget::SubprocessListWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::SubprocessListWidget)
    {
        ui->setupUi(this);
        AutoStart = false;
        QVBoxLayout *MainLayout = new QVBoxLayout(this);
        MainLayout->setMargin(20);
        QLabel * label = new QLabel(this);
        label->setText(tr("<html><head/><body><p><img src=\":/engine/images/question.png\"/> This panel contains list of browsers. Enable checkbox, to show browser. To hide it - disable checkbox.</p></body></html>"));
        label->setWordWrap(true);
        MainLayout->addWidget(label);
        MainWidget = new QWidget(this);
        MainLayout->addWidget(MainWidget);
        MainLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding));

        Layout = new FlowLayout(MainWidget);

        MainWidget->setLayout(Layout);
    }

    void SubprocessListWidget::SetAutoStart(bool AutoStart)
    {
        this->AutoStart = AutoStart;
    }

    void SubprocessListWidget::Clear()
    {
        QLayoutItem* item;
        while ( ( item = Layout->takeAt( 0 ) ) != 0 )
        {
            delete item->widget();
            delete item;
        }
        Data.clear();
        Indexes.clear();
        this->disconnect();

    }

    void SubprocessListWidget::CommunicatorDestroyed()
    {
        IProcessComunicator* Communicator = qobject_cast<IProcessComunicator*>(sender());
        if(!Communicator)
            return;
        QList<IProcessComunicator*> values = Data.values();

        int index = values.indexOf(Communicator);
        if(index >= 0)
        {
            Data[Data.key(values.at(index))] = 0;
        }
    }

    void SubprocessListWidget::Add(IProcessComunicator* Communicator, int index)
    {
        QCheckBox *Box = 0;
        connect(Communicator,SIGNAL(Received(QString)),this,SLOT(Received(QString)));
        connect(Communicator,SIGNAL(OnSuspend()),this,SLOT(CommunicatorDestroyed()));
        if(Indexes.contains(index))
        {
            Box = Indexes[index];
            Data[Box] = Communicator;
            if(Box->isChecked())
            {
                 Communicator->Send("<Visible>1</Visible>");
            }
        }else
        {
            Box = new QCheckBox(MainWidget);
            Data.insert(Box,Communicator);
            Indexes.insert(index,Box);
            Box->setText(QString(tr("Browser # %1")).arg(QString::number(index)));

            Layout->addWidget(Box);
            connect(Box,SIGNAL(toggled(bool)),this,SLOT(ChangedCheckState(bool)));
        }
        if(AutoStart)
            Box->setChecked(true);
    }

    void SubprocessListWidget::Received(const QString & Message)
    {

        QXmlStreamReader xmlReader(Message);

        while(!xmlReader.atEnd() && !xmlReader.hasError())
        {
            QXmlStreamReader::TokenType token = xmlReader.readNext();

            if(xmlReader.name() == "Minimized" && token == QXmlStreamReader::StartElement)
            {
                IProcessComunicator *Comunicator = qobject_cast<IProcessComunicator *>(sender());
                QCheckBox *box = Data.key(Comunicator);
                if(box)
                {
                    box->setChecked(false);
                }
            }
        }

        if (xmlReader.hasError())
        {
            return;
        }
    }

    void SubprocessListWidget::ChangedCheckState(bool state)
    {
        IProcessComunicator * Communicator = Data[qobject_cast<QCheckBox *>(sender())];
        if(Communicator)
        {
            Communicator->Send(QString("<Visible>%1</Visible>").arg(QString::number(state)));
        }
    }

    SubprocessListWidget::~SubprocessListWidget()
    {
        delete ui;
    }

    void SubprocessListWidget::changeEvent(QEvent *e)
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
