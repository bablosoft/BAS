#ifndef SOLVERFACTORY_H
#define SOLVERFACTORY_H
#include "engine_global.h"

#include "isolverfactory.h"
#include "manualcaptchasolver.h"
#include "antigatecaptchasolver.h"
#include "ihttpclientfactory.h"
namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT SolverFactory : public ISolverFactory
    {
        Q_OBJECT
        ManualCaptchaSolver * ManualSolver;
        AntigateCaptchaSolver * AntigateSolver;
        AntigateCaptchaSolver * DbcSolver;
        AntigateCaptchaSolver * RucaptchaSolver;
        AntigateCaptchaSolver * TwocaptchaSolver;
        IHttpClientFactory * HttpClientFactory;
    public:
        explicit SolverFactory(QObject *parent = 0);
        virtual ISolver* GetSolver(const QString& name);

        void SetHttpClientFactory(IHttpClientFactory * HttpClientFactory);
        IHttpClientFactory * GetHttpClientFactory();
    signals:

    private slots:
        void UsedManual();
        void UsedAntigate();
        void UsedDbc();
        void UsedRucaptcha();
        void Used2Captcha();

        void FailedManual();
        void FailedAntigate();
        void FailedDbc();
        void FailedRucaptcha();
        void Failed2Captcha();
    };
}

#endif // SOLVERFACTORY_H
