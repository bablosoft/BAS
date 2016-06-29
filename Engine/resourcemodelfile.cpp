#include "resourcemodelfile.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    ResourceModelFile::ResourceModelFile(QObject *parent) :
        ResourceModelAbstract(parent)
    {
        renew_interval = -1;
        write = false;
        read = true;
        mix = false;
        success = 0;
        fails = 0;
        number_simultaneous_use = 0;
        interval_between_usage = 0;
        load_interval = 0;
        renew_interval = 0;
        Greedy = false;
    }

    QString ResourceModelFile::GetFilename()
    {
        return filename;
    }

    void ResourceModelFile::SetFilename(const QString& val)
    {
        filename = val;
    }


    bool ResourceModelFile::GetWrite()
    {
        return write;
    }
    void ResourceModelFile::SetWrite(bool val)
    {
        write = val;
    }

    bool ResourceModelFile::GetRead()
    {
        return read;
    }

    void ResourceModelFile::SetRead(bool val)
    {
        read = val;
    }

    bool ResourceModelFile::GetMix()
    {
        return mix;
    }
    void ResourceModelFile::SetMix(bool val)
    {
        mix = val;
    }

    int ResourceModelFile::GetSuccessAttempts()
    {
        return success;
    }
    void ResourceModelFile::SetSuccessAttempts(int val)
    {
        success = val;
    }

    int ResourceModelFile::GetFailAttempts()
    {
        return fails;
    }
    void ResourceModelFile::SetFailAttempts(int val)
    {
        fails = val;
    }

    int ResourceModelFile::GetNumberSimultaneousUse()
    {
        return number_simultaneous_use;
    }
    void ResourceModelFile::SetNumberSimultaneousUse(int val)
    {
        number_simultaneous_use = val;
    }

    int ResourceModelFile::GetIntervalBetweenUsage()
    {
        return interval_between_usage;
    }
    void ResourceModelFile::SetIntervalBetweenUsage(int val)
    {
        interval_between_usage = val;
    }

    QString ResourceModelFile::GetTypeId()
    {
        return QString("LinesFromFile");
    }

    int ResourceModelFile::GetLoadInterval()
    {
        return load_interval;
    }

    void ResourceModelFile::SetLoadInterval(int val)
    {
        load_interval = val;
    }

    int ResourceModelFile::GetRenewInterval()
    {
        return renew_interval;
    }

    void ResourceModelFile::SetRenewInterval(int val)
    {
        renew_interval = val;
    }


    bool ResourceModelFile::GetGreedy()
    {
        return Greedy;
    }
    void ResourceModelFile::SetGreedy(bool Greedy)
    {
        this->Greedy = Greedy;
    }

}
