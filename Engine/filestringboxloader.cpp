#include "filestringboxloader.h"
#include <QDir>
#include <QTextStream>
#include "every_cpp.h"
namespace BrowserAutomationStudioFramework
{
    FileStringBoxLoader::FileStringBoxLoader(QObject *parent) :
        IStringBoxLoader(parent)
    {
        CurrentFile = 0;
        CurrentStreamPosition = 0;
        CurrentFileListIterator = 0;
        WaitingForNewPortionReuqest = false;
        Read = true;
        Write = false;
    }

    void FileStringBoxLoader::SetRead(bool Read)
    {
        this->Read = Read;
    }

    void FileStringBoxLoader::SetWrite(bool Write)
    {
        this->Write = Write;
    }

    void FileStringBoxLoader::SetFileName(const QString& FileName)
    {
        this->FileName = FileName;
    }


    bool FileStringBoxLoader::LoadFile(const QString& file)
    {
        if(!CurrentFile)
        {
            CurrentFile = new QFile(file, this);
            if (!CurrentFile->open(QIODevice::ReadOnly))
            {
                CurrentFile->close();
                CurrentFile->deleteLater();
                CurrentFile = 0;
                CurrentStreamPosition = 0;
                return true;
            }
        }

        QTextStream in(CurrentFile);
        in.setCodec("UTF-8");
        if(!in.seek(CurrentStreamPosition))
        {
            CurrentFile->close();
            CurrentFile->deleteLater();
            CurrentFile = 0;
            CurrentStreamPosition = 0;
            return true;
        }

        while ( !in.atEnd() )
        {
            QString line = in.readLine();
            if(!line.isEmpty())
            {
                list.append(line);
            }
            if(list.length() > 1000000)
            {
                CurrentStreamPosition = in.pos();
                return false;
            }
        }


        CurrentFile->close();
        CurrentFile->deleteLater();
        CurrentFile = 0;
        CurrentStreamPosition = 0;
        return true;

    }

    void FileStringBoxLoader::Load()
    {
        if(!Read)
        {
            emit DataLoadedCompletely();
            emit Loaded(list);
            list.clear();
            WaitingForNewPortionReuqest = false;
            return;
        }
        if(WaitingForNewPortionReuqest)
        {
            for(;CurrentFileListIterator<CurrentFileList.length();CurrentFileListIterator++)
            {
                if(!LoadFile(CurrentFileList.at(CurrentFileListIterator)))
                {
                    emit Loaded(list);
                    list.clear();
                    return;
                }

            }

            emit DataLoadedCompletely();
            emit Loaded(list);
            list.clear();
            WaitingForNewPortionReuqest = false;
            return;
        }


        list.clear();
        WaitingForNewPortionReuqest = true;
        if(FileName.contains("|"))
        {
            CurrentFileList.clear();
            CurrentFileListIterator = 0;
            foreach(QString SingleFileName, FileName.split("|"))
            {
                QFileInfo info(SingleFileName);
                if(info.isFile())
                {
                    CurrentFileList.append(SingleFileName);
                }
            }


            foreach(QString SingleFileName,CurrentFileList)
            {
                if(!LoadFile(SingleFileName))
                {
                    emit Loaded(list);
                    list.clear();
                    return;
                }

                CurrentFileListIterator++;
            }

        }else
        {
            QFileInfo info(FileName);

            if(info.isFile())
            {
                CurrentFileList.clear();
                CurrentFileList.append(FileName);
                CurrentFileListIterator = 0;
                if(!LoadFile(FileName))
                {
                    emit Loaded(list);
                    list.clear();
                    return;
                }
            }else if(info.isDir())
            {
                QDir directory(FileName);
                CurrentFileList.clear();
                CurrentFileListIterator = 0;
                foreach(QString file, directory.entryList())
                {
                    QString filename = directory.filePath(file);
                    QFileInfo i(filename);
                    if(i.isFile() && !filename.endsWith(".temp"))
                    {
                        CurrentFileList.append(filename);
                    }
                }

                foreach(QString file, CurrentFileList)
                {
                    if(!LoadFile(file))
                    {
                        emit Loaded(list);
                        list.clear();
                        return;
                    }

                    CurrentFileListIterator++;
                }
            }
        }
        emit DataLoadedCompletely();
        emit Loaded(list);
        list.clear();
        WaitingForNewPortionReuqest = false;

    }


    void FileStringBoxLoader::CleanFile(const QString& file)
    {
        if(!Read)
        {
            QFileInfo info(file);
            if(!info.exists())
            {
                info.absoluteDir().mkpath(".");
            }
        }
        if(!ToAdd.empty() && ToRemove.empty())
        {
            QFile outputFile(file);
            if(outputFile.open(QIODevice::WriteOnly | QIODevice::Append))
            {
                QTextStream out(&outputFile);
                out.setCodec("UTF-8");
                for(QString AddString:ToAdd)
                {
                    out<<AddString<<"\r\n";
                }
                outputFile.close();
            }

        }else
        {
            QFile inputFile(file);
            QFile outputFile(file + ".temp");
            outputFile.remove();

            if (inputFile.open(QIODevice::ReadOnly))
            {
                QTextStream in(&inputFile);
                in.setCodec("UTF-8");
                if(outputFile.open(QIODevice::WriteOnly))
                {
                    QTextStream out(&outputFile);
                    out.setCodec("UTF-8");
                    while ( !in.atEnd() )
                    {
                        QString line = in.readLine();
                        if(!line.isEmpty() && !ToRemove.contains(line))
                        {
                            out<<line<<"\r\n";
                        }
                    }
                    for(QString AddString:ToAdd)
                    {
                        out<<AddString<<"\r\n";
                    }
                }
            }
            inputFile.close();

            if(inputFile.remove())
            {
                outputFile.rename(inputFile.fileName());
            }else
            {
                outputFile.close();
                outputFile.remove();
            }
        }
        ToAdd.clear();

    }

    void FileStringBoxLoader::ForceSync()
    {
        Sync(true);
    }

    void FileStringBoxLoader::Sync(bool Force)
    {
        if(FileName.isEmpty())
            return;
        if((!ToRemove.isEmpty() || !ToAdd.isEmpty()) && (Force || Write))
        {
            if(FileName.contains("|"))
            {
                foreach(QString SingleFileName,FileName.split("|"))
                {
                    QFileInfo info(SingleFileName);
                    if(info.isFile())
                        CleanFile(SingleFileName);
                }

            }else
            {
                QFileInfo info(FileName);
                if(info.isFile() || !Read)
                {
                    CleanFile(FileName);
                }else if(info.isDir())
                {
                    QDir directory(FileName);
                    QStringList files = directory.entryList();
                    foreach(QString file, files)
                    {
                        QString filename = directory.filePath(file);
                        QFileInfo i(filename);
                        if(i.isFile() && !filename.endsWith(".temp"))
                        {
                            CleanFile(filename);
                        }
                    }
                }
            }
            ToRemove.clear();
        }

    }

    FileStringBoxLoader::~FileStringBoxLoader()
    {
        Sync(false);
    }

    void FileStringBoxLoader::ItemDeleted(const QString& item)
    {
        if(FileName.isEmpty())
            return;
        ToRemove.append(item);
        ToAdd.removeAll(item);
        if(ToRemove.length() + ToAdd.length()>100000)
        {
            Sync(false);
        }
    }

    void FileStringBoxLoader::ItemAdded(const QString& item)
    {
        if(FileName.isEmpty())
            return;
        ToRemove.removeAll(item);
        ToAdd.append(item);
        if(ToRemove.length() + ToAdd.length()>100000)
        {
            Sync(false);
        }
    }
}
