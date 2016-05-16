#ifndef RESOURCEMODELDATABASE_H
#define RESOURCEMODELDATABASE_H
#include "engine_global.h"

#include "resourcemodelabstract.h"
#include <QStringList>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ResourceModelDatabase : public ResourceModelAbstract
    {
        Q_OBJECT
        QStringList GroupNames;
        int TableId;
        QList<int> ColumnIds;
        bool clean;
        bool mix;
        int success;
        int fails;
        int number_simultaneous_use;
        int interval_between_usage;
        int load_interval;
        int renew_interval;
        bool Greedy;
    public:
        explicit ResourceModelDatabase(QObject *parent = 0);

        virtual QString GetTypeId();

        QStringList GetGroupList();
        void SetGroupList(const QStringList& Groups);

        int GetTableId();
        void SetTableId(int TableId);

        QList<int> GetColumnIds();
        void SetColumnIds(const QList<int>& ColumnIds);

        bool GetClean();
        void SetClean(bool val);

        bool GetMix();
        void SetMix(bool val);

        int GetSuccessAttempts();
        void SetSuccessAttempts(int val);

        int GetFailAttempts();
        void SetFailAttempts(int val);

        int GetNumberSimultaneousUse();
        void SetNumberSimultaneousUse(int val);

        int GetIntervalBetweenUsage();
        void SetIntervalBetweenUsage(int val);

        int GetLoadInterval();
        void SetLoadInterval(int val);

        int GetRenewInterval();
        void SetRenewInterval(int val);

        bool GetGreedy();
        void SetGreedy(bool Greedy);
    signals:

    public slots:

    };
}

#endif // RESOURCEMODELDATABASE_H
