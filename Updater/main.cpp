#include "updateprogress.h"
#include "updater.h"
#include <QApplication>
#include <QStyleFactory>
#include <QMessageBox>
#include <QSharedMemory>
#include <QSystemSemaphore>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    bool IsCloseRequest = a.arguments().contains("--close");
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));

    qApp->setStyle(QStyleFactory::create("fusion"));

    QFont font = qApp->font();
    font.setPixelSize(13);
    qApp->setFont(font);

    QPalette palette;
    qApp->setPalette(palette);

    QSystemSemaphore sema("SAFESWISSSEM1", 1);
    bool isRunning;
    sema.acquire();

    {
        QSharedMemory shmem("SAFESWISSSHMEM2");
        shmem.attach();
    }

    QSharedMemory shmem("SAFESWISSSHMEM2");
    if (shmem.attach())
    {
        isRunning = true;
    }
    else
    {
        shmem.create(1);
        isRunning = false;
    }

    sema.release();


    if(isRunning && !IsCloseRequest)
    {
        QMessageBox msgBox;
        msgBox.setText("Application already running");
        msgBox.exec();
        return 0;
    }


    Updater u;
    if(u.Start(a.arguments()))
        return a.exec();
    else
        return 0;
}

