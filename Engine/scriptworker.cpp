#include "scriptworker.h"
#include "debugterminate.h"
#include "csvhelperwrapper.h"
#include <limits>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{


    ScriptWorker::ScriptWorker(QObject *parent) :
        IWorker(parent), Browser(0), Logger(0), Results1(0),Results2(0), Results3(0),Results4(0),Results5(0),Results6(0),Results7(0),Results8(0),Results9(0), Waiter(0),engine(0),ThreadNumber(0),IsAborted(false),ProcessComunicator(0), HttpClient1(0), HttpClient2(0), Pop3Client(0), ImapClient(0), DoTrace(false), MaxFail(999999), MaxSuccess(100), IsFailExceedRunning(false), IsSuccessExceedRunning(false), FunctionData(0), CurrentWebElement(0), HttpClientIndex(1),DieInstant(false), DontCreateMore(false), SuccessNumber(0), FailNumber(0), HttpClientNextTimeout(-1), SolverNotFailNextTime(false), SubstageId(0), SubstageParentId(0), CurrentAction(-1)
    {
    }


    void ScriptWorker::SetSuccessNumber(qint64* SuccessNumber)
    {
        this->SuccessNumber = SuccessNumber;
    }
    qint64 ScriptWorker::GetSuccessNumber()
    {
        if(!SuccessNumber)
            return -1;
        return *SuccessNumber;
    }

    void ScriptWorker::SetFailNumber(qint64* FailNumber)
    {
        this->FailNumber = FailNumber;
    }
    qint64 ScriptWorker::GetFailNumber()
    {
        if(!FailNumber)
            return -1;
        return *FailNumber;
    }

    void ScriptWorker::SetProjectPath(const QString& Path)
    {
        this->ProjectPath = Path;
    }
    QString ScriptWorker::GetProjectPath()
    {
        return ProjectPath;
    }


    bool ScriptWorker::IsDieInstant()
    {
        return DieInstant;
    }

    bool ScriptWorker::IsDontCreateMore()
    {
        return DontCreateMore;
    }

    IHttpClient* ScriptWorker::GetActualHttpClient()
    {
        if(HttpClientIndex == 1)
            return HttpClient1;
        else
            return HttpClient2;
    }

    void ScriptWorker::SwitchHttpClient(int index)
    {
        HttpClientIndex = index;
    }

    ScriptWorker::~ScriptWorker()
    {

        for(FunctionRunData* func:FunctionDataList)
            func->Stop();
        FunctionDataList.clear();
    }

    void ScriptWorker::SetModuleManager(IModuleManager *ModuleManager)
    {
        this->ModuleManager = ModuleManager;
    }

    IModuleManager* ScriptWorker::GetModuleManager()
    {
        return ModuleManager;
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

    void ScriptWorker::SetStringBuilder(IStringBuilder *StringBuilder)
    {
        this->StringBuilder = StringBuilder;
    }

    IStringBuilder * ScriptWorker::GetStringBuilder()
    {
        return StringBuilder;
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


    void ScriptWorker::SetThreadNumber(qint64 ThreadNumber)
    {
        this->ThreadNumber = ThreadNumber;
    }
    qint64 ScriptWorker::GetThreadNumber()
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

    void ScriptWorker::SetAdditionEngineScripts(QList<QString>* AdditionalScripts)
    {
        this->AdditionalScripts = AdditionalScripts;
    }
    QList<QString>* ScriptWorker::GetAdditionEngineScripts()
    {
        return AdditionalScripts;
    }

    void ScriptWorker::InterruptAction()
    {
        if(IsRecord)
        {
            if(Waiter)
                Waiter->Stop();

            Fail(tr("Aborted By User"),false);
        }
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

        engine->globalObject().setProperty("_K", qApp->property("lang").toString());

        QHash<QString,QObject*>::iterator i = Modules.begin();
        while (i != Modules.end())
        {
            QScriptValue Value = engine->newQObject(i.value());
            engine->globalObject().setProperty(i.key(), Value);
            i++;
        }
        Browser->SetScriptResources(ScriptResources);

        foreach(QString script, ScriptResources->GetEngineScripts())
            engine->evaluate(script);


        int ScriptLength = AdditionalScripts->size();
        for(int i = 0;i<ScriptLength;i++)
        {
            QString Script = AdditionalScripts->at(i);
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

        if(HttpClient1)
        {
            HttpClient1->Disconnect();
        }
        if(HttpClient2)
        {
            HttpClient2->Disconnect();
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
                QString Message = engine->uncaughtException().toString();
                if(DoTrace)
                     Message += tr(" Line number:") + QString::number(engine->uncaughtExceptionLineNumber()) + tr(" During execution of script ") + Script;

                if(IsRecord)
                {
                    Logger->WriteFail(PrepareMessage(Message));
                    if(Browser)
                        Browser->StartSection(QString(),1,"");
                    break;
                }else
                {
                    ResultMessage = Message;
                    ResultStatus = IWorker::FailStatus;
                    ScriptFinished(true);
                    break;
                }
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
                        ResultMessage = tr("Fail number exceed");
                        ResultStatus = IWorker::FailStatus;
                        Abort(true);
                        break;
                    }
                    if(IsSuccessExceedRunning)
                    {
                        ResultMessage = tr("Success number exceed");
                        ResultStatus = IWorker::SuccessStatus;
                        Abort(true);
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




    void ScriptWorker::Abort(bool SignalResourceHandlers)
    {

        ScriptFinished(SignalResourceHandlers);
        if(engine)
            engine->abortEvaluation();
        if(Waiter)
            Waiter->Abort();

    }


    QString ScriptWorker::Preprocess(const QString& script)
    {
        return GetPreprocessor()->Preprocess(script, 0);
    }

    void ScriptWorker::Fail(const QString& message, bool dont_create_more)
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
            QString Message;
            if(FailFunction.isEmpty())
            {
                Message = message;
            }else
            {
                Message = tr("Fail number exceed");
            }

            if(IsRecord)
            {
                Logger->WriteFail(PrepareMessage(Message));
                SetScript("section_start(\"test\",1,function(){})");
                AbortSubscript();
                RunSubScript();
            }else
            {
                DontCreateMore = dont_create_more;
                ResultMessage = Message;
                ResultStatus = IWorker::FailStatus;
                Abort(true);
            }
        }

    }

    void ScriptWorker::SetMaxFail(int MaxFail)
    {
        this->MaxFail = MaxFail;
    }

    void ScriptWorker::Die(const QString& message, bool instant)
    {
        if(IsRecord)
        {
            Logger->WriteFail(PrepareMessage(message));
            SetScript("section_start(\"test\",1,function(){})");
            AbortSubscript();
            RunSubScript();
        }else
        {
            DieInstant = instant;
            ResultMessage = message;
            ResultStatus = IWorker::DieStatus;
            Abort(true);
        }
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
                ResultMessage = tr("Success number exceed");
            }
            ResultStatus = IWorker::SuccessStatus;
            Abort(true);

        }
    }
    void ScriptWorker::SetMaxSuccess(int MaxSuccess)
    {
        this->MaxSuccess = MaxSuccess;
    }



    void ScriptWorker::ScriptFinished(bool SignalResourceHandlers)
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
        if(SignalResourceHandlers)
        {
            switch(ResultStatus)
            {
                case IWorker::FailStatus: ResourceHandlers->Fail(); break;
                case IWorker::DieStatus: ResourceHandlers->Die(); break;
                case IWorker::SuccessStatus: ResourceHandlers->Success(); break;
            }
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
        Fail(tr("Failed because process is stopped"), false);
    }

    void ScriptWorker::FailBecauseOfTimeout()
    {
        if(HttpClient1)
            HttpClient1->Stop();
        if(HttpClient2)
            HttpClient2->Stop();

        Fail(FailMessage, false);
    }

    void ScriptWorker::Sleep(int msec, const QString& callback)
    {
        Script = callback;
        Waiter->Sleep(msec,this,SLOT(RunSubScript()));
    }

    QString ScriptWorker::Spintax(const QString& Text)
    {
        return StringBuilder->Expand(Text);
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

    static QScriptValue prototype_nowait(QScriptContext *ctx, QScriptEngine *engine)
    {
        IWebElement *web = qobject_cast<IWebElement*>(ctx->thisObject().toQObject());
        if(!web)
        {
            return engine->undefinedValue();
        }
        if(ctx->argumentCount()!=0)
        {
            return engine->undefinedValue();
        }
        return prepare(engine,web->nowait());
    }

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

    static QScriptValue prototype_xpath(QScriptContext *ctx, QScriptEngine *engine)
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
        return prepare(engine,web->xpath(ctx->argument(0).toString()));
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

    static QScriptValue prototype_frame_css(QScriptContext *ctx, QScriptEngine *engine)
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
        return prepare(engine,web->frame_css(ctx->argument(0).toString()));
    }

    static QScriptValue prototype_frame_element(QScriptContext *ctx, QScriptEngine *engine)
    {
        IWebElement *web = qobject_cast<IWebElement*>(ctx->thisObject().toQObject());
        if(!web)
        {
            return engine->undefinedValue();
        }
        if(ctx->argumentCount()!=0)
        {
            return engine->undefinedValue();
        }
        return prepare(engine,web->frame_element());
    }

    static QScriptValue prototype_frame_match(QScriptContext *ctx, QScriptEngine *engine)
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
        return prepare(engine,web->frame_match(ctx->argument(0).toString()));
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

    static QScriptValue prototype_xpath_all(QScriptContext *ctx, QScriptEngine *engine)
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

        return prepare(engine,web->xpath_all(ctx->argument(0).toString()));
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
        ScriptWorker* Worker = qobject_cast<ScriptWorker*>(engine->parent());
        web->setParent(Worker);
        if(Worker->CurrentWebElement)
        {
            Worker->CurrentWebElement->deleteLater();
            Worker->CurrentWebElement = 0;
        }

        Worker->CurrentWebElement = web;

        QScriptValue res = engine->newQObject(web);
        res.setProperty("css", engine->newFunction(prototype_css));
        res.setProperty("nowait", engine->newFunction(prototype_nowait));
        res.setProperty("xpath", engine->newFunction(prototype_xpath));
        res.setProperty("frame", engine->newFunction(prototype_frame));
        res.setProperty("frame_css", engine->newFunction(prototype_frame_css));
        res.setProperty("frame_element", engine->newFunction(prototype_frame_element));
        res.setProperty("frame_match", engine->newFunction(prototype_frame_match));
        res.setProperty("position", engine->newFunction(prototype_position));
        res.setProperty("all", engine->newFunction(prototype_all));
        res.setProperty("xpath_all", engine->newFunction(prototype_xpath_all));
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

            Die(tr("All data have been processed for ") + LastHandlerName, false);
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
            return PrepareMessage(tr("Thread suspended"));
        }

        bool ShowActionId = false;

        switch(ResultStatus)
        {
            case IWorker::FailStatus: ShowActionId = true; status = tr("Thread ended"); break;
            case IWorker::DieStatus: status = tr("Thread ended"); break;
            case IWorker::SuccessStatus: status = tr("Thread succeeded"); break;
        }
        QString text = status + tr(" with message \"") + ResultMessage + "\"";
        if(ShowActionId)
        {
            text = PrepareMessage(text);
        }else
        {
            text = PrepareMessageNoId(text);
        }
        return text;
    }

    QString ScriptWorker::GetResultMessageRawWithId()
    {
        QString result;
        if(CurrentAction >= 0)
        {
            result += QString("[") + QString::number(CurrentAction) + QString("] ");
        }
        result += ResultMessage;
        return result;
    }

    QString ScriptWorker::GetResultMessageRaw()
    {
        return ResultMessage;
    }

    void ScriptWorker::SetCurrentAction(qint64 CurrentAction)
    {
        this->CurrentAction = CurrentAction;
    }

    QString ScriptWorker::PrepareMessage(const QString &message)
    {
        QString status;
        QString datestring = QTime::currentTime().toString("hh:mm:ss");
        if(CurrentAction >= 0)
        {
            status += QString("[") + QString::number(CurrentAction) + QString("] ");
        }
        status  += "[" + datestring + "]";

        status += QString(" ") + tr("Thread #") + QString::number(ThreadNumber) + " : " + message;
        return status;
    }

    QString ScriptWorker::PrepareMessageNoId(const QString &message)
    {
        QString status;
        QString datestring = QTime::currentTime().toString("hh:mm:ss");

        status  += "[" + datestring + "]";

        status += QString(" ") + tr("Thread #") + QString::number(ThreadNumber) + " : " + message;
        return status;
    }



    void ScriptWorker::SolveInternal(const QString& method, const QString& base64, const QStringList & params,const QString& callback)
    {
        engine->globalObject().setProperty("LAST_CAPTCHA_ID", "");
        ISolver* solver = GetSolverFactory()->GetSolver(method);
        if(!solver)
        {
            Fail(tr("CAPTCHA_FAIL") + " : " + tr("Failed to get solver"), false);
            return;
        }
        Script = callback;

        QString id = solver->Solve(base64,params);
        GetWaiter()->WaitForSolver(solver,id,this,SLOT(SolverSuccess()),this,SLOT(SolverFailed()));
    }

    void ScriptWorker::Solve(const QString& method, const QString& base64, const QStringList & params,const QString& callback)
    {
        SolverNotFailNextTime = false;
        SolveInternal(method, base64,params, callback);
    }
    void ScriptWorker::SolveNoFail(const QString& method, const QString& base64, const QStringList & params,const QString& callback)
    {
        SolverNotFailNextTime = true;
        SolveInternal(method, base64,params, callback);
    }

    void ScriptWorker::SolverSuccess()
    {
        QString res = GetWaiter()->GetLastSolverResult();
        QString id = GetWaiter()->GetLastSolverId();
        engine->globalObject().setProperty("LAST_CAPTCHA_ID", id);

        if(!SolverNotFailNextTime)
        {
            if(res.startsWith("CAPTCHA_FAIL"))
            {
                Fail(res.replace("CAPTCHA_FAIL",tr("CAPTCHA_FAIL")), false);
                return;
            }
        }
        SetAsyncResult(QScriptValue(res));


        RunSubScript();
    }

    void ScriptWorker::SolverFailed()
    {
        engine->globalObject().setProperty("LAST_CAPTCHA_ID", "");
        Fail(tr("Captcha wait timeout"), false);
    }

    QString ScriptWorker::ExecuteNativeModuleCodeSync(const QString& DllName, const QString& FunctionName, const QString& InputParam)
    {
        std::shared_ptr<FunctionRunData> FunctionDataInternal(ModuleManager->PrepareExecuteFunction(DllName,FunctionName,InputParam,GetThreadNumber()));
        if(FunctionDataInternal->IsError)
        {
            Fail(QString::fromStdString(FunctionDataInternal->ErrorString), false);
            return QString();
        }
        if(FunctionDataInternal->IsAync)
        {
            Fail(tr("Async function is called in sync mode"), false);
            return QString();
        }

        FunctionDataInternal->Execute();

        if(FunctionDataInternal->ExecuteError)
        {
            Fail(tr("Failed to run function ") + DllName + QString(".") + FunctionName, false);
            return QString();
        }

        return QString::fromUtf8(FunctionDataInternal->OutputJson.data(),FunctionDataInternal->OutputJson.size());

    }

    void ScriptWorker::ExecuteNativeModuleCodeAsync(const QString& DllName, const QString& FunctionName, const QString& InputParam, const QString& Callback)
    {
        FunctionData = ModuleManager->PrepareExecuteFunction(DllName,FunctionName,InputParam,GetThreadNumber());
        if(FunctionData->IsError)
        {
            Fail(QString::fromStdString(FunctionData->ErrorString), false);
            delete FunctionData;
            return;
        }
        if(!FunctionData->IsAync)
        {
            Fail(tr("Sync function is called in async mode"), false);
            delete FunctionData;
            return;
        }

        QThread* thread = new QThread;

        FunctionDataList.append(FunctionData);

        SetScript(Callback);
        SetFailMessage(tr("Failed to execute module function ") + DllName + QString(".") + FunctionName);
        if(FunctionData->WaitInfinite)
            Waiter->WaitInfinity(FunctionData,SIGNAL(ReadyResult()),this,SLOT(DllResult()));
        else
            Waiter->WaitForSignal(FunctionData,SIGNAL(ReadyResult()),this,SLOT(DllResult()),this, SLOT(FailBecauseOfTimeout()));

        FunctionData->moveToThread(thread);


        connect(thread, SIGNAL(started()), FunctionData, SLOT(Execute()));
        connect(FunctionData, SIGNAL(Finished()), this, SLOT(RemoveFromFunctionDataList()));
        connect(FunctionData, SIGNAL(Finished()), thread, SLOT(quit()));

        connect(thread, SIGNAL(finished()), FunctionData, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));


        thread->start();
    }

    void ScriptWorker::RemoveFromFunctionDataList()
    {
        if(qobject_cast<FunctionRunData *>(sender()) == FunctionData)
        {
            FunctionData = 0;
        }
        FunctionDataList.removeAll(qobject_cast<FunctionRunData *>(sender()));
    }

    void ScriptWorker::DllResult()
    {
        if(FunctionData == 0)
            return;
        if(FunctionData->ExecuteError)
        {
            Fail(tr("Failed to run function ") + FunctionData->DllName + QString(".") + FunctionData->FunctionName, false);
        }else
        {
            QString Result = QString::fromUtf8(FunctionData->OutputJson.data(),FunctionData->OutputJson.size());
            SetAsyncResult(QScriptValue(Result));
            RunSubScript();
        }
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
        SetFailMessage(tr("Failed to get mail number with Pop3CLient"));
        Waiter->WaitForSignal(Pop3Client,SIGNAL(Result()),this,SLOT(Pop3ClientResult()),this, SLOT(FailBecauseOfTimeout()));
        Pop3Client->PullNumberOfMessages();
    }

    void ScriptWorker::Pop3ClientLoadMessage(int index, const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(tr("Failed to get message with Pop3CLient"));
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

    /* Timeout */

    void ScriptWorker::SetGeneralWaitTimeout(int timeout)
    {
        if(Waiter)
            Waiter->SetGeneralWaitTimeout(timeout);
    }

    void ScriptWorker::SetGeneralWaitTimeoutNext(int timeout)
    {
        if(Waiter)
            Waiter->SetGeneralWaitTimeoutNext(timeout);
    }

    void ScriptWorker::SetSolverWaitTimeout(int timeout)
    {
        if(Waiter)
            Waiter->SetSolverWaitTimeout(timeout);
    }

    void ScriptWorker::SetSolverWaitTimeoutNext(int timeout)
    {
        if(Waiter)
            Waiter->SetSolverWaitTimeoutNext(timeout);
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
        SetFailMessage(tr("Failed to get mail number with ImapCLient"));
        Waiter->WaitForSignal(ImapClient,SIGNAL(Result()),this,SLOT(ImapClientResult()),this, SLOT(FailBecauseOfTimeout()));
        ImapClient->PullNumberOfMessages();
    }

    void ScriptWorker::ImapClientSearchMessages(const QString& Sender,const QString& Subject,const QString& Body,const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(tr("Failed to search mail with ImapCLient"));
        Waiter->WaitForSignal(ImapClient,SIGNAL(Result()),this,SLOT(ImapClientResult()),this, SLOT(FailBecauseOfTimeout()));
        ImapClient->SearchMessages(Sender,Subject,Body);
    }

    void ScriptWorker::ImapClientCustomSearchMessages(const QString& Query,const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(tr("Failed to custom search mail with ImapCLient"));
        Waiter->WaitForSignal(ImapClient,SIGNAL(Result()),this,SLOT(ImapClientResult()),this, SLOT(FailBecauseOfTimeout()));
        ImapClient->SearchCustomMessages(Query);
    }

    void ScriptWorker::ImapClientPullMessage(const QString& Uid,const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(tr("Failed to fetch mail with ImapCLient"));
        Waiter->WaitForSignal(ImapClient,SIGNAL(Result()),this,SLOT(ImapClientResult()),this, SLOT(FailBecauseOfTimeout()));
        ImapClient->PullMessage(Uid);
    }

    void ScriptWorker::ImapClientCustomQuery(const QString& Url,const QString& Command,const QString& Filter,const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(tr("Failed to execute custom query with ImapCLient"));
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
        if(GetActualHttpClient())
            GetActualHttpClient()->deleteLater();
        if(HttpClientIndex == 1)
            HttpClient1 = HttpClientFactory->GetHttpClient();
        else
            HttpClient2 = HttpClientFactory->GetHttpClient();
        GetActualHttpClient()->setParent(this);

        QScriptValue HttpClientValue = engine->newQObject(GetActualHttpClient());
        engine->globalObject().setProperty("HttpClient" + QString::number(HttpClientIndex), HttpClientValue);
    }

    void ScriptWorker::FollowRedirectInternal(bool IsGet)
    {

        QString Location = GetActualHttpClient()->GetHeader("Location");

        //Relative location
        while(Location.startsWith("."))
            Location.remove(0,1);

        if(Location.startsWith("//"))
        {
            QUrl url = QUrl(GetActualHttpClient()->GetLastUrl());

            QUrl urllocation = QUrl(Location);
            urllocation.setScheme(url.scheme());
            Location = urllocation.toString();

        }else if(Location.startsWith("/"))
        {
            QUrl url = QUrl(GetActualHttpClient()->GetLastUrl());
            QUrl urllocation = QUrl(Location);
            url.setPath(urllocation.path());
            url.setQuery(urllocation.query());
            url.setFragment(urllocation.fragment());

            Location = url.toString();
        }
        GetActualHttpClient()->Disconnect();
        if(!Location.isEmpty())
        {
            SetFailMessage(tr("Failed to get page ") + Location + tr(" with HttpClient"));
            if(IsGet)
            {
                if(HttpClientNextTimeout >= 0)
                    Waiter->SetGeneralWaitTimeoutNext(HttpClientNextTimeout);
                Waiter->WaitForSignal(GetActualHttpClient(),SIGNAL(Finished()),this,SLOT(FollowRedirect()),this,SLOT(FailBecauseOfTimeout()));
                GetActualHttpClient()->Get(Location);
            }else
            {
                if(HttpClientNextTimeout >= 0)
                    Waiter->SetGeneralWaitTimeoutNext(HttpClientNextTimeout);
                Waiter->WaitForSignal(GetActualHttpClient(),SIGNAL(Finished()),this,SLOT(FollowRedirectDownload()),this,SLOT(FailBecauseOfTimeout()));
                GetActualHttpClient()->Download(Location, CurrentFileDownload);
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
        SetFailMessage(tr("Failed to post page ") + url + tr(" with HttpClient"));
        HttpClientNextTimeout = Waiter->GetGeneralWaitTimeoutNext();
        Waiter->WaitForSignal(GetActualHttpClient(),SIGNAL(Finished()),this,SLOT(FollowRedirect()),this,SLOT(FailBecauseOfTimeout()));
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
        if(p1.contains("encoding"))
        {
            Options.ContentTypeEncoding = p1["encoding"];
        }
        if(p1.contains("method"))
        {
            Options.Method = p1["method"];
        }
        GetActualHttpClient()->Post(url,p,Options);
    }

    void ScriptWorker::HttpClientPostNoRedirect(const QString& url, const QStringList & params, const QStringList & params_glob, const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(tr("Failed to post page ") + url + tr(" with HttpClient"));
        Waiter->WaitForSignal(GetActualHttpClient(),SIGNAL(Finished()),this,SLOT(RunSubScript()),this,SLOT(FailBecauseOfTimeout()));
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
        if(p1.contains("encoding"))
        {
            Options.ContentTypeEncoding = p1["encoding"];
        }
        if(p1.contains("method"))
        {
            Options.Method = p1["method"];
        }
        GetActualHttpClient()->Post(url,p,Options);
    }

    void ScriptWorker::HttpClientGetNoRedirect(const QString& url, const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(tr("Failed to get page ") + url + tr(" with HttpClient"));
        Waiter->WaitForSignal(GetActualHttpClient(),SIGNAL(Finished()),this,SLOT(RunSubScript()),this,SLOT(FailBecauseOfTimeout()));
        GetActualHttpClient()->Get(url);
    }

    void ScriptWorker::HttpClientGetRedirect(const QString& url, const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(tr("Failed to get page ") + url + tr(" with HttpClient"));
        HttpClientNextTimeout = Waiter->GetGeneralWaitTimeoutNext();
        Waiter->WaitForSignal(GetActualHttpClient(),SIGNAL(Finished()),this,SLOT(FollowRedirect()),this,SLOT(FailBecauseOfTimeout()));
        GetActualHttpClient()->Get(url);
    }

    void ScriptWorker::HttpClientGetNoRedirect2(const QString& url, const QStringList & params_glob, const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(tr("Failed to get page ") + url + tr(" with HttpClient"));
        QHash<QString,QString> p1;
        bool isname = true;
        QString name = "";
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
        GetOptions Options;
        if(p1.contains("method"))
        {
            Options.Method = p1["method"];
        }

        Waiter->WaitForSignal(GetActualHttpClient(),SIGNAL(Finished()),this,SLOT(RunSubScript()),this,SLOT(FailBecauseOfTimeout()));
        GetActualHttpClient()->Get(url,Options);
    }

    void ScriptWorker::HttpClientGetRedirect2(const QString& url, const QStringList & params_glob, const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(tr("Failed to get page ") + url + tr(" with HttpClient"));
        QHash<QString,QString> p1;
        bool isname = true;
        QString name = "";
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
        GetOptions Options;
        if(p1.contains("method"))
        {
            Options.Method = p1["method"];
        }
        HttpClientNextTimeout = Waiter->GetGeneralWaitTimeoutNext();
        Waiter->WaitForSignal(GetActualHttpClient(),SIGNAL(Finished()),this,SLOT(FollowRedirect()),this,SLOT(FailBecauseOfTimeout()));
        GetActualHttpClient()->Get(url,Options);
    }

    void ScriptWorker::HttpClientDownload(const QString& url, const QString& file, const QString& callback)
    {
        SetScript(callback);
        SetFailMessage(tr("Failed to download page ") + url + tr(" with HttpClient"));
        HttpClientNextTimeout = Waiter->GetGeneralWaitTimeoutNext();
        Waiter->WaitForSignal(GetActualHttpClient(),SIGNAL(Finished()),this,SLOT(FollowRedirectDownload()),this,SLOT(FailBecauseOfTimeout()));
        CurrentFileDownload = file;
        GetActualHttpClient()->Download(url, file);
    }

    void ScriptWorker::DebugTerminate(int how)
    {
        Terminate().DoTerminate(how);
    }

    QString ScriptWorker::DatabaseAddGroup(const QString& GroupName,const QString& GroupDescription, int TableId)
    {
        DatabaseGroup Group;
        Group.IsNull = false;
        Group.Name = GroupName;
        Group.Description = GroupDescription;
        return DatabaseConnector->InsertGroup(Group,TableId);
    }

    QStringList ScriptWorker::DatabaseSelectRecords(const QString& FilterJson,int PageNumber, int PageSize, int TableId)
    {
        DatabaseSelector Selector;

        Selector.TableId = TableId;
        Selector.Filter = DatabaseConnector->ParseFilter(FilterJson);

        DatabaseGroups DbGroups;
        DbGroups.IsNull = false;
        DbGroups.GroupIdList.append("-1");
        Selector.Groups = DbGroups;

        DatabasePage Page;
        Page.IsNull = false;
        Page.PageNumber = PageNumber;
        Page.PageSize = PageSize;
        Selector.Page = Page;

        QList<DatabaseItem> ResData = DatabaseConnector->Select(Selector);

        QList<DatabaseColumn> Columns = DatabaseConnector->GetColumns(TableId);
        QStringList res;
        for(DatabaseItem &item: ResData)
        {
            QStringList line;

            for(DatabaseColumn &Column: Columns)
            {
                line.append(item.Data[Column.Id].toString());
            }
            line.append(item.Id);

            QString Line = CsvHelper->Generate(line,':');
            res.append(Line);
        }
        return res;
    }

    void ScriptWorker::DatabaseDeleteRecords(const QString& FilterJson,int TableId)
    {
        DatabaseMassSelector Selector;

        Selector.TableId = TableId;
        Selector.Filters = DatabaseConnector->ParseFilter(FilterJson);

        DatabaseGroups DbGroups;
        DbGroups.IsNull = false;
        DbGroups.GroupIdList.append("-1");
        Selector.Groups = DbGroups;

        DatabaseConnector->Delete(Selector);
    }

    QString ScriptWorker::DatabaseAddRecord(const QString& GroupId,const QStringList& Record, int TableId)
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
                        case DatabaseColumn::Date:
                        {
                            QDateTime timestamp;
                            if(StringParam.length() > 0)
                            {
                                timestamp.setTime_t(StringParam.toLongLong() / 1000);
                            }
                            else
                                timestamp = QDateTime::currentDateTime();
                            VariantParam = QVariant(timestamp);
                        }break;
                    }

                    break;
                }
            }
            Item.Data[ColumnId] = VariantParam;
        }

        DatabaseGroups Groups;
        Groups.IsNull = false;
        if(GroupId.isEmpty())
            Groups.GroupIdList.append("-1");
        else
            Groups.GroupIdList.append(GroupId);
        return DatabaseConnector->Insert(Groups,Item,TableId);
    }


    void ScriptWorker::DatabaseUpdateRecord(const QString& RecordId,const QStringList& Record, int TableId)
    {
        DatabaseItem item;
        item.Id = RecordId;
        item.IsNull = false;

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
                        case DatabaseColumn::Date:
                        {
                            QDateTime timestamp;
                            if(StringParam.length() > 0)
                            {
                                timestamp.setTime_t(StringParam.toLongLong() / 1000);
                            }
                            else
                                timestamp = QDateTime::currentDateTime();
                            VariantParam = QVariant(timestamp);
                        }break;
                    }

                    break;
                }
            }
            item.Data[ColumnId] = VariantParam;
        }

        DatabaseConnector->Update(item,TableId);
    }


    void ScriptWorker::SubstageSetStartingFunction(const QString& StartingFunction)
    {
        this->SubstageStartingFunction = StartingFunction;
    }

    QString ScriptWorker::SubstageGetStartingFunction()
    {
        return SubstageStartingFunction;
    }

    int ScriptWorker::SubstageGetId()
    {
        return SubstageId;
    }

    void ScriptWorker::SubstageSetId(int Id)
    {
        this->SubstageId = Id;
    }

    int ScriptWorker::SubstageGetParentId()
    {
        return SubstageParentId;
    }

    void ScriptWorker::SubstageSetParentId(int Id)
    {
        this->SubstageParentId = Id;
    }

    void ScriptWorker::SubstageFinished(int Id)
    {
        if(Id == SubstageId)
        {
            emit SubstageFinishedSignal();
        }
    }

    void ScriptWorker::SubstageCall(const QString& StartingFunction, qint64 ThreadsNumber, qint64 MaximumSuccess, qint64 MaximumFailure, const QString& Callback)
    {
        SubstageId = qrand() % 1000000 + 1;
        SetScript(Callback);
        if(MaximumSuccess < 0)
            MaximumSuccess = std::numeric_limits<qint64>::max();
        if(MaximumFailure < 0)
            MaximumFailure = std::numeric_limits<qint64>::max();
        Waiter->WaitInfinity(this,SIGNAL(SubstageFinishedSignal()),this,SLOT(SubstageFinishAndRunNext()));
        emit SubstageBeginSignal(StartingFunction, ThreadsNumber, MaximumSuccess, MaximumFailure, SubstageId);
    }

    void ScriptWorker::SubstageFinishAndRunNext()
    {

        if(SubstageId)
        {
            SubstageId = 0;
            RunSubScript();
        }
    }


}
