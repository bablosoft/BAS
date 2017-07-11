#include "posttoantigate.h"
#include "every_cpp.h"
#include <QMap>
#include <QPixmap>
#include <QBuffer>
#include <QMapIterator>

namespace BrowserAutomationStudioFramework
{
    PostToAntigate::PostToAntigate(QObject *parent) :
        QObject(parent)
    {
    }

    void PostToAntigate::Post(const QString& id,const QString& key,const QString& base64, const QMap<QString,QString>& Properties, const QString& soft, bool DisableImageConvert)
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

            if(DisableImageConvert)
            {
                DataFile.DataRaw = QByteArray::fromBase64(base64.toUtf8());
            }else
            {
                QImage image = QImage::fromData(QByteArray::fromBase64(base64.toUtf8()));

                QByteArray ba;
                QBuffer buffer(&ba);
                buffer.open(QIODevice::WriteOnly);

                image.save(&buffer, "JPEG");
                buffer.close();

                DataFile.DataRaw = ba;
            }
            DataFile.FileName = "image.jpg";
            DataFile.ContentType = "application/octet-stream";
            post["file"] = DataFile;
        }

        if(!soft.isEmpty())
        {
            ContentData DataSoftId;
            DataSoftId.DataString = soft;

            post["soft_id"] = DataSoftId;
        }

        QMapIterator<QString, QString> i(Properties);
        while (i.hasNext())
        {
            i.next();
            if(i.value().length() > 0 && i.key().length() > 0)
            {
                ContentData DataKey;
                DataKey.DataString = i.value();
                post[i.key()] = DataKey;
            }
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
