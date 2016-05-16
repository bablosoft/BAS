#include "networkaccessmanagercapture.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    NetworkAccessManagerCapture::NetworkAccessManagerCapture(QObject *parent) :
        QNetworkAccessManager(parent)
    {
    }

    void NetworkAccessManagerCapture::SetNetworkAccessManager(NetworkAccessManager * _NetworkAccessManager)
    {
        this->_NetworkAccessManager = _NetworkAccessManager;
    }

    void NetworkAccessManagerCapture::AddHeader(const QString& name,const QString& value)
    {
        if(Headers.contains(name))
        {
            Headers[name] = value;
        }else
            Headers.insert(name,value);
    }

    void NetworkAccessManagerCapture::CleanHeader()
    {
        Headers.clear();
    }

    QNetworkReply * NetworkAccessManagerCapture::createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData)
    {
        if(!_NetworkAccessManager->NeedToLoad(request.url().toString()))
        {
            emit UrlLoad(request.url().toString(),-1);
            return QNetworkAccessManager::createRequest(QNetworkAccessManager::GetOperation, QNetworkRequest(QUrl()));
        }

        QNetworkRequest r = QNetworkRequest(request);
        QHash<QString, QString>::iterator i = Headers.begin();
        while (i != Headers.end())
        {
            r.setRawHeader(i.key().toUtf8(),i.value().toUtf8());
            ++i;
        }

        QNetworkReply *reply = QNetworkAccessManager::createRequest(op, r, outgoingData);
        connect(reply,SIGNAL(finished()),this,SLOT(UrlLoadSlot()));
        if(_NetworkAccessManager->NeedToCache(r.url().toString()))
            connect(reply,SIGNAL(readyRead()),this,SLOT(ReadDataSlot()));


        return reply;
    }

    void NetworkAccessManagerCapture::UrlLoadSlot()
    {
        QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
        emit UrlLoad(reply->url().toString(),reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt());
    }



    void NetworkAccessManagerCapture::ReadDataSlot()
    {
        QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
        emit ReadData(reply);
    }
}
