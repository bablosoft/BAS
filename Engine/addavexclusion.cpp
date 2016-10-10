#include "addavexclusion.h"
#include "every_cpp.h"
#include <QProcess>
#include <QDir>
#include <QFile>
#include <QApplication>
#include <QTextStream>

namespace BrowserAutomationStudioFramework
{
    AddAVExclusion::AddAVExclusion(QObject *parent) : QObject(parent)
    {

    }

    void AddAVExclusion::Run()
    {
        QString path;
        {
            QFile f("AddAVExclusion.ps1");
            if(f.exists())
                return;
            if(f.open(QIODevice::WriteOnly | QIODevice::Append))
            {
                QTextStream out(&f);
                out.setCodec("UTF-8");
                out.setGenerateByteOrderMark(true);
                path = QFileInfo(f).absoluteFilePath();
                out<<"Add-MpPreference -ExclusionPath '"<<QFileInfo(f).absoluteDir().absolutePath().replace("/","\\")<<"'\r\n";
            }
            f.close();
        }


        QProcess p;
        p.start("powershell.exe",QStringList()<<"-inputformat"<<"none"<<"-ExecutionPolicy"<<"RemoteSigned"<<"-File"<<path);
        //p.start("cmd.exe",QStringList()<<"/c"<<"echo"<<QDir::currentPath());

        while(p.state() != QProcess::NotRunning)
        {
            //qDebug()<<p.state();
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }

        QString res = p.readAllStandardOutput() + "\r\n" + p.readAllStandardError();
        {
            QFile f("AddAVExclusion.log");
            if(f.open(QIODevice::WriteOnly | QIODevice::Append))
            {
                QTextStream out(&f);
                out.setCodec("UTF-8");
                path = QFileInfo(f).absoluteFilePath();
                out<<res<<"\r\n";
            }
            f.close();
        }
    }
}
