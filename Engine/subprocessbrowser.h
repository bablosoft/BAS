#ifndef SUBPROCESSBROWSER_H
#define SUBPROCESSBROWSER_H
#include "engine_global.h"

#include "ibrowser.h"
#include "iprocesscomunicatorfactory.h"

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT SubprocessBrowser : public IBrowser
    {
        Q_OBJECT
        IWorker *Worker;
        IWorker *LastInjectedWorker;
        INetworkAccessManagerFactory *NetworkAccessManagerFactory;
        INetworkAccessManager *NetworkAccessManager;
        IProcessComunicatorFactory *ProcessComunicatorFactory;
        IProcessComunicator *ProcessComunicator;
        QString NextAction;
        QString Language;
        IWorkerSettings *WorkerSettings;
    public:

        explicit SubprocessBrowser(QObject *parent = 0);

    public slots:
        virtual void SetNetworkAccessManagerFactory(INetworkAccessManagerFactory *NetworkAccessManagerFactory);
        void SetProcessComunicatorFactory(IProcessComunicatorFactory *ProcessComunicatorFactory);
        void SetLanguage(const QString& Language);
        virtual void LoadPage(const QString& url, const QString& callback);
        virtual void LoadPageInstant(const QString& url, const QString& callback);
        virtual void SetUserAgent(const QString& agent, const QString& callback);
        virtual void GetCookiesForUrl(const QString& url, const QString& callback);
        virtual void SaveCookies(const QString& callback);
        virtual void RestoreCookies(const QString& cookies, const QString& callback);
        virtual void RestoreLocalStorage(const QString& localstorage, const QString& callback);

        virtual IWebElement* GetRootElement();
        virtual void GetUrl(const QString& callback);
        virtual void CreateNewBrowser(bool ForseNewBrowserCreation, const QString& callback);
        virtual void CloseBrowser();
        virtual void SetWorkerSettings(IWorkerSettings *WorkerSettings);
        virtual IWorkerSettings * GetWorkerSettings();

        virtual INetworkAccessManager* GetNetworkAccessManager();
        virtual void SetScriptResources(IScriptResources* ScriptResources);
        virtual IScriptResources* GetScriptResources();
        virtual void SetWorker(IWorker* Worker);
        virtual IWorker* GetWorker();
        virtual void SetOpenFileName(const QString & OpenFileName, const QString& callback);
        virtual void SetStartupScript(const QString& script,const QString& script_id,const QString& target, const QString& callback);
        virtual void SetFontList(const QString& fonts, const QString& callback);
        virtual void SetPromptResult(const QString & Text, const QString& callback);
        virtual void SetHttpAuthResult(const QString & Login, const QString & Password, const QString& callback);
        virtual void MouseClickInstant(int x, int y);
        virtual void MouseClick(int x, int y, const QString& callback);
        virtual void MouseClickUp(int x, int y, const QString& callback);
        virtual void MouseClickDown(int x, int y, const QString& callback);
        virtual void PopupClose(int index, const QString& callback);
        virtual void PopupSelect(int index, const QString& callback);
        virtual void Timezone(int offset, const QString& callback);
        virtual void Geolocation(float latitude, float longitude, const QString& callback);
        virtual void MouseMove(int x, int y,const QString& params, const QString& callback);
        virtual void Resize(int x, int y, const QString& callback);
        virtual void Reset(const QString& callback);
        virtual void Jquery(const QString& callback);
        virtual void OptimizeMemory(const QString& callback);
        virtual void WaitCode(const QString& callback);
        virtual void StartSection(const QString& Name, int Id, const QString& callback);
        virtual void Scroll(int x, int y, const QString& callback);
        virtual void Render(int x, int y, int width, int height, const QString& callback);
        virtual void DebugVariablesResult(const QString& data, const QString& callback);
        virtual void SendWorkerSettings(const QString& json, const QString& callback);


        virtual void ClearImageData(const QString& callback);
        virtual void SetImageData(const QString& base64, const QString& callback);
        virtual void FindImage(const QString& callback);

        void MarkBeforeReset();
        void MarkAfterReset();

        virtual void OnSupend();
        virtual void SimulateCrush(const QString& callback);
    signals:
        void ProcessCreated(IProcessComunicator *Communicator);
        void Loaded();
        void LoadedInstant();
        void GetUrl();
        void SetUserAgent();
        void GetCookiesForUrl();
        void SaveCookies();
        void RestoreLocalStorage();
        void RestoreCookies();
        void SetOpenFileName();
        void SetStartupScript();
        void SetFontList();
        void SetHttpAuthResult();
        void SetPromptResult();
        void MouseClick();
        void MouseClickUp();
        void MouseClickDown();
        void PopupSelect();
        void PopupClose();
        void MouseMove();
        void Resize();
        void Reset();
        void Scroll();
        void Render();
        void Jquery();
        void OptimizeMemory();
        void WaitCode();
        void DebugVariablesResult();
        void Timezone();
        void Geolocation();
        void Crush();
        void ClearImageData();
        void SetImageData();
        void FindImage();
        void SendWorkerSettings();

    private slots:
        void Received(const QString& value);
        void WorkerStopped();
    };
}
#endif // SUBPROCESSBROWSER_H

