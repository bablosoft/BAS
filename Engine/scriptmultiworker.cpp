#include "scriptmultiworker.h"
#include <QTime>
#include <QTimer>
#include "csvhelperwrapper.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    ScriptMultiWorker::ScriptMultiWorker(QObject *parent) :
        IMultiWorker(parent), engine(0), Waiter(0), ResourceHandlers(0), IsAborted(false), StageTimeoutTimer(0), DoTrace(false), Helper(0), IsRecord(false)
    {
    }

    void ScriptMultiWorker::SetDatabaseConnector(IDatabaseConnector *DatabaseConnector)
    {
        this->DatabaseConnector = DatabaseConnector;
    }

    IDatabaseConnector * ScriptMultiWorker::GetDatabaseConnector()
    {
        return DatabaseConnector;
    }

    void ScriptMultiWorker::SetCsvHelper(ICsvHelper *CsvHelper)
    {
        this->CsvHelper = CsvHelper;
    }

    ICsvHelper * ScriptMultiWorker::GetCsvHelper()
    {
        return CsvHelper;
    }

    void ScriptMultiWorker::SetHelperFactory(IHelperFactory* HelperFactory)
    {
        this->HelperFactory = HelperFactory;
    }
    IHelperFactory* ScriptMultiWorker::GetHelperFactory()
    {
        return HelperFactory;
    }

    void ScriptMultiWorker::SetHtmlParserFactory(IHtmlParserFactory* HtmlParserFactory)
    {
        this->HtmlParserFactory = HtmlParserFactory;
    }

    IHtmlParserFactory* ScriptMultiWorker::GetHtmlParserFactory()
    {
        return HtmlParserFactory;
    }

    void ScriptMultiWorker::SetProperties(IProperties* Properties)
    {
        this->Properties = Properties;
    }

    IProperties* ScriptMultiWorker::GetProperties()
    {
        return Properties;
    }

    void ScriptMultiWorker::SetReportData(IScriptMultiWorkerReportData *ReportData)
    {
        this->ReportData = ReportData;
    }

    IScriptMultiWorkerReportData * ScriptMultiWorker::GetReportData()
    {
        return ReportData;
    }


    void ScriptMultiWorker::SetHttpClientFactory(IHttpClientFactory* HttpClientFactory)
    {
        this->HttpClientFactory = HttpClientFactory;
    }

    IHttpClientFactory* ScriptMultiWorker::GetHttpClientFactory()
    {
        return HttpClientFactory;
    }

    void ScriptMultiWorker::SetPop3ClientFactory(IPop3ClientFactory* Pop3ClientFactory)
    {
        this->Pop3ClientFactory = Pop3ClientFactory;
    }

    IPop3ClientFactory* ScriptMultiWorker::GetPop3ClientFactory()
    {
        return Pop3ClientFactory;
    }

    void ScriptMultiWorker::SetImapClientFactory(IImapClientFactory* ImapClientFactory)
    {
        this->ImapClientFactory = ImapClientFactory;
    }

    IImapClientFactory* ScriptMultiWorker::GetImapClientFactory()
    {
        return ImapClientFactory;
    }


    void ScriptMultiWorker::SetPreprocessor(IPreprocessor *Preprocessor)
    {
        this->Preprocessor = Preprocessor;
    }

    IPreprocessor * ScriptMultiWorker::GetPreprocessor()
    {
        return Preprocessor;

    }


    void ScriptMultiWorker::SetWorkerFactory(IWorkerFactory *WorkerFactory)
    {
        this->WorkerFactory = WorkerFactory;
    }

    IWorkerFactory * ScriptMultiWorker::GetWorkerFactory()
    {
        return WorkerFactory;
    }

    void ScriptMultiWorker::SetBrowserFactory(IBrowserFactory *BrowserFactory)
    {
        this->BrowserFactory = BrowserFactory;
    }

    IBrowserFactory * ScriptMultiWorker::GetBrowserFactory()
    {
        return BrowserFactory;
    }

    void ScriptMultiWorker::SetLogger(ILogger *Logger)
    {
        this->Logger = Logger;
    }

    ILogger * ScriptMultiWorker::GetLogger()
    {
        return Logger;
    }

    void ScriptMultiWorker::SetResults1(ILogger *Results1)
    {
        this->Results1 = Results1;
    }
    ILogger * ScriptMultiWorker::GetResults1()
    {
        return Results1;
    }

    void ScriptMultiWorker::SetResults2(ILogger *Results2)
    {
        this->Results2 = Results2;
    }
    ILogger * ScriptMultiWorker::GetResults2()
    {
        return Results2;
    }

    void ScriptMultiWorker::SetResults3(ILogger *Results3)
    {
        this->Results3 = Results3;
    }
    ILogger * ScriptMultiWorker::GetResults3()
    {
        return Results3;
    }

    void ScriptMultiWorker::SetResults4(ILogger *Results4)
    {
        this->Results4 = Results4;
    }
    ILogger * ScriptMultiWorker::GetResults4()
    {
        return Results4;
    }

    void ScriptMultiWorker::SetResults5(ILogger *Results5)
    {
        this->Results5 = Results5;
    }
    ILogger * ScriptMultiWorker::GetResults5()
    {
        return Results5;
    }

    void ScriptMultiWorker::SetResults6(ILogger *Results6)
    {
        this->Results6 = Results6;
    }
    ILogger * ScriptMultiWorker::GetResults6()
    {
        return Results6;
    }

    void ScriptMultiWorker::SetResults7(ILogger *Results7)
    {
        this->Results7 = Results7;
    }
    ILogger * ScriptMultiWorker::GetResults7()
    {
        return Results7;
    }

    void ScriptMultiWorker::SetResults8(ILogger *Results8)
    {
        this->Results8 = Results8;
    }
    ILogger * ScriptMultiWorker::GetResults8()
    {
        return Results8;
    }

    void ScriptMultiWorker::SetResults9(ILogger *Results9)
    {
        this->Results9 = Results9;
    }
    ILogger * ScriptMultiWorker::GetResults9()
    {
        return Results9;
    }

    void ScriptMultiWorker::SetScript(const QString& Script)
    {
        this->Script = Script;
    }

    QString ScriptMultiWorker::GetScript()
    {
        return Script;
    }

    void ScriptMultiWorker::SetScriptSuspender(IScriptSuspender* ScriptSuspender)
    {
        this->ScriptSuspender = ScriptSuspender;

    }

    IScriptSuspender* ScriptMultiWorker::GetScriptSuspender()
    {
        return ScriptSuspender;
    }

    void ScriptMultiWorker::SetAbortFunction(const QString& AbortFunction)
    {
        this->AbortFunction = AbortFunction;
    }


    void ScriptMultiWorker::SetWaiterFactory(IWaiterFactory* WaiterFactory)
    {
        this->WaiterFactory = WaiterFactory;
        if(Waiter)
            Waiter->deleteLater();
        Waiter = WaiterFactory->CreateWaiter();
        Waiter->setParent(this);
    }
    IWaiterFactory* ScriptMultiWorker::GetWaiterFactory()
    {
        return WaiterFactory;
    }

    void ScriptMultiWorker::SetScriptResources(IScriptResources* ScriptResources)
    {
        this->ScriptResources = ScriptResources;
    }
    IScriptResources* ScriptMultiWorker::GetScriptResources()
    {
        return ScriptResources;
    }

    void ScriptMultiWorker::SetResourceHandlersFactory(IResourceHandlersFactory* ResourceHandlersFactory)
    {
        this->ResourceHandlersFactory = ResourceHandlersFactory;
        if(ResourceHandlers)
            ResourceHandlers->deleteLater();
        ResourceHandlers = ResourceHandlersFactory->CreateResourceHandlers();
        ResourceHandlers->setParent(this);
    }
    IResourceHandlersFactory* ScriptMultiWorker::GetResourceHandlersFactory()
    {
        return ResourceHandlersFactory;
    }

    void ScriptMultiWorker::SetSolverFactory(ISolverFactory* FactorySolver)
    {
        this->FactorySolver = FactorySolver;
    }
    ISolverFactory* ScriptMultiWorker::GetSolverFactory()
    {
        return FactorySolver;
    }

    void ScriptMultiWorker::SetEngineResources(IEngineResources* EngineRes)
    {
        this->EngineRes = EngineRes;
    }
    IEngineResources* ScriptMultiWorker::GetEngineResources()
    {
        return EngineRes;
    }

    void ScriptMultiWorker::SetDoTrace(bool DoTrace)
    {
        this->DoTrace = DoTrace;
    }

    bool ScriptMultiWorker::GetDoTrace()
    {
        return DoTrace;
    }

    void ScriptMultiWorker::SetIsRecord(bool IsRecord)
    {
        this->IsRecord = IsRecord;
    }

    bool ScriptMultiWorker::GetIsRecord()
    {
        return IsRecord;
    }

    void ScriptMultiWorker::ProgressValueSlot(int value)
    {
        emit ProgressValue(value);
    }

    void ScriptMultiWorker::ProgressMaximumSlot(int max)
    {
        emit ProgressMaximum(max);
    }

    void ScriptMultiWorker::AddModule(QObject *Module, const QString& Name, bool AddToMultiWorker, bool AddToWorker)
    {
        if(AddToMultiWorker)
            ModulesMultiWorker.insert(Name,Module);

        if(AddToWorker)
            ModulesScriptWorker.insert(Name,Module);
    }

    void ScriptMultiWorker::Run()
    {
        if(!Helper)
        {
            Helper = HelperFactory->GetHelper();
            Helper->setParent(this);
        }

        engine = new QScriptEngine(this);
        NeedToSetAsyncResult = false;

        QScriptValue ScriptMultiWorkerValue = engine->newQObject(this);
        engine->globalObject().setProperty("MultiScriptWorker", ScriptMultiWorkerValue);

        QScriptValue CsvHelperValue = engine->newQObject(new CsvHelperWrapper(engine,CsvHelper,this));
        engine->globalObject().setProperty("CsvHelper", CsvHelperValue);

        QScriptValue Results1Value = engine->newQObject(Results1);
        engine->globalObject().setProperty("Results1", Results1Value);

        QScriptValue Results2Value = engine->newQObject(Results2);
        engine->globalObject().setProperty("Results2", Results2Value);

        QScriptValue Results3Value = engine->newQObject(Results3);
        engine->globalObject().setProperty("Results3", Results3Value);

        QScriptValue Results4Value = engine->newQObject(Results4);
        engine->globalObject().setProperty("Results4", Results4Value);

        QScriptValue Results5Value = engine->newQObject(Results5);
        engine->globalObject().setProperty("Results5", Results5Value);

        QScriptValue Results6Value = engine->newQObject(Results6);
        engine->globalObject().setProperty("Results6", Results6Value);

        QScriptValue Results7Value = engine->newQObject(Results7);
        engine->globalObject().setProperty("Results7", Results7Value);

        QScriptValue Results8Value = engine->newQObject(Results8);
        engine->globalObject().setProperty("Results8", Results8Value);

        QScriptValue Results9Value = engine->newQObject(Results9);
        engine->globalObject().setProperty("Results9", Results9Value);

        QScriptValue PropertiesValue = engine->newQObject(Properties);
        engine->globalObject().setProperty("Properties", PropertiesValue);


        QScriptValue EngineResValue = engine->newQObject(EngineRes);
        engine->globalObject().setProperty("EngineRes", EngineResValue);

        QScriptValue ResourceHandlersValue = engine->newQObject(ResourceHandlers);
        engine->globalObject().setProperty("ResourceHandlers", ResourceHandlersValue);

        QScriptValue LoggerValue = engine->newQObject(Logger);
        engine->globalObject().setProperty("Logger", LoggerValue);

        QScriptValue WaiterValue = engine->newQObject(Waiter);
        engine->globalObject().setProperty("Waiter", WaiterValue);

        QScriptValue HelperValue = engine->newQObject(Helper);
        engine->globalObject().setProperty("Helper", HelperValue);

        QHash<QString,QObject*>::iterator i = ModulesMultiWorker.begin();
        while (i != ModulesMultiWorker.end())
        {
            QScriptValue Value = engine->newQObject(i.value());
            engine->globalObject().setProperty(i.key(), Value);
            i++;
        }

        connect(ScriptSuspender, SIGNAL(Suspended(IWorker*)), this, SLOT(WorkerSuspended(IWorker*)));
        connect(ScriptSuspender, SIGNAL(Resumed(IWorker*)), this, SLOT(WorkerResumed()));

        foreach(QString script, ScriptResources->GetMultiEngineScripts())
            engine->evaluate(script);


        //Script = Preprocessor->Preprocess(Script,0);

        ReportData->Start();

        RunSubScript();


    }
    void ScriptMultiWorker::RunSubScript()
    {
        if(engine->isEvaluating())
        {
            OnFinishScript += ";" + Script;
            return;
        }
        while(true)
        {
            if(NeedToSetAsyncResult)
            {
                engine->evaluate("_set_result(MultiScriptWorker.GetAsyncResult())");
                NeedToSetAsyncResult = false;
            }
            engine->evaluate(Script);
            if(engine->hasUncaughtException())
            {
                ResourceHandlers->Fail();
                ReportData->Final(QString("Script finished with error :") + engine->uncaughtException().toString());
                ReportData->Stop();
                QString Exception = engine->uncaughtException().toString();
                if(DoTrace)
                    Exception += QString(" Line number:") + QString::number(engine->uncaughtExceptionLineNumber()) +  " During execution of script " + Script;

                Logger->WriteFail(QString("[%1] Script finished with error : ").arg(CurrentTimeString()) + Exception );
                emit Finished();
                break;
            }else
            {
                if(!IsAborted && !OnFinishScript.isEmpty())
                {
                    Script = OnFinishScript;
                    OnFinishScript.clear();
                }else if(!IsAborted && Waiter && !Waiter->IsActive())
                {
                    Script = "_next()";
                    continue;

                }else
                {
                    break;
                }
            }
        }
    }

    void ScriptMultiWorker::Decrypt(const QString& Data)
    {
        Script = Preprocessor->Decrypt(Data);
        RunSubScript();
    }


    void ScriptMultiWorker::AbortSubscript()
    {
        engine->abortEvaluation();
    }

    void ScriptMultiWorker::SuccessInternal()
    {

        ReportData->Stop();
        Abort();
    }

    void ScriptMultiWorker::FailInternal(const QString&  message)
    {
        Logger->WriteFail(message);
        ReportData->Fail(QString("Ended with message: ") + message);
        ReportData->Final(message);
        ReportData->Stop();
        Abort();
    }

    void ScriptMultiWorker::Abort()
    {
        NoNeedToCreateWorkersMore = true;
        if(engine)
        {
            engine->abortEvaluation();
        }
        if(Waiter)
            Waiter->Abort();

        ReportData->Final("Aborted By User");
        ReportData->Stop();

        AbortWorkers();


        ScriptFinished();

    }

    void ScriptMultiWorker::ScriptFinished()
    {
        if(IsAborted)
            return;
        engine->evaluate(AbortFunction);
        AbortFunction.clear();
        IsAborted = true;
        ResourceHandlers->Success();
        Logger->Write(QString("[%1] Script finished correctly").arg(CurrentTimeString()));
        emit Finished();
    }


    void ScriptMultiWorker::AbortWorkers()
    {
        foreach(IWorker *w,Workers)
        {
            if(w)
            {
                w->Abort();
            }

        }

        foreach(IBrowser *b,Browsers)
        {
            b->SetWorker(0);
        }
    }

    void ScriptMultiWorker::RunStage(int ThreadsNumber, int MaximumSuccess, int MaximumFailure, int MaxRunTime, const QString& WorkerFunction, const QString& callback)
    {
        if(IsRecord)
        {
            ThreadsNumber = 1;
            MaximumSuccess = 1;
            MaximumFailure = 1;
            MaxRunTime = 0;
        }
        ReportData->Final("Success");
        Script = callback;
        SuccessLeft = MaximumSuccess;
        FailLeft = MaximumFailure;
        WorkerScript = WorkerFunction;
        NoNeedToCreateWorkersMore = false;
        Browsers = BrowserFactory->Create(ThreadsNumber);
        WorkerRunning = ThreadsNumber;
        Waiter->WaitForStageFinished(this,SIGNAL(StageFinished()),this,SLOT(RunSubScript()));
        for(int i = 0;i<ThreadsNumber;i++)
        {
            CreateWorker(i);
        }
        if(MaxRunTime>10)
        {
            StageTimeoutTimer = new QTimer(this);
            StageTimeoutTimer->setSingleShot(true);

            connect(StageTimeoutTimer,SIGNAL(timeout()), this, SLOT(StageTimeout()));
            StageTimeoutTimer->start(MaxRunTime);
        }
    }

    void ScriptMultiWorker::StageTimeout()
    {
        ReportData->Final("Stage Timeout");
        StageTimeoutTimer->deleteLater();
        StageTimeoutTimer = 0;
        NoNeedToCreateWorkersMore = true;
        AbortWorkers();
    }

    void ScriptMultiWorker::WorkerSuspended(IWorker * Worker)
    {
        WorkerFinishedWithArgument(Worker);
    }

    void ScriptMultiWorker::WorkerResumed()
    {
        int index = -1;int i = 0;
        foreach(IWorker *w,Workers)
        {
            if(!w)
                index = i;
            i++;
        }
        if(index >= 0)
        {
            TakeWorkerFromSuspended(index);
        }
    }

    void ScriptMultiWorker::WorkerFinishedWithArgument(IWorker * w)
    {
        int SuspendedCount = ScriptSuspender->Count();
        bool DontCreateNewWaitForSuspended = false;
        bool IsSuspended = false;


        switch(w->GetResultStatus())
        {
            case IWorker::SuccessStatus:
            {
                Logger->WriteSuccess(w->GetResultMessage());
                if(w->GetResultMessageRaw() != "none")
                {
                    if(!NoNeedToCreateWorkersMore)
                    {
                        ReportData->Success(w->GetResultMessageRaw());
                        emit Success();
                    }

                    SuccessLeft--;
                    if(SuccessLeft<=0)
                    {
                       NoNeedToCreateWorkersMore = true;
                    }else if(SuccessLeft - SuspendedCount <= 0)
                    {
                        DontCreateNewWaitForSuspended = true;
                    }
                }

            }break;
            case IWorker::FailStatus:
            {
                Logger->WriteFail(w->GetResultMessage());
                if(!NoNeedToCreateWorkersMore)
                {
                    ReportData->Fail(w->GetResultMessageRaw());
                    emit Failed();
                }
                FailLeft--;
                if(FailLeft<=0)
                {
                    ReportData->Final("Too Much Fails");
                    NoNeedToCreateWorkersMore = true;
                }
            }break;
            case IWorker::DieStatus:
            {
                Logger->Write(w->GetResultMessage());
                if(!NoNeedToCreateWorkersMore)
                {
                    ReportData->Fail(QString("Ended with message: ") + w->GetResultMessageRaw());
                    ReportData->Final(QString("Ended with message: ") + w->GetResultMessageRaw());
                    NoNeedToCreateWorkersMore = true;
                }
            }break;
            case IWorker::SuspendStatus:
            {
                Logger->Write(w->GetResultMessage());
                IsSuspended = true;

                if(SuccessLeft - SuspendedCount <= 0)
                {
                    DontCreateNewWaitForSuspended = true;
                }
            }break;

        }
        int index = Workers.indexOf(w);
        if(!IsSuspended)
        {
            w->GetWaiter()->Abort();
            w->disconnect();
            w->deleteLater();
        }

        Workers.replace(index,0);
        if(DontCreateNewWaitForSuspended)
        {

            WorkerResumed();
            return;
        }

        WorkerRunning --;

        if(WorkerRunning == 0 && NoNeedToCreateWorkersMore)
        {
            Logger->Write("Stage Finished");
            if(StageTimeoutTimer)
            {
                StageTimeoutTimer->deleteLater();
                StageTimeoutTimer = 0;
            }

            emit StageFinished();
            return;
        }
        if(NoNeedToCreateWorkersMore)
        {
            AbortWorkers();
        }else
        {
            WorkerRunning ++;
            CreateWorker(index);
        }
    }

    void ScriptMultiWorker::WorkerFinished()
    {
        IWorker * w = qobject_cast<IWorker*>(sender());
        WorkerFinishedWithArgument(w);
    }

    bool ScriptMultiWorker::TakeWorkerFromSuspended(int index)
    {
        QPair<IWorker*,IScriptSuspender::WorkerStatus> SuspenderStatus = ScriptSuspender->GetWorker();
        if(SuspenderStatus.second == IScriptSuspender::Ready)
        {
            IWorker *worker = SuspenderStatus.first;
            worker->setParent(this);
            Workers.replace(index,worker);
            worker->SetBrowser(Browsers.at(index));
            worker->RunSubScript();
            return true;
        }
        return false;

    }

    void ScriptMultiWorker::CreateWorker(int index)
    {
        if(TakeWorkerFromSuspended(index))
            return;

        IWorker *worker = WorkerFactory->CreateWorker();
        worker->SetIsRecord(IsRecord);
        connect(worker,SIGNAL(SuccessedButRescued(QString)),ReportData,SLOT(SuccessAndRescued(QString)));
        connect(worker,SIGNAL(FailedButRescued(QString)),ReportData,SLOT(FailAndRescued(QString)));
        connect(worker,SIGNAL(ProgressMaximum(int)),this,SLOT(ProgressMaximumSlot(int)));
        connect(worker,SIGNAL(ProgressValue(int)),this,SLOT(ProgressValueSlot(int)));

        QHash<QString,QObject*>::iterator i = ModulesScriptWorker.begin();
        while (i != ModulesScriptWorker.end())
        {
            worker->AddModule(i.value(),i.key());
            i++;
        }

        worker->SetDatabaseConnector(DatabaseConnector);
        worker->SetPreprocessor(Preprocessor);
        worker->SetThreadNumber(index + 1);
        worker->SetHttpClientFactory(HttpClientFactory);
        worker->SetPop3ClientFactory(Pop3ClientFactory);
        worker->SetImapClientFactory(ImapClientFactory);
        worker->SetHtmlParserFactory(HtmlParserFactory);
        worker->SetHelperFactory(HelperFactory);
        worker->SetProperties(Properties);
        worker->SetCsvHelper(CsvHelper);

        worker->setParent(this);
        worker->SetDoTrace(GetDoTrace());

        worker->SetBrowser(Browsers.at(index));

        worker->SetLogger(Logger);

        worker->SetResults1(Results1);
        worker->SetResults2(Results2);
        worker->SetResults3(Results3);
        worker->SetResults4(Results4);
        worker->SetResults5(Results5);
        worker->SetResults6(Results6);
        worker->SetResults7(Results7);
        worker->SetResults8(Results8);
        worker->SetResults9(Results9);

        worker->SetScript(WorkerScript);

        worker->SetScriptResources(ScriptResources);

        worker->SetScriptSuspender(ScriptSuspender);

        IResourceHandlers* ResourceHandlers = ResourceHandlersFactory->CreateResourceHandlers();
        ResourceHandlers->setParent(worker);
        worker->SetResourceHandlers(ResourceHandlers);

        IWaiter* WaiterLocal = WaiterFactory->CreateWaiter();
        WaiterLocal->setParent(worker);

        worker->SetWaiter(WaiterLocal);

        worker->SetSolverFactory(FactorySolver);

        worker->SetEngineResources(EngineRes);


        if(index < Workers.size())
        {
            Workers.replace(index,worker);
        }else
        {
            Workers.append(worker);
        }

        connect(worker,SIGNAL(Finished()),this,SLOT(WorkerFinished()));
        worker->Run();


    }

    void ScriptMultiWorker::SetAsyncResult(const QScriptValue & AsyncResult)
    {
        NeedToSetAsyncResult = true;
        this->AsyncResult = AsyncResult;
    }

    QScriptValue ScriptMultiWorker::GetAsyncResult()
    {
        return AsyncResult;
    }

    void ScriptMultiWorker::ReloadResource(const QString& name)
    {
        EngineRes->Reload(name);
    }

    void ScriptMultiWorker::RemoveResource(const QString& name)
    {
        EngineRes->Remove(name);
    }

    void ScriptMultiWorker::AddResource(const QString& name, bool successes, bool fails, int simultaneous, int interval, bool greedy, bool dont_give_up)
    {
        EngineRes->Create(name, successes, fails, simultaneous, interval, greedy, dont_give_up);
    }

    void ScriptMultiWorker::GetHandler(const QString& name, bool die_on_fail, const QString& callback)
    {
        DieOnFailHandler = die_on_fail;
        Script = callback;
        QSet<QString> temp;
        Waiter->WaitForHandler(EngineRes,name,temp,this,SLOT(HandlerWaitFinishedSuccess()),this,SLOT(HandlerWaitFinishedFailed()));
    }

    QScriptValue ScriptMultiWorker::GetAllData(const QString& name)
    {
        QList<QScriptValue> data = EngineRes->GetAllData(name);

        QScriptValue res = engine->newArray(data.length());
        int index = 0;
        foreach(QScriptValue val, data)
        {
            res.setProperty(index,val);

            index ++;
        }

        return res;

    }

    QScriptValue ScriptMultiWorker::GetRandomSubarrayData(const QString& name, int size)
    {
        QList<QScriptValue> data = EngineRes->GetRandomSubarrayData(name, size);

        QScriptValue res = engine->newArray(data.length());
        int index = 0;
        foreach(QScriptValue val, data)
        {
            res.setProperty(index,val);

            index ++;
        }

        return res;
    }

    QScriptValue ScriptMultiWorker::GetAtIndex(const QString& name, int index)
    {
        return EngineRes->GetAtIndex(name,index);
    }

    void ScriptMultiWorker::SetAtIndex(const QString& name, int index, const QString& val)
    {
        EngineRes->SetAtIndex(name,index,val);
    }

    QScriptValue ScriptMultiWorker::GetTotalLength(const QString& name)
    {
        return QScriptValue(EngineRes->GetTotalLength(name));
    }

    void ScriptMultiWorker::HandlerWaitFinishedSuccess()
    {
        IResourceHandler *ihandler = Waiter->GetLastHandler();
        if(!ihandler)
        {
            SetAsyncResult(engine->undefinedValue());
        }else
        {
            ResourceHandlers->AddHandler(ihandler);
            SetAsyncResult(engine->newQObject(ihandler));
        }


        RunSubScript();
    }

    void ScriptMultiWorker::Sleep(int msec, const QString& callback)
    {
        Script = callback;
        Waiter->Sleep(msec,this,SLOT(RunSubScript()));
    }

    void ScriptMultiWorker::HandlerWaitFinishedFailed()
    {
        if(DieOnFailHandler)
        {
            ResourceHandlers->Fail();
            ReportData->Final("Failed to get resource inside core");
            Logger->Write("failed to get resource");
            emit Finished();
        }else
        {
            engine->evaluate("_set_result(null)");
            RunSubScript();
        }
    }

    QString ScriptMultiWorker::CurrentTimeString()
    {
        return QTime::currentTime().toString("hh:mm:ss");;
    }

    QString ScriptMultiWorker::DatabaseAddGroup(const QString& GroupName,const QString& GroupDescription, int TableId)
    {
        DatabaseGroup Group;
        Group.IsNull = false;
        Group.Name = GroupName;
        Group.Description = GroupDescription;
        return DatabaseConnector->InsertGroup(Group,TableId);
    }



}
