#include "moduledll.h"
#include <stdio.h>
#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QDateTime>
#include <QTextStream>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDirIterator>
#include <QProcess>


extern "C" {

    void* StartDll()
    {

        QDir dir(".");
        dir.setNameFilters(QStringList() << "temp_*.bat");
        dir.setFilter(QDir::Files);
        foreach(QString dirFile, dir.entryList())
        {
            dir.remove(dirFile);
        }
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


    void ProcessManagerRunExe(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {

        QString location;
        QString arguments;
        bool waitfinish;
        {
            QJsonDocument InputObject;
            QJsonParseError err;
            InputObject = QJsonDocument::fromJson(QByteArray(InputJson),&err);
            if(err.error)
                return;
            location = InputObject.object()["location"].toString();
            arguments = InputObject.object()["arguments"].toString();

            waitfinish = InputObject.object()["waitfinish"].toBool();
        }



        if(!waitfinish)
        {
            if(arguments.isEmpty())
            {
                QProcess::startDetached(location,QStringList(),QFileInfo(location).absoluteDir().absolutePath());
            }else
                QProcess::startDetached(location,arguments.split(" "),QFileInfo(location).absoluteDir().absolutePath());

            return;
        }


        QProcess p;
        p.setWorkingDirectory(QFileInfo(location).absoluteDir().absolutePath());
        if(arguments.isEmpty())
        {
            p.start(location);
        }else
            p.start(location,arguments.split(" "));



        while(p.state() != QProcess::NotRunning)
        {
            if(*NeedToStop)
            {
                p.kill();
                return;
            }
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }

        QString res = p.readAllStandardOutput();

        QByteArray ResArray = res.toUtf8();

        char * ResMemory = AllocateSpace(ResArray.size(),AllocateData);
        memcpy(ResMemory, ResArray.data(), ResArray.size() );
    }

}
