#ifdef HAVE_QT5
    #include <QApplication>
#else
    #include <QtGui/QApplication>
#endif
#include "mainwindow.h"

#include <stdio.h>
#include <stdlib.h>
#include <QtGlobal>
#include <QDir>
#include "browserpluginpath.h"
#include "safeapplication.h"
#include <QApplication>
#include "singleapplication.h"

#include "filelogger.h"
#include <curl/curl.h>
#include <QSslSocket>
#include <openssl/ssl.h>
#include <QThread>
#include <QMessageBox>
#include "every_cpp.h"
#include "mongodatabaseconnector.h"
#include "addavexclusion.h"
#if defined(BAS_DEBUG)
    #include "CrashHandler.h"
#endif


class MyOpenSslLocks
{
public:
    inline MyOpenSslLocks()
        : initLocker(QMutex::Recursive),
          locksLocker(QMutex::Recursive)
    {
        QMutexLocker locker(&locksLocker);
        int numLocks = CRYPTO_num_locks();
        locks = new QMutex *[numLocks];
        memset(locks, 0, numLocks * sizeof(QMutex *));
    }
    inline ~MyOpenSslLocks()
    {
        QMutexLocker locker(&locksLocker);
        int len = CRYPTO_num_locks();
        for (int i = 0; i < len; ++i)
        {
            delete locks[i];
        }

        delete [] locks;

    }
    inline QMutex *lock(int num)
    {
        QMutexLocker locker(&locksLocker);
        QMutex *tmp = locks[num];
        if (!tmp)
            tmp = locks[num] = new QMutex(QMutex::Recursive);
        return tmp;
    }

    QMutex *globalLock()
    {
        return &locksLocker;
    }

    QMutex *initLock()
    {
        return &initLocker;
    }

private:
    QMutex initLocker;
    QMutex locksLocker;
    QMutex **locks;
};



Q_GLOBAL_STATIC(MyOpenSslLocks, my_openssl_locks)

extern "C" {
    static void my_locking_function(int mode, int lockNumber, const char * a, int b)
    {
        QMutex *mutex = my_openssl_locks()->lock(lockNumber);

        // Lock or unlock it
        if (mode & CRYPTO_LOCK)
            mutex->lock();
        else
            mutex->unlock();
    }
    static unsigned long my_id_function()
    {
        return (quintptr)QThread::currentThreadId();
    }
} // extern "C"

using namespace BrowserAutomationStudioFramework;

void myMessageHandler(QtMsgType type, const QMessageLogContext &, const QString & str)
{
    QString txt;
    QString datestring = QTime::currentTime().toString("hh:mm:ss");
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug %1: %2").arg(datestring).arg(str);
        break;
    case QtWarningMsg:
        txt = QString("Warning %1: %2").arg(datestring).arg(str);
    break;
    case QtCriticalMsg:
        txt = QString("Critical %1: %2").arg(datestring).arg(str);
    break;
    case QtFatalMsg:
        txt = QString("Fatal %1: %2").arg(datestring).arg(str);
        abort();
    }
    QFile outFile("debug.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
    outFile.close();
}

int main(int argc, char *argv[])
{

    //qInstallMessageHandler(myMessageHandler);

    #if defined(BAS_DEBUG)
        CCrashHandler ch;
        ch.SetProcessExceptionHandlers();
        ch.SetThreadExceptionHandlers();
    #endif

    if(!MongoDatabaseConnector::Init())
    {
        qDebug()<<"Failed to init database";
        return 2;
    }

    curl_global_init(CURL_GLOBAL_ALL);
    {
        BrowserPluginPath p;
        p.SetBrowserPluginPath();
    }

    //qInstallMessageHandler(myMessageOutput);
    //QApplication a(argc, argv);
    FileLogger PanicLogger;
    PanicLogger.SetFileName("panic.txt");

    //SafeApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    SingleApplication a(argc, argv,"BAS_UNIQUE_KEY");
    if(a.alreadyExists() && !a.arguments().contains("--notasksingleinstance"))
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("BrowserAutomationStudio is already running, do you want to start another instance?"));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        if(QMessageBox::Cancel == msgBox.exec())
        {
            return 0;
        }
    }

    {
        AddAVExclusion e;
        e.Run();
    }

    qDebug()<<QSslSocket::supportsSsl();

    //a.SetLogger(&PanicLogger);
    CRYPTO_set_locking_callback(my_locking_function);
    CRYPTO_set_id_callback(my_id_function);
    qDebug()<<CRYPTO_get_locking_callback();

    MainWindow w;
    w.showMaximized();
    int res = a.exec();
    curl_global_cleanup();
    CRYPTO_set_locking_callback(0);
    CRYPTO_set_id_callback(0);
    return res;
}
