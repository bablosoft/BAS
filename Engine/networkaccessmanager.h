#ifndef NETWORKACCESSMANAGER_H
#define NETWORKACCESSMANAGER_H
#include "engine_global.h"

#include "inetworkaccessmanager.h"
#include <QStringList>
#include <QHash>
#include "networkaccessmanagercapture.h"
#include "iworker.h"

namespace BrowserAutomationStudioFramework
{
    class NetworkAccessManagerCapture;
    class ENGINESHARED_EXPORT NetworkAccessManager : public INetworkAccessManager
    {
        Q_OBJECT
        struct MaskStruct
        {
            QString mask;
            bool allow;
        };
        QList<MaskStruct> CacheMask;
        QList<MaskStruct> RequestMask;
        QHash<QString,QByteArray> CachedData;
        QHash<QString,int> CachedStatus;
        QStringList LoadedUrls;
        bool CheckListOfMask(const QList<MaskStruct>& Masks, const QString& Text, bool Default);
        NetworkAccessManagerCapture *CaptureManager;
        IWorker *Worker;
    public:

        explicit NetworkAccessManager(QObject *parent = 0);
        bool NeedToLoad(const QString& url);
        bool NeedToCache(const QString& url);

        virtual void SetWorker(IWorker *Worker);
        virtual IWorker * GetWorker();

    protected:

    signals:

    public slots:
        virtual void AddHeader(const QString& name,const QString& value,const QString& target, const QString& callback);
        virtual void SetHeaderList(const QString& json,const QString& callback);
        virtual void CleanHeader(const QString& callback);

        virtual void AddCacheMaskAllow(const QString& Mask, const QString& callback);
        virtual void AddCacheMaskDeny(const QString& Mask, const QString& callback);
        virtual void AddRequestMaskAllow(const QString& Mask, const QString& callback);
        virtual void AddRequestMaskDeny(const QString& Mask, const QString& callback);
        virtual void ClearCacheMask(const QString& callback);
        virtual void ClearRequestMask(const QString& callback);
        virtual void ClearMasks(const QString& callback);
        virtual void ClearData(const QString& callback);
        virtual void ClearLoadedUrl(const QString& callback);
        virtual void ClearCachedData(const QString& callback);
        virtual void ClearAll(const QString& callback);
        virtual void RestrictPopups(const QString& callback);
        virtual void AllowPopups(const QString& callback);
        virtual void RestrictDownloads(const QString& callback);
        virtual void AllowDownloads(const QString& callback);
        QByteArray FindCacheByMask(const QString& Mask);
        virtual void FindCacheByMaskBase64(const QString& Mask, const QString& callback);
        virtual void FindStatusByMask(const QString& Mask, const QString& callback);
        virtual void FindCacheByMaskString(const QString& Mask, const QString& callback);
        virtual void IsUrlLoadedByMask(const QString& Mask, const QString& callback);
        virtual void GetLoadStats(const QString& callback);
        virtual QNetworkAccessManager *GetNetworkAccessManager();
        virtual void SetProxy(const QString& server, int Port, bool IsHttp, const QString& name, const QString& password,const QString& target, const QString& callback);


    private slots:
        void ReadData(QNetworkReply*);
        void UrlLoad(const QString& url, int status);
    };
}

#endif // NETWORKACCESSMANAGER_H
