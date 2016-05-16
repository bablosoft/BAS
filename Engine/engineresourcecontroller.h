#ifndef ENGINERESOURCECONTROLLER_H
#define ENGINERESOURCECONTROLLER_H
#include "engine_global.h"


#include "iresourcecontroller.h"
#include "iwaiterfactory.h"
#include "engineresources.h"
#include "istringbuilder.h"
#include "ihttpclientfactory.h"
#include "iresourcewatcher.h"
#include "idatabaseconnector.h"
#include "icsvhelper.h"



namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT EngineResourceController : public IResourceController
    {
        Q_OBJECT
        EngineResources *EngineRes;
        IStringBuilder *StringBuilder;
        IHttpClientFactory *HttpClientFactory;
        IWaiterFactory *WaiterFactory;
        QList<IResourceWatcher *> WatcherList;
        IDatabaseConnector * DatabaseConnector;
        ICsvHelper * CsvHelper;
    public:
        explicit EngineResourceController(QObject *parent = 0);
        void SetEngineResources(EngineResources *Resources);
        EngineResources * GetEngineResources();
        void SetStringBuilder(IStringBuilder *StringBuilder);
        IStringBuilder * GetStringBuilder();
        void SetHttpClientFactory(IHttpClientFactory *HttpClientFactory);
        void SetWaiterFactory(IWaiterFactory *WaiterFactory);
        void SetDatabaseConnector(IDatabaseConnector *DatabaseConnector);
        void SetCsvHelper(ICsvHelper *CsvHelper);
        QList<IResourceWatcher *> GetWatcherList();
    signals:

    public slots:
        virtual void FromViewToModel(IResources * resources, bool Clear = true);
        virtual void FromModelToView(IResources * resources, bool Clear = true);
    };
}

#endif // ENGINERESOURCECONTROLLER_H
