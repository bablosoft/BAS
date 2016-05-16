#include "posttoantigate.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    PostToAntigate::PostToAntigate(QObject *parent) :
        QObject(parent)
    {
    }

    void PostToAntigate::Post(const QString& id,const QString& key,const QString& base64, bool IsRussian)
    {
        this->id = id;
        QHash<QString,ContentData> post;

        {
            ContentData DataMethod;
            DataMethod.DataString = "post";
            post["method"] = DataMethod;
        }

        {
            ContentData DataKey;
            DataKey.DataString = key;
            post["key"] = DataKey;
        }

        {
            ContentData DataFile;
            DataFile.DataRaw = QByteArray::fromBase64(base64.toUtf8());
            DataFile.FileName = "image.jpg";
            DataFile.ContentType = "application/octet-stream";
            post["file"] = DataFile;
        }

        {
            ContentData DataSoftId;
            DataSoftId.DataString = "398";
            post["soft_id"] = DataSoftId;
        }
        if(IsRussian)
        {
            ContentData IsRussian;
            IsRussian.DataString = "1";
            post["is_russian"] = IsRussian;
        }

        HttpClient->Connect(this,SLOT(submitRequestFinished()));
        HttpClient->Post(Server + "in.php",post);

    }

    void PostToAntigate::SetServer(const QString& Server)
    {
        this->Server = Server;
    }

    void PostToAntigate::submitRequestFinished()
    {
        if(HttpClient->WasError())
        {
            emit PostedToAntigate(HttpClient->GetErrorString(),id,false);
            return;
        }
        QString res = HttpClient->GetContent();
        if(!res.startsWith("OK|"))
        {
            emit PostedToAntigate(res,id,false);
            return;
        }
        QString r = res.remove(0,3);
        emit PostedToAntigate(r,id,true);
    }

    void PostToAntigate::SetHttpClient(IHttpClient * HttpClient)
    {
        this->HttpClient = HttpClient;
    }

    IHttpClient * PostToAntigate::GetHttpClient()
    {
        return HttpClient;
    }
}
