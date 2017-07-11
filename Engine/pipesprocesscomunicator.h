#ifndef PIPESPROCESSCOMUNICATOR_H
#define PIPESPROCESSCOMUNICATOR_H
#include "engine_global.h"
#include "iprocesscomunicator.h"
#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include <QProcess>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT PipesProcessComunicator : public IProcessComunicator
    {
        Q_OBJECT
        QString key;
        QString Location;
        QProcess *Process;
        bool isError;
        QString errorString;
        QStringList Params;
        QStringList Arguments;

    public:
        explicit PipesProcessComunicator(QObject *parent = 0);
        virtual void SetLocation(const QString& Location);
        void SetCommandLineParams(const QStringList& Params);

        virtual void CreateProcess(const QStringList& arguments);
        virtual void ConnectToProcess(const QString& key_in, const QString& key_out);
        virtual void Send(const QString& value);
        virtual void Abort();
        virtual void AbortByUser();
        virtual bool IsError();
        virtual QString ErrorString();
        virtual bool HasProcess();



    public slots:
        virtual void Suspend();
        void ReceivedAll(const QString& key, const QString& data);
        void ProcessStartedAll(const QString& key);
        void ProcessStoppedAll(const QString& key);
    signals:
        void SendSignal(const QString& key, const QString& data);
    private slots:
        void UnexpectedFinished();

    };
}

#endif // PIPESPROCESSCOMUNICATOR_H
