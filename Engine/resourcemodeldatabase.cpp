#include "resourcemodeldatabase.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    ResourceModelDatabase::ResourceModelDatabase(QObject *parent) :
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
        renew_interval = 0;
        Greedy = false;
    }

    QStringList ResourceModelDatabase::GetGroupList()
    {
        return GroupNames;
    }

    void ResourceModelDatabase::SetGroupList(const QStringList& val)
    {
        GroupNames = val;
    }

    int ResourceModelDatabase::GetTableId()
    {
        return TableId;
    }
    void ResourceModelDatabase::SetTableId(int TableId)
    {
        this->TableId = TableId;
    }

    QList<int> ResourceModelDatabase::GetColumnIds()
    {
        return ColumnIds;
    }

    void ResourceModelDatabase::SetColumnIds(const QList<int>& ColumnIds)
    {
        this->ColumnIds = ColumnIds;
    }

    bool ResourceModelDatabase::GetClean()
    {
        return clean;
    }
    void ResourceModelDatabase::SetClean(bool val)
    {
        clean = val;
    }

    bool ResourceModelDatabase::GetMix()
    {
        return mix;
    }
    void ResourceModelDatabase::SetMix(bool val)
    {
        mix = val;
    }

    int ResourceModelDatabase::GetSuccessAttempts()
    {
        return success;
    }
    void ResourceModelDatabase::SetSuccessAttempts(int val)
    {
        success = val;
    }

    int ResourceModelDatabase::GetFailAttempts()
    {
        return fails;
    }
    void ResourceModelDatabase::SetFailAttempts(int val)
    {
        fails = val;
    }

    int ResourceModelDatabase::GetNumberSimultaneousUse()
    {
        return number_simultaneous_use;
    }
    void ResourceModelDatabase::SetNumberSimultaneousUse(int val)
    {
        number_simultaneous_use = val;
    }

    int ResourceModelDatabase::GetIntervalBetweenUsage()
    {
        return interval_between_usage;
    }
    void ResourceModelDatabase::SetIntervalBetweenUsage(int val)
    {
        interval_between_usage = val;
    }

    QString ResourceModelDatabase::GetTypeId()
    {
        return QString("Database");
    }

    int ResourceModelDatabase::GetLoadInterval()
    {
        return load_interval;
    }

    void ResourceModelDatabase::SetLoadInterval(int val)
    {
        load_interval = val;
    }

    int ResourceModelDatabase::GetRenewInterval()
    {
        return renew_interval;
    }

    void ResourceModelDatabase::SetRenewInterval(int val)
    {
        renew_interval = val;
    }


    bool ResourceModelDatabase::GetGreedy()
    {
        return Greedy;
    }
    void ResourceModelDatabase::SetGreedy(bool Greedy)
    {
        this->Greedy = Greedy;
    }

}
