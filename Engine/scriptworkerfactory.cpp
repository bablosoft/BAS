#include "scriptworkerfactory.h"
#include "scriptworker.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    ScriptWorkerFactory::ScriptWorkerFactory(QObject *parent) :
        IWorkerFactory(parent)
    {
    }
    IWorker *ScriptWorkerFactory::CreateWorker()
    {
        return new ScriptWorker();
    }

}
