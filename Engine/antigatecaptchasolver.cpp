#include "antigatecaptchasolver.h"
#include <QHash>
#include <QStringList>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    AntigateCaptchaSolver::AntigateCaptchaSolver(QObject *parent) :
        ISolver(parent),Iterator(0),StartedMonitor(false),timeout(8000)
    {
        Server = "http://antigate.com/";
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


    QString AntigateCaptchaSolver::Solve(const QString& base64)
    {
        emit Used();
        QString i = QString::number(Iterator++);
        PostToAntigate * post = new PostToAntigate(this);
        post->SetServer(Server);
        IHttpClient * client = HttpClientFactory->GetHttpClient();
        client->setParent(post);
        post->SetHttpClient(client);
        connect(post,SIGNAL(PostedToAntigate(QString,QString,bool)),this,SLOT(PostedToAntigate(QString,QString,bool)));
        post->Post(i,key,base64,Properties);
        return i;
    }

    void AntigateCaptchaSolver::PostedToAntigate(const QString& antigate_id, const QString& id, bool res)
    {
        sender()->deleteLater();
        if(res)
        {
            IdToAntigateIdList[antigate_id] = id;
            StartMonitor();
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


    void AntigateCaptchaSolver::SetProperty(const QString& name,const QString& value)
    {
        if(name == "key")
        {
            key = value;
        }else if(name == "timeout")
        {
            timeout = value.toInt();
        }else
        {
            if(value.isEmpty())
                Properties.remove(name);
            else
                Properties[name] = value;
        }
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
