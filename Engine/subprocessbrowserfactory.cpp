#include "subprocessbrowserfactory.h"
#include "subprocessbrowser.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    SubprocessBrowserFactory::SubprocessBrowserFactory(QObject *parent) :
        IBrowserFactory(parent)
    {
        Widget = new SubprocessListWidget();
        Language = "en";
    }

    QWidget *SubprocessBrowserFactory::GetWidget(bool AutoStart)
    {
        Widget->SetAutoStart(AutoStart);
        return Widget;
    }

    void SubprocessBrowserFactory::ClearAll()
    {
        foreach(IBrowser* b,BrowserList)
            b->deleteLater();

        BrowserList.clear();
        BrowserListUnused.clear();
        Widget->Clear();
    }

    void SubprocessBrowserFactory::Clear(QList<IBrowser*>* Browsers)
    {
        for(IBrowser *Browser:*Browsers)
        {
            if(!BrowserListUnused.contains(Browser))
                BrowserListUnused.append(Browser);
        }
    }


    QList<IBrowser*> SubprocessBrowserFactory::Create(int size)
    {
        QList<IBrowser*> res;

        for(int i = 0;i<size;i++)
        {
            if(!BrowserListUnused.empty())
            {
                res.append(BrowserListUnused.first());
                BrowserListUnused.removeFirst();
                continue;
            }
            SubprocessBrowser * o = new SubprocessBrowser(this);
            o->SetLanguage(Language);
            connect(o,SIGNAL(ProcessCreated(IProcessComunicator*)), this, SLOT(ProcessCreated(IProcessComunicator*)));
            o->SetNetworkAccessManagerFactory(NetworkAccessManagerFactory);
            o->SetProcessComunicatorFactory(ProcessComunicatorFactory);
            BrowserList.append(o);
            res.append(o);
        }
        return res;
    }

    void SubprocessBrowserFactory::SetLanguage(const QString & Language)
    {
        this->Language = Language;
    }

    void SubprocessBrowserFactory::ProcessCreated(IProcessComunicator* Comunicator)
    {
        emit OnBrowserCreated();
        int index = BrowserList.indexOf(qobject_cast<IBrowser*>(sender()));
        Widget->Add(Comunicator,index);
    }


    void SubprocessBrowserFactory::SetNetworkAccessManager(INetworkAccessManagerFactory *NetworkAccessManagerFactory)
    {
        this->NetworkAccessManagerFactory = NetworkAccessManagerFactory;
    }

    INetworkAccessManagerFactory * SubprocessBrowserFactory::GetNetworkAccessManager()
    {
        return NetworkAccessManagerFactory;
    }

    void SubprocessBrowserFactory::SetProcessComunicatorFactory(IProcessComunicatorFactory *ProcessComunicatorFactory)
    {
        this->ProcessComunicatorFactory = ProcessComunicatorFactory;
    }

    IProcessComunicatorFactory * SubprocessBrowserFactory::GetProcessComunicatorFactory()
    {
        return ProcessComunicatorFactory;
    }

}
