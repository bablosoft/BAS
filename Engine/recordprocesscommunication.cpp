#include "recordprocesscommunication.h"
#include "every_cpp.h"
#include <QXmlStreamWriter>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

namespace BrowserAutomationStudioFramework
{
    RecordProcessCommunication::RecordProcessCommunication(QObject *parent) :
        IRecordProcessCommunication(parent)
    {
        Comunicator = 0;
        CanSend = false;
        CanSendIsChanged = false;
    }

    void RecordProcessCommunication::SendIsChanged()
    {
        if(Comunicator && CanSendIsChanged && CanSend)
        {
            CanSendIsChanged = false;
            QString WriteString;
            QXmlStreamWriter xmlWriter(&WriteString);
            xmlWriter.writeTextElement("IsChanged","");
            Comunicator->Send(WriteString);
        }
    }


    QString RecordProcessCommunication::ConvertResources(const QList<IRecordProcessCommunication::ResourceDescription>& Resources)
    {
        QJsonArray array;
        for(ResourceDescription res:Resources)
        {
            QJsonObject obj;
            obj["name"] = res.Name;
            obj["description"] = res.Description;
            array.append(obj);
        }

        QJsonDocument doc;
        doc.setArray(array);
        QString res = doc.toJson();
        return res;
    }

    void RecordProcessCommunication::SendCode(const QString& Code,const QString& Schema)
    {
        if(Comunicator && CanSend)
        {

            QString WriteString;
            QXmlStreamWriter xmlWriter(&WriteString);
            xmlWriter.writeStartElement("SetCode");
            xmlWriter.writeAttribute("Schema", Schema);
            xmlWriter.writeCharacters(Code);

            xmlWriter.writeEndElement();
            Comunicator->Send(WriteString);
            SendData.clear();
            SendDataSchema.clear();
        }else
        {
            SendData = Code;
            SendDataSchema = Schema;
        }
    }

    void RecordProcessCommunication::StopRecorder()
    {
        emit Stop();
    }

    void RecordProcessCommunication::SetWindow(const QString& Window)
    {
        if(Comunicator && CanSend)
        {
            QString WriteString;
            QXmlStreamWriter xmlWriter(&WriteString);
            xmlWriter.writeTextElement("SetWindow",Window);
            Comunicator->Send(WriteString);
            this->Window.clear();
        }else
        {
            this->Window = Window;
        }
    }

    void RecordProcessCommunication::HighlightAction(const QString& ActionId)
    {
        if(Comunicator && CanSend)
        {
            QString WriteString;
            QXmlStreamWriter xmlWriter(&WriteString);
            xmlWriter.writeTextElement("HighlightAction",ActionId);
            Comunicator->Send(WriteString);
        }
    }



    void RecordProcessCommunication::RestoreOriginalStage()
    {
        if(Comunicator && CanSend)
        {
            QString WriteString;
            QXmlStreamWriter xmlWriter(&WriteString);
            xmlWriter.writeTextElement("RestoreOriginalStage","");
            Comunicator->Send(WriteString);
        }
    }

    void RecordProcessCommunication::SendResources(const QList<IRecordProcessCommunication::ResourceDescription>& Resources)
    {
        if(Comunicator && CanSend)
        {
            QString WriteString;
            QXmlStreamWriter xmlWriter(&WriteString);
            xmlWriter.writeTextElement("SetResources",ConvertResources(Resources));
            Comunicator->Send(WriteString);
            SendResourcesString.clear();
        }else
        {
            SendResourcesString = ConvertResources(Resources);
        }

    }

    void RecordProcessCommunication::ReceivedData(const QString& text)
    {
        QXmlStreamReader xmlReader(text);
        while(!xmlReader.atEnd() && !xmlReader.hasError())
        {
            QXmlStreamReader::TokenType token = xmlReader.readNext();

            if(xmlReader.name() == "ReceivedCode" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                bool CanSendIsChangedSaved = CanSendIsChanged;
                CanSendIsChanged = false;
                emit ReceiveCode(xmlReader.text().toString());
                CanSendIsChanged = CanSendIsChangedSaved;
            }
            if(xmlReader.name() == "LoadScript" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                emit LoadScript(xmlReader.text().toString());
            }
            if(xmlReader.name() == "MaximizeWindow" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                emit MaximizeWindow();
            }
            if(xmlReader.name() == "Interrupt" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                emit Interrupt();
            }
            if(xmlReader.name() == "Terminate" && token == QXmlStreamReader::StartElement)
            {
                emit Stop();
                /*if(Comunicator)
                    Comunicator->AbortByUser();*/
            }
            if(xmlReader.name() == "Restart" && token == QXmlStreamReader::StartElement)
            {
                emit NeedRestart();
                emit Stop();
                /*if(Comunicator)
                    Comunicator->AbortByUser();*/
            }
        }
        if (xmlReader.hasError())
        {
            return;
        }
    }

    void RecordProcessCommunication::SetCanSendDataTrue()
    {
        CanSend = true;
        if(!SendData.isEmpty() && Comunicator)
        {
            QString WriteString;
            QXmlStreamWriter xmlWriter(&WriteString);
            xmlWriter.writeStartElement("SetCode");
            xmlWriter.writeAttribute("Schema", SendDataSchema);
            xmlWriter.writeCharacters(SendData);

            xmlWriter.writeEndElement();
            Comunicator->Send(WriteString);
            SendData.clear();
            SendDataSchema.clear();
        }

        if(!SendResourcesString.isEmpty() && Comunicator)
        {
            QString WriteString;
            QXmlStreamWriter xmlWriter(&WriteString);
            xmlWriter.writeTextElement("SetResources",SendResourcesString);
            Comunicator->Send(WriteString);
            SendResourcesString.clear();
        }

        if(!Window.isEmpty() && Comunicator)
        {
            SetWindow(Window);
        }
    }

    void RecordProcessCommunication::SetCanSendDataFalse()
    {
        CanSend = false;
        SendData.clear();
        SendResourcesString.clear();
        Comunicator = 0;
    }

    void RecordProcessCommunication::Closed()
    {
        CanSendIsChanged = false;
    }

    void RecordProcessCommunication::InstallProcessComunicator(IProcessComunicator *Comunicator)
    {
        CanSend = false;
        CanSendIsChanged = true;
        this->Comunicator = Comunicator;
        connect(Comunicator,SIGNAL(Received(QString)),this,SLOT(ReceivedData(QString)));
        connect(Comunicator,SIGNAL(ProcessStarted()),this,SLOT(SetCanSendDataTrue()));
        connect(Comunicator,SIGNAL(ProcessFinished()),this,SLOT(SetCanSendDataFalse()));
    }
}
