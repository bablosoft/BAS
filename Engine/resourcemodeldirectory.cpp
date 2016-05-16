#include "resourcemodeldirectory.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    ResourceModelDirectory::ResourceModelDirectory(QObject *parent) :
        ResourceModelAbstract(parent)
    {
        renew_interval = -1;
        clean = false;
        mix = false;
        success = 0;
        fails = 0;
        number_simultaneous_use = 0;
        interval_between_usage = 0;
        load_interval = 0;
        Greedy = false;
        renew_interval = 0;
    }



    QString ResourceModelDirectory::GetDirectory()
    {
        return directory;
    }

    void ResourceModelDirectory::SetDirectory(const QString& val)
    {
        directory = val;
    }


    QString ResourceModelDirectory::GetWildcard()
    {
        return wildcard;
    }
    void ResourceModelDirectory::SetWildcard(const QString& val)
    {
        wildcard = val;
    }

    bool ResourceModelDirectory::GetClean()
    {
        return clean;
    }
    void ResourceModelDirectory::SetClean(bool val)
    {
        clean = val;
    }

    bool ResourceModelDirectory::GetMix()
    {
        return mix;
    }
    void ResourceModelDirectory::SetMix(bool val)
    {
        mix = val;
    }

    int ResourceModelDirectory::GetSuccessAttempts()
    {
        return success;
    }
    void ResourceModelDirectory::SetSuccessAttempts(int val)
    {
        success = val;
    }

    int ResourceModelDirectory::GetFailAttempts()
    {
        return fails;
    }
    void ResourceModelDirectory::SetFailAttempts(int val)
    {
        fails = val;
    }

    int ResourceModelDirectory::GetNumberSimultaneousUse()
    {
        return number_simultaneous_use;
    }
    void ResourceModelDirectory::SetNumberSimultaneousUse(int val)
    {
        number_simultaneous_use = val;
    }

    int ResourceModelDirectory::GetIntervalBetweenUsage()
    {
        return interval_between_usage;
    }
    void ResourceModelDirectory::SetIntervalBetweenUsage(int val)
    {
        interval_between_usage = val;
    }

    QString ResourceModelDirectory::GetTypeId()
    {
        return QString("FilesFromDirectory");
    }

    int ResourceModelDirectory::GetLoadInterval()
    {
        return load_interval;
    }

    void ResourceModelDirectory::SetLoadInterval(int val)
    {
        load_interval = val;
    }

    int ResourceModelDirectory::GetRenewInterval()
    {
        return renew_interval;
    }

    void ResourceModelDirectory::SetRenewInterval(int val)
    {
        renew_interval = val;
    }

    bool ResourceModelDirectory::GetGreedy()
    {
        return Greedy;
    }
    void ResourceModelDirectory::SetGreedy(bool Greedy)
    {
        this->Greedy = Greedy;
    }
}
