#include "periodicalhttprequest.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    PeriodicalHttpRequest::PeriodicalHttpRequest(QObject *parent) :
        QObject(parent)
    {
        StartedMonitor = false;
    }

    void PeriodicalHttpRequest::SetHttpClientFactory(IHttpClientFactory * HttpClientFactory)
    {
        this->HttpClientFactory = HttpClientFactory;
    }
    void PeriodicalHttpRequest::Start(const QString& Url)
    {
        this->Url = Url;
        if(!StartedMonitor)
        {
            HttpClient = HttpClientFactory->GetHttpClient();
            HttpClient->setParent(this);
            Timer.setSingleShot(true);
            Timer.start(8000);
            connect(&Timer, SIGNAL(timeout()), this, SLOT(StartIteration()));
            StartedMonitor = true;
        }
    }

    QString PeriodicalHttpRequest::GetLastResponce()
    {
        return LastResponse;
    }

    void PeriodicalHttpRequest::StartIteration()
    {
        HttpClient->Connect(this,SLOT(DoneIteration()));
        HttpClient->Get(Url);
    }


    void PeriodicalHttpRequest::DoneIteration()
    {

        if(HttpClient->WasError())
        {
            LastResponse = "";
        }else
        {
            LastResponse = HttpClient->GetContent();
        }
        Timer.start(8000);
    }
}
