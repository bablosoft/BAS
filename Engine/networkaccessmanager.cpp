#include "networkaccessmanager.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QRegExp>
#include <QNetworkProxy>
#include "networkcookiejar.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    NetworkAccessManager::NetworkAccessManager(QObject *parent) :
        INetworkAccessManager(parent)
    {
        CaptureManager = new NetworkAccessManagerCapture(this);

        CaptureManager->cookieJar()->deleteLater();

        NetworkCookieJar *jar = new NetworkCookieJar(CaptureManager);
        CaptureManager->setCookieJar(jar);

        CaptureManager->SetNetworkAccessManager(this);
        connect(CaptureManager,SIGNAL(ReadData(QNetworkReply*)),this,SLOT(ReadData(QNetworkReply*)));
        connect(CaptureManager,SIGNAL(UrlLoad(QString, int)),this,SLOT(UrlLoad(QString, int)));
    }

    void NetworkAccessManager::AddHeader(const QString& name,const QString& value,const QString& target, const QString& callback)
    {
        CaptureManager->AddHeader(name,value);
        Worker->SetScript(callback);
        Worker->RunSubScript();
    }

    void NetworkAccessManager::SetHeaderList(const QString& json,const QString& callback)
    {
        Worker->SetScript(callback);
        Worker->RunSubScript();
    }

    void NetworkAccessManager::CleanHeader(const QString& callback)
    {
        CaptureManager->CleanHeader();
        Worker->SetScript(callback);
        Worker->RunSubScript();
    }



    void NetworkAccessManager::SetProxy(const QString& server, int Port, bool IsHttp, const QString& name, const QString& password,const QString& target, const QString& callback)
    {
        if(server.isEmpty() || Port<=0)
        {
            CaptureManager->setProxy(QNetworkProxy::NoProxy);
        }else
        {
            QNetworkProxy proxy;
            if(IsHttp)
            {
                proxy.setType(QNetworkProxy::HttpProxy);
            }else
            {
                proxy.setType(QNetworkProxy::Socks5Proxy);
            }

            proxy.setHostName(server);
            proxy.setPort(Port);

            proxy.setUser(name);
            proxy.setPassword(password);

            CaptureManager->setProxy(proxy);
        }

        Worker->SetScript(callback);
        Worker->RunSubScript();
    }

    void NetworkAccessManager::SetWorker(IWorker *Worker)
    {
        this->Worker = Worker;
    }

    IWorker * NetworkAccessManager::GetWorker()
    {
        return Worker;
    }


    QNetworkAccessManager *NetworkAccessManager::GetNetworkAccessManager()
    {
        return CaptureManager;
    }


    void NetworkAccessManager::AddCacheMaskAllow(const QString& Mask, const QString& callback)
    {
        MaskStruct mask;
        mask.allow = true;
        mask.mask = Mask;
        CacheMask.append(mask);
        Worker->SetScript(callback);
        Worker->RunSubScript();

    }

    void NetworkAccessManager::AddCacheMaskDeny(const QString& Mask, const QString& callback)
    {
        MaskStruct mask;
        mask.allow = false;
        mask.mask = Mask;
        CacheMask.append(mask);
        Worker->SetScript(callback);
        Worker->RunSubScript();

    }

    void NetworkAccessManager::AddRequestMaskAllow(const QString& Mask, const QString& callback)
    {
        MaskStruct mask;
        mask.allow = true;
        mask.mask = Mask;
        RequestMask.append(mask);
        Worker->SetScript(callback);
        Worker->RunSubScript();

    }

    void NetworkAccessManager::AddRequestMaskDeny(const QString& Mask, const QString& callback)
    {
        MaskStruct mask;
        mask.allow = false;
        mask.mask = Mask;
        RequestMask.append(mask);
        Worker->SetScript(callback);
        Worker->RunSubScript();

    }

    void NetworkAccessManager::ClearCacheMask(const QString& callback)
    {
        CacheMask.clear();
        Worker->SetScript(callback);
        Worker->RunSubScript();
    }

    void NetworkAccessManager::ClearRequestMask(const QString& callback)
    {
        RequestMask.clear();
        Worker->SetScript(callback);
        Worker->RunSubScript();
    }


    void NetworkAccessManager::ClearLoadedUrl(const QString& callback)
    {
        LoadedUrls.clear();
        Worker->SetScript(callback);
        Worker->RunSubScript();
    }

    void NetworkAccessManager::ClearCachedData(const QString& callback)
    {
        CachedData.clear();
        Worker->SetScript(callback);
        Worker->RunSubScript();
    }

    void NetworkAccessManager::ClearMasks(const QString& callback)
    {
        RequestMask.clear();
        CacheMask.clear();

        Worker->SetScript(callback);
        Worker->RunSubScript();
    }
    void NetworkAccessManager::ClearData(const QString& callback)
    {
        CachedData.clear();
        CachedStatus.clear();
        LoadedUrls.clear();

        Worker->SetScript(callback);
        Worker->RunSubScript();
    }


    void NetworkAccessManager::ClearAll(const QString& callback)
    {
        CachedData.clear();
        CachedStatus.clear();
        LoadedUrls.clear();
        RequestMask.clear();
        CacheMask.clear();
        Worker->SetScript(callback);
        Worker->RunSubScript();
    }

    void NetworkAccessManager::RestrictPopups(const QString& callback)
    {
        Worker->SetScript(callback);
        Worker->RunSubScript();
    }

    void NetworkAccessManager::AllowPopups(const QString& callback)
    {
        Worker->SetScript(callback);
        Worker->RunSubScript();
    }

    void NetworkAccessManager::RestrictDownloads(const QString& callback)
    {
        Worker->SetScript(callback);
        Worker->RunSubScript();
    }
    void NetworkAccessManager::AllowDownloads(const QString& callback)
    {
        Worker->SetScript(callback);
        Worker->RunSubScript();
    }

    QByteArray NetworkAccessManager::FindCacheByMask(const QString& Mask)
    {
        QRegExp MaskRegexp;
        MaskRegexp.setPatternSyntax(QRegExp::Wildcard);
        MaskRegexp.setPattern(Mask);
        QList<QString> keys = CachedData.keys();

        foreach(QString key,keys)
        {
            if(MaskRegexp.exactMatch(key))
            {
                return CachedData.value(key);
            }
        }
        return QByteArray();
    }

    void NetworkAccessManager::FindStatusByMask(const QString& Mask, const QString& callback)
    {
        QRegExp MaskRegexp;
        MaskRegexp.setPatternSyntax(QRegExp::Wildcard);
        MaskRegexp.setPattern(Mask);
        QList<QString> keys = CachedStatus.keys();

        foreach(QString key,keys)
        {
            if(MaskRegexp.exactMatch(key))
            {
                Worker->SetAsyncResult(QScriptValue(CachedStatus.value(key)));
                Worker->SetScript(callback);
                Worker->RunSubScript();
                return;
            }
        }
        Worker->SetAsyncResult(QScriptValue(-1));
        Worker->SetScript(callback);
        Worker->RunSubScript();
    }

    void NetworkAccessManager::FindCacheByMaskBase64(const QString& Mask, const QString& callback)
    {

        Worker->SetAsyncResult(QScriptValue(QString(FindCacheByMask(Mask).toBase64())));
        Worker->SetScript(callback);
        Worker->RunSubScript();
    }

    void NetworkAccessManager::FindCacheByMaskString(const QString& Mask, const QString& callback)
    {

        Worker->SetAsyncResult(QScriptValue(QString::fromUtf8(FindCacheByMask(Mask))));
        Worker->SetScript(callback);
        Worker->RunSubScript();
    }

    void NetworkAccessManager::IsUrlLoadedByMask(const QString& Mask, const QString& callback)
    {
        QRegExp MaskRegexp;
        MaskRegexp.setPatternSyntax(QRegExp::Wildcard);
        MaskRegexp.setPattern(Mask);

        foreach(QString url,LoadedUrls)
        {
            if(MaskRegexp.exactMatch(url))
            {
                Worker->SetAsyncResult(QScriptValue(true));
                Worker->SetScript(callback);
                Worker->RunSubScript();
                return;
            }
        }

        Worker->SetAsyncResult(QScriptValue(false));
        Worker->SetScript(callback);
        Worker->RunSubScript();
    }

    void NetworkAccessManager::GetLoadStats(const QString& callback)
    {

    }

    bool NetworkAccessManager::CheckListOfMask(const QList<MaskStruct>& Masks, const QString& Text, bool Default)
    {
        bool res = Default;
        foreach(MaskStruct Mask, Masks)
        {
            QRegExp MaskRegexp;
            MaskRegexp.setPatternSyntax(QRegExp::Wildcard);
            MaskRegexp.setPattern(Mask.mask);
            if(MaskRegexp.exactMatch(Text))
            {
                res =Mask.allow;
            }
        }
        return res;
    }

    bool NetworkAccessManager::NeedToLoad(const QString& url)
    {
        return CheckListOfMask(RequestMask, url, true);
    }

    bool NetworkAccessManager::NeedToCache(const QString& url)
    {
        return CheckListOfMask(CacheMask, url, false);
    }

    void NetworkAccessManager::UrlLoad(const QString& url, int status)
    {
        LoadedUrls.append(url);
        CachedStatus.insert(url,status);
    }


    void NetworkAccessManager::ReadData(QNetworkReply * reply)
    {
        QString url = reply->url().toString();

        if(!CachedData.contains(url))
        {
            CachedData.insert(url,QByteArray());
        }

        QByteArray array = reply->peek(reply->bytesAvailable());


        if(array.isEmpty())
            return;

        QByteArray res = CachedData[url];
        res.append(array);
        CachedData[url] = res;


    }


}


