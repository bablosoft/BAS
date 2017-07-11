#include "scriptmultiworker.h"
#include <QTime>
#include <QTimer>
#include "csvhelperwrapper.h"
#include <limits>
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    ScriptMultiWorker::ScriptMultiWorker(QObject *parent) :
        IMultiWorker(parent), engine(0), Waiter(0), ResourceHandlers(0), IsAborted(false), StageTimeoutTimer(0), DoTrace(false), Helper(0), IsRecord(false), DieInstant(false), SuccessNumber(0), FailNumber(0), CurrentThreadNumber(-1)
    {
    }


    void ScriptMultiWorker::SetProjectPath(const QString& ProjectPath)
    {
        this->ProjectPath = ProjectPath;
    }
    QString ScriptMultiWorker::GetProjectPath()
    {
        return ProjectPath;
    }

    void ScriptMultiWorker::SetModuleManager(IModuleManager *ModuleManager)
    {
        this->ModuleManager = ModuleManager;
    }

    IModuleManager* ScriptMultiWorker::GetModuleManager()
    {
        return ModuleManager;
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

    void ScriptMultiWorker::SetStringBuilder(IStringBuilder *StringBuilder)
    {
        this->StringBuilder = StringBuilder;
    }

    IStringBuilder * ScriptMultiWorker::GetStringBuilder()
    {
        return StringBuilder;
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

    void ScriptMultiWorker::SetWorkerSettings(IWorkerSettings* WorkerSettings)
    {
        this->WorkerSettings = WorkerSettings;
    }

    IWorkerSettings* ScriptMultiWorker::GetWorkerSettings()
    {
        return WorkerSettings;
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

    void ScriptMultiWorker::SetAdditionEngineScripts(const QList<QString>& AdditionalScripts)
    {
        this->AdditionalScripts = AdditionalScripts;
    }

    QList<QString> ScriptMultiWorker::GetAdditionEngineScripts()
    {
        return AdditionalScripts;
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



        //Prepare additional scripts one time
        int ScriptLength = AdditionalScripts.size();
        for(int i = 0;i<ScriptLength;i++)
        {
            AdditionalScripts[i] = Preprocessor->Preprocess(AdditionalScripts[i],0);
        }
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
            //qDebug()<<"engine->evaluate(Script)"<<Script;
            engine->evaluate(Script);
            if(engine->hasUncaughtException())
            {
                ResourceHandlers->Fail();
                ReportData->Final(tr("Script finished with error :") + engine->uncaughtException().toString());
                ReportData->Stop();
                QString Exception = engine->uncaughtException().toString();
                if(DoTrace)
                    Exception += tr(" Line number:") + QString::number(engine->uncaughtExceptionLineNumber()) +  tr(" During execution of script ") + Script;

                Logger->WriteFail(tr("[%1] Script finished with error : ").arg(CurrentTimeString()) + Exception );
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
        ReportData->Fail(tr("Ended with message: ") + message);
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

        ReportData->Final(tr("Aborted By User"));
        ReportData->Stop();

        AbortWorkers(true);


        ScriptFinished();

    }

    void ScriptMultiWorker::AbortNotInstant()
    {
        NoNeedToCreateWorkersMore = true;
        ReportData->Final(tr("Aborted By User"));
    }

    void ScriptMultiWorker::InterruptAction()
    {
        emit InterruptActionSignal();
    }

    void ScriptMultiWorker::ScriptFinished()
    {
        if(IsAborted)
            return;
        engine->evaluate(AbortFunction);
        AbortFunction.clear();
        IsAborted = true;
        ResourceHandlers->Success();
        Logger->Write(tr("[%1] Script finished correctly").arg(CurrentTimeString()));
        emit Finished();
    }


    void ScriptMultiWorker::AbortWorkers(bool NotSignalResourceHandlers)
    {
        foreach(IWorker *w,Workers)
        {
            if(w)
            {
                if(NotSignalResourceHandlers)
                {
                    w->Abort(IsRecord);
                }else
                {
                    w->Abort(true);
                }
            }

        }

        foreach(IWorker *w,Substages.GetAllWorkers())
        {
            if(w)
            {
                if(NotSignalResourceHandlers)
                {
                    w->Abort(IsRecord);
                }else
                {
                    w->Abort(true);
                }
            }

        }


        foreach(IBrowser *b,Browsers)
        {
            b->SetWorker(0);
        }

        foreach(IBrowser *b,Substages.GetAllBrowsers())
        {
            b->SetWorker(0);
        }
    }

    void ScriptMultiWorker::RunSubstage(const QString& FunctionName, qint64 ThreadsNumber, qint64 MaximumSuccess, qint64 MaximumFailure, int StageId)
    {
        if(IsRecord)
        {
            ThreadsNumber = 1;
            MaximumSuccess = 1;
            MaximumFailure = 1;
        }
        int total = Substages.TotalWorkers();
        {
            QList<IBrowser*> BrowserLists = BrowserFactory->Create(ThreadsNumber);
            Substages.AddSubstage(StageId,MaximumSuccess,MaximumFailure,ThreadsNumber,BrowserLists);
        }
        QList<IWorker *> * WorkersList = Substages.GetWorkers(StageId);
        QList<IBrowser *> * BrowserLists = Substages.GetBrowsers(StageId);

        for(int i = 0;i<ThreadsNumber;i++)
        {
            CreateWorker(i,Workers.length() + total + i + 1,FunctionName,StageId,WorkersList,BrowserLists);
        }
    }


    void ScriptMultiWorker::RunStage(qint64 ThreadsNumber, qint64 MaximumSuccess, qint64 MaximumFailure, qint64 MaxRunTime, const QString& WorkerFunction, const QString& callback)
    {
        Substages.Clear();

        if(IsRecord)
        {
            CurrentThreadNumber = 1;
            ThreadsNumber = 1;
            MaximumSuccess = 1;
            MaximumFailure = 1;
            MaxRunTime = 0;
        }

        if(MaximumSuccess < 0)
            MaximumSuccess = std::numeric_limits<qint64>::max();
        if(MaximumFailure < 0)
            MaximumFailure = std::numeric_limits<qint64>::max();
        ReportData->Final(tr("Success"));
        Script = callback;
        SuccessLeft = MaximumSuccess;
        FailLeft = MaximumFailure;
        WorkerScript = WorkerFunction;
        NoNeedToCreateWorkersMore = false;
        BrowserFactory->ClearAll();
        Browsers = BrowserFactory->Create(ThreadsNumber);
        WorkerRunning = ThreadsNumber;
        CurrentThreadNumber = ThreadsNumber;
        Waiter->WaitForStageFinished(this,SIGNAL(StageFinished()),this,SLOT(RunSubScript()));
        for(int i = 0;i<ThreadsNumber;i++)
        {
            CreateWorker(i,i+1,"", 0, &Workers, &Browsers);
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
        ReportData->Final(tr("Stage Timeout"));
        StageTimeoutTimer->deleteLater();
        StageTimeoutTimer = 0;
        NoNeedToCreateWorkersMore = true;
        AbortWorkers(false);
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
        ModuleManager->StopThread(w->GetThreadNumber());

        if(w->SubstageGetParentId() > 0)
        {
            QList<IWorker *> * WorkersList = Substages.GetWorkers(w->SubstageGetParentId());
            if(!WorkersList)
                return;

            QList<IBrowser *> * BrowsersList = Substages.GetBrowsers(w->SubstageGetParentId());
            if(!BrowsersList)
                return;


            int index = WorkersList->indexOf(w);
            if(index < 0)
                return;

            WorkersList->replace(index,0);

            switch(w->GetResultStatus())
            {
                case IWorker::SuccessStatus:
                {
                    Substages.Success(w->SubstageGetParentId());
                }break;
                case IWorker::FailStatus:
                {
                    Substages.Failure(w->SubstageGetParentId());
                }break;
                case IWorker::DieStatus:
                {
                    Substages.Die(w->SubstageGetParentId());
                }break;
            }

            w->GetWaiter()->Abort();
            w->disconnect();
            w->deleteLater();

            if(NoNeedToCreateWorkersMore)
            {
                Substages.EndThread(w->SubstageGetParentId());
            }else if(Substages.CreateThread(w->SubstageGetParentId()))
                CreateWorker(index,w->GetThreadNumber(), w->SubstageGetStartingFunction(), w->SubstageGetParentId(), WorkersList, BrowsersList);

            if(Substages.NeedToFinishStage(w->SubstageGetParentId()))
            {
                QList<IBrowser *> * Browsers = Substages.GetBrowsers(w->SubstageGetParentId());
                if(Browsers)
                    BrowserFactory->Clear(Browsers);
                Substages.RemoveStage(w->SubstageGetParentId());
                emit SubstageFinished(w->SubstageGetParentId());
            }


            return;
        }

        int SuspendedCount = ScriptSuspender->Count();
        bool DontCreateNewWaitForSuspended = false;
        bool IsSuspended = false;
        bool LastDieInstant = DieInstant;
        if(w->IsDieInstant())
            DieInstant = true;

        bool DontCreateMore = w->IsDontCreateMore();

        bool IsAllDontCreateMore = true;

        if(Workers.size() < CurrentThreadNumber)
        {
            IsAllDontCreateMore = false;
        }else
        {
            foreach(IWorker *w,Workers)
            {
                if(w && !w->IsDontCreateMore())
                {
                    IsAllDontCreateMore = false;
                    break;
                }
            }
        }


        switch(w->GetResultStatus())
        {
            case IWorker::SuccessStatus:
            {
                if(w->GetResultMessageRaw() != "none")
                {
                    Logger->WriteSuccess(w->GetResultMessage());

                    if(!LastDieInstant)
                    {
                        ReportData->Success(w->GetResultMessageRaw());
                        SuccessNumber ++;
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
                if(!LastDieInstant)
                {
                    ReportData->Fail(w->GetResultMessageRawWithId());
                    FailNumber ++;
                    emit Failed();
                }
                FailLeft--;
                if(FailLeft<=0)
                {
                    ReportData->Final(tr("Too Much Fails"));
                    NoNeedToCreateWorkersMore = true;
                }
            }break;
            case IWorker::DieStatus:
            {
                Logger->Write(w->GetResultMessage());
                if(!LastDieInstant)
                {
                    ReportData->Fail(tr("Ended with message: ") + w->GetResultMessageRaw());
                    ReportData->Final(tr("Ended with message: ") + w->GetResultMessageRaw());
                }
                NoNeedToCreateWorkersMore = true;

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

        if((WorkerRunning == 0 && NoNeedToCreateWorkersMore) || IsAllDontCreateMore)
        {
            NoNeedToCreateWorkersMore = true;
            //Logger->Write("Stage Finished");
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
            if(DieInstant)
                AbortWorkers(false);
            else
            {
                foreach(IWorker *w,Workers)
                {
                    if(w)
                       w->GetWaiter()->SetSkipWaitHandlerMode();
                }
            }
        }else
        {
            if(!DontCreateMore)
            {
                WorkerRunning ++;
                CreateWorker(index,index+1, "", 0, &Workers, &Browsers);
            }
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

    void ScriptMultiWorker::CreateWorker(int index, int ThreadIndex, const QString& StartingFunction, int StageId, QList<IWorker *>* WorkersList, QList<IBrowser *>* BrowsersList)
    {
        if(TakeWorkerFromSuspended(index))
            return;


        IWorker *worker = WorkerFactory->CreateWorker();

        worker->SubstageSetStartingFunction(StartingFunction);
        worker->SubstageSetParentId(StageId);
        worker->SetModuleManager(ModuleManager);
        worker->SetStringBuilder(StringBuilder);
        worker->SetAdditionEngineScripts(&AdditionalScripts);
        worker->SetIsRecord(IsRecord);
        connect(this,SIGNAL(InterruptActionSignal()),worker,SLOT(InterruptAction()));
        connect(worker,SIGNAL(SuccessedButRescued(QString)),ReportData,SLOT(SuccessAndRescued(QString)));
        connect(worker,SIGNAL(FailedButRescued(QString)),ReportData,SLOT(FailAndRescued(QString)));
        connect(worker,SIGNAL(ProgressMaximum(int)),this,SLOT(ProgressMaximumSlot(int)));
        connect(worker,SIGNAL(ProgressValue(int)),this,SLOT(ProgressValueSlot(int)));
        connect(worker,SIGNAL(SubstageBeginSignal(QString,qint64,qint64,qint64,int)),this,SLOT(RunSubstage(QString,qint64,qint64,qint64,int)));
        connect(this,SIGNAL(SubstageFinished(int)),worker,SLOT(SubstageFinished(int)));

        QHash<QString,QObject*>::iterator i = ModulesScriptWorker.begin();
        while (i != ModulesScriptWorker.end())
        {
            worker->AddModule(i.value(),i.key());
            i++;
        }

        worker->SetDatabaseConnector(DatabaseConnector);
        worker->SetPreprocessor(Preprocessor);
        worker->SetThreadNumber(ThreadIndex);
        worker->SetSuccessNumber(&SuccessNumber);
        worker->SetFailNumber(&FailNumber);
        worker->SetProjectPath(GetProjectPath());

        worker->SetHttpClientFactory(HttpClientFactory);
        worker->SetPop3ClientFactory(Pop3ClientFactory);
        worker->SetImapClientFactory(ImapClientFactory);
        worker->SetHtmlParserFactory(HtmlParserFactory);
        worker->SetHelperFactory(HelperFactory);
        worker->SetProperties(Properties);
        worker->SetCsvHelper(CsvHelper);

        worker->setParent(this);
        worker->SetDoTrace(GetDoTrace());

        IWorkerSettings *NewWorkerSettings = WorkerSettings->Clone();
        IBrowser * BrowserAtIndex = BrowsersList->at(index);
        NewWorkerSettings->setParent(BrowserAtIndex);
        BrowserAtIndex->SetWorkerSettings(NewWorkerSettings);

        worker->SetBrowser(BrowserAtIndex);

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

        if(index < WorkersList->size())
        {
            WorkersList->replace(index,worker);
        }else
        {
            WorkersList->append(worker);
        }

        connect(worker,SIGNAL(Finished()),this,SLOT(WorkerFinished()));
        ModuleManager->StartThread(worker->GetThreadNumber());
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
            ReportData->Final(tr("All data have been processed"));
            Logger->Write(tr("All data have been processed"));
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
