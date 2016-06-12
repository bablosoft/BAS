#include "moduledll.h"
#include <stdio.h>
#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDirIterator>


extern "C" {

    void* StartDll()
    {

        return 0;
    }



    void EndDll(void * DllData)
    {

    }

    void* StartThread()
    {
        return 0;
    }

    void EndThread(void * DllData)
    {

    }


    void FileSystemReadFile(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        QString filename;
        bool isbase64;
        int from;
        int to;
        {
            QJsonDocument InputObject;
            QJsonParseError err;
            InputObject = QJsonDocument::fromJson(QByteArray(InputJson),&err);
            if(err.error)
                return;
            filename = InputObject.object()["value"].toString();
            isbase64 = InputObject.object()["base64"].toBool();
            from = InputObject.object()["from"].toInt();
            to = InputObject.object()["to"].toInt();
        }
        QFileInfo info(filename);
        if(!info.exists())
            return;

        int size = info.size();

        if(to > size)
            to = size;

        if(from > size)
            from = size;

        if(from > to)
            return;

        if(to == 0 && from == 0)
            to = size;

        QFile f(filename);

        if (!f.open(QFile::ReadOnly))
            return;

        if(!f.seek(from))
        {
            f.close();
            return;
        }

        QByteArray res = f.read(to - from);

        f.close();

        if(isbase64)
            res = res.toBase64();

        char * ResMemory = AllocateSpace(res.size(),AllocateData);
        memcpy(ResMemory, res.data(), res.size() );
    }

    void FileSystemWriteFile(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        QString path;
        QString value;
        bool base64;
        bool append;
        {
            QJsonDocument InputObject;
            QJsonParseError err;
            InputObject = QJsonDocument::fromJson(QByteArray(InputJson),&err);
            if(err.error)
                return;
            path = InputObject.object()["path"].toString();
            value = InputObject.object()["value"].toString();
            base64 = InputObject.object()["base64"].toBool();
            append = InputObject.object()["append"].toBool();
        }

        QFileInfo info(path);
        if(!QDir(info.absoluteDir()).mkpath("."))
            return;

        QFile file(path);

        QIODevice::OpenMode flags = QIODevice::WriteOnly;
        if(append)
        {
            flags = flags | QIODevice::Append;
        }
        if(!file.open(flags))
            return;

        if(base64)
        {
            file.write(QByteArray::fromBase64(value.toLatin1()));
        }else
        {
            file.write(value.toUtf8());
        }
        file.close();
    }

    void FileSystemFileInfo(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        QString path = QString::fromUtf8(InputJson);

        QFileInfo info(path);

        QVariantMap res;

        res.insert("exists", info.exists());
        res.insert("size", info.size());
        if(info.exists())
        {
            res.insert("directory", info.absoluteDir().absolutePath());
            res.insert("is_directory", !info.isFile());
            res.insert("last_modified", info.lastModified().toTime_t());
        }else
        {
            res.insert("directory", "");
            res.insert("is_directory", false);
            res.insert("last_modified", 0);
        }

        QJsonObject object = QJsonObject::fromVariantMap(res);

        QJsonDocument document;
        document.setObject(object);

        QByteArray ResArray = document.toJson();

        char * ResMemory = AllocateSpace(ResArray.size(),AllocateData);
        memcpy(ResMemory, ResArray.data(), ResArray.size() );
    }

    void FileSystemCreateDir(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        QDir(QString::fromUtf8(InputJson)).mkpath(".");
    }

    void FileSystemRemoveFile(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        QString FilePath = QString::fromUtf8(InputJson);
        QFileInfo Info(FilePath);
        if(Info.exists())
        {
            if(Info.isDir())
            {
                QDir(FilePath).removeRecursively();
            }else if(Info.isFile())
            {
                QFile(FilePath).remove();
            }
        }
    }

    void FileSystemMoveFile(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        QString path;
        QString dest;
        {
            QJsonDocument InputObject;
            QJsonParseError err;
            InputObject = QJsonDocument::fromJson(QByteArray(InputJson),&err);
            if(err.error)
                return;
            path = InputObject.object()["path"].toString();
            dest = InputObject.object()["dest"].toString();
        }
        QFileInfo InfoPath(path);
        if(InfoPath.exists())
        {
            if(InfoPath.isDir())
            {
                QDir(QFileInfo(dest).absoluteDir()).mkpath(".");
                QDir dir;
                dir.rename(path,dest);
            }else if(InfoPath.isFile())
            {
                QDir(QFileInfo(dest).absoluteDir()).mkpath(".");
                QFile(path).rename(dest);
            }
        }

    }

    bool copy_dir_recursive(QString from_dir, QString to_dir, bool replace_on_conflit)
    {
        QDir dir;
        dir.setPath(from_dir);

        from_dir += QDir::separator();
        to_dir += QDir::separator();

        foreach (QString copy_file, dir.entryList(QDir::Files))
        {
            QString from = from_dir + copy_file;
            QString to = to_dir + copy_file;

            if (QFile::exists(to))
            {
                if (replace_on_conflit)
                {
                    if (QFile::remove(to) == false)
                    {
                        return false;
                    }
                }
                else
                {
                    continue;
                }
            }

            if (QFile::copy(from, to) == false)
            {
                return false;
            }
        }

        foreach (QString copy_dir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
        {
            QString from = from_dir + copy_dir;
            QString to = to_dir + copy_dir;

            if (dir.mkpath(to) == false)
            {
                return false;
            }

            if (copy_dir_recursive(from, to, replace_on_conflit) == false)
            {
                return false;
            }
        }

        return true;
    }

    void FileSystemCopyFile(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        QString path;
        QString dest;
        {
            QJsonDocument InputObject;
            QJsonParseError err;
            InputObject = QJsonDocument::fromJson(QByteArray(InputJson),&err);
            if(err.error)
                return;
            path = InputObject.object()["path"].toString();
            dest = InputObject.object()["dest"].toString();
        }
        QFileInfo InfoPath(path);
        if(InfoPath.exists())
        {
            if(InfoPath.isDir())
            {
                QDir(dest).mkpath(".");
                copy_dir_recursive(path,dest,false);

            }else if(InfoPath.isFile())
            {
                QDir(QFileInfo(dest).absoluteDir()).mkpath(".");
                QFile(path).copy(dest);
            }
        }
    }


    void FileSystemSearch(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        QString folder;
        QString mask;
        QString contains;
        bool include_folders;
        bool include_files;
        bool recursive;
        {
            QJsonDocument InputObject;
            QJsonParseError err;
            InputObject = QJsonDocument::fromJson(QByteArray(InputJson),&err);
            if(err.error)
                return;
            folder = InputObject.object()["folder"].toString();
            mask = InputObject.object()["mask"].toString();
            contains = InputObject.object()["contains"].toString();

            include_folders = InputObject.object()["include_folders"].toBool();
            include_files = InputObject.object()["include_files"].toBool();
            recursive = InputObject.object()["recursive"].toBool();
        }

        QStringList masks = mask.split(";");

        QStringList FileList;

        QDir::Filters filters = QDir::NoDotAndDotDot;
        if(include_folders)
        {
            filters |= QDir::Dirs;
        }
        if(include_files)
        {
            filters |= QDir::Files;
        }
        QDirIterator::IteratorFlags flags = (recursive) ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags;

        QDirIterator it(folder, masks, filters, flags);
        while (it.hasNext())
        {
            if(*NeedToStop)
                return;
            QString filepath = it.next();
            if(contains.isEmpty())
            {
                FileList.append(filepath);
            }else
            {
                QFile file(filepath);
                if(file.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                    QTextStream in(&file);
                    in.setCodec("utf-8");
                    QString line;
                    do
                    {
                        line = in.readLine();
                        if (line.contains(contains, Qt::CaseSensitive))
                        {
                            FileList.append(filepath);
                            break;
                        }
                    } while (!line.isNull());
                    file.close();
                }
            }

        }

        QVariantMap res;
        res.insert("d", FileList);
        QJsonObject object = QJsonObject::fromVariantMap(res);
        QJsonDocument document;
        document.setObject(object);
        QByteArray ResArray = document.toJson();


        char * ResMemory = AllocateSpace(ResArray.size(),AllocateData);
        memcpy(ResMemory, ResArray.data(), ResArray.size() );
    }

}
