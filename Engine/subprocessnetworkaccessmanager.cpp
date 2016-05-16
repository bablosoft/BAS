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
            }


        }
        if (xmlReader.hasError())
        {
            return;
        }
    }

    void SubprocessNetworkAccessManager::AddHeader(const QString& name,const QString& value, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeStartElement("AddHeader");
            xmlWriter.writeAttribute("name", name);
            xmlWriter.writeAttribute("value", value);
        xmlWriter.writeEndElement();


        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during AddHeader"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(AddHeader()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::CleanHeader(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("CleanHeader","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during CleanHeader"));
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

    void SubprocessNetworkAccessManager::SetProxy(const QString& server, int Port, bool IsHttp, const QString& name, const QString& password, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeStartElement("SetProxy");
            xmlWriter.writeAttribute("server",server);
            xmlWriter.writeAttribute("Port",QString::number(Port));
            xmlWriter.writeAttribute("IsHttp",QString::number(IsHttp));
            xmlWriter.writeAttribute("name",name);
            xmlWriter.writeAttribute("password",password);
        xmlWriter.writeEndElement();

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during SetProxy"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(SetProxy()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::AddCacheMaskAllow(const QString& Mask, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("AddCacheMaskAllow",Mask);

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during AddCacheMaskAllow"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(AddCacheMaskAllow()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::AddCacheMaskDeny(const QString& Mask, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("AddCacheMaskDeny",Mask);

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during AddCacheMaskDeny"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(AddCacheMaskDeny()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::AddRequestMaskAllow(const QString& Mask, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("AddRequestMaskAllow",Mask);

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during AddRequestMaskAllow"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(AddRequestMaskAllow()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::AddRequestMaskDeny(const QString& Mask, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("AddRequestMaskDeny",Mask);

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during AddRequestMaskDeny"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(AddRequestMaskDeny()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::ClearCacheMask(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("ClearCacheMask","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during ClearCacheMask"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(ClearCacheMask()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::ClearRequestMask(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("ClearRequestMask","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during ClearRequestMask"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(ClearRequestMask()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::ClearLoadedUrl(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("ClearLoadedUrl","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during ClearLoadedUrl"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(ClearLoadedUrl()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::ClearCachedData(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("ClearCachedData","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during ClearCachedData"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(ClearCachedData()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::ClearAll(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("ClearAll","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during ClearAll"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(ClearAll()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::ClearMasks(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("ClearMasks","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during ClearMasks"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(ClearMasks()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }
    void SubprocessNetworkAccessManager::ClearData(const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("ClearData","");

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during ClearData"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(ClearData()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }


    void SubprocessNetworkAccessManager::FindCacheByMaskBase64(const QString& Mask, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("FindCacheByMaskBase64",Mask);

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during FindCacheByMaskBase64"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(FindCacheByMaskBase64()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::FindStatusByMask(const QString& Mask, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("FindStatusByMask",Mask);

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during FindStatusByMask"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(FindStatusByMask()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::FindCacheByMaskString(const QString& Mask, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("FindCacheByMaskString",Mask);

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during FindCacheByMaskString"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(FindCacheByMaskString()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    void SubprocessNetworkAccessManager::IsUrlLoadedByMask(const QString& Mask, const QString& callback)
    {
        QString WriteString;
        QXmlStreamWriter xmlWriter(&WriteString);
        xmlWriter.writeTextElement("IsUrlLoadedByMask",Mask);

        Worker->SetScript(callback);
        Worker->SetFailMessage(QString("Timeout during IsUrlLoadedByMask"));
        Worker->GetWaiter()->WaitForSignal(this,SIGNAL(IsUrlLoadedByMask()), Worker,SLOT(RunSubScript()), Worker, SLOT(FailBecauseOfTimeout()));
        Worker->GetProcessComunicator()->Send(WriteString);
    }

    QNetworkAccessManager *SubprocessNetworkAccessManager::GetNetworkAccessManager()
    {
        return 0;
    }
}
