#include "pipesprocesscomunicator.h"
#include <QCoreApplication>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    PipesProcessComunicator::PipesProcessComunicator(QObject *parent) :
        IProcessComunicator(parent)
    {
        Process = 0;
        isError = false;
    }

    void PipesProcessComunicator::Suspend()
    {
        emit OnSuspend();
    }

    void PipesProcessComunicator::SetLocation(const QString& Location)
    {
        this->Location = Location;
    }

    void PipesProcessComunicator::SetCommandLineParams(const QStringList& Params)
    {
        this->Params = Params;
    }

    void PipesProcessComunicator::CreateProcess(const QStringList& arguments)
    {
        Arguments = arguments;
        Abort();

        const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
        key.clear();

        for(int i = 0;i<10;i++)
        {
            key += QString(alphanum[qrand() % (sizeof(alphanum) - 1)]);
        }


        Process = new QProcess(this);
        connect(Process,SIGNAL(finished(int)),this,SLOT(UnexpectedFinished()));
        //connect(Process,SIGNAL(started()),this,SIGNAL(ProcessStarted()));

        //connect(Server2,SIGNAL(newConnection()),this,SLOT(newConnection2()));
        //qDebug()<<"Started"<<key<<Server->isListening();

        //Process->setProgram();
        //Process->setArguments(QStringList()<<key_in<<key_out);
        /*Process->setProgram("xterm");
        Process->setArguments(QStringList()<<"-hold"<<"-e"<<Location<<key_in<<key_out);*/

        QString CurrentPid = QString::number(qApp->applicationPid());

        QStringList ParamsCopy = Params;
        for(int i = 0;i<ParamsCopy.length();i++)
        {
            QString str = ParamsCopy[i];
            if(str.contains("%keyin%"))
            {
                str = str.replace("%keyin%",key);
                ParamsCopy[i] = str;
            }else if(str.contains("%keyout%"))
            {
                str = str.replace("%keyout%","none");
                ParamsCopy[i] = str;
            }else if(str.contains("%pid%"))
            {
                str = str.replace("%pid%",CurrentPid);
                ParamsCopy[i] = str;
            }

        }
        ParamsCopy = arguments + ParamsCopy;
        //qDebug()<<"Location"<<Location<<ParamsCopy;
        Process->start(Location,ParamsCopy);
    }

    void PipesProcessComunicator::ReceivedAll(const QString& key, const QString& data)
    {
        if(key == this->key)
        {
            emit Received(data);
        }
    }

    void PipesProcessComunicator::ProcessStartedAll(const QString& key)
    {
        if(key == this->key)
            emit ProcessStarted();
    }

    void PipesProcessComunicator::ProcessStoppedAll(const QString& key)
    {
        if(key == this->key)
            emit Abort();
    }


    void PipesProcessComunicator::UnexpectedFinished()
    {
        if(Process)
        {
            isError = true;
            errorString = "Process finished unexpectedly";
            Abort();
            emit ProcessFinished();
            emit Error();
            return;
        }
    }

    void PipesProcessComunicator::AbortByUser()
    {
        if(Process)
        {
            Process->kill();
            Process->deleteLater();
            Process = 0;
        }
    }


    void PipesProcessComunicator::Abort()
    {
        if(Process)
        {
            Process->kill();
            Process->deleteLater();
            Process = 0;
        }

    }
    void PipesProcessComunicator::Send(const QString& value)
    {
        if(!Process)
        {
            CreateProcess(Arguments);
        }else
        {
            //qDebug()<<"Send"<<value<<Process;
            emit SendSignal(key, value);
        }
    }

    bool PipesProcessComunicator::HasProcess()
    {
        return Process;
    }


    void PipesProcessComunicator::ConnectToProcess(const QString& key_in, const QString& key_out)
    {

    }

    bool PipesProcessComunicator::IsError()
    {
        return isError;
    }

    QString PipesProcessComunicator::ErrorString()
    {
        return errorString;
    }

}


