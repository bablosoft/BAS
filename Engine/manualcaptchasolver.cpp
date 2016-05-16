#include "manualcaptchasolver.h"

#include "singlecaptchawidget.h"
#include "flowlayout.h"
#include <QScrollArea>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    ManualCaptchaSolver::ManualCaptchaSolver(QObject *parent) :
        ISolver(parent),
        IdCounter(0),Size(0)
    {
        Scroll = new QScrollArea();

        Widget = new QWidget(Scroll);
        Scroll->setWidget(Widget);
        Scroll->setWidgetResizable(true);
        Layout = new FlowLayout(Widget,-1,10);
        Scroll->widget()->setLayout(Layout);
        emit ChangedSize(0);
        connect(this,SIGNAL(Done(QString,QString,bool)),this,SLOT(DoneSlot(QString,QString,bool)));
    }

    QWidget* ManualCaptchaSolver::GetWidget()
    {
        return Scroll;
    }

    int ManualCaptchaSolver::GetSize()
    {
        return Size;
    }

    ManualCaptchaSolver::~ManualCaptchaSolver()
    {

    }


    void ManualCaptchaSolver::SetProperty(const QString& name,const QString& value)
    {


    }

    void ManualCaptchaSolver::DoneSlot(const QString& val, const QString& id, bool res)
    {
        emit ChangedSize(--Size);
    }

    QString ManualCaptchaSolver::Solve(const QString& base64)
    {
        emit Used();
        emit ChangedSize(++Size);
        SingleCaptchaWidget *w = new SingleCaptchaWidget();
        w->setParent(Widget);
        w->SetCaptcha(base64,QString::number(IdCounter));
        connect(w,SIGNAL(Done(QString,QString,bool)),this,SIGNAL(Done(QString,QString,bool)));
        Layout->addWidget(w);
        return QString::number(IdCounter++);
    }

    bool ManualCaptchaSolver::TimeLimited()
    {
        return false;
    }

}
