#include "mainwindow.h"
#include <QApplication>
#include "browserpluginpath.h"
#include "filelogger.h"
#include "safeapplication.h"
#include <curl/curl.h>
#include <QSslSocket>
#include <openssl/ssl.h>
#include <QThread>
#include <QtGlobal>
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


using namespace BrowserAutomationStudioFramework;

int main(int argc, char *argv[])
{

    #if defined(BAS_DEBUG)
        CCrashHandler ch;
        ch.SetProcessExceptionHandlers();
        ch.SetThreadExceptionHandlers();
    #endif

    qInstallMessageHandler(myMessageHandler);
    qDebug()<<"Start 001";
    qDebug()<<"InitCurl"<<curl_global_init(CURL_GLOBAL_ALL);
    {
        qDebug()<<"Start 002";
        BrowserPluginPath p;
        qDebug()<<"Start 003";
        p.SetBrowserPluginPath();
        qDebug()<<"Start 004";
    }
    //qInstallMessageHandler(myMessageOutput);
    //QApplication a(argc, argv);
    FileLogger PanicLogger;
    qDebug()<<"Start 009";
    PanicLogger.SetFileName("panic.txt");
    qDebug()<<"Start 010";

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    SafeApplication a(argc, argv);
    qDebug()<<"Start 0100";
    {
        AddAVExclusion e;
        e.Run();
    }
    qDebug()<<"Start 011";
    if(!MongoDatabaseConnector::Init())
    {
        qDebug()<<"Failed to init database";
        return 2;
    }
    qDebug()<<"Start 012";
    qDebug()<<"Support SSL"<<QSslSocket::supportsSsl();
    qDebug()<<"SSL default lock"<<CRYPTO_num_locks()<<CRYPTO_get_locking_callback();

    qDebug()<<"Start 013";
    a.SetLogger(&PanicLogger);
    qDebug()<<"Start 014";
    a.setQuitOnLastWindowClosed(false);
    qDebug()<<"Start 015";
    CRYPTO_set_locking_callback(my_locking_function);
    qDebug()<<"Start 016";
    CRYPTO_set_id_callback(my_id_function);
    qDebug()<<"Start 017";
    qDebug()<<"SSL custom lock"<<CRYPTO_num_locks()<<CRYPTO_get_locking_callback();

    qDebug()<<"Start 018";
    MainWindow *w = new MainWindow();
    qDebug()<<"Start 99";
    if(a.arguments().contains("--silent"))
        w->SetIsSilent();

    if(a.arguments().contains("--remote"))
    {
        int index = a.arguments().indexOf("--remote");
        if(index + 1 < a.arguments().length())
        {
            QString Remote = a.arguments()[index + 1];
            qDebug()<<"Remote"<<Remote;
            w->SetRemote(Remote);
        }
    }
    qDebug()<<"Start 100";
    w->Start();
    qDebug()<<"Start 200";
    int res = a.exec();
    qDebug()<<"Start 300";
    curl_global_cleanup();
    qDebug()<<"Start 301";
    qDebug()<<"SSL custom lock"<<CRYPTO_num_locks()<<CRYPTO_get_locking_callback();
    qDebug()<<"Start 302";
    qDebug()<<"End";
    qDebug()<<"Start 303";
    CRYPTO_set_locking_callback(0);
    qDebug()<<"Start 304";
    CRYPTO_set_id_callback(0);
    qDebug()<<"Start 305";
    return res;
}
