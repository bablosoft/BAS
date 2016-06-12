#include "imodulemanager.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    IModuleManager::IModuleManager(QObject *parent) :
        QObject(parent)
    {
    }

    FunctionRunData::FunctionRunData(QObject *parent) :
        QObject(parent)
    {
    }

    void FunctionRunData::Execute()
    {
        ExecuteError = false;
        FunctionPointer(InputJson.data(),ResizeFunctionImpl,this,DllData,ThreadData,ThreadId,&NeedToStop,&ExecuteError);
        if(!NeedToStop)
            emit ReadyResult();

        emit Finished();
    }

    void FunctionRunData::Stop()
    {
        NeedToStop = true;
    }

    char* ResizeFunctionImpl(int size,void *AllocateData)
    {
        FunctionRunData* data = (FunctionRunData*)AllocateData;
        data->OutputJson.resize(size);
        return data->OutputJson.data();
    }

}
