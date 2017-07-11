#ifndef IRECORDPROCESSCOMMUNICATION_H
#define IRECORDPROCESSCOMMUNICATION_H

#include "engine_global.h"

#include <QObject>
#include <QList>
#include "iprocesscomunicator.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IRecordProcessCommunication : public QObject
    {
        Q_OBJECT
    public:
        struct ResourceDescription
        {
          QString Name;
          QString Description;
        };
        explicit IRecordProcessCommunication(QObject *parent = 0);
    signals:
        void ReceiveCode(QString Code);
        void LoadScript(QString FileName);
        void NeedRestart();
        void Interrupt();
        void Stop();
        void MaximizeWindow();
    public slots:
        virtual void SendIsChanged() = 0;
        virtual void StopRecorder() = 0;
        virtual void SendCode(const QString& Code,const QString& Schema) = 0;
        virtual void HighlightAction(const QString& ActionId) = 0;
        virtual void SendResources(const QList<ResourceDescription>& Resources) = 0;
        virtual void SetWindow(const QString& Window) = 0;
        virtual void InstallProcessComunicator(IProcessComunicator *Comunicator) = 0;
        virtual void Closed() = 0;
        virtual void RestoreOriginalStage() = 0;

    };
}

#endif // IRECORDPROCESSCOMMUNICATION_H
