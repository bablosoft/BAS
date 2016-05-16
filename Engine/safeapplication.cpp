#include "safeapplication.h"
#include <QDebug>
#include <QTime>
#include "debugterminate.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    SafeApplication::SafeApplication(int &argc, char *argv[]) : QApplication(argc, argv)
    {
        Logger = 0;
    }

    void SafeApplication::SetLogger(ILogger *Logger)
    {
        this->Logger = Logger;
    }


    bool SafeApplication::notify(QObject * receiver, QEvent * event)
    {
        try
        {
            return QApplication::notify(receiver, event);
        }
        catch(std::exception& e)
        {
            qDebug() << "Exception thrown:" << e.what()<<receiver->metaObject()->className()<<event->type();
            if(Logger)
                Logger->Write(QString("[") + QTime::currentTime().toString("hh:mm:ss") + "]" + QString("Exception thrown:") + e.what() + receiver->metaObject()->className() + QString::number(event->type()));
            Terminate().DoTerminate(4);
        }catch(...)
        {
            qDebug() << "Unknown exception"<<receiver->metaObject()->className()<<event->type();
            if(Logger)
                Logger->Write(QString("[") + QTime::currentTime().toString("hh:mm:ss") + "]" + QString("Unknown exception") + receiver->metaObject()->className() + QString::number(event->type()));
            Terminate().DoTerminate(4);
        }

    }
}
