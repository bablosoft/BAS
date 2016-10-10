#include "projectbackup.h"
#include "every_cpp.h"
#include <QDateTime>
#include <QDir>

namespace BrowserAutomationStudioFramework
{
    ProjectBackup::ProjectBackup(QObject *parent) : QObject(parent)
    {
        milliseconds = 5 * 60000;
        CodeEditor = 0;
        Timer = 0;
        DestFolder = "../../projectbackups";

    }

    void ProjectBackup::SetCodeEditor(ICodeEditor * CodeEditor)
    {
        this->CodeEditor = CodeEditor;
    }
    void ProjectBackup::SetPeriod(int milliseconds)
    {
        this->milliseconds = milliseconds;
    }
    void ProjectBackup::SetDestFolder(const QString& DestFolder)
    {
        this->DestFolder = DestFolder;
    }

    void ProjectBackup::Start()
    {
        Timer = new QTimer(this);
        Timer->setInterval(milliseconds);
        Timer->setSingleShot(false);
        connect(Timer,SIGNAL(timeout()),this,SLOT(DoBackups()));
        Timer->start();
    }

    void ProjectBackup::DoBackups()
    {
        if(!CodeEditor)
        {
            return;
        }

        QString Code = CodeEditor->GetText();
        if(LastProject == Code)
            return;
        QDateTime CurrentDateTime = QDateTime::currentDateTime();
        QDir dir(DestFolder + QDir::separator() + CurrentDateTime.toString("yyyy.MM.dd"));
        if(!dir.exists())
            dir.mkpath(".");
        QString path = dir.absoluteFilePath(QString("%1.xml").arg(CurrentDateTime.toString("hh.mm.ss")));
        QFile file(path);
        if(!file.open(QIODevice::WriteOnly))
            return;
        file.write(Code.toUtf8());
        file.close();
        LastProject = Code;
    }


}
