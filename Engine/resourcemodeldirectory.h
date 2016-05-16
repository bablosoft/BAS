#ifndef RESOURCEMODELDIRECTORY_H
#define RESOURCEMODELDIRECTORY_H
#include "engine_global.h"

#include "resourcemodelabstract.h"

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT ResourceModelDirectory : public ResourceModelAbstract
    {
        Q_OBJECT
        QString directory;
        QString wildcard;
        bool clean;
        bool mix;
        int success;
        int fails;
        int number_simultaneous_use;
        int interval_between_usage;
        int load_interval;
        bool Greedy;
        int renew_interval;
    public:
        explicit ResourceModelDirectory(QObject *parent = 0);

    signals:

    public slots:
        virtual QString GetTypeId();

        QString GetDirectory();
        void SetDirectory(const QString& val);

        QString GetWildcard();
        void SetWildcard(const QString& val);

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

        bool GetGreedy();
        void SetGreedy(bool Greedy);

        int GetRenewInterval();
        void SetRenewInterval(int val);


    };
}

#endif // RESOURCEMODELDIRECTORY_H
