#include "antigatecaptchasolver.h"
#include <QHash>
#include <QStringList>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    AntigateCaptchaSolver::AntigateCaptchaSolver(QObject *parent) :
        ISolver(parent),Iterator(0),StartedMonitor(false),timeout(8000), MultipleIds(true)
    {
        Server = "http://antigate.com/";
    }

    void AntigateCaptchaSolver::SetSoftId(const QString& SoftId)
    {
        this->SoftId = SoftId;
    }

    void AntigateCaptchaSolver::SetMultipleIds(bool MultipleIds)
    {
        this->MultipleIds = MultipleIds;
    }

    void AntigateCaptchaSolver::StartMonitor()
    {
        if(!StartedMonitor)
        {
            HttpClient = HttpClientFactory->GetHttpClient();
            HttpClient->setParent(this);
            timer.setSingleShot(true);
            timer.start(timeout);
            connect(&timer, SIGNAL(timeout()), this, SLOT(StartIteration()));
            StartedMonitor = true;
        }

    }

    void AntigateCaptchaSolver::SetServer(const QString& Server)
    {
        this->Server = Server;
    }

    void AntigateCaptchaSolver::StartSingleIteration()
    {
        QTimer * Timer = qobject_cast<QTimer*>(sender());

        if(!Timer)
            return;

        SingleIdWorker *Worker = 0;
        for(SingleIdWorker* w: Workers)
        {
            if(Timer == w->timer)
                Worker = w;
        }
        if(!Worker)
            return;

        Worker->client->Connect(this,SLOT(DoneSignleIteration()));
        QString url = QString(Server + "res.php?key=%1&action=get&id=%2").arg(key).arg(Worker->antigate_id);
        Worker->client->Get(url);
        //qDebug()<<"Sending"<<url<<"Length"<<Workers.size();
    }

    void AntigateCaptchaSolver::StartIteration()
    {
        QString ids = "";
        QList<QString> keys = IdToAntigateIdList.keys();
        int size = IdToAntigateIdList.size();
        for(int i = 0;i<size;i++)
        {
           if(i)
               ids.append(",");
           ids.append(keys.at(i));
        }
        if(size>0)
        {
            HttpClient->Connect(this,SLOT(DoneIteration()));
            HttpClient->Get(QString(Server + "res.php?key=%1&action=get&ids=%2").arg(key).arg(ids));
        }else
        {
            timer.start(timeout);
        }
    }


    void AntigateCaptchaSolver::DoneSignleIteration()
    {
        IHttpClient * Client = qobject_cast<IHttpClient*>(sender());

        if(!Client)
            return;

        SingleIdWorker *Worker = 0;
        for(SingleIdWorker* w: Workers)
        {
            if(Client == w->client)
                Worker = w;
        }
        if(!Worker)
            return;

        if(Worker->client->WasError())
        {
            Worker->timer->start(timeout);
            return;
        }

        QString res = Worker->client->GetContent();

        //qDebug()<<"Received"<<res<<"Length"<<Workers.size();

        if(res!="CAPCHA_NOT_READY")
        {
            bool Success = false;
            if(res.startsWith("OK|"))
            {
                res = res.remove(0,3);
                Success = true;
            }
            emit Done(res,Worker->id,Success,Worker->antigate_id);
            Workers.removeAll(Worker);
            Worker->deleteLater();

            //qDebug()<<"Finished"<<res<<Worker->id<<Success<<Worker->antigate_id<<"Length"<<Workers.size();
        }else
        {
            Worker->timer->start(timeout);
        }
    }

    void AntigateCaptchaSolver::DoneIteration()
    {

        if(HttpClient->WasError())
        {
            timer.start(timeout);
            return;
        }

        QString res = HttpClient->GetContent();

        QStringList list = res.split("|");
        if(list.size()!=IdToAntigateIdList.size())
        {
            timer.start(timeout);
            return;
        }
        QList<QString> v = IdToAntigateIdList.values();
        QList<QString> k = IdToAntigateIdList.keys();
        QList<QString> to_delete;
        for(int i = 0;i<list.size();i++)
        {
            if(list[i]!="CAPCHA_NOT_READY")
            {
                to_delete.append(k[i]);
                emit Done(list[i],v[i],true,k[i]);
            }
        }
        foreach(QString d, to_delete)
            IdToAntigateIdList.remove(d);
        timer.start(timeout);
    }


    QString AntigateCaptchaSolver::Solve(const QString& base64,const QStringList& props)
    {
        QMap<QString,QString> Properties;
        bool isname = true;
        QString name = "";
        bool DisableImageConvert = false;
        foreach(QString str, props)
        {
            if(isname)
            {
                name = str;
            }else
            {
                if(name == "key")
                {
                    key = str;
                }else if(name == "bas_disable_image_convert")
                {
                    DisableImageConvert = str.toInt();
                }else if(name == "serverurl")
                {
                    Server = str;
                }else if(name == "timeout")
                {
                }
                else if(!str.isEmpty())
                {
                    Properties.insert(name,str);
                }

            }
            isname = !isname;
        }

        emit Used();
        QString i = QString::number(Iterator++);
        PostToAntigate * post = new PostToAntigate(this);
        post->SetServer(Server);
        IHttpClient * client = HttpClientFactory->GetHttpClient();
        client->setParent(post);
        post->SetHttpClient(client);
        connect(post,SIGNAL(PostedToAntigate(QString,QString,bool)),this,SLOT(PostedToAntigate(QString,QString,bool)));
        post->Post(i,key,base64,Properties,SoftId,DisableImageConvert);
        return i;
    }

    void AntigateCaptchaSolver::PostedToAntigate(const QString& antigate_id, const QString& id, bool res)
    {
        sender()->deleteLater();
        if(res)
        {
            if(MultipleIds)
            {
                IdToAntigateIdList[antigate_id] = id;
                StartMonitor();
            }else
            {
                SingleIdWorker * Worker = new SingleIdWorker();
                Worker->setParent(this);
                Worker->id = id;
                Worker->antigate_id = antigate_id;
                Worker->timer = new QTimer(Worker);

                Worker->client = HttpClientFactory->GetHttpClient();
                Worker->client->setParent(Worker);
                Worker->timer->setSingleShot(true);
                Worker->timer->start(timeout);
                connect(Worker->timer, SIGNAL(timeout()), this, SLOT(StartSingleIteration()));
                Workers.append(Worker);
            }
        }
        else
            emit Done(antigate_id,id,false,0);

    }

    void AntigateCaptchaSolver::ReportBad(const QString& id)
    {
        emit Failed();
        IHttpClient * client = HttpClientFactory->GetHttpClient();
        client->setParent(this);
        client->Connect(this,SLOT(DeleteSender()));
        QString url = Server + "res.php?action=reportbad&id=" + id + "&key=" + key;
        client->Get(url);
    }

    void AntigateCaptchaSolver::DeleteSender()
    {
        //IHttpClient *Client = qobject_cast<IHttpClient *>(sender());
        sender()->deleteLater();
    }

    void AntigateCaptchaSolver::SetHttpClientFactory(IHttpClientFactory * HttpClientFactory)
    {
        this->HttpClientFactory = HttpClientFactory;
    }

    IHttpClientFactory * AntigateCaptchaSolver::GetHttpClientFactory()
    {
        return HttpClientFactory;
    }

    bool AntigateCaptchaSolver::TimeLimited()
    {
        return true;
    }
}
