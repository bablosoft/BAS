#include "solverfactory.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    SolverFactory::SolverFactory(QObject *parent) :
        ISolverFactory(parent),ManualSolver(0),AntigateSolver(0), DbcSolver(0)
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


    ISolver* SolverFactory::GetSolver(const QString& name)
    {
        if(name == "manual")
        {
            if(ManualSolver == 0)
            {
                ManualSolver = new ManualCaptchaSolver(this);
                connect(ManualSolver,SIGNAL(Used()),this,SLOT(UsedManual()));
            }
            return ManualSolver;
        }
        if(name == "antigate")
        {
            if(AntigateSolver == 0)
            {
                AntigateSolver = new AntigateCaptchaSolver(this);
                AntigateSolver->SetServer("http://antigate.com/");
                AntigateSolver->SetHttpClientFactory(HttpClientFactory);
                connect(AntigateSolver,SIGNAL(Used()),this,SLOT(UsedAntigate()));
            }
            return AntigateSolver;
        }
        if(name == "dbc")
        {
            if(DbcSolver == 0)
            {
                DbcSolver = new AntigateCaptchaSolver(this);
                DbcSolver->SetServer("http://api.dbcapi.me/");
                DbcSolver->SetHttpClientFactory(HttpClientFactory);
                connect(DbcSolver,SIGNAL(Used()),this,SLOT(UsedDbc()));
            }
            return DbcSolver;
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
