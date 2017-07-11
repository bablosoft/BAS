#ifndef RECORDPROCESSCOMMUNICATION_H
#define RECORDPROCESSCOMMUNICATION_H

#include "engine_global.h"

#include <QObject>
#include "irecordprocesscommunication.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT RecordProcessCommunication : public IRecordProcessCommunication
    {
        Q_OBJECT
        IProcessComunicator *Comunicator;
        bool CanSend;
        bool CanSendIsChanged;
        QString SendData;
        QString SendDataSchema;

        QString SendResourcesString;
        QString Window;
        QString ConvertResources(const QList<ResourceDescription>& Resources);
    public:

        explicit RecordProcessCommunication(QObject *parent = 0);

    signals:

    private slots:
        void ReceivedData(const QString& text);
        void SetCanSendDataTrue();
        void SetCanSendDataFalse();
    public slots:
        virtual void SendIsChanged();
        virtual void StopRecorder();
        virtual void SendCode(const QString& Code,const QString& Schema);
        virtual void HighlightAction(const QString& ActionId);
        virtual void SetWindow(const QString& Window);
        virtual void SendResources(const QList<ResourceDescription>& Resources);
        virtual void InstallProcessComunicator(IProcessComunicator *Comunicator);
        virtual void Closed();
        virtual void RestoreOriginalStage();
    };
}

#endif // RECORDPROCESSCOMMUNICATION_H
