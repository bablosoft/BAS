#ifndef INETWORKACCESSMANAGER_H
#define INETWORKACCESSMANAGER_H
#include "engine_global.h"


#include <QByteArray>
#include <QNetworkAccessManager>
#include "iworker.h"

namespace BrowserAutomationStudioFramework
{
    class IWorker;
    class ENGINESHARED_EXPORT INetworkAccessManager : public QObject
    {
        Q_OBJECT
    public:
        explicit INetworkAccessManager(QObject *parent = 0);

    signals:

    public slots:
        virtual void SetWorker(IWorker *Worker) = 0;
        virtual IWorker * GetWorker() = 0;

        virtual void AddHeader(const QString& name,const QString& value,const QString& target, const QString& callback) = 0;
        virtual void CleanHeader(const QString& callback) = 0;
        virtual void SetHeaderList(const QString& json,const QString& callback) = 0;

        virtual void AddCacheMaskAllow(const QString& Mask, const QString& callback) = 0;
        virtual void AddCacheMaskDeny(const QString& Mask, const QString& callback) = 0;
        virtual void AddRequestMaskAllow(const QString& Mask, const QString& callback) = 0;
        virtual void AddRequestMaskDeny(const QString& Mask, const QString& callback) = 0;
        virtual void ClearCacheMask(const QString& callback) = 0;
        virtual void ClearRequestMask(const QString& callback) = 0;
        virtual void ClearLoadedUrl(const QString& callback) = 0;
        virtual void ClearCachedData(const QString& callback) = 0;
        virtual void ClearAll(const QString& callback) = 0;
        virtual void ClearMasks(const QString& callback) = 0;
        virtual void ClearData(const QString& callback) = 0;
        virtual void RestrictPopups(const QString& callback) = 0;
        virtual void AllowPopups(const QString& callback) = 0;
        virtual void RestrictDownloads(const QString& callback) = 0;
        virtual void AllowDownloads(const QString& callback) = 0;
        virtual void SetProxy(const QString& server, int Port, bool IsHttp, const QString& name, const QString& password,const QString& target, const QString& callback) = 0;


        virtual void FindCacheByMaskBase64(const QString& Mask, const QString& callback) = 0;
        virtual void FindStatusByMask(const QString& Mask, const QString& callback) = 0;
        virtual void FindCacheByMaskString(const QString& Mask, const QString& callback) = 0;
        virtual void IsUrlLoadedByMask(const QString& Mask, const QString& callback) = 0;
        virtual void GetLoadStats(const QString& callback) = 0;
        virtual QNetworkAccessManager *GetNetworkAccessManager() = 0;
    };
}

#endif // INETWORKACCESSMANAGER_H
