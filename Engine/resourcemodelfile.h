#ifndef RESOURCEMODELFILE_H
#define RESOURCEMODELFILE_H
#include "engine_global.h"

#include "resourcemodelabstract.h"

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT ResourceModelFile : public ResourceModelAbstract
    {
        Q_OBJECT
        QString filename;
        bool write;
        bool read;
        bool mix;
        int success;
        int fails;
        int number_simultaneous_use;
        int interval_between_usage;
        int load_interval;
        int renew_interval;
        bool Greedy;
    public:
        explicit ResourceModelFile(QObject *parent = 0);

    signals:

    public slots:
        virtual QString GetTypeId();
        QString GetFilename();
        void SetFilename(const QString& val);

        bool GetWrite();
        void SetWrite(bool val);

        bool GetRead();
        void SetRead(bool val);

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
    };
}

#endif // RESOURCEMODELFILE_H
