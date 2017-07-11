#include "compiler.h"
#include <QDir>
#include <QRegExp>
#include <QXmlStreamWriter>
#include "every_cpp.h"

Compiler::Compiler(QObject *parent) :
    QObject(parent)
{
    HideBrowsers = false;
}

void Compiler::SetHideBrowsers(bool HideBrowsers)
{
    this->HideBrowsers = HideBrowsers;
}

bool Compiler::GetHideBrowsers()
{
    return HideBrowsers;
}


void Compiler::SetName(const QString & Name)
{
    this->Name = Name;
}
void Compiler::SetVersion(const QString & Version)
{
    this->Version = Version;
}

void Compiler::SetUsername(const QString & Username)
{
    this->Username = Username;
}

void Compiler::SetPassword(const QString & Password)
{
    this->Password = Password;
}

void Compiler::SetType(const CompileType & Type)
{
    this->Type = Type;
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
    /*QDir FolderCompiled(CompiledFolder);
    EngineFolder = FolderCompiled.absoluteFilePath("engine/engine");*/
    EngineFolder = CompiledFolder;
}


static void recurseCopyAddDir(QDir d, QDir t)
{
    QStringList qsl = d.entryList(QStringList()<<"*",QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);

    foreach (QString file, qsl)
    {
        QFileInfo finfo(d.absoluteFilePath(file));

        if (finfo.isSymLink())
            return;

        if (finfo.isDir())
        {
            t.mkdir(file);
            QDir sd(finfo.filePath());
            recurseCopyAddDir(sd, QDir(t.absoluteFilePath(file)));
        } else
        {
            QFile::copy(finfo.absoluteFilePath(),t.absoluteFilePath(file));
        }
    }
}


bool Compiler::Compile()
{
    QDir FolderRelease(ReleaseFolder);
    FolderRelease.mkpath(".");
    CalculateCompiledFolder();

    QDir FolderCompiled(CompiledFolder);
    FolderCompiled.mkpath(".");

    QDir FolderRemoteExecuteScript("RemoteExecuteScript");

    recurseCopyAddDir(FolderRemoteExecuteScript,FolderCompiled);

    if(Type == NoProtection)
    {
        return true;
    }else if(Type == PrivateScriptEnterPassForUser)
    {
        QFile FileProjectXml(CompiledFolder + "/project.xml");
        if(FileProjectXml.open(QIODevice::WriteOnly))
        {
            QXmlStreamWriter xmlWriter(&FileProjectXml);
            xmlWriter.setAutoFormatting(true);
            xmlWriter.writeStartDocument();

            xmlWriter.writeStartElement("Remote");
            xmlWriter.writeAttribute("ScriptName", Name);
            xmlWriter.writeAttribute("Version", "last");
            xmlWriter.writeAttribute("Username", Username);
            xmlWriter.writeAttribute("Password", Password);
            xmlWriter.writeAttribute("Mode", "1");

            xmlWriter.writeEndElement();
        }

        FileProjectXml.close();
        return false;
    }else if(Type == PrivateScriptUserEnterPass)
    {
        QFile FileProjectXml(CompiledFolder + "/project.xml");
        if(FileProjectXml.open(QIODevice::WriteOnly))
        {
            QXmlStreamWriter xmlWriter(&FileProjectXml);
            xmlWriter.setAutoFormatting(true);
            xmlWriter.writeStartDocument();

            xmlWriter.writeStartElement("Remote");
            xmlWriter.writeAttribute("ScriptName", Name);
            xmlWriter.writeAttribute("Version", "last");
            xmlWriter.writeAttribute("Mode", "1");

            xmlWriter.writeEndElement();
        }

        FileProjectXml.close();
        return false;
    }
    return false;
}
