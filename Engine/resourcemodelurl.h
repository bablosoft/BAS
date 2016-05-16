#ifndef RESOURCEMODELURL_H
#define RESOURCEMODELURL_H
#include "engine_global.h"


#include "resourcemodelabstract.h"

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT ResourceModelUrl : public ResourceModelAbstract
    {
        Q_OBJECT

        QString url;
        bool mix;
        int success;
        int fails;
        int load_interval;
        int number_simultaneous_use;
        int interval_between_usage;
        int renew_interval;

        QString Argument;
        bool Greedy;
    public:
        enum CaptureMethod{Split,Match};
        explicit ResourceModelUrl(QObject *parent = 0);
    private:
        CaptureMethod Capture;
    signals:

    public slots:


        virtual QString GetTypeId();
        QString GetUrl();
        void SetUrl(const QString& val);

        bool GetMix();
        void SetMix(bool val);

        int GetSuccessAttempts();
        void SetSuccessAttempts(int val);

        int GetFailAttempts();
        void SetFailAttempts(int val);

        int GetNumberSimultaneousUse();
        void SetNumberSimultaneousUse(int val);

        int GetLoadInterval();
        void SetLoadInterval(int val);

        int GetIntervalBetweenUsage();
        void SetIntervalBetweenUsage(int val);

        int GetRenewInterval();
        void SetRenewInterval(int val);

        CaptureMethod GetCaptureMethod();
        void SetCaptureMethod(CaptureMethod Capture);
        void SetCaptureMethod(int Capture);

        QString GetCaptureArgument();
        void SetCaptureArgument(QString Argument);

        bool GetGreedy();
        void SetGreedy(bool Greedy);
    };
}

#endif // RESOURCEMODELURL_H
