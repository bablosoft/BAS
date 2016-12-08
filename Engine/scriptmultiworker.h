#ifndef SCRIPTMULTIWORKER_H
#define SCRIPTMULTIWORKER_H
#include "engine_global.h"

#include "imultiworker.h"


#include <QScriptEngine>
#include <QTimer>
#include <QHash>



namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ScriptMultiWorker : public IMultiWorker
    {
        Q_OBJECT
        QTimer *StageTimeoutTimer;
        IBrowserFactory *BrowserFactory;
        ILogger *Logger;
        ILogger *Results1;
        ILogger *Results2;
        ILogger *Results3;
        ILogger *Results4;
        ILogger *Results5;
        ILogger *Results6;
        ILogger *Results7;
        ILogger *Results8;
        ILogger *Results9;

        QString Script;
        IWaiterFactory *WaiterFactory;
        IScriptResources *ScriptResources;
        IResourceHandlersFactory *ResourceHandlersFactory;
        ISolverFactory* FactorySolver;
        IEngineResources* EngineRes;
        IWorkerFactory *WorkerFactory;
        IHttpClientFactory *HttpClientFactory;
        IPop3ClientFactory *Pop3ClientFactory;
        IImapClientFactory *ImapClientFactory;
        IHelperFactory* HelperFactory;
        IHelper* Helper;
        ICsvHelper *CsvHelper;
        IModuleManager *ModuleManager;

        IHtmlParserFactory* HtmlParserFactory;
        IProperties* Properties;

        QScriptEngine* engine;
        IWaiter * Waiter;
        IResourceHandlers *ResourceHandlers;
        IPreprocessor *Preprocessor;
        IScriptSuspender *ScriptSuspender;
        QString AbortFunction;


        QList<IWorker *> Workers;
        QList<IBrowser *> Browsers;
        QScriptValue AsyncResult;
        bool NeedToSetAsyncResult;
        QString OnFinishScript;

        bool IsAborted;
        int WorkerRunning;
        bool NoNeedToCreateWorkersMore;
        int SuccessLeft;
        int FailLeft;
        bool DieOnFailHandler;
        void CreateWorker(int index);
        IScriptMultiWorkerReportData *ReportData;
        QHash<QString,QObject*> ModulesMultiWorker;
        QHash<QString,QObject*> ModulesScriptWorker;
        bool DoTrace;
        IDatabaseConnector *DatabaseConnector;
        bool IsRecord;

        QList<QString> AdditionalScripts;

    public:
        QString WorkerScript;

        explicit ScriptMultiWorker(QObject *parent);

        virtual void AddModule(QObject *Module, const QString& Name, bool AddToMultiWorker, bool AddToWorker);

        virtual void SetDatabaseConnector(IDatabaseConnector *DatabaseConnector);
        virtual IDatabaseConnector * GetDatabaseConnector();

        virtual void SetCsvHelper(ICsvHelper *CsvHelper);
        virtual ICsvHelper * GetCsvHelper();

        virtual void SetReportData(IScriptMultiWorkerReportData *ReportData);
        virtual IScriptMultiWorkerReportData * GetReportData();

        virtual void SetWorkerFactory(IWorkerFactory *WorkerFactory);
        virtual IWorkerFactory * GetWorkerFactory();

        virtual void SetPreprocessor(IPreprocessor *Preprocessor);
        virtual IPreprocessor * GetPreprocessor();

        virtual void SetBrowserFactory(IBrowserFactory *BrowserFactory);
        virtual IBrowserFactory * GetBrowserFactory();

        virtual void SetLogger(ILogger *Logger);
        virtual ILogger * GetLogger();

        virtual void SetResults1(ILogger *Results1);
        virtual ILogger * GetResults1();

        virtual void SetResults2(ILogger *Results2);
        virtual ILogger * GetResults2();

        virtual void SetResults3(ILogger *Results3);
        virtual ILogger * GetResults3();

        virtual void SetResults4(ILogger *Results4);
        virtual ILogger * GetResults4();

        virtual void SetResults5(ILogger *Results5);
        virtual ILogger * GetResults5();

        virtual void SetResults6(ILogger *Results6);
        virtual ILogger * GetResults6();

        virtual void SetResults7(ILogger *Results7);
        virtual ILogger * GetResults7();

        virtual void SetResults8(ILogger *Results8);
        virtual ILogger * GetResults8();

        virtual void SetResults9(ILogger *Results9);
        virtual ILogger * GetResults9();

        virtual void SetScript(const QString& Script);
        virtual QString GetScript();

        virtual void SetScriptSuspender(IScriptSuspender* ScriptSuspender);
        virtual IScriptSuspender* GetScriptSuspender();

        virtual void SetWaiterFactory(IWaiterFactory* WaiterFactory);
        virtual IWaiterFactory* GetWaiterFactory();

        virtual void SetScriptResources(IScriptResources* ScriptResources);
        virtual IScriptResources* GetScriptResources();

        virtual void SetResourceHandlersFactory(IResourceHandlersFactory* ResourceHandlersFactory);
        virtual IResourceHandlersFactory* GetResourceHandlersFactory();

        virtual void SetSolverFactory(ISolverFactory* FactorySolver);
        virtual ISolverFactory* GetSolverFactory();

        virtual void SetEngineResources(IEngineResources* EngineRes);
        virtual IEngineResources* GetEngineResources();

        virtual void SetHttpClientFactory(IHttpClientFactory* HttpClientFactory);
        virtual IHttpClientFactory* GetHttpClientFactory();

        virtual void SetPop3ClientFactory(IPop3ClientFactory* Pop3ClientFactory);
        virtual IPop3ClientFactory* GetPop3ClientFactory();

        virtual void SetImapClientFactory(IImapClientFactory* ImapClientFactory);
        virtual IImapClientFactory* GetImapClientFactory();

        virtual void SetHelperFactory(IHelperFactory* HelperFactory);
        virtual IHelperFactory* GetHelperFactory();

        virtual void SetHtmlParserFactory(IHtmlParserFactory* HtmlParserFactory);
        virtual IHtmlParserFactory* GetHtmlParserFactory();

        virtual void SetProperties(IProperties* Properties);
        virtual IProperties* GetProperties();

        virtual void SetDoTrace(bool DoTrace);
        virtual bool GetDoTrace();

        virtual void SetAdditionEngineScripts(const QList<QString>& AdditionalScripts);
        virtual QList<QString> GetAdditionEngineScripts();

        void SetIsRecord(bool IsRecord);
        bool GetIsRecord();

        virtual void SetModuleManager(IModuleManager *ModuleManager);
        virtual IModuleManager* GetModuleManager();
    signals:
        void InterruptActionSignal();
    public slots:
        void RunStage(int ThreadsNumber, int MaximumSuccess, int MaximumFailure, int MaxRunTime,const QString& WorkerFunction, const QString& callback);
        virtual void Run();
        virtual void RunSubScript();
        virtual void Abort();
        virtual void InterruptAction();
        void Decrypt(const QString& Data);
        void SuccessInternal();
        void FailInternal(const QString&  message);
        virtual void AbortWorkers(bool NotSignalResourceHandlers);
        void AbortSubscript();
        virtual void SetAsyncResult(const QScriptValue & AsyncResult);
        virtual QScriptValue GetAsyncResult();
        void GetHandler(const QString& name, bool die_on_fail, const QString& callback);
        QScriptValue GetAllData(const QString& name);
        QScriptValue GetRandomSubarrayData(const QString& name, int size);
        QScriptValue GetAtIndex(const QString& name, int index);
        void SetAtIndex(const QString& name, int index, const QString& val);

        QScriptValue GetTotalLength(const QString& name);
        void SetAbortFunction(const QString& AbortFunction);

        void Sleep(int msec, const QString& callback);
        void ReloadResource(const QString& name);
        void RemoveResource(const QString& name);

        void AddResource(const QString& name, bool successes, bool fails, int simultaneous, int interval, bool greedy, bool dont_give_up);

        void ProgressValueSlot(int);
        void ProgressMaximumSlot(int);
        QString DatabaseAddGroup(const QString& GroupName,const QString& GroupDescription, int TableId);
    private slots:
        void HandlerWaitFinishedSuccess();
        void HandlerWaitFinishedFailed();

        void ScriptFinished();
        void WorkerFinished();
        void WorkerFinishedWithArgument(IWorker * w);
        void WorkerSuspended(IWorker * Worker);
        void WorkerResumed();
        bool TakeWorkerFromSuspended(int index);
        QString CurrentTimeString();
        void StageTimeout();


    };
}

#endif // SCRIPTMULTIWORKER_H
