#ifndef SHAREDMEMORYPROCESSCOMUNICATOR_H
#define SHAREDMEMORYPROCESSCOMUNICATOR_H
#include "engine_global.h"

#include "iprocesscomunicator.h"
#include <QProcess>
#include <QSharedMemory>
#include <QTimer>
#include <QLocalServer>
#include <QLocalSocket>

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT SharedMemoryProcessComunicator : public IProcessComunicator
    {
        Q_OBJECT
        QProcess *Process;
        QSharedMemory *MemoryIn;
        QSharedMemory *MemoryOut;
        QLocalServer *Server;
        QLocalSocket *Client;
        QStringList SendArray;
        bool isError;
        QString errorString;
        QString Location;
        bool Ending;
    public:
        explicit SharedMemoryProcessComunicator(QObject *parent = 0);
        ~SharedMemoryProcessComunicator();
        virtual void SetLocation(const QString& Location);
        virtual void CreateProcess(const QStringList& arguments);
        virtual void ConnectToProcess(const QString& key_in, const QString& key_out);

        virtual void Send(const QString& value);
        virtual void Abort();
        virtual bool IsError();
        virtual QString ErrorString();


    public slots:
        virtual void Suspend();
    signals:

    private slots:
        void InThread();
        void OutThread();
        void UnexpectedFinished();

        void newConnection();
        void Connected();
        void SignalDataExist();
        void Income();
    };

}
#endif // SHAREDMEMORYPROCESSCOMUNICATOR_H

