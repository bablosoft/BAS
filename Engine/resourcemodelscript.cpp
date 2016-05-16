#include "resourcemodelscript.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    ResourceModelScript::ResourceModelScript(QObject *parent) :
        ResourceModelAbstract(parent)
    {
        dont_give_up = false;
    }


    int ResourceModelScript::GetSuccessAttempts()
    {
        return success;
    }
    void ResourceModelScript::SetSuccessAttempts(int val)
    {
        success = val;
    }

    int ResourceModelScript::GetFailAttempts()
    {
        return fails;
    }
    void ResourceModelScript::SetFailAttempts(int val)
    {
        fails = val;
    }

    int ResourceModelScript::GetNumberSimultaneousUse()
    {
        return number_simultaneous_use;
    }
    void ResourceModelScript::SetNumberSimultaneousUse(int val)
    {
        number_simultaneous_use = val;
    }

    int ResourceModelScript::GetIntervalBetweenUsage()
    {
        return interval_between_usage;
    }
    void ResourceModelScript::SetIntervalBetweenUsage(int val)
    {
        interval_between_usage = val;
    }

    QString ResourceModelScript::GetTypeId()
    {
        return QString("LinesFromScript");
    }

    bool ResourceModelScript::GetGreedy()
    {
        return greedy;
    }

    void ResourceModelScript::SetGreedy(bool Greedy)
    {
        this->greedy = Greedy;
    }

    bool ResourceModelScript::GetDontGiveUp()
    {
        return dont_give_up;
    }

    void ResourceModelScript::SetDontGiveUp(bool dont_give_up)
    {
        this->dont_give_up = dont_give_up;
    }

}
