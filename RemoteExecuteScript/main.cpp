#include "remote.h"
#include <QApplication>
#include <QStyleFactory>
#include <QFile>

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
    qInstallMessageHandler(myMessageHandler);

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));

    qApp->setStyle(QStyleFactory::create("fusion"));

    QFont font = qApp->font();
    font.setPixelSize(13);
    qApp->setFont(font);

    QPalette palette;
    qApp->setPalette(palette);

    Remote u;
    if(u.Start(a.arguments()))
        return a.exec();
    else
        return 0;
}

