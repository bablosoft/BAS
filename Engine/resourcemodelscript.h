#ifndef RESOURCEMODELSCRIPT_H
#define RESOURCEMODELSCRIPT_H

#include "engine_global.h"

#include "resourcemodelabstract.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ResourceModelScript : public ResourceModelAbstract
    {
        Q_OBJECT
        int success;
        int fails;
        int number_simultaneous_use;
        int interval_between_usage;
        bool greedy;
        bool dont_give_up;
    public:
        explicit ResourceModelScript(QObject *parent = 0);

    signals:

    public slots:
        virtual QString GetTypeId();
        int GetSuccessAttempts();
        void SetSuccessAttempts(int val);

        int GetFailAttempts();
        void SetFailAttempts(int val);

        int GetNumberSimultaneousUse();
        void SetNumberSimultaneousUse(int val);

        int GetIntervalBetweenUsage();
        void SetIntervalBetweenUsage(int val);

        bool GetDontGiveUp();
        void SetDontGiveUp(bool dont_give_up);

        bool GetGreedy();
        void SetGreedy(bool Greedy);

    };
}
#endif // RESOURCEMODELSCRIPT_H
