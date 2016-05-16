#include "urlstringboxloader.h"
#include <QRegExp>
#include <QTimer>

#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    UrlStringBoxLoader::UrlStringBoxLoader(QObject *parent) :
        IStringBoxLoader(parent)
    {
        IsLoading = false;
        HttpClient = 0;
        HttpClientFactory = 0;
        UrlIterator = 0;
        FailCount = 0;
    }

    void UrlStringBoxLoader::SetWaiter(IWaiter*Waiter)
    {
        this->Waiter = Waiter;
    }

    void UrlStringBoxLoader::SetUrl(const QString& Url)
    {
        this->Url = Url;
        UrlList = Url.split("|");
        UrlIterator = 0;
        FailCount = 0;
        if(UrlList.length() == 0)
        {
            QStringList res;
            emit DataLoadedCompletely();
            emit Loaded(res);

        }
    }

    void UrlStringBoxLoader::SetHttpClientFactory(IHttpClientFactory *HttpClientFactory)
    {
        this->HttpClientFactory = HttpClientFactory;
    }

    void UrlStringBoxLoader::Load()
    {
        if(UrlList.length() == 0)
        {
            QStringList res;
            emit DataLoadedCompletely();
            emit Loaded(res);
            return;
        }
        if(HttpClient)
        {
            HttpClient->Disconnect();
            HttpClient->deleteLater();
        }
        HttpClient = HttpClientFactory->GetHttpClient();
        HttpClient->setParent(this);
        HttpClient->AddHeader("User-Agent","Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/37.0.2049.0 Safari/537.36");
        //HttpClient->Connect(this,SLOT(LoadComplete()));
        Reqeust();
    }

    void UrlStringBoxLoader::Reqeust()
    {
        Waiter->WaitForSignal(HttpClient,SIGNAL(Finished()),this,SLOT(LoadComplete()),this, SLOT(OnFail()));
        HttpClient->Get(UrlList.at(UrlIterator));
    }

    void UrlStringBoxLoader::OnFail()
    {


        FailCount++;
        if(FailCount>10)
        {
            FailCount = 0;
            UrlIterator++;
            QStringList r;
            emit Loaded(r);
        }
        if(UrlIterator >= UrlList.length())
        {
            emit DataLoadedCompletely();
            UrlIterator = 0;
        }else
        {
            int interval = qrand()%(15)*1000 + 10000;
            QTimer::singleShot(interval,this,SLOT(Reqeust()));
        }

    }

    void UrlStringBoxLoader::LoadComplete()
    {
        if(HttpClient->WasError())
        {
            OnFail();
            return;
        }
        QString res = HttpClient->GetContent();

        if(Argument.isEmpty())
        {
            Argument = "[\r\n]";
            Capture = ResourceModelUrl::Split;
        }

        QStringList r;


        if(Capture == ResourceModelUrl::Split)
        {
            r = res.split(QRegExp(Argument),QString::SkipEmptyParts);
        }else
        {
            QRegExp regexp(Argument);
            int state_position = 0;
            while ((state_position = regexp.indexIn(res, state_position)) != -1)
            {
                if(regexp.captureCount()>0)
                    r.append(regexp.cap(1));
                else if(regexp.captureCount()==0)
                    r.append(regexp.cap(0));
                state_position += regexp.matchedLength();
            }


        }

        UrlIterator++;
        FailCount = 0;
        if(UrlIterator >= UrlList.length())
        {
            emit DataLoadedCompletely();
            UrlIterator = 0;
        }

        emit Loaded(r);




    }


    ResourceModelUrl::CaptureMethod UrlStringBoxLoader::GetCaptureMethod()
    {
        return Capture;
    }

    void UrlStringBoxLoader::SetCaptureMethod(ResourceModelUrl::CaptureMethod Capture)
    {
        this->Capture = Capture;
    }

    QString UrlStringBoxLoader::GetCaptureArgument()
    {
        return Argument;
    }

    void UrlStringBoxLoader::SetCaptureArgument(QString Argument)
    {
        this->Argument = Argument;
    }
}
