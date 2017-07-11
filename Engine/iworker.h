#ifndef IWORKER_H
#define IWORKER_H
#include "engine_global.h"

#include <QObject>
#include <QHash>
#include "ibrowser.h"
#include "ilogger.h"
#include "iwaiter.h"
#include "isolverfactory.h"
#include "iengineresources.h"
#include "iscriptresources.h"
#include "iresourcehandlers.h"
#include "iprocesscomunicator.h"
#include "ihttpclientfactory.h"
#include "iscriptsuspender.h"
#include "ihelper.h"
#include "ipop3clientfactory.h"
#include "iimapclientfactory.h"
#include "ihtmlparserfactory.h"
#include "ihelperfactory.h"
#include "ipreprocessor.h"
#include "iproperties.h"
#include "icsvhelper.h"
#include "idatabaseconnector.h"
#include "istringbuilder.h"
#include "modulemanager.h"
#include "iworkersettings.h"

namespace BrowserAutomationStudioFramework
{
    class IBrowser;
    class IWaiter;
    class IScriptSuspender;
    class ENGINESHARED_EXPORT IWorker : public QObject
    {
    Q_OBJECT

    public:
        explicit IWorker(QObject *parent = 0);

        virtual void SetStringBuilder(IStringBuilder *StringBuilder) = 0;
        virtual IStringBuilder * GetStringBuilder() = 0;

        virtual void SetProcessComunicator(IProcessComunicator *ProcessComunicator) = 0;
        virtual IProcessComunicator * GetProcessComunicator() = 0;

        virtual void SetDatabaseConnector(IDatabaseConnector *DatabaseConnector) = 0;
        virtual IDatabaseConnector * GetDatabaseConnector() = 0;

        virtual void SetCsvHelper(ICsvHelper *CsvHelper) = 0;
        virtual ICsvHelper * GetCsvHelper() = 0;

        virtual void SetBrowser(IBrowser *Browser) = 0;
        virtual IBrowser * GetBrowser() = 0;

        virtual void AddModule(QObject *Module, const QString& Name) = 0;

        virtual void SetLogger(ILogger *Logger) = 0;
        virtual ILogger * GetLogger() = 0;

        virtual void SetResults1(ILogger *Results1) = 0;
        virtual ILogger * GetResults1() = 0;

        virtual void SetResults2(ILogger *Results2) = 0;
        virtual ILogger * GetResults2() = 0;

        virtual void SetResults3(ILogger *Results3) = 0;
        virtual ILogger * GetResults3() = 0;

        virtual void SetResults4(ILogger *Results4) = 0;
        virtual ILogger * GetResults4() = 0;

        virtual void SetResults5(ILogger *Results5) = 0;
        virtual ILogger * GetResults5() = 0;

        virtual void SetResults6(ILogger *Results6) = 0;
        virtual ILogger * GetResults6() = 0;

        virtual void SetResults7(ILogger *Results7) = 0;
        virtual ILogger * GetResults7() = 0;

        virtual void SetResults8(ILogger *Results8) = 0;
        virtual ILogger * GetResults8() = 0;

        virtual void SetResults9(ILogger *Results9) = 0;
        virtual ILogger * GetResults9() = 0;

        virtual void SetPreprocessor(IPreprocessor* Preprocessor) = 0;
        virtual IPreprocessor* GetPreprocessor() = 0;

        virtual void SetScript(const QString& Script) = 0;
        virtual QString GetScript() = 0;

        virtual void SetWaiter(IWaiter* Waiter) = 0;
        virtual IWaiter* GetWaiter() = 0;

        virtual void SetScriptSuspender(IScriptSuspender* ScriptSuspender) = 0;
        virtual IScriptSuspender* GetScriptSuspender() = 0;

        virtual void SetScriptResources(IScriptResources* ScriptResources) = 0;
        virtual IScriptResources* GetScriptResources() = 0;

        virtual void SetResourceHandlers(IResourceHandlers* ResourceHandlers) = 0;
        virtual IResourceHandlers* GetResourceHandlers() = 0;

        virtual void SetSolverFactory(ISolverFactory* FactorySolver) = 0;
        virtual ISolverFactory* GetSolverFactory() = 0;

        virtual void SetEngineResources(IEngineResources* EngineRes) = 0;
        virtual IEngineResources* GetEngineResources() = 0;

        virtual void SetThreadNumber(qint64 ThreadNumber) = 0;
        virtual qint64 GetThreadNumber() = 0;

        virtual void SetSuccessNumber(qint64* SuccessNumber) = 0;
        virtual qint64 GetSuccessNumber() = 0;

        virtual void SetFailNumber(qint64* FailNumber) = 0;
        virtual qint64 GetFailNumber() = 0;

        virtual void SetProjectPath(const QString& Path) = 0;
        virtual QString GetProjectPath() = 0;

        virtual void SetHttpClientFactory(IHttpClientFactory* HttpClientFactory) = 0;
        virtual IHttpClientFactory* GetHttpClientFactory() = 0;

        virtual void SetPop3ClientFactory(IPop3ClientFactory* Pop3ClientFactory) = 0;
        virtual IPop3ClientFactory* GetPop3ClientFactory() = 0;

        virtual void SetImapClientFactory(IImapClientFactory* ImapClientFactory) = 0;
        virtual IImapClientFactory* GetImapClientFactory() = 0;

        virtual void SetHelperFactory(IHelperFactory* HelperFactory) = 0;
        virtual IHelperFactory* GetHelperFactory() = 0;

        virtual void SetHtmlParserFactory(IHtmlParserFactory* HtmlParserFactory) = 0;
        virtual IHtmlParserFactory* GetHtmlParserFactory() = 0;

        virtual void SetProperties(IProperties* Properties) = 0;
        virtual IProperties* GetProperties() = 0;

        virtual void SetDoTrace(bool DoTrace) = 0;
        virtual bool GetDoTrace() = 0;


        virtual void SetAdditionEngineScripts(QList<QString>* AdditionalScripts) = 0;
        virtual QList<QString>* GetAdditionEngineScripts() = 0;

        virtual void SetModuleManager(IModuleManager *ModuleManager) = 0;
        virtual IModuleManager* GetModuleManager() = 0;

        enum WorkerStatus{SuccessStatus,FailStatus,SuspendStatus,DieStatus};
    signals:
        void Finished();
        void ProgressValue(int);
        void ProgressMaximum(int);
        void FailedButRescued(const QString& message);
        void SuccessedButRescued(const QString& message);
        void SubstageBeginSignal(const QString& FunctionName, qint64 Threads, qint64 MaximumSuccess, qint64 MaximumFailure, int StageId);
    public slots:

        virtual void Run() = 0;
        virtual void Abort(bool SignalResourceHandlers) = 0;
        virtual void InterruptAction() = 0;
        virtual void Fail(const QString& message, bool dont_create_more) = 0;
        virtual void Die(const QString& message, bool instant) = 0;
        virtual void Success(const QString& message) = 0;
        virtual void SetFailMessage(const QString& message) = 0;
        virtual void FailBecauseOfTimeout() = 0;
        virtual void FailProcessFinished() = 0;
        virtual void RunSubScript() = 0;

        virtual void SetIsRecord(bool IsRecord) = 0;
        virtual bool GetIsRecord() = 0;

        virtual void SetAsyncResult(const QScriptValue & AsyncResult) = 0;
        virtual QScriptValue GetAsyncResult() = 0;

        virtual QString GetResultMessage() = 0;
        virtual QString GetResultMessageRaw() = 0;
        virtual QString GetResultMessageRawWithId() = 0;
        virtual WorkerStatus GetResultStatus() = 0;

        virtual bool IsDieInstant() = 0;
        virtual bool IsDontCreateMore() = 0;

        virtual void SubstageSetStartingFunction(const QString& StartingFunction) = 0;
        virtual QString SubstageGetStartingFunction() = 0;
        virtual int SubstageGetId() = 0;
        virtual void SubstageSetId(int Id) = 0;
        virtual int SubstageGetParentId() = 0;
        virtual void SubstageSetParentId(int Id) = 0;
        virtual void SubstageFinished(int Id) = 0;



    };
}

#endif // IWORKER_H
