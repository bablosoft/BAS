#include "resourcemodelurl.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    ResourceModelUrl::ResourceModelUrl(QObject *parent) :
        ResourceModelAbstract(parent)
    {
        renew_interval = -1;
        mix = false;
        success = 0;
        fails = 0;
        load_interval = 0;
        number_simultaneous_use = 0;
        interval_between_usage = 0;
        renew_interval = 0;
        Greedy = false;
    }

    QString ResourceModelUrl::GetUrl()
    {
        return url;
    }

    void ResourceModelUrl::SetUrl(const QString& val)
    {
        url = val;
    }

    bool ResourceModelUrl::GetMix()
    {
        return mix;
    }
    void ResourceModelUrl::SetMix(bool val)
    {
        mix = val;
    }

    int ResourceModelUrl::GetSuccessAttempts()
    {
        return success;
    }
    void ResourceModelUrl::SetSuccessAttempts(int val)
    {
        success = val;
    }

    int ResourceModelUrl::GetFailAttempts()
    {
        return fails;
    }
    void ResourceModelUrl::SetFailAttempts(int val)
    {
        fails = val;
    }

    int ResourceModelUrl::GetNumberSimultaneousUse()
    {
        return number_simultaneous_use;
    }
    void ResourceModelUrl::SetNumberSimultaneousUse(int val)
    {
        number_simultaneous_use = val;
    }

    int ResourceModelUrl::GetIntervalBetweenUsage()
    {
        return interval_between_usage;
    }
    void ResourceModelUrl::SetIntervalBetweenUsage(int val)
    {
        interval_between_usage = val;
    }

    int ResourceModelUrl::GetLoadInterval()
    {
        return load_interval;
    }

    void ResourceModelUrl::SetLoadInterval(int val)
    {
        load_interval = val;
    }

    ResourceModelUrl::CaptureMethod ResourceModelUrl::GetCaptureMethod()
    {
        return Capture;
    }

    void ResourceModelUrl::SetCaptureMethod(CaptureMethod Capture)
    {
        this->Capture = Capture;
    }

    void ResourceModelUrl::SetCaptureMethod(int Capture)
    {
        this->Capture = (CaptureMethod)Capture;
    }

    QString ResourceModelUrl::GetCaptureArgument()
    {
        return Argument;
    }

    void ResourceModelUrl::SetCaptureArgument(QString Argument)
    {
        this->Argument = Argument;
    }

    QString ResourceModelUrl::GetTypeId()
    {
        return QString("LinesFromUrl");
    }

    int ResourceModelUrl::GetRenewInterval()
    {
        return renew_interval;
    }

    void ResourceModelUrl::SetRenewInterval(int val)
    {
        renew_interval = val;
    }

    bool ResourceModelUrl::GetGreedy()
    {
        return Greedy;
    }
    void ResourceModelUrl::SetGreedy(bool Greedy)
    {
        this->Greedy = Greedy;
    }
}
