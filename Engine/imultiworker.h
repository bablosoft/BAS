#ifndef IMULTIWORKER_H
#define IMULTIWORKER_H
#include "engine_global.h"

#include <QObject>
#include "ibrowserfactory.h"
#include "ilogger.h"
#include "iwaiterfactory.h"
#include "iresourcehandlersfactory.h"
#include "iworkerfactory.h"
#include "ibrowserfactory.h"
#include "isolverfactory.h"
#include "iscriptresources.h"
#include "ipreprocessor.h"
#include "ihttpclientfactory.h"
#include "iscriptmultiworkerreportdata.h"
#include "ihelper.h"
#include "ipop3clientfactory.h"
#include "iimapclientfactory.h"
#include "ihtmlparserfactory.h"
#include "ihelperfactory.h"
#include "iproperties.h"
#include "icsvhelper.h"
#include "idatabaseconnector.h"
#include "imodulemanager.h"
#include "istringbuilder.h"
#include "iworkersettings.h"

namespace BrowserAutomationStudioFramework
{
    class IBrowserFactory;
    class IWaiterFactory;
    class IWorkerFactory;
    class ENGINESHARED_EXPORT IMultiWorker : public QObject
    {
        Q_OBJECT
    public:

        explicit IMultiWorker(QObject *parent = 0);

        virtual void SetStringBuilder(IStringBuilder *StringBuilder) = 0;
        virtual IStringBuilder * GetStringBuilder() = 0;

        virtual void AddModule(QObject *Module, const QString& Name, bool AddToMultiWorker, bool AddToWorker) = 0;

        virtual void SetDatabaseConnector(IDatabaseConnector *DatabaseConnector) = 0;
        virtual IDatabaseConnector * GetDatabaseConnector() = 0;

        virtual void SetWorkerFactory(IWorkerFactory *WorkerFactory) = 0;
        virtual IWorkerFactory * GetWorkerFactory() = 0;

        virtual void SetCsvHelper(ICsvHelper *CsvHelper) = 0;
        virtual ICsvHelper * GetCsvHelper() = 0;

        virtual void SetReportData(IScriptMultiWorkerReportData *ReportData) = 0;
        virtual IScriptMultiWorkerReportData * GetReportData() = 0;

        virtual void SetPreprocessor(IPreprocessor *Preprocessor) = 0;
        virtual IPreprocessor * GetPreprocessor() = 0;

        virtual void SetBrowserFactory(IBrowserFactory *BrowserFactory) = 0;
        virtual IBrowserFactory * GetBrowserFactory() = 0;

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

        virtual void SetScript(const QString& Script) = 0;
        virtual QString GetScript() = 0;

        virtual void SetWaiterFactory(IWaiterFactory* WaiterFactory) = 0;
        virtual IWaiterFactory* GetWaiterFactory() = 0;

        virtual void SetScriptResources(IScriptResources* ScriptResources) = 0;
        virtual IScriptResources* GetScriptResources() = 0;

        virtual void SetResourceHandlersFactory(IResourceHandlersFactory* ResourceHandlersFactory) = 0;
        virtual IResourceHandlersFactory* GetResourceHandlersFactory() = 0;

        virtual void SetSolverFactory(ISolverFactory* FactorySolver) = 0;
        virtual ISolverFactory* GetSolverFactory() = 0;

        virtual void SetEngineResources(IEngineResources* EngineRes) = 0;
        virtual IEngineResources* GetEngineResources() = 0;

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

        virtual void SetAdditionEngineScripts(const QList<QString>& AdditionalScripts) = 0;
        virtual QList<QString> GetAdditionEngineScripts() = 0;

        virtual void SetDoTrace(bool DoTrace) = 0;
        virtual bool GetDoTrace() = 0;

        virtual void SetModuleManager(IModuleManager *ModuleManager) = 0;
        virtual IModuleManager* GetModuleManager() = 0;

        virtual void SetProjectPath(const QString& ProjectPath) = 0;
        virtual QString GetProjectPath() = 0;

        virtual void SetWorkerSettings(IWorkerSettings* WorkerSettings) = 0;
        virtual IWorkerSettings* GetWorkerSettings() = 0;
    signals:
        void Finished();
        void StageFinished();
        void Success();
        void Failed();
        void ProgressValue(int);
        void ProgressMaximum(int);
    public slots:

        virtual void Run() = 0;
        virtual void Abort() = 0;
        virtual void AbortNotInstant() = 0;
        virtual void InterruptAction() = 0;



    };
}

#endif // IMULTIWORKER_H
