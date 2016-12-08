#include "remote.h"
#include <QDir>
#include <QProcess>
#include <QDebug>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <QXmlStreamReader>
#include <QDirIterator>
#include "JlCompress.h"

Remote::Remote(QObject *parent) :
    QObject(parent)
{
    Client = new HttpClient(this);
    ForceFree = false;
    UI = 0;
}

void Remote::Exit()
{
    if(UI)
    {
        UI->deleteLater();
        UI = 0;
    }
    qDebug()<<"Exit";
    QTimer::singleShot(0,[](){
         QCoreApplication::exit(0);
    });
}

void Remote::DetectSettings()
{
    IsValid = true;

    IsX64 = QSysInfo::currentCpuArchitecture() == "x86_64";
    IsSilent = Arguments.contains("--silent");
    Arguments.removeAll("--silent");

    IsRemote = Arguments.contains("--remote");
    Arguments.removeAll("--remote");

    QString PrevKey;
    for(QString Key:Arguments)
    {
        if(PrevKey == "--script")
        {
            ScriptName = Key;
        }else if(PrevKey == "--server")
        {
            Server = Key;
        }else if(PrevKey == "--username")
        {
            Username = Key;
        }else if(PrevKey == "--password")
        {
            Password = Key;
        }
        PrevKey = Key;
    }
    if(Server.isEmpty())
    {
         QSettings Settings("remote_settings.ini",QSettings::IniFormat,this);
         Server = Settings.value("Server","https://bablosoft.com/").toString();
         qDebug()<<"Server from settings"<<Server;
    }

    if(IsRemote && (ScriptName.isEmpty() || Server.isEmpty()))
    {
        ErrorMessage = "No script name or server name";
        IsValid = false;
    }

    qDebug()<<"IsValid"<<IsValid<<"IsX64"<<IsX64<<"IsSilent"<<IsSilent<<"IsRemote"<<IsRemote<<"ScriptName"<<ScriptName<<"Server"<<Server<<"Username"<<Username<<"PasswordLength"<<Password.length();

}

void Remote::DetectScriptProperties()
{
    if(IsRemote)
    {
        if(UI)
            UI->show();
        Client->Connect(this,SLOT(ScriptPropertiesHttpClientResp()));
        qDebug()<<"GET"<<Server + QString("scripts/") + ScriptName + QString("/properties");
        Client->Get(Server + QString("scripts/") + ScriptName + QString("/properties"));
    }else
    {
        //Parse project.xml
        {
            QFileInfo info("project.xml");
            if(!info.exists())
            {
                if(IsSilent)
                {
                    Exit();
                }else
                {
                    UI->SetError("project.xml not fount");
                }
                return;
            }
        }

        QString HashString, EngineVersion;
        {
            QFile f("project.xml");
            if (f.open(QFile::ReadOnly))
            {
                QCryptographicHash hash(QCryptographicHash::Sha256);
                if (hash.addData(&f))
                {
                     HashString = QString::fromUtf8(hash.result().toHex());
                }
            }
            f.close();
        }

        if(HashString.isEmpty())
        {
            if(IsSilent)
            {
                Exit();
            }else
            {
                UI->SetError("failed to compute hash");
            }
            return;
        }

        {
            QFile file("project.xml");
            QXmlStreamReader xmlReader;
            if (!file.open(QIODevice::ReadOnly| QIODevice::Text))
            {
                if(IsSilent)
                {
                    Exit();
                }else
                {
                    UI->SetError("failed to read file");
                }
                return;
            }

            xmlReader.setDevice(&file);

            while(!xmlReader.atEnd() && !xmlReader.hasError())
            {
                QXmlStreamReader::TokenType token = xmlReader.readNext();
                if(xmlReader.name() == "EngineVersion" && token == QXmlStreamReader::StartElement)
                {
                    xmlReader.readNext();
                    EngineVersion = xmlReader.text().toString();
                }

                if(xmlReader.name() == "Remote" && token == QXmlStreamReader::StartElement)
                {
                    foreach(QXmlStreamAttribute attr,xmlReader.attributes())
                    {
                        if(attr.name() == "ScriptName")
                        {
                            this->ScriptName = attr.value().toString();
                        }
                        if(attr.name() == "Server")
                        {
                            this->Server = attr.value().toString();
                        }
                        if(attr.name() == "Username")
                        {
                            this->Username = attr.value().toString();
                        }
                        if(attr.name() == "Password")
                        {
                            this->Password = attr.value().toString();
                        }
                    }
                    qDebug()<<"Remote project.xml"<<"ScriptName"<<ScriptName<<"Server"<<Server<<"Username"<<Username<<"Password"<<Password;
                    IsRemote = true;
                    DetectScriptProperties();
                    return;
                }

            }


        }

        if(EngineVersion.isEmpty())
        {
            if(IsSilent)
            {
                Exit();
            }else
            {
                UI->SetError("failed to get engine version");
            }
            return;
        }

        emit ScriptPropertiesDetected(HashString, EngineVersion);


    }
}

void Remote::ScriptPropertiesHttpClientResp()
{
    qDebug()<<Client->GetContent();

    if(Client->WasError())
    {
        if(IsSilent)
        {
            Exit();
        }else
        {
            UI->SetError(Client->GetErrorString());
        }
        return;
    }
    QJsonDocument JsonResponse = QJsonDocument::fromJson(Client->GetContent().toUtf8());
    QJsonObject JsonObj = JsonResponse.object();
    if(!JsonObj["success"].toBool())
    {
        if(IsSilent)
        {
            Exit();
        }else
        {
            UI->SetError(JsonObj["message"].toString());
        }
        return;
    }
    if(JsonObj["free"].toBool())
    {
        ForceFree = true;
    }

    emit ScriptPropertiesDetected(JsonObj["hash"].toString(),JsonObj["engversion"].toString());
}

void Remote::ScriptPropertiesDetected(const QString& ScriptHash, const QString& EngineVersion)
{
    this->ScriptHash = "SID" + ScriptHash;
    this->EngineVersion = EngineVersion;
    this->IsValid = IsValid;
    this->ErrorMessage = ErrorMessage;

    if(UI)
        UI->SetProgress(10);
    qDebug()<<"ScriptHash"<<ScriptHash<<"EngineVersion"<<EngineVersion;

    //Check if script is already installed
    {
        QString GlobalFolder = (!IsRemote) ? "appslocal" : "appsremote";
        QString FullPath = GlobalFolder + QString("/") + ScriptName + QString("/SID") + ScriptHash + QString("/engine/FastExecuteScript.exe");
        qDebug()<<"AppPath"<<FullPath<<GlobalFolder + QString("/") + ScriptName + QString("/SID") + ScriptHash + QString("/engine/");
        QFileInfo info(FullPath);
        if(info.exists())
        {
            qDebug()<<"Run!";

            if(IsRemote)
            {
                QString FullPath = GlobalFolder + QString("/") + ScriptName + QString("/SID") + ScriptHash;

                QFile FileProjectXml(FullPath + "/engine/project.xml");
                if(FileProjectXml.open(QIODevice::WriteOnly))
                {
                    QXmlStreamWriter xmlWriter(&FileProjectXml);
                    xmlWriter.setAutoFormatting(true);
                    xmlWriter.writeStartDocument();

                    xmlWriter.writeStartElement("Remote");
                    xmlWriter.writeAttribute("ScriptName", ScriptName);
                    xmlWriter.writeAttribute("Version", "last");
                    xmlWriter.writeAttribute("Server", Server);
                    xmlWriter.writeAttribute("Username", Username);
                    xmlWriter.writeAttribute("Password", Password);
                    if(ForceFree)
                        xmlWriter.writeAttribute("Free", "true");
                    xmlWriter.writeAttribute("Mode", "1");

                    xmlWriter.writeEndElement();
                }

                FileProjectXml.close();
            }


            QStringList params;
            if(IsSilent)
                params.append("--silent");

            qDebug()<<QProcess::startDetached(FullPath,params,GlobalFolder + QString("/") + ScriptName + QString("/SID") + ScriptHash + QString("/engine/"));
            if(UI)
                UI->SetProgress(100);
            Exit();
            return;
        }
    }

    //Check if engine already downloaded
    {
        QString EnginesDir;
        EnginesDir = (IsRemote) ? "enginesprotected" : "engines";
        QString ProtectedAdd = (IsRemote) ? "Protected" : "";

        QString FullPath = EnginesDir + QString("/") + EngineVersion + QString("/engine.zip");
        qDebug()<<"EnginePath"<<FullPath;
        QFileInfo info(FullPath);
        if(info.exists())
        {
            emit EnginePrepared();
        }else
        {
            if(UI)
                UI->show();
            Client->Connect(this,SLOT(EngineDownloaded()));
            connect(Client,SIGNAL(DownloadProgress(qint64,qint64)),this,SLOT(DownloadProgress(qint64,qint64)));
            QString Arch = (IsX64) ? "64" : "32";
            QString EngineUrl = Server + QString("distr/FastExecuteScript") + ProtectedAdd + Arch + QString("/") + EngineVersion + QString("/FastExecuteScript") + ProtectedAdd + QString(".x") + Arch + QString(".zip");
            qDebug()<<"Downloading"<<EngineUrl;
            Client->Get(EngineUrl);
        }
    }
}

void Remote::DownloadProgress(qint64 BytesReceived, qint64 BytesTotal)
{
    if(BytesTotal && UI)
        UI->SetProgress(10 + (80 * BytesReceived) / BytesTotal);
}

void Remote::EngineDownloaded()
{
    if(Client->WasError())
    {
        if(IsSilent)
        {
            Exit();
        }else
        {
            UI->SetError(Client->GetErrorString());
        }
        return;
    }

    QString EnginesDir;
    EnginesDir = (IsRemote) ? "enginesprotected" : "engines";

    QDir dir(EnginesDir + QString("/") + EngineVersion);
    if(!dir.exists())
    {
        dir.mkpath(".");
    }

    QFile file(EnginesDir + QString("/") + EngineVersion + QString("/engine.zip"));
    if(!file.open(QIODevice::WriteOnly))
    {
        if(IsSilent)
        {
            Exit();
        }else
        {
            UI->SetError("Failed to write engine file");
        }
        return;
    }

    file.write(Client->GetPageData());
    file.close();

    emit EnginePrepared();
}


void Remote::EnginePrepared()
{
    qDebug()<<"EnginePrepared";
    if(UI)
    {
        UI->SetProgress(90);
        UI->hide();
    }



    //Remove temp file
    QString GlobalFolder = (!IsRemote) ? "appslocal" : "appsremote";
    QString FullPath = GlobalFolder + QString("/") + ScriptName + QString("/temp");
    {
        QDir dir(FullPath);
        if(!dir.removeRecursively())
        {
            if(IsSilent)
            {
                Exit();
            }else
            {
                UI->SetError("Failed to remove temp directory");
            }
        }
    }

    QString EnginesDir;
    EnginesDir = (IsRemote) ? "enginesprotected" : "engines";

    //Uncompress
    QStringList AllFiles = JlCompress::extractDir(EnginesDir + QString("/") + EngineVersion + QString("/engine.zip"),FullPath + "/engine");


    //Copy from prev install
    QString PreviousInstallation;
    {
        QDir dir = QDir(GlobalFolder + QString("/") + ScriptName);

        QStringList list = dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs);
        foreach(QString d, list)
        {
            if(d.startsWith("SID"))
            {
                PreviousInstallation = dir.absoluteFilePath(d);
                break;
            }

        }
    }

    if(!PreviousInstallation.isEmpty())
    {
        qDebug()<<"Copy files from "<<PreviousInstallation;

        QStringList FileList;
        QFile FileListFile(PreviousInstallation + "/engine/filelist.txt");
        if (FileListFile.open(QIODevice::ReadOnly))
        {
           QTextStream in(&FileListFile);
           while (!in.atEnd())
           {
              QString line = in.readLine();
              FileList.append(line);
           }
           FileListFile.close();
        }
        FileListFile.close();

        QDir dir = QDir(PreviousInstallation + "/engine");
        QDirIterator it(dir.absolutePath(), QDir::NoDotAndDotDot | QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext())
        {
            QString f = it.next();
            bool Exclude = false;
            for(QString ExcludeFile: FileList)
            {
                if(f.endsWith(ExcludeFile))
                {
                    Exclude = true;
                    break;
                }
            }
            if(!Exclude)
            {
                QString fa = f;
                QString fr = f.replace(dir.absolutePath(),"");
                fr = FullPath + "/engine" + fr;
                qDebug() << fa << "->" << fr;
                {
                    QDir d(fr);
                    d.mkpath("..");
                }
                QFile::copy(fa, fr);
            }
        }

    }

    //Save filelist.txt
    {
        QFile file(FullPath + "/engine/filelist.txt");
        if(!file.open(QIODevice::WriteOnly))
        {
            if(IsSilent)
            {
                Exit();
            }else
            {
                UI->SetError("Failed to write engine file");
            }
            return;
        }

        QStringList AllFilesRelative;
        for(QString s: AllFiles)
        {
            if(QFileInfo(s).isFile())
            {
                AllFilesRelative.append(s.replace(QDir(FullPath + "/engine").absolutePath(),""));
            }
        }
        AllFilesRelative.append("/filelist.txt");
        AllFilesRelative.append("/project.xml");



        QString allfiles = AllFilesRelative.join("\r\n");

        file.write(allfiles.toUtf8());

        file.close();
    }

    //Safe project.xml
    if(IsRemote)
    {
        QFile FileProjectXml(FullPath + "/engine/project.xml");
        if(FileProjectXml.open(QIODevice::WriteOnly))
        {
            QXmlStreamWriter xmlWriter(&FileProjectXml);
            xmlWriter.setAutoFormatting(true);
            xmlWriter.writeStartDocument();

            xmlWriter.writeStartElement("Remote");
            xmlWriter.writeAttribute("ScriptName", ScriptName);
            xmlWriter.writeAttribute("Version", "last");
            xmlWriter.writeAttribute("Server", Server);
            xmlWriter.writeAttribute("Username", Username);
            xmlWriter.writeAttribute("Password", Password);
            if(ForceFree)
                xmlWriter.writeAttribute("Free", "true");
            xmlWriter.writeAttribute("Mode", "1");

            xmlWriter.writeEndElement();
        }

        FileProjectXml.close();
    }else
    {
        QFile::copy("project.xml", FullPath + "/engine/project.xml");
    }

    //Rename dir
    {
        QDir dir;
        if(!dir.rename(FullPath, GlobalFolder + QString("/") + ScriptName + QString("/") + ScriptHash))
        {
            if(IsSilent)
            {
                Exit();
            }else
            {
                UI->SetError("Failed to rename dir");
            }
        }
    }

    //Remove old
    if(!PreviousInstallation.isEmpty())
    {
        qDebug()<<"Remove old";
        QDir dir(PreviousInstallation);
        dir.removeRecursively();
    }

    //Run exe
    qDebug()<<"Run!";
    QStringList params;
    if(IsSilent)
        params.append("--silent");
    QProcess::startDetached(GlobalFolder + QString("/") + ScriptName + QString("/") + ScriptHash + "/engine/FastExecuteScript.exe",params,GlobalFolder + QString("/") + ScriptName + QString("/") + ScriptHash + QString("/engine/"));
    if(UI)
        UI->SetProgress(100);
    Exit();
    return;
}

bool Remote::Start(const QStringList& Arguments)
{
    this->Arguments = Arguments;

    DetectSettings();
    if(!IsSilent)
    {
        UI = new DownloadingWidget();
        connect(UI,SIGNAL(Cancel()),this,SLOT(Exit()));

        UI->hide();
    }
    if(!IsValid)
    {
        if(IsSilent)
        {
            return false;
        }else
        {
            UI->SetError(ErrorMessage);
            return true;
        }
    }


    DetectScriptProperties();

    return true;
}

