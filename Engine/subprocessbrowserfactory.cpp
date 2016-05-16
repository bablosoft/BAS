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

    void SubprocessBrowserFactory::Clear()
    {
        foreach(IBrowser* b,BrowserList)
            b->deleteLater();

        BrowserList.clear();
        Widget->Clear();
    }

    QList<IBrowser*> SubprocessBrowserFactory::Create(int size)
    {
        Clear();
        for(int i = 0;i<size;i++)
        {
            SubprocessBrowser * o = new SubprocessBrowser(this);
            connect(o,SIGNAL(ProcessCreated(IProcessComunicator*)), this, SLOT(ProcessCreated(IProcessComunicator*)));
            o->SetNetworkAccessManagerFactory(NetworkAccessManagerFactory);
            o->SetProcessComunicatorFactory(ProcessComunicatorFactory);
            BrowserList.append(o);
        }
        return BrowserList;
    }

    void SubprocessBrowserFactory::SetLanguage(const QString & Language)
    {
        this->Language = Language;
    }

    void SubprocessBrowserFactory::ProcessCreated(IProcessComunicator* Comunicator)
    {
        emit OnBrowserCreated();
        int index = BrowserList.indexOf(qobject_cast<IBrowser*>(sender()));
        Comunicator->Send(QString("<SetInitialState>") + QString("%1,%2").arg(Language).arg(QString::number(index)) + QString("</SetInitialState>"));
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
