#include "subprocessbrowser.h"
#include "iprocesscomunicator.h"
#include "subprocesswebelement.h"
#include <QXmlStreamWriter>
#include <QFile>
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    SubprocessBrowser::SubprocessBrowser(QObject *parent) :
        IBrowser(parent), Worker(0), NetworkAccessManager(0), ProcessComunicator(0), LastInjectedWorker(0)
    {
    }

    void SubprocessBrowser::SetWorkerSettings(IWorkerSettings *WorkerSettings)
    {
        this->WorkerSettings = WorkerSettings;
    }

    IWorkerSettings * SubprocessBrowser::GetWorkerSettings()
    {
        return WorkerSettings;
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
        Worker->SetFailMessage(tr("Timeout during ") + QString("MouseClick"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(MouseClick()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::MouseClickUp(int x, int y, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("MouseClickUp",QString("%1,%2").arg(QString::number(x)).arg(QString::number(y)));

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("MouseClickUp"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(MouseClickUp()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::MouseClickDown(int x, int y, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("MouseClickDown",QString("%1,%2").arg(QString::number(x)).arg(QString::number(y)));

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("MouseClickDown"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(MouseClickDown()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::Timezone(int offset, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("Timezone",QString("%1").arg(QString::number(offset)));

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("Timezone"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(Timezone()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::Geolocation(float latitude, float longitude, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("Geolocation",QString("%1;%2").arg(QString::number(latitude)).arg(QString::number(longitude)));

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("Geolocation"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(Geolocation()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::PopupClose(int index, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("PopupClose",QString("%1").arg(QString::number(index)));

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("PopupClose"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(PopupClose()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::PopupSelect(int index, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("PopupSelect",QString("%1").arg(QString::number(index)));

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("PopupSelect"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(PopupSelect()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::MouseMove(int x, int y, const QString& params, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeStartElement("MouseMove");
            xmlWriter.writeAttribute("params", params);
            xmlWriter.writeCharacters(QString("%1,%2").arg(QString::number(x)).arg(QString::number(y)));
        xmlWriter.writeEndElement();

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("MouseMove"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(MouseMove()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::Scroll(int x, int y, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("Scroll",QString("%1,%2").arg(QString::number(x)).arg(QString::number(y)));

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("scroll"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(Scroll()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::Render(int x, int y, int width, int height, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("Render",QString("%1,%2,%3,%4").arg(QString::number(x)).arg(QString::number(y)).arg(QString::number(width)).arg(QString::number(height)));

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("render"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(Render()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::ClearImageData(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("ClearImageData","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("ClearImageData"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(ClearImageData()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::SetImageData(const QString& base64, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("SetImageData",base64);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("SetImageData"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SetImageData()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::FindImage(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("FindImage","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("FindImage"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(FindImage()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::WaitCode(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("WaitCode","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("WaitCode"));
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
            Worker->SetFailMessage(tr("Timeout during ") + QString("StartSection"));
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
        Worker->SetFailMessage(tr("Timeout during ") + QString("LoadPage ") + url);
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(Loaded()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);

    }

    void SubprocessBrowser::LoadPageInstant(const QString& url, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("Load",url);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("LoadPageInstant ") + url);
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(LoadedInstant()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);

    }

    void SubprocessBrowser::DebugVariablesResult(const QString& data, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("DebugVariablesResult",data);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("DebugVariablesResult"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(DebugVariablesResult()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::SendWorkerSettings(const QString& json, const QString& callback)
    {
        bool NeedRestart;
        bool NeedSend;
        WorkerSettings->Change(json, NeedRestart, NeedSend);

        Worker->GetProcessComunicator()->SetLocation(WorkerSettings->GetWorkerPath());

        Worker->SetAsyncResult(false);
        if(NeedRestart)
        {
            if(Worker->GetProcessComunicator()->HasProcess())
            {
                Worker->SetAsyncResult(true);
                CreateNewBrowser(true,callback);
            }else
            {
                Worker->SetScript(callback);
                Worker->RunSubScript();
            }
        }else if(NeedSend)
        {
            if(Worker->GetProcessComunicator()->HasProcess())
            {
                QString WriteString;
                QXmlStreamWriter xmlWriter(&WriteString);
                xmlWriter.writeStartElement("SendWorkerSettings");
                    xmlWriter.writeAttribute("EncodeUtf8", QString::number(WorkerSettings->GetEncodeUtf8()));
                    xmlWriter.writeAttribute("SkipFrames", QString::number(WorkerSettings->GetSkipFrames()));
                    xmlWriter.writeAttribute("RefreshConnections", QString::number(WorkerSettings->GetRefreshConnections()));
                xmlWriter.writeEndElement();

                Worker->SetScript(callback);
                Worker->SetFailMessage(tr("Timeout during ") + QString("WorkerSettings"));
                Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SendWorkerSettings()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
                qDebug()<<"SendWorkerSettings"<<WriteString;
                if(Worker->GetProcessComunicator())
                    Worker->GetProcessComunicator()->Send(WriteString);
            }else
            {
                Worker->SetScript(callback);
                Worker->RunSubScript();
            }
        }else
        {
            Worker->SetScript(callback);
            Worker->RunSubScript();
        }
    }

    void SubprocessBrowser::SetOpenFileName(const QString & OpenFileName, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("SetOpenFileName",OpenFileName);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("OpenFileName ") + OpenFileName);
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SetOpenFileName()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::SetStartupScript(const QString& script,const QString& script_id,const QString& target, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeStartElement("SetStartupScript");
            xmlWriter.writeAttribute("target", target);
            xmlWriter.writeAttribute("script_id", script_id);
            xmlWriter.writeCharacters(script);
        xmlWriter.writeEndElement();

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("SetStartupScript"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SetStartupScript()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::SetFontList(const QString& fonts, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("SetFontList",fonts);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("SetFontList"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SetFontList()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }


    void SubprocessBrowser::SetPromptResult(const QString & Text, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("SetPromptResult",Text);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("SetPromptResult ") + Text);
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SetPromptResult()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::SetHttpAuthResult(const QString & Login, const QString & Password, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("SetHttpAuthResult",Login + ":" + Password);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("SetHttpAuthResult ") + Login);
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SetHttpAuthResult()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::SetUserAgent(const QString& agent, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("SetUserAgent",agent);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("SetUserAgent"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SetUserAgent()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::Resize(int x, int y, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("Resize",QString::number(x) + "," + QString::number(y));

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("Resize"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(Resize()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::Reset(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("Reset","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("Reset"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(Reset()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::Jquery(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("Jquery","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("Jquery"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(Jquery()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::OptimizeMemory(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("OptimizeMemory","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("OptimizeMemory"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(OptimizeMemory()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::GetCookiesForUrl(const QString& url, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("GetCookiesForUrl",url);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("GetCookiesForUrl ") + url);
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(GetCookiesForUrl()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::SaveCookies(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("SaveCookies", "");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("SaveCookies"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SaveCookies()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::RestoreCookies(const QString& cookies, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("RestoreCookies", cookies);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("RestoreCookies"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(RestoreCookies()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessBrowser::RestoreLocalStorage(const QString& localstorage, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("RestoreLocalStorage", localstorage);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("RestoreLocalStorage"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(RestoreLocalStorage()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
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
        Worker->SetFailMessage(tr("Timeout during ") + QString("GetUrl"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(GetUrl()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
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
            }else if(xmlReader.name() == "SetStartupScript" && token == QXmlStreamReader::StartElement)
            {
                emit SetStartupScript();
            }
            else if(xmlReader.name() == "SetFontList" && token == QXmlStreamReader::StartElement)
            {
                emit SetFontList();
            }
            else if(xmlReader.name() == "SetPromptResult" && token == QXmlStreamReader::StartElement)
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
            }else if(xmlReader.name() == "RestoreLocalStorage" && token == QXmlStreamReader::StartElement)
            {
                emit RestoreLocalStorage();
            }else if(xmlReader.name() == "MouseClick" && token == QXmlStreamReader::StartElement)
            {
                emit MouseClick();
            }else if(xmlReader.name() == "MouseClickUp" && token == QXmlStreamReader::StartElement)
            {
                emit MouseClickUp();
            }else if(xmlReader.name() == "MouseClickDown" && token == QXmlStreamReader::StartElement)
            {
                emit MouseClickDown();
            }else if(xmlReader.name() == "LoadedInstant" && token == QXmlStreamReader::StartElement)
            {
                emit LoadedInstant();
            }else if(xmlReader.name() == "Timezone" && token == QXmlStreamReader::StartElement)
            {
                emit Timezone();
            }else if(xmlReader.name() == "Geolocation" && token == QXmlStreamReader::StartElement)
            {
                emit Geolocation();
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
            }else if(xmlReader.name() == "DebugVariablesResult" && token == QXmlStreamReader::StartElement)
            {
                emit DebugVariablesResult();
            }else if(xmlReader.name() == "SendWorkerSettings" && token == QXmlStreamReader::StartElement)
            {
                emit SendWorkerSettings();
            }
            else if(xmlReader.name() == "OptimizeMemory" && token == QXmlStreamReader::StartElement)
            {
                emit OptimizeMemory();
            }
            else if(xmlReader.name() == "ClearImageData" && token == QXmlStreamReader::StartElement)
            {
                emit OptimizeMemory();
            }
            else if(xmlReader.name() == "SetImageData" && token == QXmlStreamReader::StartElement)
            {
                emit SetImageData();
            }
            else if(xmlReader.name() == "FindImage" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                Worker->SetAsyncResult(QScriptValue(xmlReader.text().toString()));
                emit FindImage();
            }
            else if(xmlReader.name() == "PopupClose" && token == QXmlStreamReader::StartElement)
            {
                emit PopupClose();
            }
            else if(xmlReader.name() == "PopupSelect" && token == QXmlStreamReader::StartElement)
            {
                emit PopupSelect();
            }else if(xmlReader.name() == "WaitCode" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                QString code = xmlReader.text().toString();
                NextAction.clear();
                QRegExp Regexp("section\\_start\\(\\s*\\\"[^\\\"]*\\\"\\s*\\,\\s*(\\-?\\d*)\\)\\!");
                if(Regexp.indexIn(code, 0)>=0)
                    NextAction = Regexp.cap(1);
                QString Script = Worker->GetPreprocessor()->Preprocess(QString(" { ") + code + QString(" } "),0);
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

    void SubprocessBrowser::SetLanguage(const QString& Language)
    {
        this->Language = Language;
    }

    void SubprocessBrowser::CloseBrowser()
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("CloseBrowser","");
        Worker->GetProcessComunicator()->Abort();
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->setProperty("empty",true);
    }


    void SubprocessBrowser::CreateNewBrowser(bool ForseNewBrowserCreation, const QString& callback)
    {
        {
            QFile settings("settings_worker.ini");
            if (settings.open(QFile::ReadOnly | QFile::Text))
            {
                QTextStream in(&settings);
                QString file_string = in.readAll();

                if(file_string.contains("Restart=true"))
                    ForseNewBrowserCreation = true;
                qDebug()<<file_string<<ForseNewBrowserCreation;
            }
            settings.close();
        }

        bool CreateNewBrowser = ForseNewBrowserCreation || !ProcessComunicator || ProcessComunicator->property("empty").toBool();
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
        if(CreateNewBrowser || NumberUsed > 10)
        {
            OnSupend();

            Worker->SetProcessComunicator(ProcessComunicatorFactory->CreateProcessComunicator());
            ProcessComunicator = Worker->GetProcessComunicator();
            Worker->GetProcessComunicator()->setParent(this);
            Worker->GetProcessComunicator()->SetLocation(WorkerSettings->GetWorkerPath());


            NetworkAccessManager = NetworkAccessManagerFactory->CreateNetworkAccessManager();
            connect(Worker->GetProcessComunicator(),SIGNAL(Received(QString)),NetworkAccessManager,SLOT(Received(QString)));
            NetworkAccessManager->setParent(Worker->GetProcessComunicator());
            
            //connect(Worker->GetProcessComunicator(),SIGNAL(ProcessFinished()),this,SLOT(WorkerStopped()));
            //connect(Worker->GetProcessComunicator(),SIGNAL(Error()),this,SLOT(WorkerStopped()));

            connect(Worker->GetProcessComunicator(),SIGNAL(Received(QString)),this,SLOT(Received(QString)));
            Worker->SetFailMessage(QString("Timeout during creating new process"));
            Worker->GetWaiter()->WaitForSignal(Worker->GetProcessComunicator(),SIGNAL(ProcessStarted()),Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
            Worker->SetScript(callback);
            QStringList arg;
            arg.append(Language);
            arg += WorkerSettings->GetCommandLineParameters();
            Worker->GetProcessComunicator()->CreateProcess(arg);
            if(!NextAction.isEmpty())
            {
                Worker->GetProcessComunicator()->Send(QString("<SetNextAction>") + NextAction + QString("</SetNextAction>"));
            }
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

    void SubprocessBrowser::SimulateCrush(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("Crush","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("Crush"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(Crush()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        if(Worker->GetProcessComunicator())
            Worker->GetProcessComunicator()->Send(WriteString);
    }
}
