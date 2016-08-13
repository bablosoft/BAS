#include "engineresourcecontroller.h"
#include "engineresourcefixedinteger.h"
#include "engineresourcerandominteger.h"
#include "engineresourcefixedstring.h"
#include "resourcemodelfixedstring.h"
#include "resourcemodelurl.h"
#include "resourcemodelfixedinteger.h"
#include "resourcemodeldatabase.h"
#include "resourcemodelrandominteger.h"
#include "engineresourcerandomstring.h"
#include "resourcemodelrandomstring.h"
#include "resourcemodelselect.h"
#include "resourcemodelfile.h"
#include "engineresourcestringbox.h"
#include "stringbox.h"
#include "stringboxproxy.h"
#include "stringboxperiodicalloader.h"
#include "filestringboxloader.h"
#include "databasestringboxloader.h"
#include "urlstringboxloader.h"
#include "directorystringboxloader.h"
#include "resourcemodeldirectory.h"
#include "resourcemodelscript.h"
#include "emptystringboxloader.h"
#include "stringboxwatcher.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    EngineResourceController::EngineResourceController(QObject *parent) :
        IResourceController(parent)
    {
    }

    void EngineResourceController::SetHttpClientFactory(IHttpClientFactory *HttpClientFactory)
    {
        this->HttpClientFactory = HttpClientFactory;
    }

    void EngineResourceController::SetWaiterFactory(IWaiterFactory *WaiterFactory)
    {
        this->WaiterFactory = WaiterFactory;
    }

    void EngineResourceController::SetEngineResources(EngineResources *Resources)
    {
        EngineRes = Resources;
    }
    EngineResources * EngineResourceController::GetEngineResources()
    {
        return EngineRes;
    }
    void EngineResourceController::SetStringBuilder(IStringBuilder *StringBuilder)
    {
        this->StringBuilder = StringBuilder;
    }
    IStringBuilder * EngineResourceController::GetStringBuilder()
    {
        return StringBuilder;
    }

    QList<IResourceWatcher *> EngineResourceController::GetWatcherList()
    {
        return WatcherList;
    }

    void EngineResourceController::FromViewToModel(IResources * resources, bool Clear)
    {

    }

    void EngineResourceController::SetDatabaseConnector(IDatabaseConnector *DatabaseConnector)
    {
        this->DatabaseConnector = DatabaseConnector;
    }

    void EngineResourceController::SetCsvHelper(ICsvHelper *CsvHelper)
    {
        this->CsvHelper = CsvHelper;
    }



    void EngineResourceController::FromModelToView(IResources * resources, bool Clear)
    {
        if(Clear)
            EngineRes->Clear();

        WatcherList.clear();

        QList<IResourceModel * > * model = resources->GetModelList();
        int size = model->size();
        for(int i = 0;i<size;i++)
        {
            IResourceModel *m = model->at(i);
            QStringList Names = m->GetName().split(",");
            foreach(QString Name,Names)
            {
               if(m->GetTypeId() == "FixedString")
               {
                   ResourceModelFixedString * r = qobject_cast<ResourceModelFixedString *>(m);
                   EngineResourceFixedString * n = new EngineResourceFixedString(EngineRes);
                   n->SetInfo("Type",m->GetTypeId());

                   n->SetValue(r->GetValue());
                   EngineRes->Add(Name,n);
               }else if(m->GetTypeId() == "FixedInteger")
               {
                   ResourceModelFixedInteger * r = qobject_cast<ResourceModelFixedInteger *>(m);
                   EngineResourceFixedInteger * n = new EngineResourceFixedInteger(EngineRes);
                   n->SetInfo("Type",m->GetTypeId());
                   int v = r->GetValue();

                   n->SetValue(v);
                   EngineRes->Add(Name,n);
               }else if(m->GetTypeId() == "RandomInteger")
               {
                   ResourceModelRandomInteger * r = qobject_cast<ResourceModelRandomInteger *>(m);
                   EngineResourceRandomInteger * n = new EngineResourceRandomInteger(EngineRes);
                   n->SetInfo("Type",m->GetTypeId());
                   n->SetInfo("Maximum",QString::number(r->GetMaxUserValue()));
                   n->SetInfo("Minimum",QString::number(r->GetMinUserValue()));
                   int v = r->GetMinUserValue();

                   n->SetMinValue(v);
                   v = r->GetMaxUserValue();

                   n->SetMaxValue(v);
                   EngineRes->Add(Name,n);

               }
               else if(m->GetTypeId() == "RandomString")
               {
                   ResourceModelRandomString * r = qobject_cast<ResourceModelRandomString *>(m);
                   EngineResourceRandomString * n = new EngineResourceRandomString(EngineRes);
                   n->SetInfo("Type",m->GetTypeId());
                   n->SetInfo("Mask",r->GetValue());


                   n->SetValue(r->GetValue());
                   n->SetStringBuilder(StringBuilder);

                   EngineRes->Add(Name,n);
               }else if(m->GetTypeId() == "Select")
               {
                   ResourceModelSelect * r = qobject_cast<ResourceModelSelect *>(m);
                   EngineResourceFixedString * n = new EngineResourceFixedString(EngineRes);
                   n->SetInfo("Type",m->GetTypeId());

                   QString res;
                   QStringList val = r->GetValues();
                   bool first = true;
                   foreach(int index,r->GetSelected())
                   {
                       if(!first)
                       {
                           res += ",";
                       }
                       first = false;
                       res += val.at(index);
                   }
                   n->SetInfo("Options",res);


                   n->SetValue(res);

                   EngineRes->Add(Name,n);
               }else if(m->GetTypeId() == "Database")
               {

                   ResourceModelDatabase * r = qobject_cast<ResourceModelDatabase *>(m);
                   EngineResourceStringBox * n = new EngineResourceStringBox(EngineRes);
                   n->SetInfo("Type",m->GetTypeId());
                   n->SetInfo("SuccessAttempts",QString::number(r->GetSuccessAttempts()));
                   n->SetInfo("FailAttempts",QString::number(r->GetFailAttempts()));




                   StringBox *box = new StringBox();

                   DatabaseStringBoxLoader *loader = new DatabaseStringBoxLoader();
                   StringBoxProxy *proxy = new StringBoxProxy();
                   StringBoxPeriodicalLoader * period = new StringBoxPeriodicalLoader();
                   if(r->GetVisibleByUser())
                   {
                       StringBoxWatcher *Watcher = new StringBoxWatcher(EngineRes);
                       WatcherList.append(Watcher);
                       Watcher->SetName(Name);
                       Watcher->SetStringBox(box);
                       Watcher->SetStringBoxPeriodicalLoader(period);
                   }

                   period->setParent(n);
                   proxy->setParent(period);
                   box->setParent(proxy);
                   loader->setParent(proxy);

                   box->SetMaxSuccess(r->GetSuccessAttempts());
                   box->SetMaxFail(r->GetFailAttempts());
                   box->SetMaxSimultaneousUse(r->GetNumberSimultaneousUse());
                   box->SetInterval(r->GetIntervalBetweenUsage());
                   box->SetGreedy(r->GetGreedy());

                   proxy->SetFilterIncome(r->GetLoadInterval());
                   proxy->SetStringBoxLoader(loader);
                   proxy->SetStringBox(box);
                   proxy->SetMix(r->GetMix());
                   proxy->SetDontGiveUp(r->GetLoadInterval() || r->GetRenewInterval() > 0);

                   loader->SetDatabaseConnector(DatabaseConnector);
                   loader->SetGroups(r->GetGroupList());
                   loader->SetTableId(r->GetTableId());
                   loader->SetColumns(r->GetColumnIds());
                   loader->SetCsvHelper(CsvHelper);

                   period->SetReloadInterval(r->GetLoadInterval());
                   period->SetRenewInterval(r->GetRenewInterval());
                   period->SetStringBoxProxy(proxy);
                   period->Start();
                   if(r->GetClean())
                       connect(box,SIGNAL(Removed(QString)),loader,SLOT(ItemDeleted(QString)));

                   n->SetValue(box);
                   n->SetStringBoxProxy(proxy);
                   n->SetDatabase(DatabaseConnector,r->GetTableId(),CsvHelper,r->GetColumnIds());


                   EngineRes->Add(Name,n);

               }else if(m->GetTypeId() == "LinesFromFile")
               {

                   ResourceModelFile * r = qobject_cast<ResourceModelFile *>(m);
                   EngineResourceStringBox * n = new EngineResourceStringBox(EngineRes);
                   n->SetInfo("Type",m->GetTypeId());
                   n->SetInfo("FileName",r->GetFilename());
                   n->SetInfo("Location",r->GetFilename());
                   n->SetInfo("SuccessAttempts",QString::number(r->GetSuccessAttempts()));
                   n->SetInfo("FailAttempts",QString::number(r->GetFailAttempts()));




                   StringBox *box = new StringBox();

                   FileStringBoxLoader *loader = new FileStringBoxLoader();
                   StringBoxProxy *proxy = new StringBoxProxy();
                   StringBoxPeriodicalLoader * period = new StringBoxPeriodicalLoader();
                   if(r->GetVisibleByUser())
                   {
                       StringBoxWatcher *Watcher = new StringBoxWatcher(EngineRes);
                       WatcherList.append(Watcher);
                       Watcher->SetName(Name);
                       Watcher->SetStringBox(box);
                       Watcher->SetStringBoxPeriodicalLoader(period);
                   }

                   period->setParent(n);
                   proxy->setParent(period);
                   box->setParent(proxy);
                   loader->setParent(proxy);

                   box->SetMaxSuccess(r->GetSuccessAttempts());
                   box->SetMaxFail(r->GetFailAttempts());
                   box->SetMaxSimultaneousUse(r->GetNumberSimultaneousUse());
                   box->SetInterval(r->GetIntervalBetweenUsage());
                   box->SetGreedy(r->GetGreedy());

                   proxy->SetFilterIncome(r->GetLoadInterval());
                   proxy->SetStringBoxLoader(loader);
                   proxy->SetStringBox(box);
                   proxy->SetMix(r->GetMix());
                   proxy->SetDontGiveUp(r->GetLoadInterval() || r->GetRenewInterval() > 0);

                   loader->SetFileName(r->GetFilename());
                   loader->SetRead(r->GetRead());
                   loader->SetWrite(r->GetWrite());

                   period->SetReloadInterval(r->GetLoadInterval());
                   period->SetRenewInterval(r->GetRenewInterval());
                   period->SetStringBoxProxy(proxy);
                   period->Start();
                   connect(box,SIGNAL(Removed(QString)),loader,SLOT(ItemDeleted(QString)));
                   connect(box,SIGNAL(Inserted(QString)),loader,SLOT(ItemAdded(QString)));

                   connect(n,SIGNAL(Synced()),loader,SLOT(ForceSync()));

                   n->SetValue(box);
                   n->SetStringBoxProxy(proxy);


                   EngineRes->Add(Name,n);

               }else if(m->GetTypeId() == "LinesFromScript")
               {
                   ResourceModelScript * r = qobject_cast<ResourceModelScript *>(m);
                   EngineResourceStringBox * n = new EngineResourceStringBox(EngineRes);
                   n->SetInfo("Type",m->GetTypeId());

                   StringBox *box = new StringBox();
                   EmptyStringBoxLoader *loader = new EmptyStringBoxLoader();
                   StringBoxProxy *proxy = new StringBoxProxy();
                   StringBoxPeriodicalLoader * period = new StringBoxPeriodicalLoader();

                   period->setParent(n);
                   proxy->setParent(period);
                   box->setParent(proxy);
                   loader->setParent(proxy);

                   box->SetMaxSuccess(r->GetSuccessAttempts());
                   box->SetMaxFail(r->GetFailAttempts());
                   box->SetMaxSimultaneousUse(r->GetNumberSimultaneousUse());
                   box->SetInterval(r->GetIntervalBetweenUsage());
                   box->SetGreedy(r->GetGreedy());


                   proxy->SetFilterIncome(false);
                   proxy->SetStringBoxLoader(loader);
                   proxy->SetStringBox(box);
                   proxy->SetMix(false);
                   proxy->SetDontGiveUp(r->GetDontGiveUp());


                   period->SetReloadInterval(0);
                   period->SetStringBoxProxy(proxy);
                   period->Start();

                   n->SetValue(box);
                   n->SetStringBoxProxy(proxy);


                   EngineRes->Add(Name,n);
               }else if(m->GetTypeId() == "LinesFromUrl")
               {
                   ResourceModelUrl * r = qobject_cast<ResourceModelUrl *>(m);
                   EngineResourceStringBox * n = new EngineResourceStringBox(EngineRes);
                   n->SetInfo("Type",m->GetTypeId());

                   n->SetInfo("Url",r->GetUrl());
                   n->SetInfo("Location",r->GetUrl());
                   n->SetInfo("SuccessAttempts",QString::number(r->GetSuccessAttempts()));
                   n->SetInfo("FailAttempts",QString::number(r->GetFailAttempts()));

                   StringBox *box = new StringBox();
                   UrlStringBoxLoader *loader = new UrlStringBoxLoader();
                   StringBoxProxy *proxy = new StringBoxProxy();
                   StringBoxPeriodicalLoader * period = new StringBoxPeriodicalLoader();
                   if(r->GetVisibleByUser())
                   {
                       StringBoxWatcher *Watcher = new StringBoxWatcher(EngineRes);
                       WatcherList.append(Watcher);
                       Watcher->SetName(Name);
                       Watcher->SetStringBox(box);
                       Watcher->SetStringBoxPeriodicalLoader(period);
                   }
                   period->setParent(n);
                   proxy->setParent(period);
                   box->setParent(proxy);
                   loader->setParent(proxy);
                   IWaiter *Waiter = WaiterFactory->CreateWaiter();
                   Waiter->setParent(loader);
                   loader->SetWaiter(Waiter);
                   loader->SetCaptureMethod(r->GetCaptureMethod());
                   loader->SetCaptureArgument(r->GetCaptureArgument());

                   box->SetMaxSuccess(r->GetSuccessAttempts());
                   box->SetMaxFail(r->GetFailAttempts());
                   box->SetMaxSimultaneousUse(r->GetNumberSimultaneousUse());
                   box->SetInterval(r->GetIntervalBetweenUsage());
                   box->SetGreedy(r->GetGreedy());


                   proxy->SetFilterIncome(r->GetLoadInterval() > 0);
                   proxy->SetStringBoxLoader(loader);
                   proxy->SetStringBox(box);
                   proxy->SetMix(r->GetMix());
                   proxy->SetDontGiveUp(r->GetLoadInterval() > 0  || r->GetRenewInterval() > 0);

                   loader->SetUrl(r->GetUrl());
                   loader->SetHttpClientFactory(HttpClientFactory);

                   int interval = r->GetLoadInterval();
                   if(interval<0)
                       interval = 0;
                   period->SetReloadInterval(interval);
                   period->SetRenewInterval(r->GetRenewInterval());
                   period->SetStringBoxProxy(proxy);
                   period->Start();

                   n->SetValue(box);
                   n->SetStringBoxProxy(proxy);

                   EngineRes->Add(Name,n);

               }else if(m->GetTypeId() == "FilesFromDirectory")
               {
                   ResourceModelDirectory * r = qobject_cast<ResourceModelDirectory *>(m);
                   EngineResourceStringBox * n = new EngineResourceStringBox(EngineRes);
                   n->SetInfo("Type",m->GetTypeId());
                   n->SetInfo("Directory",r->GetDirectory());
                   n->SetInfo("Location",r->GetDirectory());
                   n->SetInfo("SuccessAttempts",QString::number(r->GetSuccessAttempts()));
                   n->SetInfo("FailAttempts",QString::number(r->GetFailAttempts()));

                   StringBox *box = new StringBox();
                   DirectoryStringBoxLoader *loader = new DirectoryStringBoxLoader();
                   StringBoxProxy *proxy = new StringBoxProxy();
                   StringBoxPeriodicalLoader * period = new StringBoxPeriodicalLoader();
                   if(r->GetVisibleByUser())
                   {
                       StringBoxWatcher *Watcher = new StringBoxWatcher(EngineRes);
                       WatcherList.append(Watcher);
                       Watcher->SetName(Name);
                       Watcher->SetStringBox(box);
                       Watcher->SetStringBoxPeriodicalLoader(period);
                   }
                   period->setParent(n);
                   proxy->setParent(period);
                   box->setParent(proxy);
                   loader->setParent(proxy);

                   box->SetMaxSuccess(r->GetSuccessAttempts());
                   box->SetMaxFail(r->GetFailAttempts());
                   box->SetMaxSimultaneousUse(r->GetNumberSimultaneousUse());
                   box->SetInterval(r->GetIntervalBetweenUsage());
                   box->SetGreedy(r->GetGreedy());


                   proxy->SetFilterIncome(r->GetLoadInterval());
                   proxy->SetStringBoxLoader(loader);
                   proxy->SetStringBox(box);
                   proxy->SetMix(r->GetMix());
                   proxy->SetDontGiveUp(r->GetLoadInterval() || r->GetRenewInterval() > 0);

                   loader->SetDirectoryName(r->GetDirectory());
                   loader->SetDirectoryMask(r->GetWildcard());

                   period->SetReloadInterval(r->GetLoadInterval());
                   period->SetRenewInterval(r->GetRenewInterval());
                   period->SetStringBoxProxy(proxy);
                   period->Start();
                   if(r->GetClean())
                       connect(box,SIGNAL(Removed(QString)),loader,SLOT(ItemDeleted(QString)));

                   n->SetValue(box);
                   n->SetStringBoxProxy(proxy);

                   EngineRes->Add(Name,n);

               }
            }

        }
    }



}


