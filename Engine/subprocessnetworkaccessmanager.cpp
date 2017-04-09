#include "subprocessnetworkaccessmanager.h"
#include <QXmlStreamWriter>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    SubprocessNetworkAccessManager::SubprocessNetworkAccessManager(QObject *parent) :
        INetworkAccessManager(parent)
    {

    }



    void SubprocessNetworkAccessManager::Received(const QString& value)
    {
        QXmlStreamReader xmlReader(value);
        while(!xmlReader.atEnd() && !xmlReader.hasError())
        {
            QXmlStreamReader::TokenType token = xmlReader.readNext();


            if(xmlReader.name() == "AddCacheMaskAllow" && token == QXmlStreamReader::StartElement)
            {
                emit AddCacheMaskAllow();
            }else if(xmlReader.name() == "SetProxy" && token == QXmlStreamReader::StartElement)
            {
                emit SetProxy();
            }else if(xmlReader.name() == "AddHeader" && token == QXmlStreamReader::StartElement)
            {
                emit AddHeader();
            }else if(xmlReader.name() == "SetHeaderList" && token == QXmlStreamReader::StartElement)
            {
                emit SetHeaderList();
            }else if(xmlReader.name() == "CleanHeader" && token == QXmlStreamReader::StartElement)
            {
                emit CleanHeader();
            }else if(xmlReader.name() == "AddCacheMaskDeny" && token == QXmlStreamReader::StartElement)
            {
                emit AddCacheMaskDeny();
            }else if(xmlReader.name() == "AddRequestMaskAllow" && token == QXmlStreamReader::StartElement)
            {
                emit AddRequestMaskAllow();
            }else if(xmlReader.name() == "AddRequestMaskDeny" && token == QXmlStreamReader::StartElement)
            {
                emit AddRequestMaskDeny();
            }else if(xmlReader.name() == "ClearCacheMask" && token == QXmlStreamReader::StartElement)
            {
                emit ClearCacheMask();
            }else if(xmlReader.name() == "ClearRequestMask" && token == QXmlStreamReader::StartElement)
            {
                emit ClearRequestMask();
            }else if(xmlReader.name() == "ClearLoadedUrl" && token == QXmlStreamReader::StartElement)
            {
                emit ClearLoadedUrl();
            }else if(xmlReader.name() == "ClearCachedData" && token == QXmlStreamReader::StartElement)
            {
                emit ClearCachedData();
            }else if(xmlReader.name() == "ClearAll" && token == QXmlStreamReader::StartElement)
            {
                emit ClearAll();
            }else if(xmlReader.name() == "ClearMasks" && token == QXmlStreamReader::StartElement)
            {
                emit ClearMasks();
            }else if(xmlReader.name() == "ClearData" && token == QXmlStreamReader::StartElement)
            {
                emit ClearData();
            }else if(xmlReader.name() == "AllowPopups" && token == QXmlStreamReader::StartElement)
            {
                emit AllowPopups();
            }else if(xmlReader.name() == "RestrictPopups" && token == QXmlStreamReader::StartElement)
            {
                emit RestrictPopups();
            }else if(xmlReader.name() == "AllowDownloads" && token == QXmlStreamReader::StartElement)
            {
                emit AllowDownloads();
            }else if(xmlReader.name() == "RestrictDownloads" && token == QXmlStreamReader::StartElement)
            {
                emit RestrictDownloads();
            }else if(xmlReader.name() == "FindCacheByMaskBase64" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                Worker->SetAsyncResult(QScriptValue(xmlReader.text().toString()));
                emit FindCacheByMaskBase64();
            }else if(xmlReader.name() == "FindCacheByMaskString" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                Worker->SetAsyncResult(QScriptValue(xmlReader.text().toString()));
                emit FindCacheByMaskString();
            }else if(xmlReader.name() == "FindStatusByMask" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                Worker->SetAsyncResult(QScriptValue(xmlReader.text().toInt()));
                emit FindStatusByMask();
            }else if(xmlReader.name() == "IsUrlLoadedByMask" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                Worker->SetAsyncResult(QScriptValue(xmlReader.text().toString().toInt()));
                emit IsUrlLoadedByMask();
            }else if(xmlReader.name() == "GetLoadStats" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                Worker->SetAsyncResult(QScriptValue(xmlReader.text().toString()));
                emit GetLoadStats();
            }


        }
        if (xmlReader.hasError())
        {
            return;
        }
    }

    void SubprocessNetworkAccessManager::AddHeader(const QString& name,const QString& value,const QString& target, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeStartElement("AddHeader");
            xmlWriter.writeAttribute("name", name);
            xmlWriter.writeAttribute("value", value);
            xmlWriter.writeAttribute("target", target);
        xmlWriter.writeEndElement();


        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("AddHeader"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(AddHeader()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::SetHeaderList(const QString& json,const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeStartElement("SetHeaderList");
            xmlWriter.writeAttribute("json", json);
        xmlWriter.writeEndElement();


        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("SetHeaderList"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SetHeaderList()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::CleanHeader(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("CleanHeader","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("CleanHeader"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(CleanHeader()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::SetWorker(IWorker *Worker)
    {
        this->Worker = Worker;
    }
    IWorker * SubprocessNetworkAccessManager::GetWorker()
    {
        return Worker;
    }

    void SubprocessNetworkAccessManager::SetProxy(const QString& server, int Port, bool IsHttp, const QString& name, const QString& password,const QString& target, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeStartElement("SetProxy");
            xmlWriter.writeAttribute("server",server);
            xmlWriter.writeAttribute("Port",QString::number(Port));
            xmlWriter.writeAttribute("IsHttp",QString::number(IsHttp));
            xmlWriter.writeAttribute("name",name);
            xmlWriter.writeAttribute("password",password);
            xmlWriter.writeAttribute("target", target);
        xmlWriter.writeEndElement();

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("SetProxy"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SetProxy()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::AddCacheMaskAllow(const QString& Mask, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("AddCacheMaskAllow",Mask);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("AddCacheMaskAllow"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(AddCacheMaskAllow()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::AddCacheMaskDeny(const QString& Mask, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("AddCacheMaskDeny",Mask);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("AddCacheMaskDeny"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(AddCacheMaskDeny()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::AddRequestMaskAllow(const QString& Mask, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("AddRequestMaskAllow",Mask);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("AddRequestMaskAllow"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(AddRequestMaskAllow()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::AddRequestMaskDeny(const QString& Mask, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("AddRequestMaskDeny",Mask);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("AddRequestMaskDeny"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(AddRequestMaskDeny()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::ClearCacheMask(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("ClearCacheMask","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("ClearCacheMask"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(ClearCacheMask()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::ClearRequestMask(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("ClearRequestMask","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("ClearRequestMask"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(ClearRequestMask()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::ClearLoadedUrl(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("ClearLoadedUrl","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("ClearLoadedUrl"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(ClearLoadedUrl()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::ClearCachedData(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("ClearCachedData","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("ClearCachedData"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(ClearCachedData()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::ClearAll(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("ClearAll","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("ClearAll"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(ClearAll()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::ClearMasks(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("ClearMasks","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("ClearMasks"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(ClearMasks()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::ClearData(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("ClearData","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("ClearData"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(ClearData()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::RestrictPopups(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("RestrictPopups","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("RestrictPopups"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(RestrictPopups()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::AllowPopups(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("AllowPopups","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("AllowPopups"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(AllowPopups()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::RestrictDownloads(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("RestrictDownloads","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("RestrictDownloads"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(RestrictDownloads()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::AllowDownloads(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("AllowDownloads","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("AllowDownloads"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(AllowDownloads()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }


    void SubprocessNetworkAccessManager::FindCacheByMaskBase64(const QString& Mask, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("FindCacheByMaskBase64",Mask);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("FindCacheByMaskBase64"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(FindCacheByMaskBase64()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::FindStatusByMask(const QString& Mask, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("FindStatusByMask",Mask);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("FindStatusByMask"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(FindStatusByMask()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::FindCacheByMaskString(const QString& Mask, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("FindCacheByMaskString",Mask);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("FindCacheByMaskString"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(FindCacheByMaskString()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::IsUrlLoadedByMask(const QString& Mask, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("IsUrlLoadedByMask",Mask);

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("IsUrlLoadedByMask"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(IsUrlLoadedByMask()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::GetLoadStats(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("GetLoadStats","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(tr("Timeout during ") + QString("GetLoadStats"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(GetLoadStats()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    QNetworkAccessManager *SubprocessNetworkAccessManager::GetNetworkAccessManager()
    {
        return 0;
    }
}
