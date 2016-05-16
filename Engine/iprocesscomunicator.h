#ifndef IPROCESSCOMUNICATOR_H
#define IPROCESSCOMUNICATOR_H
#include "engine_global.h"

#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IProcessComunicator : public QObject
    {
        Q_OBJECT

    public:
        explicit IProcessComunicator(QObject *parent = 0);
        virtual void CreateProcess() = 0;
        virtual void ConnectToProcess(const QString& key_in, const QString& key_out) = 0;
        virtual void Send(const QString& value) = 0;
        virtual void Abort() = 0;
        virtual void AbortByUser() = 0;
        virtual bool IsError() = 0;
        virtual QString ErrorString() = 0;

    signals:
        void Received(const QString& value);
        void ProcessStarted();
        void ProcessFinished();
        void Error();
        void OnSuspend();
    public slots:
        virtual void Suspend() = 0;
    };
}

#endif // IPROCESSCOMUNICATOR_H
