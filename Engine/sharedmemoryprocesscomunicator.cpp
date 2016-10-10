#include "sharedmemoryprocesscomunicator.h"
#include <QEventLoop>
#include "every_cpp.h"



namespace BrowserAutomationStudioFramework
{
    SharedMemoryProcessComunicator::SharedMemoryProcessComunicator(QObject *parent) :
        IProcessComunicator(parent),Process(0)
    {
        MemoryIn = new QSharedMemory(this);
        MemoryOut = new QSharedMemory(this);
        Server = 0;
        Client = 0;

    }

    void SharedMemoryProcessComunicator::SetLocation(const QString& Location)
    {
        this->Location = Location;
    }

    void SharedMemoryProcessComunicator::Suspend()
    {
        emit OnSuspend();
    }

    void SharedMemoryProcessComunicator::CreateProcess(const QStringList& arguments)
    {
        Abort();
        SendArray.clear();
        const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
        QString key_in = "";
        QString key_out = "";

        for(int i = 0;i<10;i++)
        {
            key_in += QString(alphanum[qrand() % (sizeof(alphanum) - 1)]);
            key_out += QString(alphanum[qrand() % (sizeof(alphanum) - 1)]);
        }

        MemoryIn->setKey(key_in);
        if(!MemoryIn->create(256*1024))
        {
            isError = true;
            errorString = MemoryIn->errorString();
            emit Error();
            return;
        }
        if(!MemoryIn->lock())
        {
            isError = true;
            errorString = MemoryIn->errorString();
            emit Error();
            return;
        }
        ((char *)MemoryIn->data())[0] = 0;
        MemoryIn->unlock();
        MemoryOut->setKey(key_out);
        if(!MemoryOut->create(256*1024))
        {
            isError = true;
            errorString = MemoryOut->errorString();
            emit Error();
            return;
        }
        if(!MemoryOut->lock())
        {
            isError = true;
            errorString = MemoryOut->errorString();
            emit Error();
            return;
        }
        ((char *)MemoryOut->data())[0] = 0;
        MemoryOut->unlock();

        Process = new QProcess(this);
        connect(Process,SIGNAL(finished(int)),this,SLOT(UnexpectedFinished()));
        connect(Process,SIGNAL(started()),this,SIGNAL(ProcessStarted()));
        connect(Process,SIGNAL(readyReadStandardOutput()),this,SLOT(InThread()));

        Process->start(Location,QStringList()<<key_in<<key_out);

        Server = new QLocalServer(this);
        connect(Server,SIGNAL(newConnection()),this,SLOT(newConnection()));
        if(!Server->listen("SERVER" + key_in))
        {
            isError = true;
            errorString = QString("Failed to start listen server %1").arg(Server->errorString());
            emit Error();
        }


    }

    void SharedMemoryProcessComunicator::newConnection()
    {
        Client = Server->nextPendingConnection();
        connect(Client,SIGNAL(readyRead()),this,SLOT(Income()));
        if(!SendArray.isEmpty())
        {
            SignalDataExist();
        }
    }

    void SharedMemoryProcessComunicator::Connected()
    {

        connect(Client,SIGNAL(readyRead()),this,SLOT(Income()));
        if(!SendArray.isEmpty())
        {
            SignalDataExist();
        }
    }

    void SharedMemoryProcessComunicator::SignalDataExist()
    {

        if(Client)
        {
            OutThread();
            Client->write("a");
            Client->flush();
        }
    }


    void SharedMemoryProcessComunicator::Income()
    {
        Client->readAll();
        InThread();
    }

    void SharedMemoryProcessComunicator::Abort()
    {
        if(Server)
            Server->close();

        if(Client)
            Client->close();

        if(Process)
        {
            Process->kill();
            Process->deleteLater();
            Process = 0;
        }

        if(MemoryIn->isAttached())
            MemoryIn->detach();

        if(MemoryOut->isAttached())
            MemoryOut->detach();
    }

    SharedMemoryProcessComunicator::~SharedMemoryProcessComunicator()
    {
        Abort();
    }

    void SharedMemoryProcessComunicator::UnexpectedFinished()
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

    void SharedMemoryProcessComunicator::ConnectToProcess(const QString& key_in, const QString& key_out)
    {
        Abort();
        MemoryIn->setKey(key_in);
        MemoryOut->setKey(key_out);
        bool InAttach = MemoryIn->attach();
        if(!InAttach)
        {
            isError = true;
            errorString = MemoryIn->errorString();
            emit Error();
            return;
        }
        bool OutAttach = MemoryOut->attach();
        if(!OutAttach)
        {
            isError = true;
            errorString = MemoryOut->errorString();
            emit Error();
            return;
        }
        Client = new QLocalSocket(this);
        connect(Client,SIGNAL(connected()),this,SLOT(Connected()));
        Client->connectToServer("SERVER" + key_out);
    }

    void SharedMemoryProcessComunicator::Send(const QString& value)
    {
        SendArray.append(value);
        SignalDataExist();
    }

    void SharedMemoryProcessComunicator::OutThread()
    {
        if(SendArray.isEmpty())
        {
            return;
        }
        if(MemoryOut->lock())
        {
            QString Data = "<Messages>";
            int total_left = 256*1024-21;
            bool added = false;
            foreach(QString el,SendArray)
            {
                if(total_left - el.size()>=0)
                {
                    Data += el;
                    added = true;
                }else
                    break;
            }

            if(!added)
            {
                isError = true;
                errorString = "Message " + SendArray.at(0).left(100) + "... is too big";
                SendArray.removeAt(0);
                MemoryOut->unlock();
                emit Error();
                return;
            }

            Data += "</Messages>";
            char *to = (char*)MemoryOut->data();
            if(*to == 0)
            {
                QByteArray b = Data.toUtf8();
                const char *from = b.data();
                int len = strlen(from);

                memcpy(to, from , len);
                to[len] = 0;
                SendArray.clear();
            }
        }
        MemoryOut->unlock();

    }

    void SharedMemoryProcessComunicator::InThread()
    {
        QString res;
        if(MemoryIn->lock())
        {
            char *from = (char*)MemoryIn->data();
            if(*from != 0)
            {
                res = QString::fromUtf8(from);

                emit Received(res);
                *from = 0;
            }

        }
        MemoryIn->unlock();
    }

    bool SharedMemoryProcessComunicator::IsError()
    {
        return isError;
    }
    QString SharedMemoryProcessComunicator::ErrorString()
    {
        return errorString;
    }
}
