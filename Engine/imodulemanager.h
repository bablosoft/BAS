#ifndef IMODULEMANAGER_H
#define IMODULEMANAGER_H

#include <QObject>
#include <memory>
#include <functional>
#include "engine_global.h"


namespace BrowserAutomationStudioFramework
{
    class FunctionRunData;

    class ENGINESHARED_EXPORT IModuleManager : public QObject
    {
        Q_OBJECT
    public:
        typedef char* (*ResizeFunction)(int,void*);
        typedef void* (*ModuleOnStartFunction)();
        typedef void (*ModuleOnEndFunction)(void*);
        typedef void (*ModuleWorkFunction)(char *InputJson, ResizeFunction AllocateSpace, void *AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool *WasError);

        struct ModuleFunctionClass
        {
            QString Alias;
            bool IsAsync;
            bool IsWaitInfinite;
            ModuleWorkFunction WorkFunction;
        };
        using ModuleFunction = std::shared_ptr<ModuleFunctionClass>;

        struct ModuleDllClass
        {
            QString Name;
            QString FileName;
            ModuleOnStartFunction StartDllFunction;
            ModuleOnEndFunction EndDllFunction;
            ModuleOnStartFunction StartThreadFunction;
            ModuleOnEndFunction EndThreadFunction;
            QList<ModuleFunction> FunctionList;
        };
        using ModuleDll = std::shared_ptr<ModuleDllClass>;


        struct ModuleInfoClass
        {
            QString Name;
            QString Description;
            QString DeveloperName;
            QString DeveloperEmail;
            QString DeveloperSite;
            QList<QString> EngineCode;
            QList<ModuleDll> Dlls;
            int ApiVersion;
            int MajorVersion;
            int MinorVersion;
            bool IsEnabled;
        };

        using ModuleInfo = std::shared_ptr<ModuleInfoClass>;



        explicit IModuleManager(QObject *parent = 0);
        virtual QList<ModuleInfo> GetModuleInfo() = 0;
        virtual bool IsModuleEnabled(const QString& ModuleName) = 0;
        virtual void SetModuleEnabled(const QString& ModuleName, bool IsEnabled) = 0;
        virtual int GetModuleSystemVersion() = 0;
        virtual QList<QString> GetModuleEngineCode() = 0;
        virtual void StartAllDlls() = 0;
        virtual void StopAllDlls() = 0;
        virtual void StartThread(unsigned int ThreadId) = 0;
        virtual void StopThread(unsigned int ThreadId) = 0;
        virtual FunctionRunData * PrepareExecuteFunction(const QString& DllName, const QString& FunctionName, const QString& InputParam, unsigned int ThreadId) = 0;
    signals:

    public slots:

    };

    char* ResizeFunctionImpl(int size,void *AllocateData);

    class FunctionRunData : public QObject
    {
        Q_OBJECT
        public:
            explicit FunctionRunData(QObject *parent = 0);

            IModuleManager::ModuleWorkFunction FunctionPointer;
            QString DllName;
            QString FunctionName;
            std::vector<char> InputJson;
            std::vector<char>  OutputJson;
            void* DllData;
            void* ThreadData;
            unsigned int ThreadId;
            bool IsError;
            std::string ErrorString;
            bool IsAync;
            bool WaitInfinite;
            bool NeedToStop;
            bool ExecuteError;
        signals:
            void ReadyResult();
            void Finished();
        public slots:
            void Execute();
            void Stop();
    };
}

#endif // IMODULEMANAGER_H

