#include "scriptworker.h"
#include "debugterminate.h"
#include "csvhelperwrapper.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{


    ScriptWorker::ScriptWorker(QObject *parent) :
        IWorker(parent), Browser(0), Logger(0), Results1(0),Results2(0), Results3(0),Results4(0),Results5(0),Results6(0),Results7(0),Results8(0),Results9(0), Waiter(0),engine(0),ThreadNumber(0),IsAborted(false),ProcessComunicator(0), HttpClient(0), Pop3Client(0), ImapClient(0), DoTrace(false), MaxFail(100), MaxSuccess(100), IsFailExceedRunning(false), IsSuccessExceedRunning(false)
    {

    }

    void ScriptWorker::SetDatabaseConnector(IDatabaseConnector *DatabaseConnector)
    {
        this->DatabaseConnector = DatabaseConnector;
    }
    IDatabaseConnector * ScriptWorker::GetDatabaseConnector()
    {
        return DatabaseConnector;
    }


    void ScriptWorker::SetCsvHelper(ICsvHelper *CsvHelper)
    {
        this->CsvHelper = CsvHelper;
    }

    ICsvHelper * ScriptWorker::GetCsvHelper()
    {
        return CsvHelper;
    }

    void ScriptWorker::SetPreprocessor(IPreprocessor* Preprocessor)
    {
        this->Preprocessor = Preprocessor;
    }

    void ScriptWorker::SetProperties(IProperties* Properties)
    {
        this->Properties = Properties;
    }

    IProperties* ScriptWorker::GetProperties()
    {
        return Properties;
    }

    IPreprocessor* ScriptWorker::GetPreprocessor()
    {
        return Preprocessor;
    }

    void ScriptWorker::SetHelperFactory(IHelperFactory* HelperFactory)
    {
        this->HelperFactory = HelperFactory;
    }

    IHelperFactory* ScriptWorker::GetHelperFactory()
    {
        return HelperFactory;
    }

    void ScriptWorker::SetHtmlParserFactory(IHtmlParserFactory* HtmlParserFactory)
    {
        this->HtmlParserFactory = HtmlParserFactory;
    }

    IHtmlParserFactory* ScriptWorker::GetHtmlParserFactory()
    {
        return HtmlParserFactory;
    }

    void ScriptWorker::SetHttpClientFactory(IHttpClientFactory* HttpClientFactory)
    {
        this->HttpClientFactory = HttpClientFactory;
    }

    IHttpClientFactory* ScriptWorker::GetHttpClientFactory()
    {
        return HttpClientFactory;
    }

    void ScriptWorker::SetProcessComunicator(IProcessComunicator *ProcessComunicator)
    {
        this->ProcessComunicator = ProcessComunicator;
    }

    IProcessComunicator * ScriptWorker::GetProcessComunicator()
    {
        return ProcessComunicator;
    }

    void ScriptWorker::SetAsyncResult(const QScriptValue & AsyncResult)
    {
        NeedToSetAsyncResult = true;
        this->AsyncResult = AsyncResult;
    }

    QScriptValue ScriptWorker::GetAsyncResult()
    {
        return AsyncResult;
    }


    void ScriptWorker::SetThreadNumber(int ThreadNumber)
    {
        this->ThreadNumber = ThreadNumber;
    }
    int ScriptWorker::GetThreadNumber()
    {
        return ThreadNumber;
    }

    void ScriptWorker::SetResourceHandlers(IResourceHandlers* ResourceHandlers)
    {
        this->ResourceHandlers = ResourceHandlers;
    }

    IResourceHandlers* ScriptWorker::GetResourceHandlers()
    {
        return ResourceHandlers;
    }

    void ScriptWorker::SetBrowser(IBrowser *Browser)
    {
        this->Browser = Browser;
    }

    IBrowser * ScriptWorker::GetBrowser()
    {
        return Browser;
    }

    void ScriptWorker::SetWaiter(IWaiter *Waiter)
    {
        this->Waiter = Waiter;
    }

    IWaiter * ScriptWorker::GetWaiter()
    {
        return Waiter;
    }


    void ScriptWorker::SetScriptResources(IScriptResources* ScriptResources)
    {
        this->ScriptResources = ScriptResources;
    }

    IScriptResources* ScriptWorker::GetScriptResources()
    {
        return ScriptResources;
    }

    void ScriptWorker::SetLogger(ILogger *Logger)
    {
        this->Logger = Logger;
    }

    ILogger * ScriptWorker::GetLogger()
    {
        return Logger;
    }

    void ScriptWorker::SetResults1(ILogger *Results1)
    {
        this->Results1 = Results1;
    }
    ILogger * ScriptWorker::GetResults1()
    {
        return Results1;
    }

    void ScriptWorker::SetResults2(ILogger *Results2)
    {
        this->Results2 = Results2;
    }
    ILogger * ScriptWorker::GetResults2()
    {
        return Results2;
    }

    void ScriptWorker::SetResults3(ILogger *Results3)
    {
        this->Results3 = Results3;
    }
    ILogger * ScriptWorker::GetResults3()
    {
        return Results3;
    }

    void ScriptWorker::SetResults4(ILogger *Results4)
    {
        this->Results4 = Results4;
    }
    ILogger * ScriptWorker::GetResults4()
    {
        return Results4;
    }

    void ScriptWorker::SetResults5(ILogger *Results5)
    {
        this->Results5 = Results5;
    }
    ILogger * ScriptWorker::GetResults5()
    {
        return Results5;
    }

    void ScriptWorker::SetResults6(ILogger *Results6)
    {
        this->Results6 = Results6;
    }
    ILogger * ScriptWorker::GetResults6()
    {
        return Results6;
    }

    void ScriptWorker::SetResults7(ILogger *Results7)
    {
        this->Results7 = Results7;
    }
    ILogger * ScriptWorker::GetResults7()
    {
        return Results7;
    }


    void ScriptWorker::SetResults8(ILogger *Results8)
    {
        this->Results8 = Results8;
    }
    ILogger * ScriptWorker::GetResults8()
    {
        return Results8;
    }

    void ScriptWorker::SetResults9(ILogger *Results9)
    {
        this->Results9 = Results9;
    }
    ILogger * ScriptWorker::GetResults9()
    {
        return Results9;
    }

    void ScriptWorker::SetScript(const QString& Script)
    {
        this->Script = Script;
    }

    QString ScriptWorker::GetScript()
    {
        return Script;
    }

    void ScriptWorker::SetSolverFactory(ISolverFactory* FactorySolver)
    {
        this->FactorySolver = FactorySolver;

    }

    ISolverFactory* ScriptWorker::GetSolverFactory()
    {
        return FactorySolver;
    }

    void ScriptWorker::SetEngineResources(IEngineResources* EngineRes)
    {
        this->EngineRes = EngineRes;
    }

    IEngineResources* ScriptWorker::GetEngineResources()
    {
        return EngineRes;
    }

    void ScriptWorker::SetScriptSuspender(IScriptSuspender* ScriptSuspender)
    {
        this->ScriptSuspender = ScriptSuspender;

    }

    IScriptSuspender* ScriptWorker::GetScriptSuspender()
    {
        return ScriptSuspender;
    }


    void ScriptWorker::ProgressValueSlot(int value)
    {
        emit ProgressValue(value);
    }

    void ScriptWorker::ProgressMaximumSlot(int max)
    {
        emit ProgressMaximum(max);
    }

    void ScriptWorker::SetFailFunction(const QString& FailFunction)
    {
        this->FailFunction = FailFunction;
    }

    void ScriptWorker::SetFailExceedFunction(const QString& FailExceedFunction)
    {
        this->FailExceedFunction = FailExceedFunction;
    }

    void ScriptWorker::SetSuccessExceedFunction(const QString& SuccessExceedFunction)
    {
        this->SuccessExceedFunction = SuccessExceedFunction;
    }

    void ScriptWorker::SetSuccessFunction(const QString& SuccessFunction)
    {
        this->SuccessFunction = SuccessFunction;
    }

    void ScriptWorker::SetAbortFunction(const QString& AbortFunction)
    {
        this->AbortFunction = AbortFunction;
    }

    void ScriptWorker::AddModule(QObject *Module, const QString& Name)
    {
        Modules.insert(Name, Module);
    }

    void ScriptWorker::SetPop3ClientFactory(IPop3ClientFactory* Pop3ClientFactory)
    {
        this->Pop3ClientFactory = Pop3ClientFactory;
    }
    IPop3ClientFactory* ScriptWorker::GetPop3ClientFactory()
    {
        return Pop3ClientFactory;
    }

    void ScriptWorker::SetImapClientFactory(IImapClientFactory* ImapClientFactory)
    {
        this->ImapClientFactory = ImapClientFactory;
    }

    IImapClientFactory* ScriptWorker::GetImapClientFactory()
    {
        return ImapClientFactory;
    }

    void ScriptWorker::SetDoTrace(bool DoTrace)
    {
        this->DoTrace = DoTrace;
    }

    bool ScriptWorker::GetDoTrace()
    {
        return DoTrace;
    }

    void ScriptWorker::SetIsRecord(bool IsRecord)
    {
        this->IsRecord = IsRecord;
    }

    bool ScriptWorker::GetIsRecord()
    {
        return IsRecord;
    }


    void ScriptWorker::Run()
    {
        ResultMessage = "Ok";
        ResultStatus = IWorker::SuccessStatus;


        engine = new QScriptEngine(this);
        NeedToSetAsyncResult = false;

        HtmlParser = HtmlParserFactory->GetHtmlParser();
        HtmlParser->setParent(this);

        Helper = HelperFactory->GetHelper();
        Helper->setParent(this);

        QScriptValue HelperValue = engine->newQObject(Helper);
        engine->globalObject().setProperty("Helper", HelperValue);

        QScriptValue CsvHelperValue = engine->newQObject(new CsvHelperWrapper(engine,CsvHelper,this));
        engine->globalObject().setProperty("CsvHelper", CsvHelperValue);

        QScriptValue HtmlParserValue = engine->newQObject(HtmlParser);
        engine->globalObject().setProperty("HtmlParser", HtmlParserValue);

        QScriptValue BrowserValue = engine->newQObject(Browser);
        engine->globalObject().setProperty("Browser", BrowserValue);

        QScriptValue ScriptWorkerValue = engine->newQObject(this);
        engine->globalObject().setProperty("ScriptWorker", ScriptWorkerValue);

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

        QScriptValue LoggerValue = engine->newQObject(Logger);
        engine->globalObject().setProperty("Logger", LoggerValue);

        QScriptValue FactorySolverValue = engine->newQObject(FactorySolver);
        engine->globalObject().setProperty("FactorySolver", FactorySolverValue);

        QScriptValue EngineResValue = engine->newQObject(EngineRes);
        engine->globalObject().setProperty("EngineRes", EngineResValue);

        QScriptValue ResourceHandlersValue = engine->newQObject(ResourceHandlers);
        engine->globalObject().setProperty("ResourceHandlers", ResourceHandlersValue);

        QScriptValue PropertiesValue = engine->newQObject(Properties);
        engine->globalObject().setProperty("Properties", PropertiesValue);

        QHash<QString,QObject*>::iterator i = Modules.begin();
        while (i != Modules.end())
        {
            QScriptValue Value = engine->newQObject(i.value());
            engine->globalObject().setProperty(i.key(), Value);
            i++;
        }

        engine->globalObject().setProperty("ThreadNumber", ThreadNumber);

        Browser->SetScriptResources(ScriptResources);

        foreach(QString script, ScriptResources->GetEngineScripts())
            engine->evaluate(script);

        foreach(QString script, ScriptResources->GetModuleScripts())
        {
            QString Script = Preprocessor->Preprocess(script,0);
            engine->evaluate(Script);
        }

        RunSubScript();

    }

    void ScriptWorker::AttachNetworkAccessManager()
    {
        Browser->GetNetworkAccessManager()->SetWorker(this);
        QScriptValue NetworkAccessManagerValue = engine->newQObject(Browser->GetNetworkAccessManager());
        engine->globalObject().setProperty("NetworkAccessManager", NetworkAccessManagerValue);
    }


    void ScriptWorker::RunSubScript()
    {
        Browser->SetWorker(this);

        QScriptValue BrowserValue = engine->newQObject(Browser);
        engine->globalObject().setProperty("Browser", BrowserValue);


        ResultStatus = IWorker::SuccessStatus;

        if(HttpClient)
        {
            HttpClient->Disconnect();
        }
        if(Pop3Client)
        {
            Pop3Client->disconnect();
            Pop3Client->Reset();

        }

        if(engine->isEvaluating())
        {
            OnFinishScript += ";" + Script;
            return;
        }
        while(true)
        {
            if(NeedToSetAsyncResult)
            {
                engine->evaluate("_set_result(ScriptWorker.GetAsyncResult())");
                NeedToSetAsyncResult = false;
            }
            engine->evaluate(Script);



            if(ResultStatus == IWorker::SuspendStatus)
            {
                break;
            }
            if(engine->hasUncaughtException())
            {
                ResultMessage = engine->uncaughtException().toString();
                if(DoTrace)
                     ResultMessage += QString(" Line number:") + QString::number(engine->uncaughtExceptionLineNumber()) + " During execution of script " + Script;
                ResultStatus = IWorker::FailStatus;
                ScriptFinished();
                break;
            }else
            {


                if(!IsAborted && !OnFinishScript.isEmpty())
                {
                    Script = OnFinishScript;
                    OnFinishScript.clear();
                }else if(!IsAborted && Waiter && !Waiter->IsActive())
                {

                    if(IsFailExceedRunning)
                    {
                        ResultMessage = "Fail number exceed";
                        ResultStatus = IWorker::FailStatus;
                        Abort();
                        break;
                    }
                    if(IsSuccessExceedRunning)
                    {
                        ResultMessage = "Success number exceed";
                        ResultStatus = IWorker::SuccessStatus;
                        Abort();
                        break;
                    }
                    Script = "_next()";
                    continue;

                }else
                {


                    break;
                }
            }
        }
    }

    void ScriptWorker::Decrypt(const QString& Data)
    {
        Script = Preprocessor->Decrypt(Data);
        RunSubScript();
    }


    void ScriptWorker::AbortSubscript()
    {
        engine->abortEvaluation();
    }




    void ScriptWorker::Abort()
    {

        ScriptFinished();
        if(engine)
            engine->abortEvaluation();
        if(Waiter)
            Waiter->Abort();

    }




    void ScriptWorker::Fail(const QString& message)
    {
        if(!FailFunction.isEmpty() && MaxFail <= 0 && !FailExceedFunction.isEmpty())
        {
            SetAsyncResult(QScriptValue(message));
            IsFailExceedRunning = true;
            SetScript(FailExceedFunction);
            FailExceedFunction.clear();
            AbortSubscript();
            RunSubScript();
            return;
        }
        if(!FailFunction.isEmpty() && MaxFail > 0)
        {
            MaxFail--;
            emit FailedButRescued(message);
            SetAsyncResult(QScriptValue(message));
            SetScript(FailFunction);
            FailFunction.clear();
            AbortSubscript();
            RunSubScript();
        }else
        {
            if(FailFunction.isEmpty())
            {
                ResultMessage = message;
            }else
            {
                ResultMessage = "Fail number exceed";
            }
            ResultStatus = IWorker::FailStatus;
            Abort();
        }

    }

    void ScriptWorker::SetMaxFail(int MaxFail)
    {
        this->MaxFail = MaxFail;
    }

    void ScriptWorker::Die(const QString& message)
    {
        ResultMessage = message;
        ResultStatus = IWorker::DieStatus;
        Abort();
    }
    void ScriptWorker::Success(const QString& message)
    {
        if(!SuccessFunction.isEmpty() && MaxSuccess <= 0 && !SuccessExceedFunction.isEmpty())
        {
            SetAsyncResult(QScriptValue(message));
            IsSuccessExceedRunning = true;
            SetScript(SuccessExceedFunction);
            SuccessExceedFunction.clear();
            AbortSubscript();
            RunSubScript();
            return;
        }
        if(!SuccessFunction.isEmpty() && MaxSuccess > 0)
        {
            MaxSuccess--;
            emit SuccessedButRescued(message);
            //ResourceHandlers->Success();
            SetAsyncResult(QScriptValue(message));
            SetScript(SuccessFunction);
            SuccessFunction.clear();
            AbortSubscript();
            RunSubScript();
        }else
        {
            if(SuccessFunction.isEmpty())
            {
                ResultMessage = message;
            }else
            {
                ResultMessage = "Success number exceed";
            }
            ResultStatus = IWorker::SuccessStatus;
            Abort();

        }
    }
    void ScriptWorker::SetMaxSuccess(int MaxSuccess)
    {
        this->MaxSuccess = MaxSuccess;
    }



    void ScriptWorker::ScriptFinished()
    {
        if(IsAborted)
        {
            return;
        }
        if(IsRecord && ProcessComunicator)
            ProcessComunicator->Send("<ScriptFinished/>");
        engine->evaluate(AbortFunction);
        AbortFunction.clear();
        IsAborted = true;
        switch(ResultStatus)
        {
            case IWorker::FailStatus: ResourceHandlers->Fail(); break;
            case IWorker::DieStatus: ResourceHandlers->Die(); break;
            case IWorker::SuccessStatus: ResourceHandlers->Success(); break;
        }
        if(ProcessComunicator)
            disconnect(ProcessComunicator,SIGNAL(Received(QString)),0,0);

        emit Finished();
    }

    void ScriptWorker::SetFailMessage(const QString& message)
    {
        this->FailMessage = message;
    }

    void ScriptWorker::FailProcessFinished()
    {
        Fail("Failed because process is stopped");
    }

    void ScriptWorker::FailBecauseOfTimeout()
    {
        if(HttpClient)
            HttpClient->Stop();

        Fail(FailMessage);
    }

    void ScriptWorker::Sleep(int msec, const QString& callback)
    {
        Script = callback;
        Waiter->Sleep(msec,this,SLOT(RunSubScript()));
    }

    void ScriptWorker::Suspend(int msec, const QString& callback)
    {
        Script = callback;
        IWorker::WorkerStatus State = this->ResultStatus;
        ResultStatus = IWorker::SuspendStatus;
        if(!ScriptSuspender->Suspend(msec, this))
        {
            ResultStatus = State;
            Waiter->Sleep(msec,this,SLOT(RunSubScript()));
        }
    }


    void ScriptWorker::ReloadResource(const QString& name)
    {
        EngineRes->Reload(name);
    }


    QScriptValue ScriptWorker::GetSolver(const QString& name)
    {
        ISolver *isolver = FactorySolver->GetSolver(name);
        if(!isolver)
        {
            return engine->undefinedValue();
        }
        return engine->newQObject(isolver);
    }




    static QScriptValue prepare(QScriptEngine *engine, IWebElement* web);

    static QScriptValue prototype_css(QScriptContext *ctx, QScriptEngine *engine)
    {
        IWebElement *web = qobject_cast<IWebElement*>(ctx->thisObject().toQObject());
        if(!web)
        {
            return engine->undefinedValue();
        }
        if(ctx->argumentCount()!=1)
        {
            return engine->undefinedValue();
        }
        return prepare(engine,web->css(ctx->argument(0).toString()));
    }

    static QScriptValue prototype_frame(QScriptContext *ctx, QScriptEngine *engine)
    {
        IWebElement *web = qobject_cast<IWebElement*>(ctx->thisObject().toQObject());
        if(!web)
        {
            return engine->undefinedValue();
        }
        if(ctx->argumentCount()!=1)
        {
            return engine->undefinedValue();
        }
        return prepare(engine,web->frame(ctx->argument(0).toString()));
    }

    static QScriptValue prototype_position(QScriptContext *ctx, QScriptEngine *engine)
    {
        IWebElement *web = qobject_cast<IWebElement*>(ctx->thisObject().toQObject());
        if(!web)
        {
            return engine->undefinedValue();
        }
        if(ctx->argumentCount()!=2)
        {
            return engine->undefinedValue();
        }
        return prepare(engine,web->position(ctx->argument(0).toInt32(),ctx->argument(1).toInt32()));
    }

    static QScriptValue prototype_at(QScriptContext *ctx, QScriptEngine *engine)
    {
        IWebElement *web = qobject_cast<IWebElement*>(ctx->thisObject().toQObject());
        if(!web)
        {
            return engine->undefinedValue();
        }
        if(ctx->argumentCount()!=1)
        {
            return engine->undefinedValue();
        }
        return prepare(engine,web->at(ctx->argument(0).toInt32()));
    }

    static QScriptValue prototype_match(QScriptContext *ctx, QScriptEngine *engine)
    {
        IWebElement *web = qobject_cast<IWebElement*>(ctx->thisObject().toQObject());
        if(!web)
        {
            return engine->undefinedValue();
        }
        if(ctx->argumentCount()!=1)
        {
            return engine->undefinedValue();
        }
        return prepare(engine,web->match(ctx->argument(0).toString()));
    }

    static QScriptValue prototype_all(QScriptContext *ctx, QScriptEngine *engine)
    {
        IWebElement *web = qobject_cast<IWebElement*>(ctx->thisObject().toQObject());
        if(!web)
        {
            return engine->undefinedValue();
        }
        if(ctx->argumentCount()!=1)
        {
            return engine->undefinedValue();
        }

        return prepare(engine,web->all(ctx->argument(0).toString()));
    }

    static QScriptValue prototype_match_all(QScriptContext *ctx, QScriptEngine *engine)
    {
        IWebElement *web = qobject_cast<IWebElement*>(ctx->thisObject().toQObject());
        if(!web)
        {
            return engine->undefinedValue();
        }
        if(ctx->argumentCount()!=1)
        {
            return engine->undefinedValue();
        }
        return prepare(engine,web->match_all(ctx->argument(0).toString()));
    }


    static QScriptValue prepare(QScriptEngine *engine, IWebElement* web)
    {
        QScriptValue res = engine->newQObject(web,QScriptEngine::ScriptOwnership);
        res.setProperty("css", engine->newFunction(prototype_css));
        res.setProperty("frame", engine->newFunction(prototype_frame));
        res.setProperty("position", engine->newFunction(prototype_position));
        res.setProperty("all", engine->newFunction(prototype_all));
        res.setProperty("match", engine->newFunction(prototype_match));
        res.setProperty("match_all", engine->newFunction(prototype_match_all));
        res.setProperty("at", engine->newFunction(prototype_at));

        return res;
    }



    QScriptValue ScriptWorker::PrepareWebElement(IWebElement* web)
    {
        web->SetWorker(this);
        return prepare(engine,web);
    }

    QScriptValue ScriptWorker::GetRootElement()
    {
        return PrepareWebElement(Browser->GetRootElement());
    }

    void ScriptWorker::GetHandler(const QString& name, bool die_on_fail, const QString& callback)
    {
        LastHandlerName = name;
        DieOnFailHandler = die_on_fail;
        Script = callback;
        Waiter->WaitForHandler(EngineRes,name,RefuseData[name],this,SLOT(HandlerWaitFinishedSuccess()),this,SLOT(HandlerWaitFinishedFailed()));

    }

    void ScriptWorker::Refuse(const QString & name,const QString & value)
    {
        RefuseData[name].insert(value);
    }

    QScriptValue ScriptWorker::GetAllData(const QString& name)
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

    QScriptValue ScriptWorker::GetRandomSubarrayData(const QString& name, int size)
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

    QScriptValue ScriptWorker::GetAtIndex(const QString& name, int index)
    {
        return EngineRes->GetAtIndex(name,index);
    }

    void ScriptWorker::SetAtIndex(const QString& name, int index, const QString& val)
    {
        EngineRes->SetAtIndex(name,index,val);
    }

    QScriptValue ScriptWorker::GetTotalLength(const QString& name)
    {
        return QScriptValue(EngineRes->GetTotalLength(name));
    }


    void ScriptWorker::HandlerWaitFinishedSuccess()
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

    void ScriptWorker::HandlerWaitFinishedFailed()
    {
        if(Waiter->IsResourceRefused())
        {
            engine->evaluate("IS_REFUSED=true;");
            RunSubScript();
            return;
        }

        if(DieOnFailHandler)
        {

            Die("failed to get resource " + LastHandlerName);
        }else
        {
            engine->evaluate("_set_result(null)");
            RunSubScript();
        }
    }


    IWorker::WorkerStatus ScriptWorker::GetResultStatus()
    {
        return ResultStatus;
    }

    QString ScriptWorker::GetResultMessage()
    {
        QString status;
        if(ResultStatus == IWorker::SuspendStatus)
        {
            return PrepareMessage("Thread suspended");
        }

        switch(ResultStatus)
        {
            case IWorker::FailStatus: status = "Thread failed"; break;
            case IWorker::DieStatus: status = "Thread died"; break;
            case IWorker::SuccessStatus: status = "Thread succeeded"; break;
        }
        return PrepareMessage(status + " with message \"" + ResultMessage + "\"");
    }

    QString ScriptWorker::GetResultMessageRaw()
    {
        return ResultMessage;
    }

    QString ScriptWorker::PrepareMessage(const QString &message)
    {
        QString status;
        QString datestring = QTime::currentTime().toString("hh:mm:ss");
        status  = "[" + datestring + "] Thread #" + QString::number(ThreadNumber) + " : " + message;
        return status;
    }



    void ScriptWorker::Solve(const QString& method, const QString& base64,const QString& callback)
    {
        ISolver* solver = GetSolverFactory()->GetSolver(method);
        if(!solver)
        {
            Fail("CAPTCHA_FAIL : Failed to get solver");
            return;
        }
        Script = callback;

        QString id = solver->Solve(base64);
        GetWaiter()->WaitForSolver(solver,id,this,SLOT(SolverSuccess()),this,SLOT(SolverFailed()));
    }

    void ScriptWorker::SolverSuccess()
    {
        QString res = GetWaiter()->GetLastSolverResult();
        if(res.startsWith("CAPTCHA_FAIL"))
        {
            Fail(res);
            return;
        }
        SetAsyncResult(QScriptValue(res));


        RunSubScript();
    }

    void ScriptWorker::SolverFailed()
    {
        Fail("Captcha wait timeout");
    }

    /* Pop3CLient */
    void ScriptWorker::NewPop3Client()
    {
        if(Pop3Client)
            Pop3Client->deleteLater();
        Pop3Client = Pop3ClientFactory->GetPop3Client();
        Pop3Client->setParent(this);


        QScriptValue Pop3ClientValue = engine->newQObject(Pop3Client);
        engine->globalObject().setProperty("Pop3Client", Pop3ClientValue);
    }

    void ScriptWorker::Pop3ClientLoadMessageNumber(const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(QString("Failed to get mail number with Pop3CLient"));
        Waiter->WaitForSignal(Pop3Client,SIGNAL(Result()),this,SLOT(Pop3ClientResult()),this, SLOT(FailBecauseOfTimeout()));
        Pop3Client->PullNumberOfMessages();
    }

    void ScriptWorker::Pop3ClientLoadMessage(int index, const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(QString("Failed to get message with Pop3CLient"));
        Waiter->WaitForSignal(Pop3Client,SIGNAL(Result()),this,SLOT(Pop3ClientResult()),this, SLOT(FailBecauseOfTimeout()));
        Pop3Client->PullMessage(index);
    }


    void ScriptWorker::Pop3ClientResult()
    {
        Pop3Client->disconnect();
        Pop3Client->Reset();
        if(Pop3Client->GetStatus())
        {
            RunSubScript();
        }else
        {
            SetFailMessage(Pop3Client->GetLastError());
            FailBecauseOfTimeout();
        }

    }

    /* ImapClient */
    void ScriptWorker::NewImapClient()
    {
        if(ImapClient)
            ImapClient->deleteLater();
        ImapClient = ImapClientFactory->GetImapClient();
        ImapClient->setParent(this);


        QScriptValue ImapClientValue = engine->newQObject(ImapClient);
        engine->globalObject().setProperty("ImapClient", ImapClientValue);
    }

    void ScriptWorker::ImapClientPullNumberOfMessages(const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(QString("Failed to get mail number with ImapCLient"));
        Waiter->WaitForSignal(ImapClient,SIGNAL(Result()),this,SLOT(ImapClientResult()),this, SLOT(FailBecauseOfTimeout()));
        ImapClient->PullNumberOfMessages();
    }

    void ScriptWorker::ImapClientSearchMessages(const QString& Sender,const QString& Subject,const QString& Body,const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(QString("Failed to search mail with ImapCLient"));
        Waiter->WaitForSignal(ImapClient,SIGNAL(Result()),this,SLOT(ImapClientResult()),this, SLOT(FailBecauseOfTimeout()));
        ImapClient->SearchMessages(Sender,Subject,Body);
    }

    void ScriptWorker::ImapClientCustomSearchMessages(const QString& Query,const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(QString("Failed to custom search mail with ImapCLient"));
        Waiter->WaitForSignal(ImapClient,SIGNAL(Result()),this,SLOT(ImapClientResult()),this, SLOT(FailBecauseOfTimeout()));
        ImapClient->SearchCustomMessages(Query);
    }

    void ScriptWorker::ImapClientPullMessage(const QString& Uid,const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(QString("Failed to fetch mail with ImapCLient"));
        Waiter->WaitForSignal(ImapClient,SIGNAL(Result()),this,SLOT(ImapClientResult()),this, SLOT(FailBecauseOfTimeout()));
        ImapClient->PullMessage(Uid);
    }

    void ScriptWorker::ImapClientCustomQuery(const QString& Url,const QString& Command,const QString& Filter,const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(QString("Failed to execute custom query with ImapCLient"));
        Waiter->WaitForSignal(ImapClient,SIGNAL(Result()),this,SLOT(ImapClientResult()),this, SLOT(FailBecauseOfTimeout()));
        ImapClient->CustomQuery(Url,Command, Filter);
    }

    void ScriptWorker::ImapClientResult()
    {
        ImapClient->disconnect();
        if(ImapClient->GetStatus())
        {
            RunSubScript();
        }else
        {
            SetFailMessage(ImapClient->GetLastError());
            FailBecauseOfTimeout();
        }
    }

    /* HttpClient */
    void ScriptWorker::NewHttpClient()
    {
        if(HttpClient)
            HttpClient->deleteLater();
        HttpClient = HttpClientFactory->GetHttpClient();
        HttpClient->setParent(this);

        QScriptValue HttpClientValue = engine->newQObject(HttpClient);
        engine->globalObject().setProperty("HttpClient", HttpClientValue);
    }

    void ScriptWorker::FollowRedirectInternal(bool IsGet)
    {

        QString Location = HttpClient->GetHeader("Location");
        //Relative location
        while(Location.startsWith("."))
            Location.remove(0,1);

        if(Location.startsWith("/"))
        {
            QUrl url = QUrl(HttpClient->GetLastUrl());
            url.setPath(Location);

            Location = url.toString();
        }
        HttpClient->Disconnect();
        if(!Location.isEmpty())
        {
            SetFailMessage(QString("Failed to get page ") + Location + " with HttpClient");
            if(IsGet)
            {
                Waiter->WaitInfinity(HttpClient,SIGNAL(Finished()),this,SLOT(FollowRedirect()));
                HttpClient->Get(Location);
            }else
            {
                Waiter->WaitInfinity(HttpClient,SIGNAL(Finished()),this,SLOT(FollowRedirectDownload()));
                HttpClient->Download(Location, CurrentFileDownload);
            }
        }else
        {
            RunSubScript();
        }
    }


    void ScriptWorker::FollowRedirect()
    {
        FollowRedirectInternal(true);
    }

    void ScriptWorker::FollowRedirectDownload()
    {
        FollowRedirectInternal(false);
    }




    void ScriptWorker::HttpClientPostRedirect(const QString& url, const QStringList & params, const QStringList & params_glob, const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(QString("Failed to post page ") + url + " with HttpClient");
        Waiter->WaitInfinity(HttpClient,SIGNAL(Finished()),this,SLOT(FollowRedirect()));
        QHash<QString,QString> p;
        bool isname = true;
        QString name = "";
        foreach(QString str, params)
        {
            if(isname)
            {
                name = str;
            }else
            {
                p.insert(name,str);
            }
            isname = !isname;
        }

        QHash<QString,QString> p1;
        isname = true;
        name = "";
        foreach(QString str, params_glob)
        {
            if(isname)
            {
                name = str;
            }else
            {
                p1.insert(name,str);
            }
            isname = !isname;
        }
        PostOptions Options;
        if(p1.contains("content-type"))
        {
            Options.PrepareStrategy = p1["content-type"];
        }
        HttpClient->Post(url,p,Options);
    }

    void ScriptWorker::HttpClientPostNoRedirect(const QString& url, const QStringList & params, const QStringList & params_glob, const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(QString("Failed to post page ") + url + " with HttpClient");
        Waiter->WaitInfinity(HttpClient,SIGNAL(Finished()),this,SLOT(RunSubScript()));
        QHash<QString,QString> p;
        bool isname = true;
        QString name = "";
        foreach(QString str, params)
        {
            if(isname)
            {
                name = str;
            }else
            {
                p.insert(name,str);
            }
            isname = !isname;
        }

        QHash<QString,QString> p1;
        isname = true;
        name = "";
        foreach(QString str, params_glob)
        {
            if(isname)
            {
                name = str;
            }else
            {
                p1.insert(name,str);
            }
            isname = !isname;
        }
        PostOptions Options;
        if(p1.contains("content-type"))
        {
            Options.PrepareStrategy = p1["content-type"];
        }
        HttpClient->Post(url,p,Options);
    }

    void ScriptWorker::HttpClientGetNoRedirect(const QString& url, const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(QString("Failed to get page ") + url + " with HttpClient");
        Waiter->WaitInfinity(HttpClient,SIGNAL(Finished()),this,SLOT(RunSubScript()));
        HttpClient->Get(url);
    }

    void ScriptWorker::HttpClientGetRedirect(const QString& url, const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(QString("Failed to get page ") + url + " with HttpClient");
        Waiter->WaitInfinity(HttpClient,SIGNAL(Finished()),this,SLOT(FollowRedirect()));
        HttpClient->Get(url);
    }

    void ScriptWorker::HttpClientDownload(const QString& url, const QString& file, const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(QString("Failed to download page ") + url + " with HttpClient");
        Waiter->WaitInfinity(HttpClient,SIGNAL(Finished()),this,SLOT(FollowRedirectDownload()));
        CurrentFileDownload = file;
        HttpClient->Download(url, file);
    }

    void ScriptWorker::DebugTerminate(int how)
    {
        Terminate().DoTerminate(how);
    }

    void ScriptWorker::DatabaseAddRecord(const QString& GroupId,const QStringList& Record, int TableId)
    {
        DatabaseItem Item;
        Item.IsNull = false;

        QList<DatabaseColumn> Columns = DatabaseConnector->GetColumns(TableId);

        for(int i = 0;i<Record.length() - 1;i+=2)
        {
            int ColumnId = Record.at(i).toInt();
            QString StringParam = Record.at(i+1);
            QVariant VariantParam;
            foreach(DatabaseColumn Column, Columns)
            {
                if(ColumnId == Column.Id)
                {
                    switch(Column.Type)
                    {
                        case DatabaseColumn::Int: VariantParam = QVariant(StringParam.toInt());break;
                        case DatabaseColumn::String: VariantParam = QVariant(StringParam);break;
                        case DatabaseColumn::Bool: VariantParam = QVariant(StringParam == "true");break;
                        case DatabaseColumn::Date: VariantParam = QVariant(QDateTime::fromString(StringParam,"yyyy-MM-ddTHH:mm:ss"));break;
                    }

                    break;
                }
            }
            Item.Data[ColumnId] = VariantParam;
        }

        DatabaseGroups Groups;
        Groups.IsNull = false;
        Groups.GroupIdList.append(GroupId);
        DatabaseConnector->Insert(Groups,Item,TableId);
    }

}
