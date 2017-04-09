#ifndef SUBPROCESSNETWORKACCESSMANAGER_H
#define SUBPROCESSNETWORKACCESSMANAGER_H
#include "engine_global.h"

#include "inetworkaccessmanager.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT SubprocessNetworkAccessManager : public INetworkAccessManager
    {
        Q_OBJECT
        IWorker* Worker;
    public:
        explicit SubprocessNetworkAccessManager(QObject *parent = 0);

    signals:
        void AddCacheMaskAllow();
        void AddCacheMaskDeny();
        void AddRequestMaskAllow();
        void AddRequestMaskDeny();
        void ClearCacheMask();
        void ClearRequestMask();
        void ClearLoadedUrl();
        void ClearCachedData();
        void ClearAll();
        void ClearMasks();
        void ClearData();
        void FindCacheByMaskBase64();
        void FindCacheByMaskString();
        void IsUrlLoadedByMask();
        void GetLoadStats();
        void SetProxy();
        void CleanHeader();
        void FindStatusByMask();
        void AddHeader();
        void SetHeaderList();
        void RestrictPopups();
        void AllowPopups();
        void RestrictDownloads();
        void AllowDownloads();
    public slots:
        virtual void SetWorker(IWorker *Worker);
        virtual IWorker * GetWorker();
        void AddHeader(const QString& name,const QString& value,const QString& target, const QString& callback);
        void SetHeaderList(const QString& json,const QString& callback);
        void CleanHeader(const QString& callback);
        virtual void SetProxy(const QString& server, int Port, bool IsHttp, const QString& name, const QString& password,const QString& target, const QString& callback);
        virtual void AddCacheMaskAllow(const QString& Mask, const QString& callback);
        virtual void AddCacheMaskDeny(const QString& Mask, const QString& callback);
        virtual void AddRequestMaskAllow(const QString& Mask, const QString& callback);
        virtual void AddRequestMaskDeny(const QString& Mask, const QString& callback);
        virtual void ClearCacheMask(const QString& callback);
        virtual void ClearRequestMask(const QString& callback);
        virtual void ClearLoadedUrl(const QString& callback);
        virtual void ClearCachedData(const QString& callback);
        virtual void ClearAll(const QString& callback);
        virtual void ClearMasks(const QString& callback);
        virtual void ClearData(const QString& callback);
        virtual void RestrictPopups(const QString& callback);
        virtual void AllowPopups(const QString& callback);
        virtual void RestrictDownloads(const QString& callback);
        virtual void AllowDownloads(const QString& callback);


        virtual void FindCacheByMaskBase64(const QString& Mask, const QString& callback);
        virtual void FindStatusByMask(const QString& Mask, const QString& callback);
        virtual void FindCacheByMaskString(const QString& Mask, const QString& callback);
        virtual void IsUrlLoadedByMask(const QString& Mask, const QString& callback);
        virtual void GetLoadStats(const QString& callback);
        virtual QNetworkAccessManager *GetNetworkAccessManager();
    private slots:
        void Received(const QString& value);
    };
}

#endif // SUBPROCESSNETWORKACCESSMANAGER_H
