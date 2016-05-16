#include "curlexecutor.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    CurlExecutor::CurlExecutor(QObject *parent) :
        QObject(parent)
    {
        Curl = 0;
        Thread = 0;
        Result = false;
        Data = "Not Run";
        UseExternalThread = false;

    }

    void CurlExecutor::SetThread(QThread *Thread)
    {
        this->Thread = Thread;
        UseExternalThread = true;
    }



    CurlExecutor::~CurlExecutor()
    {
        Stop();
    }

    void CurlExecutor::Stop()
    {
        if(Curl)
        {
            emit StopCurl();
            Curl = 0;
        }
    }

    void CurlExecutor::SetFilename(const QString& FileName)
    {
        this->FileName = FileName;
    }




    void CurlExecutor::Execute()
    {

        if(!UseExternalThread)
        {
            Thread = new QThread();
        }



        Curl = new CurlWrapper();
        Curl->SetFileName(FileName);
        Curl->SetOptions(Options);
        Curl->SetFilter(Filter);
        Curl->moveToThread(Thread);



        connect(this, SIGNAL(StartCurl()), Curl, SLOT(Start()));
        connect(this, SIGNAL(StopCurl()), Curl, SLOT(Stop()));
        connect(Curl, SIGNAL(Done(bool,QByteArray,QByteArray)), this, SLOT(DoneWrapper(bool,QByteArray,QByteArray)));
        connect(Curl, SIGNAL(Done(bool,QByteArray,QByteArray)), Curl, SLOT(deleteLater()));

        if(!UseExternalThread)
        {
            connect(Curl, SIGNAL(Done(bool,QByteArray,QByteArray)), Thread, SLOT(quit()));
            connect(Thread, SIGNAL(finished()), Thread, SLOT(deleteLater()));
        }

        Thread->start();

        emit StartCurl();

    }




    void CurlExecutor::DoneWrapper(bool Result,const QByteArray& Data,const QByteArray& Log)
    {
        this->Result = Result;
        this->Data = Data;
        this->Log = Log;
        Curl = 0;
        Options.clear();
        Filter.clear();
        emit Done();

    }

    QtCUrl::Options* CurlExecutor::GetOptions()
    {
        return &Options;
    }

    bool CurlExecutor::GetResult()
    {
        return Result;
    }

    QByteArray CurlExecutor::GetDataByteArray()
    {
        return Data;
    }

    void CurlExecutor::SetFilter(const QString& Filter)
    {
        this->Filter = Filter;
    }

    QByteArray CurlExecutor::GetLogByteArray()
    {
        return this->Log;
    }
}
