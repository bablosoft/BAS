#include "subprocessbrowser.h"
#include "iprocesscomunicator.h"
#include "subprocesswebelement.h"
#include <QXmlStreamWriter>
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    SubprocessBrowser::SubprocessBrowser(QObject *parent) :
        IBrowser(parent), Worker(0), NetworkAccessManager(0), ProcessComunicator(0), LastInjectedWorker(0)
    {
    }

    void SubprocessBrowser::MouseClickInstant(int x, int y)
    {

    }

    void SubprocessBrowser::MouseClick(int x, int y, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("MouseClick",QString("%1,%2").arg(QString::number(x)).arg(QString::number(y)));

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during MouseClick"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(MouseClick()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::MouseMove(int x, int y, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("MouseMove",QString("%1,%2").arg(QString::number(x)).arg(QString::number(y)));

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during MouseMove"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(MouseMove()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::Scroll(int x, int y, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("Scroll",QString("%1,%2").arg(QString::number(x)).arg(QString::number(y)));

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during scroll"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(Scroll()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::Render(int x, int y, int width, int height, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("Render",QString("%1,%2,%3,%4").arg(QString::number(x)).arg(QString::number(y)).arg(QString::number(width)).arg(QString::number(height)));

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during render"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(Render()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::WaitCode(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("WaitCode","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during WaitCode"));
        Worker->GetWaiter()->WaitInfinity(this,SIGNAL(WaitCode()),Worker,SLOT(RunSubScript()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::StartSection(const QString& Name, int Id, const QString& callback)
    {
        if(Id)
        {
            QString WriteString;
            QXmlStreamWriter xmlWriter(&WriteString);
            xmlWriter.writeTextElement("StartSection",QString("%1").arg(QString::number(Id)));

            Worker->SetScript(callback);
            Worker->SetFailMessage(QString("Timeout during StartSection"));
            Worker->GetWaiter()->WaitInfinity(this,SIGNAL(WaitCode()), Worker,SLOT(RunSubScript()));
            if(Worker->GetProcessComunicator())
                Worker->GetProcessComunicator()->Send(WriteString);
        }else
        {
            Worker->SetScript(callback);
            Worker->RunSubScript();
        }

    }


    void SubprocessBrowser::LoadPage(const QString& url, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("Load",url);

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during LoadPage ") + url);
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(Loaded()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);

    }

    void SubprocessBrowser::SetOpenFileName(const QString & OpenFileName, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("SetOpenFileName",OpenFileName);

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during OpenFileName ") + OpenFileName);
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SetOpenFileName()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::SetPromptResult(const QString & Text, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("SetPromptResult",Text);

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during SetPromptResult ") + Text);
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SetPromptResult()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::SetHttpAuthResult(const QString & Login, const QString & Password, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("SetHttpAuthResult",Login + ":" + Password);

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during SetHttpAuthResult ") + Login);
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SetHttpAuthResult()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::SetUserAgent(const QString& agent, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("SetUserAgent",agent);

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during SetUserAgent"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SetUserAgent()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::Resize(int x, int y, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("Resize",QString::number(x) + "," + QString::number(y));

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during Resize"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(Resize()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::Reset(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("Reset","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during Reset"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(Reset()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::Jquery(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("Jquery","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during Jquery"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(Jquery()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::OptimizeMemory(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("OptimizeMemory","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during OptimizeMemory"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(OptimizeMemory()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::GetCookiesForUrl(const QString& url, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("GetCookiesForUrl",url);

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during GetCookiesForUrl ") + url);
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(GetCookiesForUrl()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::SaveCookies(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("SaveCookies", "");

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during SaveCookies"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SaveCookies()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::RestoreCookies(const QString& cookies, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("RestoreCookies", cookies);

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during RestoreCookies"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(RestoreCookies()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }


    IWebElement* SubprocessBrowser::GetRootElement()
    {
         SubprocessWebElement *el = new SubprocessWebElement();
         connect(Worker->GetProcessComunicator(),SIGNAL(Received(QString)),el,SLOT(Received(QString)));
         return el;
    }
    void SubprocessBrowser::GetUrl(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("GetUrl","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during GetUrl"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(GetUrl()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::Received(const QString& value)
    {

        QXmlStreamReader xmlReader(value);
        while(!xmlReader.atEnd() && !xmlReader.hasError())
        {
            if(!Worker)
                return;

            QXmlStreamReader::TokenType token = xmlReader.readNext();

            if(xmlReader.name() == "Load" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                Worker->SetAsyncResult(QScriptValue(xmlReader.text().toString().toInt() == 0));
                emit Loaded();
            }else if(xmlReader.name() == "GetUrl" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                Worker->SetAsyncResult(QScriptValue(xmlReader.text().toString()));
                emit GetUrl();
            }else if(xmlReader.name() == "SetUserAgent" && token == QXmlStreamReader::StartElement)
            {
                emit SetUserAgent();
            }else if(xmlReader.name() == "SetOpenFileName" && token == QXmlStreamReader::StartElement)
            {
                emit SetOpenFileName();
            }else if(xmlReader.name() == "SetPromptResult" && token == QXmlStreamReader::StartElement)
            {
                emit SetPromptResult();
            }
            else if(xmlReader.name() == "SetHttpAuthResult" && token == QXmlStreamReader::StartElement)
            {
                emit SetHttpAuthResult();
            }
            else if(xmlReader.name() == "GetCookiesForUrl" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                Worker->SetAsyncResult(QScriptValue(xmlReader.text().toString()));
                emit GetCookiesForUrl();
            }else if(xmlReader.name() == "SaveCookies" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                Worker->SetAsyncResult(QScriptValue(xmlReader.text().toString()));
                emit SaveCookies();
            }else if(xmlReader.name() == "RestoreCookies" && token == QXmlStreamReader::StartElement)
            {
                emit RestoreCookies();
            }else if(xmlReader.name() == "MouseClick" && token == QXmlStreamReader::StartElement)
            {
                emit MouseClick();
            }else if(xmlReader.name() == "MouseMove" && token == QXmlStreamReader::StartElement)
            {
                emit MouseMove();
            }else if(xmlReader.name() == "Resize" && token == QXmlStreamReader::StartElement)
            {
                emit Resize();
            }else if(xmlReader.name() == "Reset" && token == QXmlStreamReader::StartElement)
            {
                emit Reset();
            }else if(xmlReader.name() == "Render" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                Worker->SetAsyncResult(QScriptValue(xmlReader.text().toString()));
                emit Render();
            }else if(xmlReader.name() == "Scroll" && token == QXmlStreamReader::StartElement)
            {
                emit Scroll();
            }else if(xmlReader.name() == "Jquery" && token == QXmlStreamReader::StartElement)
            {
                emit Jquery();
            }else if(xmlReader.name() == "OptimizeMemory" && token == QXmlStreamReader::StartElement)
            {
                emit OptimizeMemory();
            }else if(xmlReader.name() == "WaitCode" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                QString Script = Worker->GetPreprocessor()->Preprocess(QString(" { ") + xmlReader.text().toString() + QString(" } "),0);
                Worker->SetScript(Script);
                emit WaitCode();
            }
        }
        if (xmlReader.hasError())
        {
            return;
        }
    }

    void SubprocessBrowser::OnSupend()
    {
        if(Worker && Worker->GetProcessComunicator())
        {
            Worker->GetProcessComunicator()->Suspend();
            Worker->GetProcessComunicator()->disconnect();
            Worker->GetProcessComunicator()->deleteLater();

        }else if(ProcessComunicator)
        {
            ProcessComunicator->Suspend();
            ProcessComunicator->disconnect();
            ProcessComunicator->deleteLater();
        }
        ProcessComunicator = 0;

        if(Worker)
        {
            Worker->SetProcessComunicator(0);
        }
    }

    void SubprocessBrowser::WorkerStopped()
    {
        OnSupend();

        if(Worker)
        {
            Worker->FailProcessFinished();
        }
    }

    void SubprocessBrowser::MarkBeforeReset()
    {
        if(ProcessComunicator)
        {
            ProcessComunicator->setProperty("mbr",QVariant(true));
        }
    }

    void SubprocessBrowser::MarkAfterReset()
    {
        if(ProcessComunicator)
        {
            ProcessComunicator->setProperty("mbr",QVariant(false));
        }
    }

    void SubprocessBrowser::CreateNewBrowser(bool ForseNewBrowserCreation, const QString& callback)
    {
        bool CreateNewBrowser = ForseNewBrowserCreation || !ProcessComunicator;
        if(LastInjectedWorker == Worker && !CreateNewBrowser)
        {
            Worker->SetScript(callback);
            Worker->RunSubScript();
            return;
        }

        LastInjectedWorker = Worker;
        int NumberUsed = 0;
        if(ProcessComunicator)
        {
            QVariant NumberUsedVariant = ProcessComunicator->property("used");
            if(NumberUsedVariant.isValid() && !NumberUsedVariant.isNull())
                NumberUsed = NumberUsedVariant.toInt();
            if(NumberUsed<0)
                NumberUsed = 0;

            NumberUsed++;

            ProcessComunicator->setProperty("used",QVariant(NumberUsed));
            QVariant mbr = ProcessComunicator->property("mbr");
            if(!mbr.isNull() && mbr.isValid() && mbr.toBool())
            {
                NumberUsed = 1000;
            }
        }

        //Create process first time
        if(CreateNewBrowser || NumberUsed > 100)
        {
            OnSupend();

            Worker->SetProcessComunicator(ProcessComunicatorFactory->CreateProcessComunicator());
            ProcessComunicator = Worker->GetProcessComunicator();
            Worker->GetProcessComunicator()->setParent(this);

            NetworkAccessManager = NetworkAccessManagerFactory->CreateNetworkAccessManager();
            connect(Worker->GetProcessComunicator(),SIGNAL(Received(QString)),NetworkAccessManager,SLOT(Received(QString)));
            NetworkAccessManager->setParent(Worker->GetProcessComunicator());
            
            connect(Worker->GetProcessComunicator(),SIGNAL(ProcessFinished()),this,SLOT(WorkerStopped()));
            connect(Worker->GetProcessComunicator(),SIGNAL(Error()),this,SLOT(WorkerStopped()));

            connect(Worker->GetProcessComunicator(),SIGNAL(Received(QString)),this,SLOT(Received(QString)));
            Worker->SetFailMessage(QString("Timeout during creating new process"));
            Worker->GetWaiter()->WaitForSignal(Worker->GetProcessComunicator(),SIGNAL(ProcessStarted()),Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
            Worker->SetScript(callback);
            Worker->GetProcessComunicator()->CreateProcess();
            emit ProcessCreated(ProcessComunicator);
        }
        //Use existing process
        else
        {
            Worker->SetProcessComunicator(ProcessComunicator);


            disconnect(Worker->GetProcessComunicator(),SIGNAL(Received(QString)),0,0);

            connect(Worker->GetProcessComunicator(),SIGNAL(Received(QString)),this,SLOT(Received(QString)));
            connect(Worker->GetProcessComunicator(),SIGNAL(Received(QString)),NetworkAccessManager,SLOT(Received(QString)));
            
            Worker->SetScript(callback);
            Worker->RunSubScript();
        }
    }
    INetworkAccessManager* SubprocessBrowser::GetNetworkAccessManager()
    {
        return NetworkAccessManager;
    }
    void SubprocessBrowser::SetScriptResources(IScriptResources* ScriptResources)
    {

    }
    IScriptResources* SubprocessBrowser::GetScriptResources()
    {
        return 0;
    }
    void SubprocessBrowser::SetWorker(IWorker* Worker)
    {
        this->Worker = Worker;
    }


    IWorker* SubprocessBrowser::GetWorker()
    {
        return Worker;
    }
    void SubprocessBrowser::SetNetworkAccessManagerFactory(INetworkAccessManagerFactory *NetworkAccessManagerFactory)
    {
        this->NetworkAccessManagerFactory = NetworkAccessManagerFactory;
    }

    void SubprocessBrowser::SetProcessComunicatorFactory(IProcessComunicatorFactory *ProcessComunicatorFactory)
    {
        this->ProcessComunicatorFactory = ProcessComunicatorFactory;
    }
}
