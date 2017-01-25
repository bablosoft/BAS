#include "solverfactory.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    SolverFactory::SolverFactory(QObject *parent) :
        ISolverFactory(parent),ManualSolver(0),AntigateSolver(0), DbcSolver(0),RucaptchaSolver(0),TwocaptchaSolver(0),CapMonsterSolver(0)
    {
    }

    void SolverFactory::UsedManual()
    {
        emit UsedSolver("Manual");
    }

    void SolverFactory::UsedAntigate()
    {
        emit UsedSolver("Antigate");
    }

    void SolverFactory::UsedDbc()
    {
        emit UsedSolver("Dbc");
    }

    void SolverFactory::UsedRucaptcha()
    {
        emit UsedSolver("RuCaptcha");
    }

    void SolverFactory::Used2Captcha()
    {
        emit UsedSolver("2Captcha");
    }

    void SolverFactory::UsedCapmonster()
    {
        emit UsedSolver("Capmonster");
    }




    void SolverFactory::FailedManual()
    {
        emit FailedSolver("Manual");
    }

    void SolverFactory::FailedAntigate()
    {
        emit FailedSolver("Antigate");
    }

    void SolverFactory::FailedDbc()
    {
        emit FailedSolver("Dbc");
    }

    void SolverFactory::FailedRucaptcha()
    {
        emit FailedSolver("RuCaptcha");
    }

    void SolverFactory::Failed2Captcha()
    {
        emit FailedSolver("2Captcha");
    }

    void SolverFactory::FailedCapmonster()
    {
        emit FailedSolver("Capmonster");
    }


    ISolver* SolverFactory::GetSolver(const QString& name)
    {
        if(name == "manual")
        {
            if(ManualSolver == 0)
            {
                ManualSolver = new ManualCaptchaSolver(this);
                connect(ManualSolver,SIGNAL(Used()),this,SLOT(UsedManual()));
                connect(ManualSolver,SIGNAL(Failed()),this,SLOT(FailedManual()));
            }
            return ManualSolver;
        }
        if(name == "antigate")
        {
            if(AntigateSolver == 0)
            {
                AntigateSolver = new AntigateCaptchaSolver(this);
                AntigateSolver->SetServer("http://antigate.com/");
                AntigateSolver->SetSoftId("784");
                AntigateSolver->SetHttpClientFactory(HttpClientFactory);
                connect(AntigateSolver,SIGNAL(Used()),this,SLOT(UsedAntigate()));
                connect(AntigateSolver,SIGNAL(Failed()),this,SLOT(FailedAntigate()));
            }
            return AntigateSolver;
        }
        if(name == "capmonster" || name == "capmonsterimage" || name == "capmonsteraudio")
        {
            if(CapMonsterSolver == 0)
            {
                CapMonsterSolver = new AntigateCaptchaSolver(this);
                CapMonsterSolver->SetServer("");
                CapMonsterSolver->SetMultipleIds(false);
                CapMonsterSolver->SetHttpClientFactory(HttpClientFactory);
                connect(CapMonsterSolver,SIGNAL(Used()),this,SLOT(UsedCapmonster()));
                connect(CapMonsterSolver,SIGNAL(Failed()),this,SLOT(FailedCapmonster()));
            }
            return CapMonsterSolver;
        }
        if(name == "dbc")
        {
            if(DbcSolver == 0)
            {
                DbcSolver = new AntigateCaptchaSolver(this);
                DbcSolver->SetServer("http://api.dbcapi.me/");
                DbcSolver->SetHttpClientFactory(HttpClientFactory);
                connect(DbcSolver,SIGNAL(Used()),this,SLOT(UsedDbc()));
                connect(DbcSolver,SIGNAL(Failed()),this,SLOT(FailedDbc()));
            }
            return DbcSolver;
        }
        if(name == "rucaptcha")
        {
            if(RucaptchaSolver == 0)
            {
                RucaptchaSolver = new AntigateCaptchaSolver(this);
                RucaptchaSolver->SetServer("http://rucaptcha.com/");
                RucaptchaSolver->SetSoftId("1345");
                RucaptchaSolver->SetMultipleIds(false);

                RucaptchaSolver->SetHttpClientFactory(HttpClientFactory);
                connect(RucaptchaSolver,SIGNAL(Used()),this,SLOT(UsedRucaptcha()));
                connect(RucaptchaSolver,SIGNAL(Failed()),this,SLOT(FailedRucaptcha()));
            }
            return RucaptchaSolver;
        }
        if(name == "2captcha")
        {
            if(TwocaptchaSolver == 0)
            {
                TwocaptchaSolver = new AntigateCaptchaSolver(this);
                TwocaptchaSolver->SetServer("http://2captcha.com/");
                TwocaptchaSolver->SetSoftId("1346");
                TwocaptchaSolver->SetMultipleIds(false);
                TwocaptchaSolver->SetHttpClientFactory(HttpClientFactory);
                connect(TwocaptchaSolver,SIGNAL(Used()),this,SLOT(Used2Captcha()));
                connect(TwocaptchaSolver,SIGNAL(Failed()),this,SLOT(Failed2Captcha()));

            }
            return TwocaptchaSolver;
        }
        return 0;
    }


    void SolverFactory::SetHttpClientFactory(IHttpClientFactory * HttpClientFactory)
    {
        this->HttpClientFactory = HttpClientFactory;
    }

    IHttpClientFactory * SolverFactory::GetHttpClientFactory()
    {
        return HttpClientFactory;
    }
}
