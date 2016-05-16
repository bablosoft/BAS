#include "multitimer.h"
#include "every_cpp.h"
#include <QDebug>


namespace BrowserAutomationStudioFramework
{
    MultiTimer::MultiTimer(QObject *parent) :
        QObject(parent)
    {
        Timer = new QTimer(this);
        Timer->setSingleShot(false);
        Timer->setInterval(1000);
        connect(Timer,SIGNAL(timeout()),this,SLOT(TimeoutSlot()));
        Timer->start();
    }

    void MultiTimer::TimeoutSlot()
    {
        QDateTime now = QDateTime::currentDateTime();
        emit Timeout(now);
    }

}
