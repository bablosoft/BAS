#include "processcomunicatorfactory.h"
#include "pipesprocesscomunicator.h"
#include <QCoreApplication>
#include "every_cpp.h"



namespace BrowserAutomationStudioFramework
{

    ProcessComunicatorFactory::ProcessComunicatorFactory(QObject *parent) :
        IProcessComunicatorFactory(parent)
    {
        Server = new QLocalServer(this);
        connect(Server,SIGNAL(newConnection()),this,SLOT(NewConnection()));
        Server->listen(QString("\\\\.\\pipe\\basworkerpipes") + QString::number(qApp->applicationPid()));
        Compress = new SnappyStringCompress(this);
    }

    void ProcessComunicatorFactory::NewConnection()
    {
        QLocalSocket *Client = Server->nextPendingConnection();

        if(!Client)
            return;

        connect(Client,SIGNAL(disconnected()),this,SLOT(Finished()));

        LocalServerData Data = std::make_shared<ProcessComunicatorFactory::LocalServerDataClass>();

        Sockets[Client] = Data;


        connect(Client,SIGNAL(readyRead()),this,SLOT(Income()));

    }

    QLocalSocket * ProcessComunicatorFactory::FindLocalServerByKey(const QString& Key)
    {
        QHashIterator<QLocalSocket *,LocalServerData> i(Sockets);
        while (i.hasNext())
        {
            i.next();
            if(i.value()->key == Key)
                return i.key();
        }
        return 0;
    }


    void ProcessComunicatorFactory::Send(const QString& key, const QString& data)
    {
        QLocalSocket *Client = FindLocalServerByKey(key);
        if(Client)
        {
            Client->write(QString("<Messages>" + Compress->Compress(data) + "</Messages>").toUtf8());
            Client->flush();
        }else
        {
            if(ToSend.contains(key))
            {
                ToSend[key].append(data);
            }else
            {
                ToSend[key] = data;
            }
        }
    }

    void ProcessComunicatorFactory::Finished()
    {
        QLocalSocket *Client = (QLocalSocket *)(sender());
        if(Client)
        {
            if(Sockets.contains(Client))
            {
                QString key = Sockets[Client]->key;
                ToSend.remove(key);
                emit SocketStoped(key);
            }
            Sockets.remove(Client);


            Client->deleteLater();
        }

    }

    void ProcessComunicatorFactory::Income()
    {
        QLocalSocket *Client = (QLocalSocket *)(sender());

        if(!Sockets.contains(Client))
            return;

        LocalServerData Data = Sockets[Client];

        Data->data.append(Client->readAll());
        QString str = QString::fromUtf8(Data->data);

        {
            bool cont = true;
            bool changed = false;
            while(cont)
            {
                cont = false;
                int s = str.indexOf("<Key>");

                if(s>=0)
                {
                    int e = str.indexOf("</Key>",s);
                    if(e>=0)
                    {
                        changed = true;
                        QString mid = str.mid(s+5,e-s+6 - 5 - 6);
                        str.remove(0,e+6);
                        Data->key = mid;
                        emit KeyStart(mid);
                        if(ToSend.contains(mid))
                        {
                            Send(mid,ToSend[mid]);
                            ToSend.remove(mid);
                        }
                        break;
                    }
                }

            }
            if(changed)
            {
                Data->data = str.toUtf8();
            }
        }

        {
            bool cont = true;
            bool changed = false;
            while(cont)
            {
                cont = false;
                int s = str.indexOf("<Messages>");

                if(s>=0)
                {
                    int e = str.indexOf("</Messages>",s);
                    if(e>=0)
                    {
                        changed = true;
                        QString mid = str.mid(s + 10,e-s-10);
                        str.remove(0,e+11);

                        emit Received(Data->key, "<Messages>" + Compress->Uncompress(mid) + "</Messages>");
                        cont = true;
                    }
                }

            }
            if(changed)
            {
                Data->data = str.toUtf8();
            }
        }

    }


    IProcessComunicator * ProcessComunicatorFactory::CreateProcessComunicator()
    {
        PipesProcessComunicator * res = new PipesProcessComunicator();
        connect(this,SIGNAL(Received(QString,QString)),res,SLOT(ReceivedAll(QString,QString)));
        connect(res,SIGNAL(SendSignal(QString,QString)),this,SLOT(Send(QString,QString)));
        connect(this,SIGNAL(KeyStart(QString)),res,SLOT(ProcessStartedAll(QString)));
        connect(this,SIGNAL(SocketStoped(QString)),res,SLOT(ProcessStoppedAll(QString)));

        res->SetCommandLineParams(Params);
        emit ProcessComunicatorCreated(res);
        return res;
    }

    void ProcessComunicatorFactory::SetCommandLineParams(const QStringList& Params)
    {
        this->Params = Params;
    }

}
