#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H
#include <QObject>
#include <QHash>
#include "imodulemanager.h"
#include "engine_global.h"


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ModuleManager : public IModuleManager
    {
        Q_OBJECT
        QList<ModuleInfo> ModuleInfoCache;
        struct DllDataClass
        {
            QString DllName;
            int ThreadNumber;
            void *data;
        };
        using DllData = std::shared_ptr<DllDataClass>;
        QList<DllData> DllDataList;
        QList<DllData> ThreadDataList;
        void RemoveAllThreadData(int ThreadNumber);
        DllData FindDllData(const QList<DllData> & List, const QString& DllName, int ThreadNumber = -1);
        ModuleFunction FindFunction(const QString& DllName, const QString& FunctionName);
        void* GetDllData(const QString& DllName);
        void* GetThreadData(const QString& DllName, unsigned int ThreadId);
    public:
        explicit ModuleManager(QObject *parent = 0);
        virtual QList<ModuleInfo> GetModuleInfo();
        virtual bool IsModuleEnabled(const QString& ModuleName);
        virtual void SetModuleEnabled(const QString& ModuleName, bool IsEnabled);
        virtual int GetModuleSystemVersion();
        virtual QList<QString> GetModuleEngineCode();
        virtual void StartAllDlls();
        virtual void StopAllDlls();
        virtual void StartThread(unsigned int ThreadId);
        virtual void StopThread(unsigned int ThreadId);
        virtual FunctionRunData* PrepareExecuteFunction(const QString& DllName, const QString& FunctionName, const QString& InputParam, unsigned int ThreadId);

    signals:

    public slots:

    };
}

#endif // MODULEMANAGER_H

