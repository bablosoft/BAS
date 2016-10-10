#include "compiler.h"
#include <QDir>
#include <QRegExp>
#include "every_cpp.h"

Compiler::Compiler(QObject *parent) :
    QObject(parent)
{
}
void Compiler::SetName(const QString & Name)
{
    this->Name = Name;
}
void Compiler::SetVersion(const QString & Version)
{
    this->Version = Version;
}

QString Compiler::GetName()
{
    return Name;
}
QString Compiler::GetVersion()
{
    return Version;
}
void Compiler::SetOs(const QString & Os)
{
    this->Os = Os;
}

QString Compiler::GetOs()
{
    return Os;
}

void Compiler::SetReleaseFolder(const QString& ReleaseFolder)
{
    this->ReleaseFolder = ReleaseFolder;
}

QString Compiler::GetEngineFolder()
{
    return EngineFolder;
}

QString Compiler::GetCompiledFolder()
{
    return QDir(CompiledFolder).absolutePath();
}
void Compiler::SetBuildFolder(const QString& BuildFolder)
{
    this->BuildFolder = BuildFolder;
}

void Compiler::CalculateCompiledFolder()
{
    QDir FolderRelease(ReleaseFolder);
    QString nameCopy = Name;
    QString NameEscapedOriginal = nameCopy.replace(QRegExp("\\s"),".").replace(QRegExp("[^a-zA-Z1-9]"),"");

    QStringList Exists = FolderRelease.entryList(QStringList()<<"*",QDir::Dirs | QDir::NoDotAndDotDot);

    if(NameEscapedOriginal.isEmpty())
        NameEscapedOriginal = "OnlyEnglishNames";
    int iterator = 0;

    CompiledFolder = NameEscapedOriginal;
    while(Exists.contains(CompiledFolder))
    {
        CompiledFolder = NameEscapedOriginal + "." + QString::number(++iterator);
    }
    CompiledFolder = FolderRelease.absoluteFilePath(CompiledFolder);
    QDir FolderCompiled(CompiledFolder);
    EngineFolder = FolderCompiled.absoluteFilePath("engine/engine");

}


static void recurseCopyAddDir(const QString& ModuleFolder, QDir d, QDir t)
{
    QStringList qsl = d.entryList(QStringList()<<"*",QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);

    foreach (QString file, qsl)
    {
        if(!d.absoluteFilePath(file).startsWith(ModuleFolder))
        {
            if(file.endsWith(".xml"))
                continue;
            if(file.endsWith(".ini") && !file.startsWith("settings_worker.ini"))
                continue;
            if(file.endsWith(".txt") && !file.startsWith("chrome_command_line.txt"))
                continue;

            if(file.endsWith("FastExecuteScriptShortcut.exe"))
                continue;
        }


        QFileInfo finfo(d.absoluteFilePath(file));

        if (finfo.isSymLink())
            return;

        if (finfo.isDir())
        {
            t.mkdir(file);
            QDir sd(finfo.filePath());
            recurseCopyAddDir(ModuleFolder,sd, QDir(t.absoluteFilePath(file)));
        } else
        {
            QFile::copy(finfo.absoluteFilePath(),t.absoluteFilePath(file));
        }
    }
}


void Compiler::Compile()
{
    QDir FolderRelease(ReleaseFolder);
    FolderRelease.mkdir(".");
    CalculateCompiledFolder();
    FolderRelease.mkdir(CompiledFolder);
    QDir FolderCompiled(CompiledFolder);

    QDir FolderBuild(BuildFolder);
    QFile::copy(FolderBuild.absoluteFilePath("FastExecuteScriptShortcut.exe"),FolderCompiled.absoluteFilePath("Run.exe"));

    FolderCompiled.mkdir("engine");
    FolderCompiled.cd("engine");
    QFile::copy(FolderBuild.absoluteFilePath("FastExecuteScriptShortcut.exe"),FolderCompiled.absoluteFilePath("FastExecuteScript.exe"));

    FolderCompiled.mkdir("engine");
    FolderCompiled.cd("engine");

    QString ModulesFolder;
    {
        QDir FolderBuild(BuildFolder);
        FolderBuild.cd("modules");
        ModulesFolder = FolderBuild.absolutePath();
    }

    recurseCopyAddDir(ModulesFolder,FolderBuild,FolderCompiled);




}
