#include "curlwrapper.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    CurlWrapper::CurlWrapper(QObject *parent) :
        QObject(parent)
    {
        cUrl = 0;
    }

    void CurlWrapper::SetFilter(const QString& Filter)
    {
        this->Filter = Filter;
    }

    void CurlWrapper::SetFileName(const QString& FileName)
    {

        this->FileName = FileName;
    }


    void CurlWrapper::SetOptions(const QtCUrl::Options& Options)
    {
        this->Options = Options;
    }

    CurlWrapper::~CurlWrapper()
    {

    }

    void CurlWrapper::Stop()
    {
        if(cUrl)
            cUrl->MarkAutoDelete();
    }


    void CurlWrapper::Start()
    {
        AlreadyDeleted = false;
        cUrl = new QtCUrl();
        cUrl->SetFileName(FileName);

        QtCUrl *cUrlCopy = cUrl;
        cUrl->SetFilter(Filter);

        cUrl->exec(Options);
        cUrl = 0;

        bool result = cUrlCopy->lastError().code() == CURLE_OK;

        QByteArray Data = (result)?cUrlCopy->GetDataByteArray():cUrlCopy->errorBuffer().toUtf8();
        QByteArray Log = cUrlCopy->GetLogByteArray();
        delete cUrlCopy;

        emit Done(result, Data, Log);



    }


}

